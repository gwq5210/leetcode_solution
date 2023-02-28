/*
 * @lc app=leetcode.cn id=224 lang=cpp
 *
 * [224] 基本计算器
 *
 * https://leetcode.cn/problems/basic-calculator/description/
 *
 * algorithms
 * Hard (42.40%)
 * Likes:    871
 * Dislikes: 0
 * Total Accepted:    111.9K
 * Total Submissions: 263.8K
 * Testcase Example:  '"1 + 1"'
 *
 * 给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
 *
 * 注意:不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "1 + 1"
 * 输出：2
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = " 2-1 + 2 "
 * 输出：3
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = "(1+(4+5+2)-3)+(6+8)"
 * 输出：23
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 3 * 10^5
 * s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
 * s 表示一个有效的表达式
 * '+' 不能用作一元运算(例如， "+1" 和 "+(2 + 3)" 无效)
 * '-' 可以用作一元运算(即 "-1" 和 "-(2 + 3)" 是有效的)
 * 输入中不存在两个连续的操作符
 * 每个数字和运行的计算将适合于一个有符号的 32位 整数
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
  int OpCmp(char lop, char rop) {
    static std::unordered_map<char, int> ops{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}};
    return ops[lop] - ops[rop];
  }
  bool IsOp(char op) { return op == '+' || op == '-' || op == '*' || op == '/'; }
  int Calc(int x, char op, int y) {
    switch (op) {
      case '+':
        return x + y;
      case '-':
        return x - y;
      case '*':
        return x * y;
      case '/':
        return x / y;
      case '%':
        return x % y;
      default:
        return 0;
    }
    return 0;
  }
  void CalcTop(std::stack<char>& op, std::stack<long long>& nums) {
    int y = nums.top();
    nums.pop();
    int x = 0;
    if (!nums.empty()) {
      x = nums.top();
      nums.pop();
    }
    int v = Calc(x, op.top(), y);
    op.pop();
    nums.push(v);
  }
  void PreProcess(std::string& s) {
    int count = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (!std::isspace(s[i])) {
        s[count++] = s[i];
      }
    }
    s.resize(count);
  }
  int calculate(std::string s) {
    PreProcess(s);

    std::stack<char> op;
    std::stack<long long> nums;
    nums.push(0);

    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '(') {
        op.push(s[i]);
        if (s[i + 1] == '+' || s[i + 1] == '-') {
          nums.push(0);
        }
      } else if (s[i] == ')') {
        while (op.top() != '(') {
          CalcTop(op, nums);
        }
        op.pop();
      } else if (IsOp(s[i])) {
        while (!op.empty() && OpCmp(op.top(), s[i]) >= 0) {
          CalcTop(op, nums);
        }
        op.push(s[i]);
      } else if (std::isdigit(s[i])) {
        long long v = 0;
        while (i < s.size() && std::isdigit(s[i])) {
          v = v * 10 + s[i] - '0';
          ++i;
        }
        nums.push(v);
        --i;
      }
    }
    while (!op.empty()) {
      CalcTop(op, nums);
    }
    return nums.top();
  }
};