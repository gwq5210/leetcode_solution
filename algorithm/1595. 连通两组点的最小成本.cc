/*
 * @lc app=leetcode.cn id=1595 lang=cpp
 *
 * [1595] 连通两组点的最小成本
 *
 * https://leetcode.cn/problems/minimum-cost-to-connect-two-groups-of-points/description/
 *
 * algorithms
 * Hard (50.03%)
 * Likes:    65
 * Dislikes: 0
 * Total Accepted:    2.9K
 * Total Submissions: 5.7K
 * Testcase Example:  '[[15,96],[36,2]]'
 *
 * 给你两组点，其中第一组中有 size1 个点，第二组中有 size2 个点，且 size1 >= size2 。
 *
 * 任意两点间的连接成本 cost 由大小为 size1 x size2 矩阵给出，其中 cost[i][j] 是第一组中的点 i 和第二组中的点 j
 * 的连接成本。如果两个组中的每个点都与另一组中的一个或多个点连接，则称这两组点是连通的。换言之，第一组中的每个点必须至少与第二组中的一个点连接，且第二组中的每个点必须至少与第一组中的一个点连接。
 *
 * 返回连通两组点所需的最小成本。
 *
 *
 *
 * 示例 1：
 *
 *
 *
 * 输入：cost = [[15, 96], [36, 2]]
 * 输出：17
 * 解释：连通两组点的最佳方法是：
 * 1--A
 * 2--B
 * 总成本为 17 。
 *
 *
 * 示例 2：
 *
 *
 *
 * 输入：cost = [[1, 3, 5], [4, 1, 1], [1, 5, 3]]
 * 输出：4
 * 解释：连通两组点的最佳方法是：
 * 1--A
 * 2--B
 * 2--C
 * 3--A
 * 最小成本为 4 。
 * 请注意，虽然有多个点连接到第一组中的点 2 和第二组中的点 A
 * ，但由于题目并不限制连接点的数目，所以只需要关心最低总成本。
 *
 * 示例 3：
 *
 * 输入：cost = [[2, 5, 1], [3, 4, 7], [8, 1, 2], [6, 2, 4], [3, 8, 8]]
 * 输出：10
 *
 *
 *
 *
 * 提示：
 *
 *
 * size1 == cost.length
 * size2 == cost[i].length
 * 1 <= size1, size2 <= 12
 * size1 >= size2
 * 0 <= cost[i][j] <= 100
 *
 *
 */

#include <cstdio>
#include <iterator>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  static constexpr int kInf = std::numeric_limits<int>::max() / 2;
  int connectTwoGroups(std::vector<std::vector<int>>& cost) {
    int m = cost.size();
    int n = cost[0].size();
    int count = 1 << n;
    // dp[i][j] 表示为已选 i 行，列选取情况位掩码为 j 下的最小成本
    // 边界条件是 dp[0][0] = 0;，其他情况取最大值
    // 转移方程如下，其中 m 表示不选择下标为 k 的列，枚举 k 即可
    // dp[i][j] = std::min(dp[i - 1][m], dp[i-1][j]) + cost[i - 1][k];
    // 总得来说，可以使用如下转移方程，x = j | (1 << k);
    // dp[i][x] = std::min(dp[i][x], dp[i - 1][j] + cost[i - 1][k]);
    // 这种情况是第 i 行只能选择一行
    // 对于特定行，如果选了2列，就可以看成只选1列的基础上，再额外加上1列的成本。
    // 类似的选了k列的成本，也就是k-1列的基础上额外加了1列的成本。
    // 这样我们可以在同一行内进行状态转移，只需在原代码的基础上做1处改动即可
    // 即 dp[i][x] 不但可以是 dp[i-1][j]+cost[i-1][k]，也可以是 dp[i-1][j]+cost[i-1][k]。
    // 注意 x 不可能比 j 小，如果 x>j，由于 x 是从小到大枚举的，计算 dp[i][x] 时，dp[i][j]必然是最优的了可以放心转移
    // 如果 x==j，由于矩阵元素不为负，不可能转移到错误的状态。
    std::vector<std::vector<int>> dp(cost.size() + 1, std::vector<int>(count, kInf));
    dp[0][0] = 0;
    for (int i = 1; i <= m; ++i) {
      // 需要从 0 开始枚举，边界条件 0，可以转换到有效状态 x
      for (int j = 0; j < count; ++j) {
        for (int k = 0; k < n; ++k) {
          int x = j | (1 << k);
          dp[i][x] = std::min(dp[i][x], dp[i - 1][j] + cost[i - 1][k]);
          dp[i][x] = std::min(dp[i][x], dp[i][j] + cost[i - 1][k]);
        }
      }
    }
    return dp[m][count - 1];
  }
};