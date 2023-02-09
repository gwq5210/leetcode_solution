/*
 * @lc app=leetcode.cn id=1115 lang=cpp
 *
 * [1115] 交替打印 FooBar
 *
 * https://leetcode.cn/problems/print-foobar-alternately/description/
 *
 * concurrency
 * Medium (56.78%)
 * Likes:    176
 * Dislikes: 0
 * Total Accepted:    60.4K
 * Total Submissions: 106.3K
 * Testcase Example:  '1'
 *
 * 给你一个类：
 *
 *
 * class FooBar {
 * ⁠ public void foo() {
 * for (int i = 0; i < n; i++) {
 * print("foo");
 * }
 * ⁠ }
 *
 * ⁠ public void bar() {
 * for (int i = 0; i < n; i++) {
 * print("bar");
 * }
 * ⁠ }
 * }
 *
 *
 * 两个不同的线程将会共用一个 FooBar 实例：
 *
 *
 * 线程 A 将会调用 foo() 方法，而
 * 线程 B 将会调用 bar() 方法
 *
 *
 * 请设计修改程序，以确保 "foobar" 被输出 n 次。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 1
 * 输出："foobar"
 * 解释：这里有两个线程被异步启动。其中一个调用 foo() 方法, 另一个调用 bar() 方法，"foobar" 将被输出一次。
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 2
 * 输出："foobarfoobar"
 * 解释："foobar" 将被输出两次。
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

static void Print(const std::string& msg, std::string& result) {
  result += msg;
  printf("%s\n", msg.c_str());
}

class ConditionVariablePrintFooBar {
 public:
  ConditionVariablePrintFooBar(int count) : count_(count) {}

  void foo(std::function<void()> print_foo) {
    for (int i = 0; i < count_; i++) {
      std::unique_lock<std::mutex> ul(lock_);
      cv_.wait(ul, [this]() { return flag_ == 0; });
      // print_foo() outputs "foo". Do not change or remove this line.
      print_foo();
      flag_ = 1;
      cv_.notify_one();
    }
  }

  void bar(std::function<void()> print_bar) {
    for (int i = 0; i < count_; i++) {
      std::unique_lock<std::mutex> ul(lock_);
      cv_.wait(ul, [this]() { return flag_ == 1; });
      // print_bar() outputs "bar". Do not change or remove this line.
      print_bar();
      flag_ = 0;
      cv_.notify_one();
    }
  }

 private:
  int count_ = 0;
  int flag_ = 0;
  std::mutex lock_;
  std::condition_variable cv_;
};

class SemapharePrintFooBar {
 public:
  SemapharePrintFooBar(int count) : count_(count) {}

  void foo(std::function<void()> print_foo) {
    for (int i = 0; i < count_; i++) {
      // print_foo() outputs "foo". Do not change or remove this line.
      foo_sem_.acquire();
      print_foo();
      bar_sem_.release();
    }
  }

  void bar(std::function<void()> print_bar) {
    for (int i = 0; i < count_; i++) {
      // print_bar() outputs "bar". Do not change or remove this line.
      bar_sem_.acquire();
      print_bar();
      foo_sem_.release();
    }
  }

 private:
  int count_ = 0;
  std::binary_semaphore bar_sem_{0};
  std::binary_semaphore foo_sem_{1};
};

template <typename T>
void PrintTest() {
  int count = 3;
  T print(count);
  std::string expect_result("foobarfoobarfoobar");

  {
    std::string result;
    std::thread foo([&result, &print]() { print.foo([&result]() { Print("foo", result); }); });
    std::thread bar([&result, &print]() { print.bar([&result]() { Print("bar", result); }); });

    foo.join();
    bar.join();
    EXPECT_EQ(result, expect_result);
  }

  {
    using namespace std::chrono_literals;
    std::string result;
    std::thread foo([&result, &print]() {
      std::this_thread::sleep_for(200ms);
      print.foo([&result]() { Print("foo", result); });
    });
    std::thread bar([&result, &print]() { print.bar([&result]() { Print("bar", result); }); });

    foo.join();
    bar.join();
    EXPECT_EQ(result, expect_result);
  }
}

TEST(PrintFooBarTest, PrintFooBarTest) {
  PrintTest<SemapharePrintFooBar>();
  PrintTest<ConditionVariablePrintFooBar>();
}
