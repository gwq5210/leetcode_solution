/*
 * @lc app=leetcode.cn id=52 lang=cpp
 *
 * [52] N 皇后 II
 *
 * https://leetcode.cn/problems/n-queens-ii/description/
 *
 * algorithms
 * Hard (82.45%)
 * Likes:    414
 * Dislikes: 0
 * Total Accepted:    113.8K
 * Total Submissions: 137.9K
 * Testcase Example:  '4'
 *
 * n 皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 *
 * 给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。
 *
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 4
 * 输出：2
 * 解释：如上图所示，4 皇后问题存在两个不同的解法。
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 1
 * 输出：1
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
  int totalNQueens(int n) {
    std::vector<std::vector<std::string>> ans;
    std::vector<std::string> qmap(n, std::string(n, '.'));
    DFS(n, ans, 0, qmap);
    return ans.size();
  }
  std::vector<std::vector<std::string>> solveNQueens1(int n) {
    std::vector<std::vector<std::string>> ans;
    std::vector<int> qpos;
    std::vector<std::vector<int>> ans_pos;
    std::unordered_set<int> pos;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        pos.emplace(Set(i, j));
      }
    }
    DFS1(n, pos, ans_pos, 0, qpos);
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

  // 这里是从第一行到第 n 行进行枚举，枚举第 index 行所在的列，通过集合判断列，和两条斜线是否存在皇后
  // 复杂度是 n!
  void DFS(int n, std::vector<std::vector<std::string>>& ans, int index, std::vector<std::string>& qmap) {
    if (index >= n) {
      ans.emplace_back(qmap);
      return;
    }
    for (int i = 0; i < n; ++i) {
      int x = index;
      int y = i;
      if (cols_ & (1 << y) || x1_ & (1 << (x + y)) || x2_ & (1 << (n + x - y))) {
        continue;
      }
      qmap[x][y] = 'Q';
      cols_ |= 1 << y;
      x1_ |= 1 << (x + y);
      x2_ |= 1 << (n + x - y);
      DFS(n, ans, index + 1, qmap);
      cols_ ^= 1 << y;
      x1_ ^= 1 << (x + y);
      x2_ ^= 1 << (n + x - y);
      qmap[x][y] = '.';
    }
  }

  // 这里枚举是枚举第 index 个可用的坐标
  void DFS1(int n, std::unordered_set<int> pos, std::vector<std::vector<int>>& ans_pos, int index,
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
      DFS1(n, pos_bak, ans_pos, index + 1, qpos);
      qpos.pop_back();
    }
  }

 private:
  int cols_ = 0;
  int x1_ = 0;
  int x2_ = 0;
};