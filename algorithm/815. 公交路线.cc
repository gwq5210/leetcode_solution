/*
 * @lc app=leetcode.cn id=815 lang=cpp
 *
 * [815] 公交路线
 *
 * https://leetcode.cn/problems/bus-routes/description/
 *
 * algorithms
 * Hard (44.22%)
 * Likes:    333
 * Dislikes: 0
 * Total Accepted:    35.8K
 * Total Submissions: 80.9K
 * Testcase Example:  '[[1,2,7],[3,6,7]]\n1\n6'
 *
 * 给你一个数组 routes ，表示一系列公交线路，其中每个 routes[i] 表示一条公交线路，第 i 辆公交车将会在上面循环行驶。
 *
 *
 * 例如，路线 routes[0] = [1, 5, 7] 表示第 0 辆公交车会一直按序列 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1
 * -> ... 这样的车站路线行驶。
 *
 *
 * 现在从 source 车站出发（初始时不在公交车上），要前往 target 车站。 期间仅可乘坐公交车。
 *
 * 求出 最少乘坐的公交车数量 。如果不可能到达终点车站，返回 -1 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：routes = [[1,2,7],[3,6,7]], source = 1, target = 6
 * 输出：2
 * 解释：最优策略是先乘坐第一辆公交车到达车站 7 , 然后换乘第二辆公交车到车站 6 。
 *
 *
 * 示例 2：
 *
 *
 * 输入：routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target =
 * 12
 * 输出：-1
 *
 *
 *
 *
提示：
1 <= routes.length <= 500.
1 <= routes[i].length <= 10^5
routes[i] 中的所有值 互不相同
sum(routes[i].length) <= 10^5
0 <= routes[i][j] < 10^6
0 <= source, target < 10^6
 *
 *
 */

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  int numBusesToDestination(std::vector<std::vector<int>>& routes, int source, int target) {
    if (source == target) {
      return 0;
    }
    adjs_ = std::vector<std::vector<int>>(routes.size());
    for (int i = 0; i < routes.size(); ++i) {
      for (int j = 0; j < routes[i].size(); ++j) {
        for (int line : station_to_lines_[routes[i][j]]) {
          adjs_[i].emplace_back(line);
          adjs_[line].emplace_back(i);
        }
        station_to_lines_[routes[i][j]].emplace_back(i);
      }
    }
    std::unordered_set<int> target_lines;
    std::unordered_set<int> source_lines;
    for (int line : station_to_lines_[target]) {
      target_lines.emplace(line);
    }
    for (int line : station_to_lines_[source]) {
      source_lines.emplace(line);
    }

    // return BFS(routes, source_lines, target_lines);
    return BBFS(routes, source_lines, target_lines);
  }
  int BBFS(std::vector<std::vector<int>>& routes, std::unordered_set<int>& source_lines, std::unordered_set<int>& target_lines) {
    std::vector<int> from_dis(routes.size());
    std::vector<int> to_dis(routes.size());
    std::queue<int> from_q;
    std::queue<int> to_q;
    for (int line : source_lines) {
      from_q.push(line);
      from_dis[line] = 1;
    }
    for (int line : target_lines) {
      to_q.push(line);
      to_dis[line] = 1;
    }
    while (!from_q.empty() && !to_q.empty()) {
      int from_count = from_q.size();
      int to_count = to_q.size();
      if (from_count < 0) {
        for (int i = 0; i < from_count; ++i) {
          int front = from_q.front();
          from_q.pop();
          if (to_dis[front] != 0) {
            return from_dis[front] + to_dis[front] - 1;
          }
          for (int line : adjs_[front]) {
            if (from_dis[line] == 0) {
              from_q.push(line);
              from_dis[line] = from_dis[front] + 1;
            }
          }
        }
      } else {
        for (int i = 0; i < to_count; ++i) {
          int front = to_q.front();
          to_q.pop();
          if (from_dis[front] != 0) {
            return from_dis[front] + to_dis[front] - 1;
          }
          for (int line : adjs_[front]) {
            if (to_dis[line] == 0) {
              to_q.push(line);
              to_dis[line] = to_dis[front] + 1;
            }
          }
        }
      }
    }
    return -1;
  }
  int BFS(std::vector<std::vector<int>>& routes, std::unordered_set<int>& source_lines, std::unordered_set<int>& target_lines) {
    std::vector<int> dis(routes.size());
    std::queue<int> q;
    for (int line : source_lines) {
      q.push(line);
      dis[line] = 1;
    }
    while (!q.empty()) {
      int front = q.front();
      q.pop();
      if (target_lines.count(front)) {
        return dis[front];
      }
      for (int line : adjs_[front]) {
        if (dis[line] == 0) {
          q.push(line);
          dis[line] = dis[front] + 1;
        }
      }
    }
    return -1;
  }

 private:
  std::vector<std::vector<int>> adjs_;
  std::unordered_map<int, std::vector<int>> station_to_lines_;
};