/*
 * @lc app=leetcode.cn id=1330 lang=cpp
 *
 * [1330] 翻转子数组得到最大的数组值
 *
 * https://leetcode.cn/problems/reverse-subarray-to-maximize-array-value/description/
 *
 * algorithms
 * Hard (42.18%)
 * Likes:    72
 * Dislikes: 0
 * Total Accepted:    2K
 * Total Submissions: 4.6K
 * Testcase Example:  '[2,3,1,5,4]'
 *
 * 给你一个整数数组 nums 。「数组值」定义为所有满足 0 <= i < nums.length-1 的 |nums[i]-nums[i+1]|
 * 的和。
 *
 * 你可以选择给定数组的任意子数组，并将该子数组翻转。但你只能执行这个操作 一次 。
 *
 * 请你找到可行的最大 数组值 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：nums = [2,3,1,5,4]
 * 输出：10
 * 解释：通过翻转子数组 [3,1,5] ，数组变成 [2,5,1,3,4] ，数组值为 10 。
 *
 *
 * 示例 2：
 *
 * 输入：nums = [2,4,9,24,2,1,10]
 * 输出：68
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 3*10^4
 * -10^5 <= nums[i] <= 10^5
 *
 *
 */

#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


// i-1, [i, j], j+1
// nums[i-1]-nums[j], nums[j]-nums[j-1], ...
// nums[i+1]-nums[i],nums[i]-nums[j+1]
class Solution {
 public:
  int maxValueAfterReverse(std::vector<int>& nums) {

  }
};