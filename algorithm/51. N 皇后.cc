/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 *
 * https://leetcode.cn/problems/n-queens/description/
 *
 * algorithms
 * Hard (74.24%)
 * Likes:    1664
 * Dislikes: 0
 * Total Accepted:    285.3K
 * Total Submissions: 384.6K
 * Testcase Example:  '4'
 *
 * 按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
 *
 * n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 *
 * 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
 *
 *
 *
 * 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 4
 * 输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 * 解释：如上图所示，4 皇后问题存在两个不同的解法。
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 1
 * 输出：[["Q"]]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 9
 *
 *
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
  int Set(int x, int y) {
    int res = x;
    res <<= 4;
    res |= y;
    return res;
  }
  std::pair<int, int> Get(int x) { return std::make_pair(x >> 4, x & 0xf); }
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> ans;
    std::vector<int> qpos;
    std::vector<std::vector<int>> ans_pos;
    std::unordered_set<int> pos;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        pos.emplace(Set(i, j));
      }
    }
    DFS(n, pos, ans_pos, 0, qpos);
    for (auto& qp : ans_pos) {
      std::vector<std::string> tmp(n, std::string(n, '.'));
      for (int p : qp) {
        auto [x, y] = Get(p);
        tmp[x][y] = 'Q';
      }
      ans.emplace_back(std::move(tmp));
    }
    return ans;
  }
  void RemovePos(int p, int n, std::unordered_set<int>& pos) {
    auto [x, y] = Get(p);
    // 上，下，左，右，左上，右上，左下，右下
    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
    pos.erase(p);
    for (int i = 0; i < 8; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      while (nx >= 0 && nx < n && ny >= 0 && ny < n) {
        pos.erase(Set(nx, ny));
        nx += dx[i];
        ny += dy[i];
      }
    }
    for (auto it = pos.begin(); it != pos.end();) {
      auto [nx, ny] = Get(*it);
      if (nx < x || (x == nx && ny < y)) {
        pos.erase(it++);
      } else {
        ++it;
      }
    }
  }
  void DFS(int n, std::unordered_set<int> pos, std::vector<std::vector<int>>& ans_pos, int index,
           std::vector<int>& qpos) {
    if (n - index > pos.size()) {
      return;
    }
    if (index >= n) {
      ans_pos.emplace_back(qpos);
      return;
    }
    for (int p : pos) {
      std::unordered_set<int> pos_bak(pos.begin(), pos.end());
      RemovePos(p, n, pos_bak);
      qpos.emplace_back(p);
      DFS(n, pos_bak, ans_pos, index + 1, qpos);
      qpos.pop_back();
    }
  }
};