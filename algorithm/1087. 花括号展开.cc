/*
 * @lc app=leetcode.cn id=1087 lang=cpp
 *
 * [1087] 花括号展开
 *
 * https://leetcode.cn/problems/brace-expansion/
 *
给定一个表示单词列表的字符串 s 。单词中的每个字母都有一个或多个选项。

如果有一个选项，则字母按原样表示。
如果有多个选项，则用大括号分隔选项。例如,  "{a,b,c}"  表示选项  ["a", "b", "c"]  。
例如，如果  s = "a{b,c}"  ，第一个字符总是 'a' ，但第二个字符可以是 'b' 或 'c' 。原来的列表是 ["ab", "ac"] 。

请你 按字典顺序 ，返回所有以这种方式形成的单词。



示例 1：

输入：s = "{a,b}c{d,e}f"
输出：["acdf","acef","bcdf","bcef"]
示例 2：

输入：s = "abcd"
输出：["abcd"]


提示：

1 <= S.length <= 50
s 由括号 '{}' , ',' 和小写英文字母组成。
s 保证是一个有效的输入。
没有嵌套的大括号。
在一对连续的左括号和右括号内的所有字符都是不同的。
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
  std::string ParseOne(std::string_view sv) {
    if (sv[0] != '{') {
      return std::string(sv);
    }
    int i = 1;
    std::string res;
    while (i + 1 < sv.size()) {
      if (std::isalpha(sv[i])) {
        res += sv[i];
      }
      ++i;
    }
    return res;
  }
  std::vector<std::string> Parse(std::string_view sv) {
    if (sv.empty()) {
      return {};
    }
    std::vector<std::string> res;
    int i = 0;
    std::string_view one;
    std::string_view other;
    if (sv[0] != '{') {
      one = sv.substr(0, 1);
      other = sv.substr(1);
    } else {
      int r = 0;
      while (r < sv.size() && sv[r] != '}') {
        ++r;
      }
      one = sv.substr(0, r + 1);
      other = sv.substr(r + 1);
    }
    std::string one_res = ParseOne(one);
    std::sort(one_res.begin(), one_res.end());
    if (other.empty()) {
      for (char c : one_res) {
        res.emplace_back(std::string(1, c));
      }
      return res;
    }
    std::vector<std::string> other_res = Parse(other);
    for (char c : one_res) {
      for (auto& s : other_res) {
        res.emplace_back(c + s);
      }
    }
    return res;
  }
  std::vector<std::string> expand(std::string s) { return Parse(s); }
};
