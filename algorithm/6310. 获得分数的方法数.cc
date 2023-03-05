/*
 * @lc app=leetcode.cn id=6310 lang=cpp
 *
 * [6310] 获得分数的方法数
 *
 * https://leetcode.cn/problems/number-of-ways-to-earn-points/
 *
考试中有 n 种类型的题目。给你一个整数 target 和一个下标从 0 开始的二维整数数组 types ，其中 types[i] = [counti, marksi]
表示第 i 种类型的题目有 counti 道，每道题目对应 marksi 分。

返回你在考试中恰好得到 target 分的方法数。由于答案可能很大，结果需要对 109 +7 取余。

注意，同类型题目无法区分。

比如说，如果有 3 道同类型题目，那么解答第 1 和第 2 道题目与解答第 1 和第 3 道题目或者第 2 和第 3 道题目是相同的。


示例 1：

输入：target = 6, types = [[6,1],[3,2],[2,3]]
输出：7
解释：要获得 6 分，你可以选择以下七种方法之一：
- 解决 6 道第 0 种类型的题目：1 + 1 + 1 + 1 + 1 + 1 = 6
- 解决 4 道第 0 种类型的题目和 1 道第 1 种类型的题目：1 + 1 + 1 + 1 + 2 = 6
- 解决 2 道第 0 种类型的题目和 2 道第 1 种类型的题目：1 + 1 + 2 + 2 = 6
- 解决 3 道第 0 种类型的题目和 1 道第 2 种类型的题目：1 + 1 + 1 + 3 = 6
- 解决 1 道第 0 种类型的题目、1 道第 1 种类型的题目和 1 道第 2 种类型的题目：1 + 2 + 3 = 6
- 解决 3 道第 1 种类型的题目：2 + 2 + 2 = 6
- 解决 2 道第 2 种类型的题目：3 + 3 = 6
示例 2：

输入：target = 5, types = [[50,1],[50,2],[50,5]]
输出：4
解释：要获得 5 分，你可以选择以下四种方法之一：
- 解决 5 道第 0 种类型的题目：1 + 1 + 1 + 1 + 1 = 5
- 解决 3 道第 0 种类型的题目和 1 道第 1 种类型的题目：1 + 1 + 1 + 2 = 5
- 解决 1 道第 0 种类型的题目和 2 道第 1 种类型的题目：1 + 2 + 2 = 5
- 解决 1 道第 2 种类型的题目：5
示例 3：

输入：target = 18, types = [[6,1],[3,2],[2,3]]
输出：1
解释：只有回答所有题目才能获得 18 分。


提示：

1 <= target <= 1000
n == types.length
1 <= n <= 50
types[i].length == 2
1 <= counti, marksi <= 50
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
  static constexpr int kMod = 1e9 + 7;
  int waysToReachTarget(int target, std::vector<std::vector<int>>& types) {
    int n = types.size();
    std::vector<int> dp(target + 1);
    dp[0] = 1;
    // dp 只依赖上一行，因此使用滚动数组
    // 需要注意枚举的方向需要改变, 需要从大到小枚举j
    // 同时，二维数组的第一列总是 1，也就是dp[0]
    // 因此 dp[0] 可以一直不用计算
    for (int i = 1; i <= types.size(); ++i) {
      int count = types[i - 1][0];
      int marks = types[i - 1][1];
      for (int j = target; j >= 0; --j) {
        for (int k = 1; k <= count && k * marks <= j; ++k) {
          dp[j] = (dp[j] + dp[j - k * marks]) % kMod;
        }
      }
    }
    return dp[target];
  }
  int waysToReachTarget1(int target, std::vector<std::vector<int>>& types) {
    // dp[i][j] 表示 [0,i] 所表示的类型组成分数 j 的方法数
    // 初始条件 dp[0][0] = 1;
    // dp[i][j] = 求和dp[i-1][j-k], j-k>=0, k=0,marks,2*marks,3*marks...
    int n = types.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(target + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= types.size(); ++i) {
      int count = types[i - 1][0];
      int marks = types[i - 1][1];
      for (int j = 0; j <= target; ++j) {
        for (int k = 0; k <= count && k * marks <= j; ++k) {
          dp[i][j] = (dp[i][j] + dp[i - 1][j - k * marks]) % kMod;
        }
      }
    }
    return dp[n][target];
  }
};