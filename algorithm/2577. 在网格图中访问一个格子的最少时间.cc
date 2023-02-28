/*
 * @lc app=leetcode.cn id=2577 lang=cpp
 *
 * [2577] 在网格图中访问一个格子的最少时间
 *
 * https://leetcode.cn/problems/find-the-maximum-number-of-marked-indices/description/
 *
给你一个 m x n 的矩阵 grid ，每个元素都为 非负 整数，其中 grid[row][col] 表示可以访问格子 (row, col) 的 最早
时间。也就是说当你访问格子 (row, col) 时，最少已经经过的时间为 grid[row][col] 。

你从 最左上角 出发，出发时刻为 0 ，你必须一直移动到上下左右相邻四个格子中的 任意
一个格子（即不能停留在格子上）。每次移动都需要花费 1 单位时间。

请你返回 最早 到达右下角格子的时间，如果你无法到达右下角的格子，请你返回 -1 。



示例 1：



输入：grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
输出：7
解释：一条可行的路径为：
- 时刻 t = 0 ，我们在格子 (0,0) 。
- 时刻 t = 1 ，我们移动到格子 (0,1) ，可以移动的原因是 grid[0][1] <= 1 。
- 时刻 t = 2 ，我们移动到格子 (1,1) ，可以移动的原因是 grid[1][1] <= 2 。
- 时刻 t = 3 ，我们移动到格子 (1,2) ，可以移动的原因是 grid[1][2] <= 3 。
- 时刻 t = 4 ，我们移动到格子 (1,1) ，可以移动的原因是 grid[1][1] <= 4 。
- 时刻 t = 5 ，我们移动到格子 (1,2) ，可以移动的原因是 grid[1][2] <= 5 。
- 时刻 t = 6 ，我们移动到格子 (1,3) ，可以移动的原因是 grid[1][3] <= 6 。
- 时刻 t = 7 ，我们移动到格子 (2,3) ，可以移动的原因是 grid[2][3] <= 7 。
最终到达时刻为 7 。这是最早可以到达的时间。
示例 2：



输入：grid = [[0,2,4],[3,2,1],[1,0,4]]
输出：-1
解释：没法从左上角按题目规定走到右下角。


提示：

m == grid.length
n == grid[i].length
2 <= m, n <= 1000
4 <= m * n <= 10^5
0 <= grid[i][j] <= 10^5
grid[0][0] == 0
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
  static constexpr int kInf = std::numeric_limits<int>::max() / 2;
  static constexpr int dx[] = {0, 0, -1, 1};
  static constexpr int dy[] = {1, -1, 0, 0};
  struct Node {
    int x = 0;
    int y = 0;
    int d = 0;
    bool operator<(const Node& other) const { return d > other.d; }
  };
  // 如果 grid[0][1]<=1 或者 grid[1][0]<=1，那么可以通过「反复横跳」来「等待」。否则根本就无法从起点出发，返回 −1。
  // 若这两个位置能走出去，那么其他位置一定可以通过在相邻附近某两个格子反复横跳的方式等到时间够用(即>grid[i][j])，一定有解
  // 类似最短路问题，可以使用 dijkstra 求解
  int minimumTime(std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    if (grid[0][1] > 1 && grid[1][0] > 1) {
      return -1;
    }
    std::vector<std::vector<int>> vis(m, std::vector<int>(n));
    std::vector<std::vector<int>> dis(m, std::vector<int>(n, kInf));
    std::priority_queue<Node> pq;
    pq.push(Node{0, 0, 0});
    while (!pq.empty()) {
      Node top = pq.top();
      pq.pop();
      // 已经求出最小值的节点就直接跳过
      if (vis[top.x][top.y]) {
        continue;
      }
      vis[top.x][top.y] = true;
      for (int i = 0; i < 4; ++i) {
        Node new_node{top.x + dx[i], top.y + dy[i], top.d + 1};
        if (new_node.x >= 0 && new_node.x < m && new_node.y >= 0 && new_node.y < n) {
          // 如果无法直接到达，则通过反复横跳到达相邻的节点
          if (new_node.d < grid[new_node.x][new_node.y]) {
            new_node.d += (grid[new_node.x][new_node.y] - new_node.d + 1) / 2 * 2;
          }
          if (new_node.d < dis[new_node.x][new_node.y]) {
            dis[new_node.x][new_node.y] = new_node.d;
            pq.push(new_node);
          }
        }
      }
    }
    return dis[m - 1][n - 1];
  }
};