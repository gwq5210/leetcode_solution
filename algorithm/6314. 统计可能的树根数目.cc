/*
 * @lc app=leetcode.cn id=6314 lang=cpp
 *
 * [6314] 统计可能的树根数目
 *
 * https://leetcode.cn/problems/count-number-of-possible-root-nodes/description/
 *
Alice 有一棵 n 个节点的树，节点编号为 0 到 n - 1 。树用一个长度为 n - 1 的二维整数数组 edges 表示，其中 edges[i] = [ai,
bi] ，表示树中节点 ai 和 bi 之间有一条边。

Alice 想要 Bob 找到这棵树的根。她允许 Bob 对这棵树进行若干次 猜测 。每一次猜测，Bob 做如下事情：

选择两个 不相等 的整数 u 和 v ，且树中必须存在边 [u, v] 。
Bob 猜测树中 u 是 v 的 父节点 。
Bob 的猜测用二维整数数组 guesses 表示，其中 guesses[j] = [uj, vj] 表示 Bob 猜 uj 是 vj 的父节点。

Alice 非常懒，她不想逐个回答 Bob 的猜测，只告诉 Bob 这些猜测里面 至少 有 k 个猜测的结果为 true 。

给你二维整数数组 edges ，Bob 的所有猜测和整数 k ，请你返回可能成为树根的 节点数目 。如果没有这样的树，则返回 0。



示例 1：



输入：edges = [[0,1],[1,2],[1,3],[4,2]], guesses = [[1,3],[0,1],[1,0],[2,4]], k = 3
输出：3
解释：
根为节点 0 ，正确的猜测为 [1,3], [0,1], [2,4]
根为节点 1 ，正确的猜测为 [1,3], [1,0], [2,4]
根为节点 2 ，正确的猜测为 [1,3], [1,0], [2,4]
根为节点 3 ，正确的猜测为 [1,0], [2,4]
根为节点 4 ，正确的猜测为 [1,3], [1,0]
节点 0 ，1 或 2 为根时，可以得到 3 个正确的猜测。
示例 2：



输入：edges = [[0,1],[1,2],[2,3],[3,4]], guesses = [[1,0],[3,4],[2,1],[3,2]], k = 1
输出：5
解释：
根为节点 0 ，正确的猜测为 [3,4]
根为节点 1 ，正确的猜测为 [1,0], [3,4]
根为节点 2 ，正确的猜测为 [1,0], [2,1], [3,4]
根为节点 3 ，正确的猜测为 [1,0], [2,1], [3,2], [3,4]
根为节点 4 ，正确的猜测为 [1,0], [2,1], [3,2]
任何节点为根，都至少有 1 个正确的猜测。


提示：

edges.length == n - 1
2 <= n <= 105
1 <= guesses.length <= 105
0 <= ai, bi, uj, vj <= n - 1
ai != bi
uj != vj
edges 表示一棵有效的树。
guesses[j] 是树中的一条边。
0 <= k <= guesses.length
 *
 *
 */

#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  int BFS0(int n, std::vector<std::vector<int>>& adjs, std::unordered_set<long long>& parents) {
    int correct_count = 0;
    std::vector<int> vis(n);
    std::queue<int> q;
    q.push(0);
    vis[0] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : adjs[u]) {
        if (vis[v]) {
          continue;
        }
        long long key = u;
        key = (key << 32 | v);
        if (parents.count(key)) {
          ++correct_count;
        }
        q.push(v);
        vis[v] = true;
      }
    }
    return correct_count;
  }
  int RerootBFS(int n, int k, int correct_count, std::vector<std::vector<int>>& adjs,
                std::unordered_set<long long>& parents) {
    std::vector<int> vis(n);
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(0, correct_count));
    vis[0] = true;
    int res = 0;
    while (!q.empty()) {
      auto [u, c] = q.front();
      q.pop();
      if (c >= k) {
        ++res;
      }
      for (int v : adjs[u]) {
        if (vis[v]) {
          continue;
        }
        int vc = c;
        long long key = u;
        key = (key << 32 | v);
        if (parents.count(key)) {
          --vc;
        }
        key = v;
        key = (key << 32 | u);
        if (parents.count(key)) {
          ++vc;
        }
        q.push(std::make_pair(v, vc));
        vis[v] = true;
      }
    }
    return res;
  }
  void DFS0(int n, int u, int fa, std::vector<std::vector<int>>& adjs, std::unordered_set<long long>& parents,
            int& correct_count) {
    for (int v : adjs[u]) {
      // 排除父节点
      if (v == fa) {
        continue;
      }
      long long key = u;
      key = (key << 32 | v);
      if (parents.count(key)) {
        ++correct_count;
      }
      DFS0(n, v, u, adjs, parents, correct_count);
    }
  }
  void RerootDFS(int n, int k, int correct_count, int u, int fa, std::vector<std::vector<int>>& adjs,
                 std::unordered_set<long long>& parents, int& res) {
    if (correct_count >= k) {
      ++res;
    }
    for (int v : adjs[u]) {
      // 排除父节点
      if (v == fa) {
        continue;
      }
      long long key = u;
      key = (key << 32 | v);
      int c = correct_count;
      if (parents.count(key)) {
        --c;
      }
      key = v;
      key = (key << 32 | u);
      if (parents.count(key)) {
        ++c;
      }
      RerootDFS(n, k, c, v, u, adjs, parents, res);
    }
  }
  // 换根dp
  // 两边dfs，第一遍求出以 0 为根的猜测正确的数量 c
  // 第二遍dfs遍历每个节点，设以节点 u 为根时对应的猜测正确的数量是 c
  // 则对 u 的子节点 v，以 v 为根时猜测正确的数量可以由 c 推算得到
  // 具体来说，如果猜测中有 u->v，则 --c
  // 如果猜测中有 v->u，则 ++c
  // 同样也可以使用BFS
  int rootCount(std::vector<std::vector<int>>& edges, std::vector<std::vector<int>>& guesses, int k) {
    int n = edges.size() + 1;
    std::vector<std::vector<int>> adjs(n);
    for (auto& edge : edges) {
      adjs[edge[0]].emplace_back(edge[1]);
      adjs[edge[1]].emplace_back(edge[0]);
    }
    // 这里的猜测 u->v，可能会有多个边的 u 是相同的
    std::unordered_set<long long> parents;
    for (auto& guess : guesses) {
      // u->v 压缩为一个 8 字节数
      // 高 4 字节存储 u
      // 低 4 字节存储 v
      long long key = guess[0];
      key = (key << 32) | guess[1];
      parents.emplace(key);
    }
    int correct_count = BFS0(n, adjs, parents);
    int res = RerootBFS(n, k, correct_count, adjs, parents);
    return res;
  }
};