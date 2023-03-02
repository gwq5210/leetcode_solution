/*
 * @lc app=leetcode.cn id= lang=cpp
 *
 * 面试题 05.02. 二进制数转字符串
 *
 * https://leetcode.cn/problems/bianry-number-to-string-lcci/
 * description/
 *
二进制数转字符串。给定一个介于0和1之间的实数（如0.72），类型为double，打印它的二进制表达式。如果该数字无法精确地用32位以内的二进制表示，则打印“ERROR”。

示例1:

 输入：0.625
 输出："0.101"
示例2:

 输入：0.1
 输出："ERROR"
 提示：0.1无法被二进制准确表示


提示：

32位包括输出中的 "0." 这两位。
题目保证输入用例的小数位数最多只有 6 位
 *
 *
 */

#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  // 每次将实数乘以 2，将此时的整数部分添加到二进制表示的末尾，然后将整数部分置为 0，重复上述操作，直到小数部分变成 0
  // 或者小数部分出现循环时结束操作。当小数部分变成 0 时，得到二进制表示下的有限小数；
  // 当小数部分出现循环时，得到二进制表示下的无限循环小数。
  // 由于这道题要求二进制表示的长度最多为 32 位，否则返回 “ERROR"，因此不需要判断给定实数的二进制表示的结果是有限小数还是无限循环小数
  // 而是在小数部分变成 0 或者二进制表示的长度超过 21 位时结束操作。当操作结束时，如果二进制表示的长度不超过 21 位则返回二进制表示，否则返回 “ERROR"。
  std::string printBin(double num) {
    std::string res = "0.";
    while (res.size() <= 32 && num != 0) {
      num *= 2;
      res += (int)num + '0';
      num -= (int)num;
    }
    return res.size() <= 32 ? res : "ERROR";
  }
};