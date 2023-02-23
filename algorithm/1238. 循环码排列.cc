/*
 * @lc app=leetcode.cn id=1238 lang=cpp
 *
 * [1238] 循环码排列
 *
 * https://leetcode.cn/problems/circular-permutation-in-binary-representation/description/
 *
 * algorithms
 * Medium (67.46%)
 * Likes:    98
 * Dislikes: 0
 * Total Accepted:    15.9K
 * Total Submissions: 20.7K
 * Testcase Example:  '2\n3'
 *
 * 给你两个整数 n 和 start。你的任务是返回任意 (0,1,2,,...,2^n-1) 的排列
 * p，并且满足：
 *
 *
 * p[0] = start
 * p[i] 和 p[i+1] 的二进制表示形式只有一位不同
 * p[0] 和 p[2^n -1] 的二进制表示形式也只有一位不同
 *
 *
 *
 *
 * 示例 1：
 *
 * 输入：n = 2, start = 3
 * 输出：[3,2,0,1]
 * 解释：这个排列的二进制表示是 (11,10,00,01)
 * ⁠    所有的相邻元素都有一位是不同的，另一个有效的排列是
 * [3,1,0,2]
 *
 *
 * 示例 2：
 *
 * 输出：n = 3, start = 2
 * 输出：[2,6,7,5,4,0,1,3]
 * 解释：这个排列的二进制表示是 (010,110,111,101,100,000,001,011)
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 16
 * 0 <= start < 2^n
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
  std::vector<int> circularPermutation(int n, int start) {
    std::vector<int> result;
    result.emplace_back(start);
    // 类似格雷码的归纳法，这里初始值为 start，格雷码是 0
    // 格雷码是从 0 开始的
    // 数组中每个数字都和start异或，并不会改变相邻数字只有一位不同这个性质
    // 比如 x y 只有第 i 位不同，那么和 start 做异或运算也就只有第 i 位计算结果不一样
    for (int i = 1; i <= n; ++i) {
      for (int j = result.size() - 1; j >= 0; --j) {
        result.emplace_back(((result[j] ^ start) | (1 << (i - 1))) ^ start);
      }
    }
    return result;
  }
  std::vector<int> circularPermutation(int n, int start) {
    int count = 1 << n;
    std::vector<int> vis(count);
    std::vector<int> result;
    int x = start;
    result.emplace_back(x);
    vis[x] = true;
    // 类似BFS，寻找相邻的没有遍历过的下一个数字
    for (int i = 0; i < count; ++i) {
      int y = x;
      for (int j = 0; j < n; ++j) {
        y = x ^ (1 << j);
        if (!vis[y]) {
          vis[y] = true;
          result.emplace_back(y);
          x = y;
          break;
        }
      }
    }
    return result;
  }
};