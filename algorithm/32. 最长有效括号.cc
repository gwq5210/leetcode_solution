/*
 * @lc app=leetcode.cn id=32 lang=cpp
 *
 * [32] 最长有效括号
 *
 * https://leetcode-cn.com/problems/longest-valid-parentheses/description/
 *
 * algorithms
 * Hard (35.68%)
 * Likes:    2163
 * Dislikes: 0
 * Total Accepted:    348.7K
 * Total Submissions: 939.7K
 * Testcase Example:  '"(()"'
 *
 * 给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。
 *
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "(()"
 * 输出：2
 * 解释：最长有效括号子串是 "()"
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = ")()())"
 * 输出：4
 * 解释：最长有效括号子串是 "()()"
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = ""
 * 输出：0
 *
 *
 *
 *
 * 提示：
 *
 *
 * 0 <= s.length <= 3 * 104
 * s[i] 为 '(' 或 ')'
 *
 *
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

class Solution {
 public:
  int longestValidParentheses(std::string s) {
    // dp[i] 表示以 s[i] 结尾的最长有效括号的长度
    // 若 s[i] == '(' 显然 dp[i] == 0
    // 若 s[i] == ')'，则字符串有如下形式
    // xxx 表示之前的有效括号
    // 这两种形式其实处理方式相同
    // 形式一: .....()
    // 形式二: .....))
    // 需要注意处理如下情况
    // ()(()())
    std::vector<int> dp(s.size());
    int res = 0;
    for (int i = 1; i < s.size(); ++i) {
      // s[i] 的右括号可以和 i - 1 - dp[i - 1] 位置的左括号组成更长的有效括号
      if (s[i] == ')' && i - 1 - dp[i - 1] >= 0 && s[i - 1 - dp[i - 1]] == '(') {
        dp[i] = dp[i - 1] + 2;
      }
      // i - dp[i] 位置还有有效的括号，则可以直接拼接起来组成更长的有效括号
      if (i - dp[i] >= 0) {
        dp[i] += dp[i - dp[i]];
      }
      res = std::max(res, dp[i]);
    }
    return res;
  }
};