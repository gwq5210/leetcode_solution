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
    // 维护两个数组，记录已有字符串指定字符的出现次数，和目标字符串指定字符的出现次数
    std::vector<int> target_stats(52);
    std::vector<int> source_stats(52);

    // 将目标字符串指定字符的出现次数记录
    for (char c : t) {
      ++target_stats[CharToIndex(c)];
    }

    // 答案表示的区间为[res_start, res_end]
    int res_start = 0;
    int res_end = s.size();
    // 当前表示的区间为[start, end]
    int start = 0;
    int end = 0;
    // s的子串是否可以涵盖t
    bool found = false;
    // 枚举右边界end
    for (int end = 0; end < s.size(); ++end) {
      // 将当前的字符加入统计
      ++source_stats[CharToIndex(s[end])];

      // 向右移动start，不满足条件时才结束
      while (Check(target_stats, source_stats)) {
        // 当前[start, end]满足要求，则使用[start, end]更新答案，并更新found
        if (res_end - res_start > end - start) {
          res_start = start;
          res_end = end;
          found = true;
        }
        // 向右移动start，同时更新统计
        --source_stats[CharToIndex(s[start])];
        ++start;
      }
    }

    // 如果没找到直接返回空串
    return found ? s.substr(res_start, res_end - res_start + 1) : "";
  }
};