/*
 * @lc app=leetcode.cn id=787 lang=cpp
 *
 * [787] K 站中转内最便宜的航班
 *
 * https://leetcode.cn/problems/cheapest-flights-within-k-stops/description/
 *
 * algorithms
 * Medium (39.46%)
 * Likes:    553
 * Dislikes: 0
 * Total Accepted:    62.8K
 * Total Submissions: 159.3K
 * Testcase Example:  '4\n[[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]]\n0\n3\n1'
 *
 * 有 n 个城市通过一些航班连接。给你一个数组 flights ，其中 flights[i] = [fromi, toi, pricei]
 * ，表示该航班都从城市 fromi 开始，以价格 pricei 抵达 toi。
 *
 * 现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，你的任务是找到出一条最多经过 k 站中转的路线，使得从 src 到
 * dst 的 价格最便宜 ，并返回该价格。 如果不存在这样的路线，则输出 -1。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入:
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 1
 * 输出: 200
 * 解释:
 * 城市航班图如下
 *
 *
 * 从城市 0 到城市 2 在 1 站中转以内的最便宜价格是 200，如图中红色所示。
 *
 * 示例 2：
 *
 *
 * 输入:
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 0
 * 输出: 500
 * 解释:
 * 城市航班图如下
 *
 *
 * 从城市 0 到城市 2 在 0 站中转以内的最便宜价格是 500，如图中蓝色所示。
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 100
 * 0 <= flights.length <= (n * (n - 1) / 2)
 * flights[i].length == 3
 * 0 <= fromi, toi < n
 * fromi != toi
 * 1 <= pricei <= 10^4
 * 航班没有重复，且不存在自环
 * 0 <= src, dst, k < n
 * src != dst
 *
 *
 */

#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  static constexpr int kInf = std::numeric_limits<int>::max() / 2;
  struct Node {
    int id = 0;
    int price = 0;
    int d = 0;
    bool operator>(const Node& node) const { return price > node.price; }
  };
  int FindCheapestPriceBellmanFord(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k) {
    std::vector<std::vector<int>> dis(2, std::vector<int>(n, kInf));
    int t = 0;
    dis[t][src] = 0;
    bool flag = false;
    for (int i = 1; i <= k + 1; ++i) {
      int p = t;
      t = 1 - t;
      dis[t] = dis[p];
      for (auto& flight : flights) {
        int from = flight[0];
        int to = flight[1];
        int price = flight[2];
        if (dis[p][from] + price < dis[t][to]) {
          dis[t][to] = dis[p][from] + price;
          flag = true;
        }
      }
      if (!flag) {
        break;
      }
    }
    return dis[t][dst] == kInf ? -1 : dis[t][dst];
  }

  int findCheapestPrice(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k) {
    // 使用邻接矩阵建图, adjs[u][v] > 0表示u到v有权值为adjs[u][v]的边
    std::vector<std::vector<int>> adjs(n, std::vector<int>(n));
    for (auto& flight : flights) {
      adjs[flight[0]][flight[1]] = flight[2];
    }

    // 因为有remain_step的限制, 这个dijkstra变得更加简单, 就像一个广搜一样
    // 我们可以使用一个最小堆来存储当前状态(当前花费cost, 当前城市city,
    // 剩余航班数remain_step)按照当前花费从小到大的顺序排列

    // 为了剪枝, 我们可以设置两个数组(如果不进行剪枝, 会超时)
    // 这个剪枝其实和原始的dijkstra类似，只是多了步数的条件
    // dis[i]是用来存储目前已知的src到节点i的最小花费
    std::vector<int> dis(n, kInf);
    // remain_step[i]用来存储src到节点i最小花费时剩余的步数是用来存储目前已知的src到节点i的最小花费
    std::vector<int> remain_step(n, k + 1);

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push(Node{src, 0, k + 1});
    while (!pq.empty()) {
      Node node = pq.top();
      pq.pop();

      // 因为我们是按花费从小到大排序, 所以一旦我们到达了终点, 我们就可以直接返回
      if (node.id == dst) {
        return node.price;
      }
      // 剩余步数为0，则跳过该节点
      if (node.d == 0) {
        continue;
      }
      for (int v = 0; v < n; ++v) {
        if (adjs[node.id][v] > 0) {
          if (node.price + adjs[node.id][v] < dis[v]) {
            // 花费更小，则进入队列并更新dis[v]和remain_step[v]
            dis[v] = node.price + adjs[node.id][v];
            remain_step[v] = node.d - 1;
            pq.push(Node{v, node.price + adjs[node.id][v], node.d - 1});
          } else if (node.d - 1 > remain_step[v]) {
            // 如果当前可走的步数比之前记录的最小花费时的可走步数大,
            // 表明我们还有可能抢救一下
            pq.push(Node{v, node.price + adjs[node.id][v], node.d - 1});
          }
        }
      }
    }
    return -1;
  }
};