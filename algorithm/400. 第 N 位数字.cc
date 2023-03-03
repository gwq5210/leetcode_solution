/*
 * @lc app=leetcode.cn id=400 lang=cpp
 *
 * [400] 第 N 位数字
 *
 * https://leetcode.cn/problems/nth-digit/description/
 *
 * algorithms
 * Medium (45.69%)
 * Likes:    363
 * Dislikes: 0
 * Total Accepted:    56K
 * Total Submissions: 122.6K
 * Testcase Example:  '3'
 *
 * 给你一个整数 n ，请你在无限的整数序列 [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...] 中找出并返回第 n
 * 位上的数字。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 3
 * 输出：3
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 11
 * 输出：0
 * 解释：第 11 位数字在序列 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... 里是 0 ，它是 10 的一部分。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 2^31 - 1
 *
 *
 */

#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  // 直接进行构造
  int findNthDigit(int n) {
    // 1 位数个数 (10 - 1) * 1，不包含 0
    // 2 位数个数 (100 - 10) * 2
    // 3 位数个数 (1000 - 100) * 3
    long long m = 1;  // 表示结果是 m 位数
    long long x = 1;
    long long count = 0;
    while (count <= n) {
      int m_count = (10 * x - x) * m;
      if (count + m_count >= n) {
        break;
      }
      count += m_count;
      x *= 10;
      ++m;
    }
    // count 表示小于 m 位数的数字总数
    // x 是 m 位数的第一个元素，即 x = 10^(m-1)
    // y 表示从 x 开始还需要数多少位
    int y = n - count;
    // num 是第一个大于或等于 n 的数的个数的数字
    int num = x + (y - 1) / m;
    // num 对应的数的个数
    long long target = count + (num - x + 1) * m;
    // printf("y = %d, num = %d, target = %d\n", y, num, target);
    int res = num % 10;
    while (target > n) {
      --target;
      num /= 10;
      res = num % 10;
    }
    return res;
  }
};