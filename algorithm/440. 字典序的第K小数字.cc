/*
 * @lc app=leetcode.cn id=440 lang=cpp
 *
 * [440] 字典序的第K小数字
 *
 * https://leetcode.cn/problems/k-th-smallest-in-lexicographical-order/description/
 *
 * algorithms
 * Hard (42.65%)
 * Likes:    554
 * Dislikes: 0
 * Total Accepted:    47.2K
 * Total Submissions: 110.9K
 * Testcase Example:  '13\n2'
 *
 * 给定整数 n 和 k，返回  [1, n] 中字典序第 k 小的数字。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: n = 13, k = 2
 * 输出: 10
 * 解释: 字典序的排列是 [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9]，所以第二小的数字是 10。
 *
 *
 * 示例 2:
 *
 *
 * 输入: n = 1, k = 1
 * 输出: 1
 *
 *
 *
 *
 * 提示:
 *
 *
 * 1 <= k <= n <= 10^9
 *
 *
 */

#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  // 计算当前节点下有多少个元素，按照分层遍历的思想
  int Count(int node, long long n) {
    int count = 0;
    long long first = node;
    long long last = node;
    while (first <= n) {
      count += std::min(last, n) - first + 1;
      first *= 10;
      last = last * 10 + 9;
    }
    return count;
  }
  int findKthNumber(int n, int k) {
    // 使用字典树的思想
    int cnt = k - 1;
    int node = 1;
    while (cnt > 0) {
      int x = Count(node, n);
      if (x <= cnt) {
        cnt -= x;
        ++node;
      } else {
        node *= 10;
        --cnt;
      }
    }
    return node;
  }
};