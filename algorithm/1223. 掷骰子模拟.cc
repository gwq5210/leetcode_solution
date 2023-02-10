/*
 * @lc app=leetcode.cn id=1223 lang=cpp
 *
 * [1223] 掷骰子模拟
 *
 * https://leetcode.cn/problems/dice-roll-simulation/description/
 *
 * algorithms
 * Hard (49.64%)
 * Likes:    154
 * Dislikes: 0
 * Total Accepted:    9.3K
 * Total Submissions: 15.9K
 * Testcase Example:  '2\n[1,1,2,2,2,3]'
 *
 * 有一个骰子模拟器会每次投掷的时候生成一个 1 到 6 的随机数。
 *
 * 不过我们在使用它时有个约束，就是使得投掷骰子时，连续 掷出数字 i 的次数不能超过 rollMax[i]（i 从 1 开始编号）。
 *
 * 现在，给你一个整数数组 rollMax 和一个整数 n，请你来计算掷 n 次骰子可得到的不同点数序列的数量。
 *
 * 假如两个序列中至少存在一个元素不同，就认为这两个序列是不同的。由于答案可能很大，所以请返回 模 10^9 + 7 之后的结果。
 *
 *
 *
 * 示例 1：
 *
 * 输入：n = 2, rollMax = [1,1,2,2,2,3]
 * 输出：34
 * 解释：我们掷 2 次骰子，如果没有约束的话，共有 6 * 6 = 36 种可能的组合。但是根据 rollMax 数组，数字 1 和 2
 * 最多连续出现一次，所以不会出现序列 (1,1) 和 (2,2)。因此，最终答案是 36-2 = 34。
 *
 *
 * 示例 2：
 *
 * 输入：n = 2, rollMax = [1,1,1,1,1,1]
 * 输出：30
 *
 *
 * 示例 3：
 *
 * 输入：n = 3, rollMax = [1,1,1,2,2,3]
 * 输出：181
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 5000
 * rollMax.length == 6
 * 1 <= rollMax[i] <= 15
 *
 *
 */

#include <cstdio>
#include <vector>

class Solution {
 public:
  static constexpr int kMod = 1e9 + 7;
  int dieSimulator1(int n, std::vector<int>& roll_max) {
    std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(6, std::vector<int>(16)));
    for (int i = 0; i < 6; ++i) {
      dp[0][i][1] = 1;
    }
    for (int i = 1; i < n; ++i) {                 // 第i次扔骰子
      for (int j = 0; j < 6; ++j) {               // 出现的点数为j
        for (int k = 1; k <= roll_max[j]; ++k) {  // j已经连续出现k次
          if (k == 1) {
            for (int x = 0; x < 6; ++x) {
              if (x == j) {
                continue;
              }
              for (int m = 1; m <= roll_max[x]; ++m) {
                dp[i][j][k] = (dp[i][j][k] + dp[i - 1][x][m]) % kMod;
              }
            }
          } else {
            dp[i][j][k] = dp[i - 1][j][k - 1] % kMod;
          }
        }
      }
    }
    int result = 0;
    for (int i = 0; i < 6; ++i) {
      for (int j = 1; j <= roll_max[i]; ++j) {
        result = (result + dp[n - 1][i][j]) % kMod;
      }
    }
    return result;
  }

  int dieSimulator(int n, std::vector<int>& roll_max) {
    std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(6, std::vector<int>(16)));
    for (int i = 0; i < 6; ++i) {
      dp[0][i][1] = 1;
    }
    for (int i = 1; i < n; ++i) {      // 第i次扔骰子
      for (int j = 0; j < 6; ++j) {    // 出现的点数为j
        for (int x = 0; x < 6; ++x) {  // 第i-1次出现x
          for (int k = 1; k <= roll_max[x]; ++k) {
            if (x != j) {
              dp[i][j][1] = (dp[i][j][1] + dp[i - 1][x][k]) % kMod;
            } else if (k - 1 >= 1) {
              dp[i][j][k] = dp[i - 1][j][k - 1] % kMod;
            }
          }
        }
      }
    }
    int result = 0;
    for (int i = 0; i < 6; ++i) {
      for (int j = 1; j <= roll_max[i]; ++j) {
        result = (result + dp[n - 1][i][j]) % kMod;
      }
    }
    return result;
  }
};
