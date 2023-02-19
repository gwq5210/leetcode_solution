/*
 * @lc app=leetcode.cn id=542 lang=cpp
 *
 * [542] 01 矩阵
 *
 * https://leetcode-cn.com/problems/01-matrix/description/
 *
 * algorithms
 * Medium (45.79%)
 * Likes:    818
 * Dislikes: 0
 * Total Accepted:    125.9K
 * Total Submissions: 270.7K
 * Testcase Example:  '[[0,0,0],[0,1,0],[0,0,0]]'
 *
 * 给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。
 *
 * 两个相邻元素间的距离为 1 。
 *
 *
 *
 * 示例 1：
 *
 *
 *
 *
 * 输入：mat = [[0,0,0],[0,1,0],[0,0,0]]
 * 输出：[[0,0,0],[0,1,0],[0,0,0]]
 *
 *
 * 示例 2：
 *
 *
 *
 *
 * 输入：mat = [[0,0,0],[0,1,0],[1,1,1]]
 * 输出：[[0,0,0],[0,1,0],[1,2,1]]
 *
 *
 *
 *
 * 提示：
 *
 *
 * m == mat.length
 * n == mat[i].length
 * 1
 * 1
 * mat[i][j] is either 0 or 1.
 * mat 中至少有一个 0 
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
  static constexpr int kInf = 2000000;
  struct Node {
    int x = 0;
    int y = 0;
    int d = 0;
  };
  std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();
    std::vector<std::vector<int>> result(m, std::vector<int>(n, kInf));
    std::queue<Node> q;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] == 0) {
          q.push(Node{i, j, 0});
          result[i][j] = 0;
        }
      }
    }
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    while (!q.empty()) {
      Node front = q.front();
      q.pop();
      for (int i = 0; i < 4; ++i) {
        Node new_node{front.x + dx[i], front.y + dy[i], front.d + 1};
        if (new_node.x < 0 || new_node.x >= m || new_node.y < 0 || new_node.y >= n) {
          continue;
        }
        if (result[new_node.x][new_node.y] == kInf) {
          q.push(new_node);
          result[new_node.x][new_node.y] = new_node.d;
        }
      }
    }
    return result;
  }
  std::vector<std::vector<int>> updateMatrix1(std::vector<std::vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();
    std::vector<std::vector<int>> result(m, std::vector<int>(n, kInf));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] == 0) {
          result[i][j] = 0;
        } else {
          result[i][j] = std::min(i - 1 >= 0 ? result[i - 1][j] : kInf, j - 1 >= 0 ? result[i][j - 1] : kInf) + 1;
        }
      }
    }
    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        if (mat[i][j] == 0) {
          result[i][j] = 0;
        } else {
          int x = std::min(i + 1 < m ? result[i + 1][j] : kInf, j + 1 < n ? result[i][j + 1] : kInf) + 1;
          if (x < result[i][j]) {
            result[i][j] = x;
          }
        }
      }
    }
    return result;
  }
};