/*
 * @lc app=leetcode.cn id=1114 lang=cpp
 *
 * [1114] 按序打印
 *
 * https://leetcode.cn/problems/print-in-order/description/
 *
 * concurrency
 * Easy (65.15%)
 * Likes:    454
 * Dislikes: 0
 * Total Accepted:    104.7K
 * Total Submissions: 160.7K
 * Testcase Example:  '[1,2,3]'
 *
 * 给你一个类：
 *
 *
 * public class Foo {
 * public void first() { print("first"); }
 * public void second() { print("second"); }
 * public void third() { print("third"); }
 * }
 *
 * 三个不同的线程 A、B、C 将会共用一个 Foo 实例。
 *
 *
 * 线程 A 将会调用 first() 方法
 * 线程 B 将会调用 second() 方法
 * 线程 C 将会调用 third() 方法
 *
 *
 * 请设计修改程序，以确保 second() 方法在 first() 方法之后被执行，third() 方法在
 * second() 方法之后被执行。
 *
 * 提示：
 *
 *
 * 尽管输入中的数字似乎暗示了顺序，但是我们并不保证线程在操作系统中的调度顺序。
 * 你看到的输入格式主要是为了确保测试的全面性。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [1,2,3]
 * 输出："firstsecondthird"
 * 解释：
 * 有三个线程会被异步启动。输入 [1,2,3] 表示线程 A 将会调用 first() 方法，线程 B
 * 将会调用 second() 方法，线程 C 将会调用 third() 方法。正确的输出是
 * "firstsecondthird"。
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [1,3,2]
 * 输出："firstsecondthird"
 * 解释：
 * 输入 [1,3,2] 表示线程 A 将会调用 first() 方法，线程 B 将会调用 third()
 * 方法，线程 C 将会调用 second() 方法。正确的输出是 "firstsecondthird"。
 *
 *
 *
 *
 *
 * 提示：
 *
 *
 * nums 是 [1, 2, 3] 的一组排列
 *
 *
 */

#include <chrono>
#include <cstdio>
#include <functional>
#include <latch>
#include <mutex>
#include <semaphore>
#include <thread>

#include <gtest/gtest.h>

static void Print(const std::string& msg, std::string& result) {
  result += msg;
  printf("%s\n", msg.c_str());
}

class ConditionVariablePrint {
 public:
  ConditionVariablePrint() {}

  void first(std::function<void()> print_first) {
    // print_first() outputs "first". Do not change or remove this line.
    print_first();
    {
      std::unique_lock<std::mutex> ul(lock_);
      flag_ = 1;
    }
    cv_.notify_all();
  }

  void second(std::function<void()> print_second) {
    std::unique_lock<std::mutex> ul(lock_);
    cv_.wait(ul, [this]() { return flag_ == 1; });
    // print_second() outputs "second". Do not change or remove this line.
    print_second();
    flag_ = 2;
    cv_.notify_all();
  }

  void third(std::function<void()> print_third) {
    std::unique_lock<std::mutex> ul(lock_);
    cv_.wait(ul, [this]() { return flag_ == 2; });
    // print_third() outputs "third". Do not change or remove this line.
    print_third();
    flag_ = 0;
  }

 private:
  int flag_ = 0;
  std::mutex lock_;
  std::condition_variable cv_;
};

class SemaphorePrint {
 public:
  SemaphorePrint() {}

  void first(std::function<void()> print_first) {
    // print_first() outputs "first". Do not change or remove this line.
    print_first();
    first_sem_.release();
  }

  void second(std::function<void()> print_second) {
    first_sem_.acquire();
    // print_second() outputs "second". Do not change or remove this line.
    print_second();
    second_sem_.release();
  }

  void third(std::function<void()> print_third) {
    second_sem_.acquire();
    // print_third() outputs "third". Do not change or remove this line.
    print_third();
  }

 private:
  std::binary_semaphore first_sem_{0};
  std::binary_semaphore second_sem_{0};
};

class BarrierPrint {
 public:
  BarrierPrint() {}

  void first(std::function<void()> print_first) {
    // print_first() outputs "first". Do not change or remove this line.
    print_first();
    first_sync_point_.count_down();
  }

  void second(std::function<void()> print_second) {
    first_sync_point_.wait();
    // print_second() outputs "second". Do not change or remove this line.
    print_second();
    second_sync_point_.count_down();
  }

  void third(std::function<void()> print_third) {
    second_sync_point_.wait();
    // print_third() outputs "third". Do not change or remove this line.
    print_third();
  }

 private:
  std::latch first_sync_point_{1};
  std::latch second_sync_point_{1};
};

// using Foo = ConditionVariablePrint;

template <typename T>
void PrintTest() {
  std::string expect_result("firstsecondthird");

  {
    T print;
    std::string result;
    std::thread first([&result, &print]() { print.first([&result]() { Print("first", result); }); });
    std::thread second([&result, &print]() { print.second([&result]() { Print("second", result); }); });
    std::thread third([&result, &print]() { print.third([&result]() { Print("third", result); }); });

    first.join();
    second.join();
    third.join();
    EXPECT_EQ(result, expect_result);
  }

  {
    T print;
    using namespace std::chrono_literals;
    std::string result;
    std::thread first([&result, &print]() {
      std::this_thread::sleep_for(500ms);
      print.first([&result]() { Print("first", result); });
    });
    std::thread second([&result, &print]() {
      std::this_thread::sleep_for(200ms);
      print.second([&result]() { Print("second", result); });
    });
    std::thread third([&result, &print]() { print.third([&result]() { Print("third", result); }); });

    first.join();
    second.join();
    third.join();
    EXPECT_EQ(result, expect_result);
  }
}

TEST(PrintTest, PrintTest) {
  PrintTest<ConditionVariablePrint>();
  PrintTest<SemaphorePrint>();
  PrintTest<BarrierPrint>();
}