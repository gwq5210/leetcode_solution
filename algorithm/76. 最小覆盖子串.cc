/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 *
 * https://leetcode.cn/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (45.11%)
 * Likes:    2343
 * Dislikes: 0
 * Total Accepted:    389.3K
 * Total Submissions: 862.9K
 * Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t
 * 所有字符的子串，则返回空字符串 "" 。
 *
 *
 *
 * 注意：
 *
 *
 * 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
 * 如果 s 中存在这样的子串，我们保证它是唯一的答案。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "ADOBECODEBANC", t = "ABC"
 * 输出："BANC"
 * 解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "a", t = "a"
 * 输出："a"
 * 解释：整个字符串 s 是最小覆盖子串。
 *
 *
 * 示例 3:
 *
 *
 * 输入: s = "a", t = "aa"
 * 输出: ""
 * 解释: t 中两个字符 'a' 均应包含在 s 的子串中，
 * 因此没有符合条件的子字符串，返回空字符串。
 *
 *
 *
 * 提示：
 *
 *
 * ^m == s.length
 * ^n == t.length
 * 1 <= m, n <= 10^5
 * s 和 t 由英文字母组成
 *
 *
 *
 * 进阶：你能设计一个在 o(m+n) 时间内解决此问题的算法吗？
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
  static int CharToIndex(char c) {
    if (c >= 'a' && c <= 'z') {
      return c - 'a';
    }
    return c - 'A' + 26;
  }
  bool Check(const std::vector<int>& target_stats, const std::vector<int>& source_stats) {
    for (int i = 0; i < target_stats.size(); ++i) {
      if (target_stats[i] > source_stats[i]) {
        return false;
      }
    }
    return true;
  }
  std::string minWindow(std::string s, std::string t) {
    std::vector<int> target_stats(52);
    std::vector<int> source_stats(52);
    for (char c : t) {
      ++target_stats[CharToIndex(c)];
    }
    int res_start = 0;
    int res_end = s.size();
    int start = 0;
    int end = 0;
    bool found = false;
    for (int end = 0; end < s.size(); ++end) {
      ++source_stats[CharToIndex(s[end])];
      while (Check(target_stats, source_stats)) {
        if (res_end - res_start > end - start) {
          res_start = start;
          res_end = end;
          found = true;
        }
        --source_stats[CharToIndex(s[start])];
        ++start;
      }
    }
    return found ? s.substr(res_start, res_end - res_start) : "";
  }
};