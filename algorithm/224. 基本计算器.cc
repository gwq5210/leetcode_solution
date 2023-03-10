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
    static std::unordered_map<char, int> ops{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}, {'^', 3}};
    return ops[lop] - ops[rop];
  }
  bool IsOp(char op) { return op == '+' || op == '-' || op == '*' || op == '/' || op == '^'; }
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
      case '^':
        return x ^ y;
      default:
        return 0;
    }
    return 0;
  }
  void CalcTop(std::stack<char>& ops, std::stack<long long>& nums) {
    int y = nums.top();
    nums.pop();
    int x = nums.top();
    nums.pop();
    int v = Calc(x, ops.top(), y);
    ops.pop();
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

  // 我们可以使用两个栈 nums 和 ops 。
  // nums ： 存放所有的数字
  // ops ：存放所有的数字以外的操作，+/- 也看做是一种操作
  // 然后从前往后做，对遍历到的字符做分情况讨论：
  // 空格 : 跳过
  // ( : 直接加入 ops 中，等待与之匹配的 )
  // ) : 使用现有的 nums 和 ops 进行计算，直到遇到左边最近的一个左括号为止，计算结果放到 nums
  // 数字 : 从当前位置开始继续往后取，将整一个连续数字整体取出，加入 nums
  // +,-,*,/,%,^ : 需要将操作放入 ops 中。在放入之前先把栈内可以算(栈内优先级相等或高)的都算掉
  // 使用现有的 nums 和 ops 进行计算，直到没有操作或者遇到左括号，计算结果放到 nums 一些细节：
  // 由于第一个数可能是负数，为了减少边界判断。一个小技巧是先往 nums 添加一个 0
  // 为防止 () 内出现的首个字符为运算符，将所有的空格去掉，并将 (- 替换为 (0-，(+ 替换为
  // (0+（当然也可以不进行这样的预处理，将这个处理逻辑放到循环里去做）
  int calculate(std::string s) {
    // 预处理去掉空格
    PreProcess(s);

    std::stack<char> ops;
    std::stack<long long> nums;
    nums.push(0);

    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '(') {
        ops.push(s[i]);
        if (s[i + 1] == '+' || s[i + 1] == '-') {
          nums.push(0);
        }
      } else if (s[i] == ')') {
        while (ops.top() != '(') {
          CalcTop(ops, nums);
        }
        ops.pop();
      } else if (IsOp(s[i])) {
        while (!ops.empty() && OpCmp(ops.top(), s[i]) >= 0) {
          CalcTop(ops, nums);
        }
        ops.push(s[i]);
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
    while (!ops.empty()) {
      CalcTop(ops, nums);
    }
    return nums.top();
  }
};