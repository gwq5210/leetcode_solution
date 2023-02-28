/*
 * @lc app=leetcode.cn id=227 lang=cpp
 *
 * [227] 基本计算器 II
 *
 * https://leetcode-cn.com/problems/basic-calculator-ii/description/
 *
 * algorithms
 * Medium (43.77%)
 * Likes:    664
 * Dislikes: 0
 * Total Accepted:    142.2K
 * Total Submissions: 319.8K
 * Testcase Example:  '"3+2*2"'
 *
 * 给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
 *
 * 整数除法仅保留整数部分。
 *
 * 你可以假设给定的表达式总是有效的。所有中间结果将在 [-2^31, 2^31 - 1] 的范围内。
 *
 * 注意：不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "3+2*2"
 * 输出：7
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = " 3/2 "
 * 输出：1
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = " 3+5 / 2 "
 * 输出：5
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 3 * 10^5
 * s 由整数和算符 ('+', '-', '*', '/') 组成，中间由一些空格隔开
 * s 表示一个 有效表达式
 * 表达式中的所有整数都是非负整数，且在范围 [0, 2^31 - 1] 内
 * 题目数据保证答案是一个 32-bit 整数
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