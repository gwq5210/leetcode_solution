/*
 * @lc app=leetcode.cn id=1139 lang=cpp
 *
 * [1139] 最大的以 1 为边界的正方形
 *
 * https://leetcode.cn/problems/largest-1-bordered-square/description/
 *
 * algorithms
 * Medium (49.48%)
 * Likes:    167
 * Dislikes: 0
 * Total Accepted:    20.9K
 * Total Submissions: 38.8K
 * Testcase Example:  '[[1,1,1],[1,0,1],[1,1,1]]'
 *
 * 给你一个由若干 0 和 1 组成的二维网格 grid，请你找出边界全部由 1 组成的最大 正方形
 * 子网格，并返回该子网格中的元素数量。如果不存在，则返回 0。
 *
 *
 *
 * 示例 1：
 *
 * 输入：grid = [[1,1,1],[1,0,1],[1,1,1]]
 * 输出：9
 *
 *
 * 示例 2：
 *
 * 输入：grid = [[1,1,0,0]]
 * 输出：1
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= grid.length <= 100
 * 1 <= grid[0].length <= 100
 * grid[i][j] 为 0 或 1
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
  bool Check(int x, int y, int k, const std::vector<std::vector<int>>& rows_sum,
             const std::vector<std::vector<int>>& cols_sum) {
    int left = y;
    int right = y + k - 1;
    int top = x;
    int bottom = x + k - 1;
    return rows_sum[top][right + 1] - rows_sum[top][left] == k &&
           rows_sum[bottom][right + 1] - rows_sum[bottom][left] == k &&
           cols_sum[left][bottom + 1] - cols_sum[left][top] == k &&
           cols_sum[right][bottom + 1] - cols_sum[right][top] == k;
  }
  int largest1BorderedSquare(std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    int result = 0;
    std::vector<std::vector<int>> rows_sum(m, std::vector<int>(n + 1));
    std::vector<std::vector<int>> cols_sum(n, std::vector<int>(m + 1));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        rows_sum[i][j + 1] = rows_sum[i][j] + grid[i][j];
        cols_sum[j][i + 1] = cols_sum[j][i] + grid[i][j];
      }
    }
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 1; k <= m - i && k <= n - j; ++k) {
          if (Check(i, j, k, rows_sum, cols_sum)) {
            result = std::max(result, k);
          }
        }
      }
    }
    return result * result;
  }
};