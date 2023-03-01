/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 *
 * https://leetcode.cn/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (37.39%)
 * Likes:    6194
 * Dislikes: 0
 * Total Accepted:    1.3M
 * Total Submissions: 3.6M
 * Testcase Example:  '"babad"'
 *
 * 给你一个字符串 s，找到 s 中最长的回文子串。
 *
 * 如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "babad"
 * 输出："bab"
 * 解释："aba" 同样是符合题意的答案。
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "cbbd"
 * 输出："bb"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 1000
 * s 仅由数字和英文字母组成
 *
 *
 */

#include <deque>
#include <map>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  std::string longestPalindrome(std::string s) {
    // dp[i][j] 表示区间 [i,j] 是否是回文串
    std::vector<std::vector<int>> dp(s.size(), std::vector<int>(s.size()));
    int idx = 0;
    int len = 1;
    for (int i = 0; i < s.size(); ++i) {
      dp[i][i] = true;
      if (i + 1 < s.size() && s[i] == s[i + 1]) {
        dp[i][i + 1] = true;
        if (len < 2) {
          len = 2;
          idx = i;
        }
      }
    }
    for (int i = 2; i < s.size(); ++i) {
      for (int j = 0; j + i < s.size(); ++j) {
        if (s[j] == s[j + i]) {
          dp[j][j + i] = dp[j + 1][j + i - 1];
        }
        if (dp[j][j + i]) {
          if (len < i + 1) {
            len = i + 1;
            idx = j;
          }
        }
      }
    }
    return s.substr(idx, len);
  }
  int Check(const std::string& s, int l, int r) {
    while (l >= 0 && r < s.size() && s[l] == s[r]) {
      --l;
      ++r;
    }
    return r - l - 1;
  }
  std::string longestPalindrome1(std::string s) {
    int res = 0;
    int idx = 0;
    // 通过中心扩展的方法寻找
    for (int i = 0; i < s.size(); ++i) {
      int len1 = Check(s, i, i);
      if (len1 > res) {
        res = len1;
        idx = i - len1 / 2;
      }
      int len2 = Check(s, i, i + 1);
      if (len2 > res) {
        res = len2;
        idx = i - len2 / 2 + 1;
      }
    }
    return s.substr(idx, res);
  }
};