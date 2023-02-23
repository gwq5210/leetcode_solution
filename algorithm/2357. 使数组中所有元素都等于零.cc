/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [2357] 使数组中所有元素都等于零
 *
 * https://leetcode.cn/problems/make-array-zero-by-subtracting-equal-amounts/description/
 *
给你一个非负整数数组 nums 。在一步操作中，你必须：

选出一个正整数 x ，x 需要小于或等于 nums 中 最小 的 非零 元素。
nums 中的每个正整数都减去 x。
返回使 nums 中所有元素都等于 0 需要的 最少 操作数。



示例 1：

输入：nums = [1,5,0,3,5]
输出：3
解释：
第一步操作：选出 x = 1 ，之后 nums = [0,4,0,2,4] 。
第二步操作：选出 x = 2 ，之后 nums = [0,2,0,0,2] 。
第三步操作：选出 x = 2 ，之后 nums = [0,0,0,0,0] 。
示例 2：

输入：nums = [0]
输出：0
解释：nums 中的每个元素都已经是 0 ，所以不需要执行任何操作。


提示：

1 <= nums.length <= 100
0 <= nums[i] <= 100
 *
 *
 */

#include <deque>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  // 每次减少一个最小值，相当于每次把最小值去掉，所有数的不同个数就是最小的操作次数
  // 注意只需要统计大于 0 的个数
  int minimumOperations(std::vector<int>& nums) {
    std::unordered_set<int> stats;
    for (int num : nums) {
      if (num > 0) {
        stats.emplace(num);
      }
    }
    return stats.size();
  }
  // 模拟
  int minimumOperations2(std::vector<int>& nums) {
    int res = 0;
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    while (sum > 0) {
      int min_v = 101;
      int count = 0;
      for (int num : nums) {
        if (num > 0) {
          min_v = std::min(min_v, num);
          ++count;
        }
      }
      for (int& num : nums) {
        if (num > 0) {
          num -= min_v;
        }
      }
      sum -= count * min_v;
      ++res;
    }
    return res;
  }
};