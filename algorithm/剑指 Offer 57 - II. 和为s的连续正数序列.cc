/*
 * @lc app=leetcode.cn id= lang=cpp
 *
 * 剑指 Offer 60. n个骰子的点数
 *
 * https://leetcode.cn/problems/nge-tou-zi-de-dian-shu-lcof/
 *
输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。

序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。



示例 1：

输入：target = 9
输出：[[2,3,4],[4,5]]
示例 2：

输入：target = 15
输出：[[1,2,3,4,5],[4,5,6],[7,8]]


限制：

1 <= target <= 10^5
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
  std::vector<std::vector<int>> findContinuousSequence(int target) {
    std::vector<std::vector<int>> result;
    int sum = 3;
    int l = 1;
    int r = 2;
    while (l <= target / 2) {
      if (sum == target) {
        result.emplace_back(std::vector<int>(r - l + 1));
        std::iota(result.back().begin(), result.back().end(), l);
        sum -= l;
        ++l;
      } else if (sum < target) {
        ++r;
        sum += r;
      } else {
        sum -= l;
        ++l;
      }
    }
    return result;
  }
};