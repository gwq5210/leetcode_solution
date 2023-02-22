/*
 * @lc app=leetcode.cn id=877 lang=cpp
 *
 * [877] 石子游戏
 *
 * https://leetcode.cn/problems/stone-game/description/
 *
 * algorithms
 * Medium (76.40%)
 * Likes:    479
 * Dislikes: 0
 * Total Accepted:    90.5K
 * Total Submissions: 118.5K
 * Testcase Example:  '[5,3,4,5]'
 *
 * Alice 和 Bob 用几堆石子在做游戏。一共有偶数堆石子，排成一行；每堆都有 正 整数颗石子，数目为 piles[i] 。
 *
 * 游戏以谁手中的石子最多来决出胜负。石子的 总数 是 奇数 ，所以没有平局。
 *
 * Alice 和 Bob 轮流进行，Alice 先开始 。 每回合，玩家从行的 开始 或 结束 处取走整堆石头。
 * 这种情况一直持续到没有更多的石子堆为止，此时手中 石子最多 的玩家 获胜 。
 *
 * 假设 Alice 和 Bob 都发挥出最佳水平，当 Alice 赢得比赛时返回 true ，当 Bob 赢得比赛时返回 false 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：piles = [5,3,4,5]
 * 输出：true
 * 解释：
 * Alice 先开始，只能拿前 5 颗或后 5 颗石子 。
 * 假设他取了前 5 颗，这一行就变成了 [3,4,5] 。
 * 如果 Bob 拿走前 3 颗，那么剩下的是 [4,5]，Alice 拿走后 5 颗赢得 10 分。
 * 如果 Bob 拿走后 5 颗，那么剩下的是 [3,4]，Alice 拿走后 4 颗赢得 9 分。
 * 这表明，取前 5 颗石子对 Alice 来说是一个胜利的举动，所以返回 true 。
 *
 *
 * 示例 2：
 *
 *
 * 输入：piles = [3,7,2,3]
 * 输出：true
 *
 *
 *
 *
 * 提示：
 *
 *
 * 2 <= piles.length <= 500
 * piles.length 是 偶数
 * 1 <= piles[i] <= 500
 * sum(piles[i]) 是 奇数
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
  // 可以将石子根据下标的奇偶分成两组
  // 第一轮先手可以选择 A 组或 B 组后，剩下玩家只能选择余下的组
  // 下一轮，先手玩家又可以在两组之间自由选择
  // 根据上述分析可知，作为先手的 Alice 可以在第一次取走石子时就决定取走哪一组的石子，并全程取走同一组的石子。
  // 既然如此，Alice 是否有必胜策略？
  // 答案是肯定的。将石子分成两组之后，可以计算出每一组的石子数量，同时知道哪一组的石子数量更多。
  // Alice 只要选择取走数量更多的一组石子即可。因此，Alice 总是可以赢得比赛。
  bool stoneGame(std::vector<int>& piles) {
    std::vector<std::vector<int>> dp(piles.size(), std::vector<int>(piles.size(), -1));
    std::vector<int> prefix_sums(piles.size() + 1);
    for (int i = 0; i < piles.size(); ++i) {
      dp[i][i] = piles[i];
      prefix_sums[i + 1] = prefix_sums[i] + piles[i];
    }
    // 从小到大枚举左右端点的间距
    for (int i = 1; i < piles.size(); ++i) {
      for (int j = 0; j + i < piles.size(); ++j) {
        // 表示区间 [l, r]
        int l = j;
        int r = j + i;
        dp[l][r] = prefix_sums[r + 1] - prefix_sums[l] - std::min(dp[l][r - 1], dp[l + 1][r]);
      }
    }
    int a = dp[0][piles.size() - 1];
    int b = prefix_sums[piles.size()] - a;
    return a > b;
  }
  bool stoneGameDFS(std::vector<int>& piles) {
    std::vector<std::vector<int>> dp(piles.size(), std::vector<int>(piles.size(), -1));
    int total = std::accumulate(piles.begin(), piles.end(), 0);
    return DFS(piles, 0, piles.size() - 1, total, dp);
  }
  int DFS(std::vector<int>& piles, int l, int r, int total, std::vector<std::vector<int>>& dp) {
    if (l == r) {
      return piles[l];
    }
    if (dp[l][r] >= 0) {
      return dp[l][r];
    }
    int v = DFS(piles, l + 1, r, total - piles[l], dp);
    v = std::min(v, DFS(piles, l, r - 1, total - piles[r], dp));
    dp[l][r] = total - v;
    return total - v;
  }
};
