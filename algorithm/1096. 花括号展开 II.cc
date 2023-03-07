/*
 * @lc app=leetcode.cn id=1096 lang=cpp
 *
 * [1096] 花括号展开 II
 *
 * https://leetcode.cn/problems/brace-expansion-ii/description/
 *
 * algorithms
 * Hard (57.83%)
 * Likes:    164
 * Dislikes: 0
 * Total Accepted:    11.8K
 * Total Submissions: 16K
 * Testcase Example:  '"{a,b}{c,{d,e}}"'
 *
 * 如果你熟悉 Shell 编程，那么一定了解过花括号展开，它可以用来生成任意字符串。
 *
 * 花括号展开的表达式可以看作一个由 花括号、逗号 和 小写英文字母 组成的字符串，定义下面几条语法规则：
 *
 *
 * 如果只给出单一的元素 x，那么表达式表示的字符串就只有 "x"。R(x) = {x}
 *
 *
 * 例如，表达式 "a" 表示字符串 "a"。
 * 而表达式 "w" 就表示字符串 "w"。
 *
 *
 * 当两个或多个表达式并列，以逗号分隔，我们取这些表达式中元素的并集。R({e_1,e_2,...}) = R(e_1) ∪ R(e_2) ∪
 * ...
 *
 * 例如，表达式 "{a,b,c}" 表示字符串 "a","b","c"。
 * 而表达式 "{{a,b},{b,c}}" 也可以表示字符串 "a","b","c"。
 *
 *
 * 要是两个或多个表达式相接，中间没有隔开时，我们从这些表达式中各取一个元素依次连接形成字符串。R(e_1 + e_2) = {a + b for
 * (a, b) in R(e_1) × R(e_2)}
 *
 * 例如，表达式 "{a,b}{c,d}" 表示字符串 "ac","ad","bc","bd"。
 *
 *
 * 表达式之间允许嵌套，单一元素与表达式的连接也是允许的。
 *
 * 例如，表达式 "a{b,c,d}" 表示字符串 "ab","ac","ad"​​​​​​。
 * 例如，表达式 "a{b,c}{d,e}f{g,h}" 可以表示字符串 "abdfg", "abdfh", "abefg", "abefh",
 * "acdfg", "acdfh", "acefg", "acefh"。
 *
 *
 *
 *
 * 给出表示基于给定语法规则的表达式 expression，返回它所表示的所有字符串组成的有序列表。
 *
 * 假如你希望以「集合」的概念了解此题，也可以通过点击 “显示英文描述” 获取详情。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：expression = "{a,b}{c,{d,e}}"
 * 输出：["ac","ad","ae","bc","bd","be"]
 *
 * 示例 2：
 *
 *
 * 输入：expression = "{{a,z},a{b,c},{ab,z}}"
 * 输出：["a","ab","ac","z"]
 * 解释：输出中 不应 出现重复的组合结果。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= expression.length <= 60
 * expression[i] 由 '{'，'}'，',' 或小写英文字母组成
 * 给出的表达式 expression 用以表示一组基于题目描述中语法构造的字符串
 *
 *
 */

#include <deque>
#include <iostream>
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
  int FindOne(std::string_view one, bool append) {
    int r = 0;
    if (one[0] != '{') {
      while (r < one.size() && std::isalpha(one[r])) {
        ++r;
      }
    } else {
      int c = 0;
      while (r < one.size()) {
        if (one[r] == '{') {
          ++c;
        } else if (one[r] == '}') {
          --c;
        }
        ++r;
        if (c == 0) {
          break;
        }
      }
    }

    if (!append) {
      return r;
    }
    if (r == one.size() || one[r] == ',' || one[r] == '}') {
      return r;
    }

    return r + FindOne(one.substr(r), true);
  }
  std::vector<std::string> ParseOne(std::string_view one) {
    std::cout << "parse one begin: " << one << std::endl;
    if (one[0] != '{') {
      return std::vector<std::string>{std::string(one)};
    }
    int l = 0;
    std::vector<std::string> result;
    while (l < one.size() && one[l] != '}') {
      ++l;
      int sub_size = FindOne(one.substr(l), true);
      std::vector<std::string> sub_res = Parse(one.substr(l, sub_size));
      for (auto& s : sub_res) {
        result.emplace_back(std::move(s));
      }
      l += sub_size;
    }
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    std::cout << "parse one end: " << one << std::endl;
    printf("result size %zu\n", result.size());
    return result;
  }
  std::vector<std::string> Parse(std::string_view expression) {
    if (expression.empty()) {
      return {};
    }
    std::cout << "parse begin: " << expression << std::endl;
    int size = FindOne(expression, false);
    std::vector<std::string> one_res = ParseOne(expression.substr(0, size));
    printf("expression size %zu, one size %d, one_res size %zu\n", expression.size(), size, one_res.size());
    if (size == expression.size()) {
      return one_res;
    }
    std::vector<std::string> other_res = Parse(expression.substr(size));
    std::sort(other_res.begin(), other_res.end());
    other_res.erase(std::unique(other_res.begin(), other_res.end()), other_res.end());
    std::vector<std::string> res;
    for (auto& first : one_res) {
      for (auto& second : other_res) {
        res.emplace_back(first + second);
      }
    }
    return res;
  }
  std::vector<std::string> braceExpansionII(std::string expression) { return Parse(expression); }
};
