/*
 * @lc app=leetcode.cn id=1140 lang=cpp
 *
 * [1140] 石子游戏 II
 *
 * https://leetcode.cn/problems/stone-game-ii/description/
 *
 * algorithms
 * Medium (66.28%)
 * Likes:    192
 * Dislikes: 0
 * Total Accepted:    13.6K
 * Total Submissions: 20K
 * Testcase Example:  '[2,7,9,4,4]'
 *
 * 爱丽丝和鲍勃继续他们的石子游戏。许多堆石子 排成一行，每堆都有正整数颗石子 piles[i]。游戏以谁手中的石子最多来决出胜负。
 *
 * 爱丽丝和鲍勃轮流进行，爱丽丝先开始。最初，M = 1。
 *
 * 在每个玩家的回合中，该玩家可以拿走剩下的 前 X 堆的所有石子，其中 1 <= X <= 2M。然后，令 M = max(M, X)。
 *
 * 游戏一直持续到所有石子都被拿走。
 *
 * 假设爱丽丝和鲍勃都发挥出最佳水平，返回爱丽丝可以得到的最大数量的石头。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：piles = [2,7,9,4,4]
 * 输出：10
 * 解释：如果一开始Alice取了一堆，Bob取了两堆，然后Alice再取两堆。爱丽丝可以得到2 + 4 + 4 =
 * 10堆。如果Alice一开始拿走了两堆，那么Bob可以拿走剩下的三堆。在这种情况下，Alice得到2 + 7 = 9堆。返回10，因为它更大。
 *
 *
 * 示例 2:
 *
 *
 * 输入：piles = [1,2,3,4,5,100]
 * 输出：104
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= piles.length <= 100
 * 1 <= piles[i] <= 10^4
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
  static constexpr int kInf = std::numeric_limits<int>::max() / 2;
  std::vector<std::vector<int>> dp;
  int stoneGameII(std::vector<int>& piles) {
    int n = piles.size();
    dp = std::vector<std::vector<int>>(101, std::vector<int>(202, -1));
    int total = 0;
    // dp[i][m] 表示当 M 为 m 时，区间为 [i, piles.size()) 可以取到的最大数量
    for (int i = n - 1; i >= 0; --i) {
      total += piles[i];
      for (int m = 1; m <= n; ++m) {
        if (2 * m >= n - i) {
          dp[i][m] = total;
          continue;
        }
        int min_v = kInf;
        for (int x = 1; x <= 2 * m && i + x < n; ++x) {
          min_v = std::min(min_v, dp[i + x][std::max(x, m)]);
        }
        dp[i][m] = total - min_v;
      }
    }
    return dp[0][1];
  }
  int stoneGameIIDFS(std::vector<int>& piles) {
    int total = 0;
    for (int i : piles) {
      total += i;
    }
    dp = std::vector<std::vector<int>>(101, std::vector<int>(202, -1));
    // return DFS(piles, 0, 1, total);
    // return DFSMemory(piles, 0, 1, total);
    // return DFS2M(piles, 0, 2, total);
    return DFSMemory2M(piles, 0, 2, total);
  }
  // 单纯 DFS 搜索，没有记忆化
  // index 表示从下标 index 开始 M 取值为 m 时可以取到的最大数量
  // total 表示 [index, piles.size()) 的石子总数
  int DFS(const std::vector<int>& piles, int index, int m, int total) {
    // 可以取的堆数 2*m 比剩余的堆数大或相等，直接全部取完即可
    if (2 * m >= piles.size() - index) {
      return total;
    }
    int c = 0;
    int x = 0;
    // 枚举本次取的石子堆数 i
    for (int i = 1; i <= 2 * m; ++i) {
      c += piles[index + i - 1];
      int next_m = std::max(i, m);
      // 从下一堆开始取，最多能取到的石子总数是 y
      // 因此当前玩家最多只能取到 total - y 数量的石子
      // 因为两者都是最优的策略
      int y = DFS(piles, index + i, next_m, total - c);

      x = std::max(x, total - y);
    }
    // 所有可以取的策略中取最大的 total - y 就是当前玩家可以取得最大石子数量
    return x;
  }

  // 加入记忆化，含义与上述一致
  int DFSMemory(const std::vector<int>& piles, int index, int m, int total) {
    if (2 * m >= piles.size() - index) {
      return total;
    }
    int c = 0;
    int x = 0;
    // index 和 m 一样时，可以取的数量是固定的，因此记录下来，下次遇到直接返回即可
    if (dp[index][m] >= 0) {
      return dp[index][m];
    }
    for (int i = 1; i <= 2 * m; ++i) {
      c += piles[index + i - 1];
      int next_m = std::max(i, m);
      int y = DFSMemory(piles, index + i, next_m, total - c);
      x = std::max(x, total - y);
      // 刚开始的时候在循环中使用如下句子进行记录
      // 这里是不对的，因为 dp[index][i] 的含义已经改变了
      // 表示从下标 index 开始 最多取 i 堆时可以取到的最大数量
      // dp[index][i] = x;
    }
    dp[index][m] = x;
    return x;
  }

  // m 的含义不同，m 是上述 m 取值的两倍
  int DFS2M(const std::vector<int>& piles, int index, int m, int total) {
    if (m >= piles.size() - index) {
      return total;
    }
    int c = 0;
    int x = 0;
    for (int i = 1; i <= m; ++i) {
      c += piles[index + i - 1];
      int next_m = std::max(i, m / 2) * 2;
      int y = DFS2M(piles, index + i, next_m, total - c);
      x = std::max(x, total - y);
    }
    return x;
  }

  int DFSMemory2M(const std::vector<int>& piles, int index, int m, int total) {
    if (m >= piles.size() - index) {
      return total;
    }
    if (dp[index][m] >= 0) {
      return dp[index][m];
    }
    int c = 0;
    int x = 0;
    for (int i = 1; i <= m; ++i) {
      c += piles[index + i - 1];
      int next_m = std::max(i, m / 2) * 2;
      int y = DFSMemory2M(piles, index + i, next_m, total - c);
      x = std::max(x, total - y);
    }
    dp[index][m] = x;
    return x;
  }
};
