/*
 * @lc app=leetcode.cn id= lang=cpp
 *
 * 剑指 Offer 60. n个骰子的点数
 *
 * https://leetcode.cn/problems/nge-tou-zi-de-dian-shu-lcof/
 *
把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。



你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。



示例 1:

输入: 1
输出: [0.16667,0.16667,0.16667,0.16667,0.16667,0.16667]
示例 2:

输入: 2
输出: [0.02778,0.05556,0.08333,0.11111,0.13889,0.16667,0.13889,0.11111,0.08333,0.05556,0.02778]


限制：

1 <= n <= 11
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
  std::vector<double> dicesProbability(int n) {
    std::vector<double> result;
    // dp[i][j] 第 i 次仍骰子得到和为 j 的数目
    // dp[i][j] = dp[i-1][j-k] + k (1<=k<=6)
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(67, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
      for (int j = i; j <= 6 * i; ++j) {
        for (int k = 1; k <= 6 && j - k >= 0; ++k) {
          dp[i][j] += dp[i - 1][j - k];
        }
      }
    }
    double total = 1;
    for (int i = 1; i <= n; ++i) {
      total *= 6;
    }
    for (int i = n; i <= 6 * n; ++i) {
      result.emplace_back(dp[n][i] / total);
    }
    return result;
  }
};