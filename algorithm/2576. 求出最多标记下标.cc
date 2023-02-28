/*
 * @lc app=leetcode.cn id=2576 lang=cpp
 *
 * [2576] 求出最多标记下标
 *
 * https://leetcode.cn/problems/find-the-maximum-number-of-marked-indices/description/
 *
给你一个下标从 0 开始的整数数组 nums 。

一开始，所有下标都没有被标记。你可以执行以下操作任意次：

选择两个 互不相同且未标记 的下标 i 和 j ，满足 2 * nums[i] <= nums[j] ，标记下标 i 和 j 。
请你执行上述操作任意次，返回 nums 中最多可以标记的下标数目。



示例 1：

输入：nums = [3,5,2,4]
输出：2
解释：第一次操作中，选择 i = 2 和 j = 1 ，操作可以执行的原因是 2 * nums[2] <= nums[1] ，标记下标 2 和 1 。
没有其他更多可执行的操作，所以答案为 2 。
示例 2：

输入：nums = [9,2,5,4]
输出：4
解释：第一次操作中，选择 i = 3 和 j = 0 ，操作可以执行的原因是 2 * nums[3] <= nums[0] ，标记下标 3 和 0 。
第二次操作中，选择 i = 1 和 j = 2 ，操作可以执行的原因是 2 * nums[1] <= nums[2] ，标记下标 1 和 2 。
没有其他更多可执行的操作，所以答案为 4 。
示例 3：

输入：nums = [7,6,8]
输出：0
解释：没有任何可以执行的操作，所以答案为 0 。


提示：

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
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
  // 如果 2 * nums[i] <= nums[j]，则称 nums[i] 和 nums[j] 匹配。
  // 如果可以匹配 k 对，那么也可以匹配小于 k 对，去掉一些数对即可做到。
  // 如果无法匹配 k 对，那么也无法匹配大于 k 对（反证法）。
  // 因此答案有单调性，可以二分。
  // 如何检测能否匹配 k 对
  // nums[i] 越小越好，nums[j] 越大越好
  // 所以只需要看最小的 k 个数和最大的 k 个数能否匹配。
  // 从小到大排序后，nums[0] 肯定要匹配 nums[n−k]。
  // 如果不这样做，nums[0] 匹配了在 nums[n−k] 右侧的数，相当于占了一个位置
  // 那么一定有个更大的 nums[i] 要匹配 nums[n−k]，这不一定能匹配上
  // 所以 nums[i] 一定要匹配 nums[n−k+i]。
  // 如果对于所有的 0<=i<k 都有 2*nums[i]<=nums[n−k+i]，那么可以匹配 k 对。
  // 我们使用二分来确定最大的 k
  int maxNumOfMarkedIndices1(std::vector<int>& nums) {
    int l = 1;
    int r = nums.size() / 2;
    std::sort(nums.begin(), nums.end());
    while (l <= r) {
      int mid = l + (r - l) / 2;
      bool flag = true;
      for (int i = 0; i < mid; ++i) {
        if (nums[i] * 2 > nums[nums.size() - mid + i]) {
          flag = false;
          break;
        }
      }
      if (flag) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return 2 * (l - 1);
  }
  int maxNumOfMarkedIndices(std::vector<int>& nums) {
    // 从方法一可以知道，我们需要用左半部分的数，去匹配右半部分的数。
    // 从右半部分中，找到第一个满足 2*nums[0]<=nums[j] 的 j，那么 nums[1] 只能匹配下标大于 j 的数，依此类推。
    // 这可以用双指针实现。
    std::sort(nums.begin(), nums.end());
    int res = 0;
    int l = 0;
    int r = (nums.size() + 1) / 2;
    auto it = std::lower_bound(nums.begin() + r, nums.end(), 2 * nums[0]);
    r = std::distance(nums.begin(), it);
    while (r < nums.size()) {
      if (2 * nums[l] <= nums[r]) {
        ++l;
        ++r;
        ++res;
      } else {
        ++r;
      }
    }
    return 2 * res;
  }
};