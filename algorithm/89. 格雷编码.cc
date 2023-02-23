/*
 * @lc app=leetcode.cn id=89 lang=cpp
 *
 * [89] 格雷编码
 *
 * https://leetcode.cn/problems/gray-code/description/
 *
 * algorithms
 * Medium (75.02%)
 * Likes:    598
 * Dislikes: 0
 * Total Accepted:    112.9K
 * Total Submissions: 149.9K
 * Testcase Example:  '2'
 *
 * n 位格雷码序列 是一个由 2^n 个整数组成的序列，其中：
 *
 * 每个整数都在范围 [0, 2^n - 1] 内（含 0 和 2^n - 1）
 * 第一个整数是 0
 * 一个整数在序列中出现 不超过一次
 * 每对 相邻 整数的二进制表示 恰好一位不同 ，且
 * 第一个 和 最后一个 整数的二进制表示 恰好一位不同
 *
 *
 * 给你一个整数 n ，返回任一有效的 n 位格雷码序列 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 2
 * 输出：[0,1,3,2]
 * 解释：
 * [0,1,3,2] 的二进制表示是 [00,01,11,10] 。
 * - 00 和 01 有一位不同
 * - 01 和 11 有一位不同
 * - 11 和 10 有一位不同
 * - 10 和 00 有一位不同
 * [0,2,3,1] 也是一个有效的格雷码序列，其二进制表示是 [00,10,11,01] 。
 * - 00 和 10 有一位不同
 * - 10 和 11 有一位不同
 * - 11 和 01 有一位不同
 * - 01 和 00 有一位不同
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 1
 * 输出：[0,1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 16
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
  // n = 0  [0]
  // n = 1  [0, 1]
  // n = 2  [00, 01, 11, 10]
  // n = 3  [000, 001, 011, 010, 110, 111, 101, 100]
  // 我们可以根据 n-1 的格雷码，构造出 n 的格雷码序列
  // 因为格雷码 n 每增加1，包含的数字会翻倍，这里我们设n位格雷码包含 c 个数，前一个 n 为 n'，所以 c = 2c'
  // 所以这时 n 中的前 c' 个数是 n' 中的所有数字前面补 0 ，相当于全部都是 n` 中的数字
  // n = 2  [ 00,  01,  11,  10]
  // n = 3  [000, 001, 011, 010] (前四个数)
  // 这时 n 中的后 c' 个数是 n' 中的所有数字前面补 1 ，然后变为逆序
  // n = 2  [ 00,  01,  11,  10]
  // 补   1 [100, 101, 111, 110]
  // 逆  序 [110, 111, 101, 100] （后四个数）
  // 结果拼接
  // n = 3  [000, 001, 011, 010, 110, 111, 101, 100]
  std::vector<int> grayCode1(int n) {
    std::vector<int> result;
    result.emplace_back(0);
    for (int i = 1; i <= n; ++i) {
      for (int j = result.size() - 1; j >= 0; --j) {
        result.emplace_back(result[j] | (1 << (i - 1)));
      }
    }
    return result;
  }
  std::vector<int> grayCode(int n) {
    std::vector<int> result;
    result.emplace_back(0);
    for (int i = 1; i <= n; ++i) {
      for (int j = result.size() - 1; j >= 0; --j) {
        result.emplace_back(result[j] | (1 << (i - 1)));
      }
    }
    return result;
  }
  std::vector<int> grayCodeBFS(int n) {
    int count = 1 << n;
    std::vector<int> vis(count);
    std::vector<int> result;
    int x = 0;
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