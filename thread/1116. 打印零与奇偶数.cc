/*
 * @lc app=leetcode.cn id=1116 lang=cpp
 *
 * [1116] 打印零与奇偶数
 *
 * https://leetcode.cn/problems/print-zero-even-odd/description/
 *
 * concurrency
 * Medium (53.92%)
 * Likes:    138
 * Dislikes: 0
 * Total Accepted:    31.7K
 * Total Submissions: 58.7K
 * Testcase Example:  '2'
 *
 * 现有函数 printNumber 可以用一个整数参数调用，并输出该整数到控制台。
 *
 *
 * 例如，调用 printNumber(7) 将会输出 7 到控制台。
 *
 *
 * 给你类 ZeroEvenOdd 的一个实例，该类中有三个函数：zero、even 和 odd 。ZeroEvenOdd
 * 的相同实例将会传递给三个不同线程：
 *
 *
 * 线程 A：调用 zero() ，只输出 0
 * 线程 B：调用 even() ，只输出偶数
 * 线程 C：调用 odd() ，只输出奇数
 *
 *
 * 修改给出的类，以输出序列 "010203040506..." ，其中序列的长度必须为 2n 。
 *
 * 实现 ZeroEvenOdd 类：
 *
 *
 * ZeroEvenOdd(int n) 用数字 n 初始化对象，表示需要输出的数。
 * void zero(printNumber) 调用 printNumber 以输出一个 0 。
 * void even(printNumber) 调用printNumber 以输出偶数。
 * void odd(printNumber) 调用 printNumber 以输出奇数。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 2
 * 输出："0102"
 * 解释：三条线程异步执行，其中一个调用 zero()，另一个线程调用 even()，最后一个线程调用odd()。正确的输出为 "0102"。
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 5
 * 输出："0102030405"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 1000
 *
 *
 */

#include <chrono>
#include <cstdio>
#include <functional>
#include <mutex>
#include <semaphore>
#include <thread>

#include <gtest/gtest.h>

static void PrintInt(int x, std::string& result) {
  result += std::to_string(x);
  printf("%d\n", x);
}

class SemapharePrintZeroEvenOdd {
 public:
  SemapharePrintZeroEvenOdd(int count) : count_(count) {}

  // printNumber(x) outputs "x", where x is an integer.
  void zero(std::function<void(int)> print_number) {
    for (int i = 0; i < count_; ++i) {
      zero_sem_.acquire();
      print_number(0);
      if (i % 2 == 0) {
        odd_sem_.release();
      } else {
        even_sem_.release();
      }
    }
  }

  void odd(std::function<void(int)> print_number) {
    for (int i = 1; i <= count_; i += 2) {
      odd_sem_.acquire();
      print_number(i);
      zero_sem_.release();
    }
  }

  void even(std::function<void(int)> print_number) {
    for (int i = 2; i <= count_; i += 2) {
      even_sem_.acquire();
      print_number(i);
      zero_sem_.release();
    }
  }

 private:
  int count_ = 0;
  std::binary_semaphore zero_sem_{1};
  std::binary_semaphore odd_sem_{0};
  std::binary_semaphore even_sem_{0};
};

class ConditionVariablePrintZeroEvenOdd {
 public:
  ConditionVariablePrintZeroEvenOdd(int count) : count_(count) {}

  // printNumber(x) outputs "x", where x is an integer.
  void zero(std::function<void(int)> print_number) {
    for (int i = 0; i < count_; ++i) {
      std::unique_lock<std::mutex> ul(lock_);
      cv_.wait(ul, [this]() { return flag_ == 0; });
      print_number(0);
      if (i % 2 == 0) {
        flag_ = 1;
      } else {
        flag_ = 2;
      }
      cv_.notify_all();
    }
  }

  void odd(std::function<void(int)> print_number) {
    for (int i = 1; i <= count_; i += 2) {
      std::unique_lock<std::mutex> ul(lock_);
      cv_.wait(ul, [this]() { return flag_ == 1; });
      print_number(i);
      flag_ = 0;
      cv_.notify_all();
    }
  }

  void even(std::function<void(int)> print_number) {
    for (int i = 2; i <= count_; i += 2) {
      std::unique_lock<std::mutex> ul(lock_);
      cv_.wait(ul, [this]() { return flag_ == 2; });
      print_number(i);
      flag_ = 0;
      cv_.notify_all();
    }
  }

 private:
  int count_ = 0;
  int flag_ = 0;
  std::mutex lock_;
  std::condition_variable cv_;
};

template <typename T>
void PrintTest() {
  int count = 3;
  std::string expect_result("010203");

  {
    T print(count);
    std::string result;
    std::thread zero([&result, &print]() { print.zero([&result](int x) { PrintInt(x, result); }); });
    std::thread even([&result, &print]() { print.even([&result](int x) { PrintInt(x, result); }); });
    std::thread odd([&result, &print]() { print.odd([&result](int x) { PrintInt(x, result); }); });

    zero.join();
    even.join();
    odd.join();
    EXPECT_EQ(result, expect_result);
  }
}

TEST(PrintZeroEvenOddTest, PrintZeroEvenOddTest) {
  PrintTest<SemapharePrintZeroEvenOdd>();
  PrintTest<ConditionVariablePrintZeroEvenOdd>();
}