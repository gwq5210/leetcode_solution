/*
 * @lc app=leetcode.cn id=1653 lang=cpp
 *
 * [1653] 使字符串平衡的最少删除次数
 *
 * https://leetcode.cn/problems/minimum-deletions-to-make-string-balanced/description/
 *
 * algorithms
 * Medium (54.88%)
 * Likes:    47
 * Dislikes: 0
 * Total Accepted:    7.2K
 * Total Submissions: 12.8K
 * Testcase Example:  '"aababbab"'
 *
 * 给你一个字符串 s ，它仅包含字符 'a' 和 'b'​​​​ 。
 *
 * 你可以删除 s 中任意数目的字符，使得 s 平衡 。当不存在下标对 (i,j) 满足 i < j ，且 s[i] = 'b' 的同时 s[j]= 'a'
 * ，此时认为 s 是 平衡 的。
 *
 * 请你返回使 s 平衡 的 最少 删除次数。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "aababbab"
 * 输出：2
 * 解释：你可以选择以下任意一种方案：
 * 下标从 0 开始，删除第 2 和第 6 个字符（"aababbab" -> "aaabbb"），
 * 下标从 0 开始，删除第 3 和第 6 个字符（"aababbab" -> "aabbbb"）。
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "bbaaaaabb"
 * 输出：2
 * 解释：唯一的最优解是删除最前面两个字符。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 10^5
 * s[i] 要么是 'a' 要么是 'b'​ 。​
 *
 *
 */

#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  // 三种可能，字符串全部为a，字符串全部为b
  // 前半部分为a，后半部分为b
  // 遍历字符串，统计[0,i],(i, s.size())的 b 和 a 的数量
  // 求出最小值即可
  int minimumDeletions1(std::string s) {
    int right_a = 0;
    int left_b = 0;
    for (char c : s) {
      if (c == 'a') {
        ++right_a;
      }
    }
    // 将所有的字符串都变成 a
    int res = right_a;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == 'a') {
        --right_a;
      } else {
        ++left_b;
      }
      res = std::min(res, right_a + left_b);
    }
    return res;
  }
  int minimumDeletions2(std::string s) {
    // 分别表示以 a，b结尾的删除之后，可以组成的字符串的最大长度
    int tail_a = 0;
    int tail_b = 0;
    for (char c : s) {
      if (c == 'a') {
        ++tail_a;
      } else {
        tail_b = std::max(tail_b, tail_a) + 1;
      }
    }
    return s.size() - std::max(tail_a, tail_b);
  }
  // 1.状态定义:
  //     dp[i]: 0~i的需要的最少删除次数
  // 2.状态转移:
  //     2.1. cs[i] == 'b'时, 不需要动
  //         dp[i] = dp[i-1]
  //     2.2. cs[i] == 'a'时, 选择i之前的所有的b删除，或者把i删除
  //         dp[i] = min(sumb, dp[i-1] + 1);
  int minimumDeletions(std::string s) {
    int res = s.size();
    int left_b = 0;
    for (char c : s) {
      if (c == 'a') {
        res = std::min(res + 1, left_b);
      } else {
        ++left_b;
      }
    }
    return res;
  }
};