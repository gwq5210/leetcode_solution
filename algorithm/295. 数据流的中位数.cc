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
#include <set>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class MedianFinder {
 public:
  /** initialize your data structure here. */
  MedianFinder() {}

  void addNum(int num) {
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

  double findMedian() {
    double res = *std::prev(left_nums_.end());
    if (count_ % 2 == 0) {
      res = (res + *right_nums_.begin()) / 2.0;
    }
    return res;
  }

 private:
  int count_ = 0;
  std::multiset<int> left_nums_;
  std::multiset<int> right_nums_;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */