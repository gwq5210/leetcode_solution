/*
 * @lc app=leetcode.cn id=90 lang=cpp
 *
 * [90] 子集 II
 *
 * https://leetcode.cn/problems/subsets-ii/description/
 *
 * algorithms
 * Medium (63.69%)
 * Likes:    1027
 * Dislikes: 0
 * Total Accepted:    272.9K
 * Total Submissions: 428.6K
 * Testcase Example:  '[1,2,2]'
 *
 * 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
 *
 * 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
 *
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [1,2,2]
 * 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [0]
 * 输出：[[],[0]]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 * -10
 *
 *
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
  // 考虑数组 [1,2,2]，选择前两个数，或者第一、三个数，都会得到相同的子集。
  // 也就是说，对于当前选择的数 x，若前面有与其相同的数 y，且没有选择 y
  // 此时包含 x 的子集，必然会出现在包含 y 的所有子集中。
  // 我们可以通过判断这种情况，来避免生成重复的子集。
  // 代码实现时，可以先将数组排序；迭代时，若发现没有选择上一个数，且当前数字与上一个数相同，则可以跳过当前生成的子集。
  std::vector<std::vector<int>> subsetsWithDup1(std::vector<int>& nums) {
    int count = 1 << nums.size();
    std::vector<std::vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < count; ++i) {
      bool add = true;
      std::vector<int> arr;
      for (int j = 0; j < nums.size(); ++j) {
        if (((i >> j) & 1)) {
          // 当前数字与前一个数字相同，且前一个数字没有选择，则跳过当前生成的子集
          if (j > 0 && (nums[j] == nums[j - 1] && (((i >> (j - 1)) & 1) == 0))) {
            add = false;
            break;
          } else {
            arr.emplace_back(nums[j]);
          }
        }
      }
      if (add) {
        result.emplace_back(std::move(arr));
      }
    }
    return result;
  }
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> arr;
    subsetsWithDupDFS(nums, true, 0, arr, result);
    return result;
  }
  void subsetsWithDupDFS(std::vector<int>& nums, bool prev, int index, std::vector<int>& arr, std::vector<std::vector<int>>& result) {
    if (index >= nums.size()) {
      result.emplace_back(arr);
      return;
    }
    subsetsWithDupDFS(nums, false, index + 1, arr, result);
    if (index > 0 && nums[index] == nums[index - 1] && !prev) {
      return;
    }
    arr.emplace_back(nums[index]);
    subsetsWithDupDFS(nums, true, index + 1, arr, result);
    arr.pop_back();
  }
};