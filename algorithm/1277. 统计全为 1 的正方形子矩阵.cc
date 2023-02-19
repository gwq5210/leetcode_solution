/*
 * @lc app=leetcode.cn id=1277 lang=cpp
 *
 * [1277] 统计全为 1 的正方形子矩阵
 *
 * https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/description/
 *
 * algorithms
 * Medium (72.54%)
 * Likes:    269
 * Dislikes: 0
 * Total Accepted:    28.9K
 * Total Submissions: 39.3K
 * Testcase Example:  '[[0,1,1,1],[1,1,1,1],[0,1,1,1]]'
 *
 * 给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1，请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。
 *
 *
 *
 * 示例 1：
 *
 * 输入：matrix =
 * [
 * [0,1,1,1],
 * [1,1,1,1],
 * [0,1,1,1]
 * ]
 * 输出：15
 * 解释：
 * 边长为 1 的正方形有 10 个。
 * 边长为 2 的正方形有 4 个。
 * 边长为 3 的正方形有 1 个。
 * 正方形的总数 = 10 + 4 + 1 = 15.
 *
 *
 * 示例 2：
 *
 * 输入：matrix =
 * [
 * ⁠ [1,0,1],
 * ⁠ [1,1,0],
 * ⁠ [1,1,0]
 * ]
 * 输出：7
 * 解释：
 * 边长为 1 的正方形有 6 个。
 * 边长为 2 的正方形有 1 个。
 * 正方形的总数 = 6 + 1 = 7.
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= arr.length <= 300
 * 1 <= arr[0].length <= 300
 * 0 <= arr[i][j] <= 1
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
  int countSquares(std::vector<std::vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    // 我们用 dp[i][j] 表示以 (i, j) 为右下角的正方形的最大边长
    // 那么除此定义之外，dp[i][j] = x 也表示以 (i, j) 为右下角的正方形的数目为 x
    //（即边长为 1, 2, ..., x 的正方形各一个）
    // 在计算出所有的 dp[i][j] 后，我们将它们进行累加，就可以得到矩阵中正方形的数目。
    std::vector<std::vector<int>> dp(m, std::vector<int>(n));
    int res = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == 1) {
          if (i == 0 || j == 0) {
            dp[i][j] = 1;
          } else {
            dp[i][j] = std::min(dp[i - 1][j], std::min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
          }
        }
        res += dp[i][j];
      }
    }
    return res;
  }
};