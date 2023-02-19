/*
 * @lc app=leetcode.cn id=221 lang=cpp
 *
 * [221] 最大正方形
 *
 * https://leetcode-cn.com/problems/maximal-square/description/
 *
 * algorithms
 * Medium (47.76%)
 * Likes:    1368
 * Dislikes: 0
 * Total Accepted:    252.3K
 * Total Submissions: 509.8K
 * Testcase Example:  '[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]'
 *
 * 在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：matrix =
 * [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
 * 输出：4
 *
 *
 * 示例 2：
 *
 *
 * 输入：matrix = [["0","1"],["1","0"]]
 * 输出：1
 *
 *
 * 示例 3：
 *
 *
 * 输入：matrix = [["0"]]
 * 输出：0
 *
 *
 *
 *
 * 提示：
 *
 *
 * m == matrix.length
 * n == matrix[i].length
 * 1
 * matrix[i][j] 为 '0' 或 '1'
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
  int maximalSquare1(std::vector<std::vector<char>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    std::vector<std::vector<int>> dp(m, std::vector<int>(n));
    int res = 0;
    for (int i = 0; i < m; ++i) {
      dp[i][0] = matrix[i][0] == '1' ? 1 : 0;
      res = std::max(res, dp[i][0]);
    }
    for (int i = 0; i < n; ++i) {
      dp[0][i] = matrix[0][i] == '1' ? 1 : 0;
      res = std::max(res, dp[0][i]);
    }
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        for (int w = std::min(i + 1, j + 1); w >= 1 && matrix[i][j] == '1'; --w) {
          int left = j - w + 1;
          int top = i - w + 1;
          if (dp[i - 1][j] >= w - 1 && dp[i][j - 1] >= w - 1 && matrix[top][left] == '1') {
            dp[i][j] = w;
            break;
          }
        }
        // printf("i %d, j %d, w %d\n", i, j, dp[i][j]);
        res = std::max(res, dp[i][j]);
      }
    }
    return res * res;
  }

  int maximalSquare(std::vector<std::vector<char>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    std::vector<std::vector<int>> dp(m, std::vector<int>(n));
    // 可以使用动态规划降低时间复杂度。我们用 dp(i,j) 表示以 (i,j) 为右下角，且只包含 1
    // 的正方形的边长最大值。如果我们能计算出所有 dp(i,j) 的值，那么其中的最大值即为矩阵中只包含
    // 1 的正方形的边长最大值，其平方即为最大正方形的面积。
    // 那么如何计算 dp 中的每个元素值呢？对于每个位置(i, j)，检查在矩阵中该位置的值：
    // 如果该位置的值是 0，则 dp(i, j) = 0，因为当前位置不可能在由 1 组成的正方形中；
    // 如果该位置的值是 1，则 dp(i, j) 的值由其上方、左方和左上方的三个相邻位置的 dp 值决定。
    // 具体而言，当前位置的元素值等于三个相邻位置的元素中的最小值加 1，状态转移方程如下：
    // dp(i, j) = min(dp(i−1, j), dp(i−1, j−1), dp(i, j−1)) + 1
    // 此外，还需要考虑边界条件。如果 i 和 j 中至少有一个为 0，则以位置 (i,j)
    // 为右下角的最大正方形的边长只能是 1，因此 dp(i,j)=1。
    // 题目1277. 统计全为 1 的正方形子矩阵与此题类似
    int res = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == '1') {
          if (i == 0 || j == 0) {
            dp[i][j] = 1;
          } else {
            dp[i][j] = std::min(dp[i - 1][j], std::min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
          }
        }
        res = std::max(res, dp[i][j]);
      }
    }
    return res * res;
  }
};