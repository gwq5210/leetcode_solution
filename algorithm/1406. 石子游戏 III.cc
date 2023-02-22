/*
 * @lc app=leetcode.cn id=1406 lang=cpp
 *
 * [1406] 石子游戏 III
 *
 * https://leetcode.cn/problems/stone-game-iii/description/
 *
 * algorithms
 * Hard (59.05%)
 * Likes:    104
 * Dislikes: 0
 * Total Accepted:    7.3K
 * Total Submissions: 12.4K
 * Testcase Example:  '[1,2,3,7]'
 *
 * Alice 和 Bob 用几堆石子在做游戏。几堆石子排成一行，每堆石子都对应一个得分，由数组 stoneValue 给出。
 *
 * Alice 和 Bob 轮流取石子，Alice 总是先开始。在每个玩家的回合中，该玩家可以拿走剩下石子中的的前 1、2 或 3 堆石子
 * 。比赛一直持续到所有石头都被拿走。
 *
 * 每个玩家的最终得分为他所拿到的每堆石子的对应得分之和。每个玩家的初始分数都是 0
 * 。比赛的目标是决出最高分，得分最高的选手将会赢得比赛，比赛也可能会出现平局。
 *
 * 假设 Alice 和 Bob 都采取 最优策略 。如果 Alice 赢了就返回 "Alice" ，Bob 赢了就返回 "Bob"，平局（分数相同）返回
 * "Tie" 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：values = [1,2,3,7]
 * 输出："Bob"
 * 解释：Alice 总是会输，她的最佳选择是拿走前三堆，得分变成 6 。但是 Bob 的得分为 7，Bob 获胜。
 *
 *
 * 示例 2：
 *
 * 输入：values = [1,2,3,-9]
 * 输出："Alice"
 * 解释：Alice 要想获胜就必须在第一个回合拿走前三堆石子，给 Bob 留下负分。
 * 如果 Alice 只拿走第一堆，那么她的得分为 1，接下来 Bob 拿走第二、三堆，得分为 5 。之后 Alice 只能拿到分数 -9
 * 的石子堆，输掉比赛。
 * 如果 Alice 拿走前两堆，那么她的得分为 3，接下来 Bob 拿走第三堆，得分为 3 。之后 Alice 只能拿到分数 -9
 * 的石子堆，同样会输掉比赛。
 * 注意，他们都应该采取 最优策略 ，所以在这里 Alice 将选择能够使她获胜的方案。
 *
 * 示例 3：
 *
 * 输入：values = [1,2,3,6]
 * 输出："Tie"
 * 解释：Alice 无法赢得比赛。如果她决定选择前三堆，她可以以平局结束比赛，否则她就会输。
 *
 *
 * 示例 4：
 *
 * 输入：values = [1,2,3,-1,-2,-3,7]
 * 输出："Alice"
 *
 *
 * 示例 5：
 *
 * 输入：values = [-1,-2,-3]
 * 输出："Tie"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= values.length <= 50000
 * -1000 <= values[i] <= 1000
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
  std::string stoneGameIII(std::vector<int>& stoneValue) {
    std::vector<std::vector<int>> dp(stoneValue.size(), std::vector<int>(4, -kInf));
    int total = std::accumulate(stoneValue.begin(), stoneValue.end(), 0);
    int a = DFS(stoneValue, 0, 3, total, dp);
    int b = total - a;
    return a > b ? "Alice" : a < b ? "Bob" : "Tie";
  }
  int DFS(const std::vector<int>& stoneValue, int index, int count, int total, std::vector<std::vector<int>>& dp) {
    // 注意处理负数的情况
    if (index >= stoneValue.size()) {
      return total;
    }
    if (dp[index][count] != -kInf) {
      return dp[index][count];
    }
    int v = kInf;
    int c = 0;
    for (int i = 1; i <= count && index + i <= stoneValue.size(); ++i) {
      c += stoneValue[index + i - 1];
      v = std::min(v, DFS(stoneValue, index + i, 3, total - c, dp));
    }
    dp[index][count] = total - v;
    return total - v;
  }
};
