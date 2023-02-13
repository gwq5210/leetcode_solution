/*
 * @lc app=leetcode.cn id=1117 lang=cpp
 *
 * [1117] H2O 生成
 *
 * https://leetcode.cn/problems/building-h2o/description/
 *
 * concurrency
 * Medium (53.59%)
 * Likes:    125
 * Dislikes: 0
 * Total Accepted:    24.7K
 * Total Submissions: 46K
 * Testcase Example:  '"HOH"'
 *
 * 现在有两种线程，氧 oxygen 和氢 hydrogen，你的目标是组织这两种线程来产生水分子。
 *
 * 存在一个屏障（barrier）使得每个线程必须等候直到一个完整水分子能够被产生出来。
 *
 * 氢和氧线程会被分别给予 releaseHydrogen 和 releaseOxygen 方法来允许它们突破屏障。
 *
 * 这些线程应该三三成组突破屏障并能立即组合产生一个水分子。
 *
 * 你必须保证产生一个水分子所需线程的结合必须发生在下一个水分子产生之前。
 *
 * 换句话说:
 *
 *
 * 如果一个氧线程到达屏障时没有氢线程到达，它必须等候直到两个氢线程到达。
 * 如果一个氢线程到达屏障时没有其它线程到达，它必须等候直到一个氧线程和另一个氢线程到达。
 *
 *
 * 书写满足这些限制条件的氢、氧线程同步代码。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: water = "HOH"
 * 输出: "HHO"
 * 解释: "HOH" 和 "OHH" 依然都是有效解。
 *
 *
 * 示例 2:
 *
 *
 * 输入: water = "OOHHHH"
 * 输出: "HHOHHO"
 * 解释: "HOHHHO", "OHHHHO", "HHOHOH", "HOHHOH", "OHHHOH", "HHOOHH", "HOHOHH" 和
 * "OHHOHH" 依然都是有效解。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 3 * n == water.length
 * 1 <= n <= 20
 * water[i] == 'O' or 'H'
 * 输入字符串 water 中的 'H' 总数将会是 2 * n 。
 * 输入字符串 water 中的 'O' 总数将会是 n 。
 *
 *
 */

#include <semaphore.h>

#include <chrono>
#include <cstdio>
#include <functional>
#include <mutex>
#include <semaphore>
#include <thread>

#include <gtest/gtest.h>


// h_count_和o_count_分别记录已经到达的H和O的个数
// H释放的条件是h_count_ < 2，否则需要等待
// O释放的条件是o_count_ == 0，否则需要等待
// 如果释放H或O可以组成一个水分子，则重置h_count_和o_count_
// 唤醒其他所有线程（因为可能不止两个线程）
class CVH2O {
 public:
  CVH2O() {}

  void hydrogen(function<void()> releaseHydrogen) {
    std::unique_lock<std::mutex> ul(lock_);
    cv_.wait(ul, [this]() { return h_count_ < 2; });
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
    ++h_count_;
    if (h_count_ == 2 && o_count_ == 1) {
      h_count_ = 0;
      o_count_ = 0;
      cv_.notify_all();
    }
  }

  void oxygen(function<void()> releaseOxygen) {
    std::unique_lock<std::mutex> ul(lock_);
    cv_.wait(ul, [this]() { return o_count_ == 0; });
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
    o_count_ = 1;
    if (h_count_ == 2 && o_count_ == 1) {
      h_count_ = 0;
      o_count_ = 0;
      cv_.notify_all();
    }
  }

 private:
  int h_count_ = 0;
  int o_count_ = 0;
  std::mutex lock_;
  std::condition_variable cv_;
};

// h_sem_表示可用的h数量，o_sem_表示可用的o数量（一个o对应数量2）
class SemH2O {
 public:
  SemH2O() {}

  void hydrogen(function<void()> releaseHydrogen) {
    h_sem_.acquire(1);  // 遇到h时h_sem_.acquire(1)表示可用h数量减1
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
    o_sem_.release(1);  // o_sem_可用数量加1，遇到两个h才可以释放一个o
  }

  void oxygen(function<void()> releaseOxygen) {
    o_sem_.acquire(2);  // 遇到o时h_sem_.acquire(2)表示可用o数量减2
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
    h_sem_.release(2);  // h_sem_可用数量加2，遇到一个o可以释放2个h
  }

 private:
  std::counting_semaphore h_sem_{2};
  std::counting_semaphore o_sem_{2};
};

class CSemH2O {
 public:
  CSemH2O() {
    sem_init(&h_sem_, 0, 2);
    sem_init(&o_sem_, 0, 2);
  }

  void hydrogen(function<void()> releaseHydrogen) {
    sem_wait(&h_sem_);
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
    sem_post(&o_sem_);
  }

  void oxygen(function<void()> releaseOxygen) {
    sem_wait(&o_sem_);
    sem_wait(&o_sem_);
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
    sem_post(&h_sem_);
    sem_post(&h_sem_);
  }

 private:
  sem_t h_sem_;
  sem_t o_sem_;
};