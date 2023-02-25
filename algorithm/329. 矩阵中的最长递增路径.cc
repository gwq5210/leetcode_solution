/*
 * @lc app=leetcode.cn id=329 lang=cpp
 *
 * [329] 矩阵中的最长递增路径
 *
 * https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/description/
 *
 * algorithms
 * Hard (48.68%)
 * Likes:    739
 * Dislikes: 0
 * Total Accepted:    92.5K
 * Total Submissions: 179.3K
 * Testcase Example:  '[[9,9,4],[6,6,8],[2,1,1]]'
 *
 * 给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度。
 *
 * 对于每个单元格，你可以往上，下，左，右四个方向移动。 你 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：matrix = [[9,9,4],[6,6,8],[2,1,1]]
 * 输出：4
 * 解释：最长递增路径为 [1, 2, 6, 9]。
 *
 * 示例 2：
 *
 *
 * 输入：matrix = [[3,4,5],[3,2,6],[2,2,1]]
 * 输出：4
 * 解释：最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动。
 *
 *
 * 示例 3：
 *
 *
 * 输入：matrix = [[1]]
 * 输出：1
 *
 *
 *
 *
 * 提示：
 *
 *
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 200
 * 0 <= matrix[i][j] <= 2^31 - 1
 *
 *
 */

#include <deque>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  int longestIncreasingPath(std::vector<std::vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    std::vector<std::vector<int>> in_degrees(m, std::vector<int>(n));
    std::queue<std::pair<int, int>> q;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    // 将矩阵看做一个有向图，计算每个单元格对应的入度，即相邻的较小的数的数量
    // 然后按照 BFS 遍历计算出层数即可
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < 4; ++k) {
          int nx = i + dx[k];
          int ny = j + dy[k];
          if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[i][j] > matrix[nx][ny]) {
            ++in_degrees[i][j];
          }
        }
        if (in_degrees[i][j] == 0) {
          q.push(std::make_pair(i, j));
        }
      }
    }
    int res = 0;
    while (!q.empty()) {
      for (int i = q.size(); i > 0; --i) {
        auto [x, y] = q.front();
        q.pop();
        for (int j = 0; j < 4; ++j) {
          int nx = x + dx[j];
          int ny = y + dy[j];
          if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx][ny] > matrix[x][y]) {
            --in_degrees[nx][ny];
            if (in_degrees[nx][ny] == 0) {
              q.push(std::make_pair(nx, ny));
            }
          }
        }
      }
      ++res;
    }
    return res;
  }
  int longestIncreasingPathDFS(std::vector<std::vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    // 记忆化搜索
    std::vector<std::vector<int>> dis(m, std::vector<int>(n));
    int res = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        res = std::max(res, DFS(matrix, m, n, i, j, dis));
      }
    }
    return res;
  }
  int DFS(std::vector<std::vector<int>>& matrix, int m, int n, int x, int y, std::vector<std::vector<int>>& dis) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int res = 0;
    int num = matrix[x][y];
    if (dis[x][y]) {
      return dis[x][y];
    }
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx][ny] > num) {
        res = std::max(res, DFS(matrix, m, n, nx, ny, dis));
      }
    }
    dis[x][y] = res + 1;
    return res + 1;
  }
};
