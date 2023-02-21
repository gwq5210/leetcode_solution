/*
 * @lc app=leetcode.cn id=295 lang=cpp
 *
 * [295] 数据流的中位数
 *
 * https://leetcode-cn.com/problems/find-median-from-data-stream/description/
 *
 * algorithms
 * Hard (51.78%)
 * Likes:    403
 * Dislikes: 0
 * Total Accepted:    35.5K
 * Total Submissions: 68.5K
 * Testcase Example:  '["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]\n' +
  '[[],[1],[2],[],[3],[]]'
 *
 * 中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。
 *
 * 例如，
 *
 * [2,3,4] 的中位数是 3
 *
 * [2,3] 的中位数是 (2 + 3) / 2 = 2.5
 *
 * 设计一个支持以下两种操作的数据结构：
 *
 *
 * void addNum(int num) - 从数据流中添加一个整数到数据结构中。
 * double findMedian() - 返回目前所有元素的中位数。
 *
 *
 * 示例：
 *
 * addNum(1)
 * addNum(2)
 * findMedian() -> 1.5
 * addNum(3)
 * findMedian() -> 2
 *
 * 进阶:
 *
 *
 * 如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
 * 如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？
 *
 *
 */
#include <deque>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class MedianFinder {
 public:
  /** initialize your data structure here. */
  MedianFinder() {}

  void addNum1(int num) {
    if (left_nums_.empty() || num <= *std::prev(left_nums_.end())) {
      left_nums_.emplace(num);
      if (right_nums_.size() + 1 < left_nums_.size()) {
        right_nums_.emplace(*std::prev(left_nums_.end()));
        left_nums_.erase(std::prev(left_nums_.end()));
      }
    } else {
      right_nums_.emplace(num);
      if (right_nums_.size() > left_nums_.size()) {
        left_nums_.emplace(*right_nums_.begin());
        right_nums_.erase(right_nums_.begin());
      }
    }
    ++count_;
  }

  double findMedian1() {
    double res = *std::prev(left_nums_.end());
    if (count_ % 2 == 0) {
      res = (res + *right_nums_.begin()) / 2.0;
    }
    return res;
  }

  void addNum2(int num) {
    if (left_pq_.empty() || num <= left_pq_.top()) {
      left_pq_.push(num);
      if (left_pq_.size() > right_pq_.size() + 1) {
        right_pq_.push(left_pq_.top());
        left_pq_.pop();
      }
    } else {
      right_pq_.push(num);
      if (right_pq_.size() > left_pq_.size()) {
        left_pq_.push(right_pq_.top());
        right_pq_.pop();
      }
    }
    ++count_;
  }

  double findMedian2() {
    double res = left_pq_.top();
    if (count_ % 2 == 0) {
      res = (res + right_pq_.top()) / 2.0;
    }
    return res;
  }

  void addNum(int num) {
    nums_.emplace(num);
    ++count_;
    if (count_ == 1) {
      left_ = nums_.begin();
      right_ = nums_.begin();
    } else {
      if (count_ % 2 == 0) {  // 当前数量是偶数
        if (num < *left_) {
          // 2 -> 1,2
          --left_;
        } else {  // num >= *right_
          // 2 -> 2,3
          // 2 -> 2,2
          ++right_;
        }
      } else {  // 当前数量是奇数
        if (num < *left_) {
          // 2,3 -> 1,2,3
          --right_;
        } else if (num >= *right_) {
          // 2,3 -> 2,3,4
          // 2,3 -> 2,3,3
          ++left_;
        } else {  // num == *left_
                  // 2,3 -> 2,2,3
          ++left_;
          --right_;
        }
      }
    }
  }

  double findMedian() {
    double res = *left_;
    if (count_ % 2 == 0) {
      res = (res + *right_) / 2.0;
    }
    return res;
  }

 private:
  int count_ = 0;
  // 两个有序集合，将所有的数字分成两部分，这和使用两个优先队列的情况类似
  // left_nums_ 中的数字都小于或等于 right_nums_ 中的数字
  // 当 count_ 为偶数时，left_nums_.size == right_nums_.size()
  // 当 count_ 为奇数时，left_nums_.size == right_nums_.size() + 1
  std::multiset<int> left_nums_;
  std::multiset<int> right_nums_;
  std::priority_queue<int> left_pq_;
  std::priority_queue<int, std::vector<int>, std::greater<int>> right_pq_;
  // 一个有序集合存储所有的元素
  // 双指针指向中位数
  // 当 count_ 为偶数时，left_ 和 right_ 分别指向构成中位数的两个数
  // 当 count_ 为奇数时，left_ 和 right_ 指向同一个元素
  // multiset 插入相等元素时，插入范围的上界
  std::multiset<int>::iterator left_;
  std::multiset<int>::iterator right_;
  std::multiset<int> nums_;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */