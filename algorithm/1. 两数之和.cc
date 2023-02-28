/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 *
 * https://leetcode.cn/problems/two-sum/description/
 *
 * algorithms
 * Easy (52.88%)
 * Likes:    16435
 * Dislikes: 0
 * Total Accepted:    4.2M
 * Total Submissions: 8M
 * Testcase Example:  '[2,7,11,15]\n9'
 *
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target 
 * 的那 两个 整数，并返回它们的数组下标。
 *
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
 *
 * 你可以按任意顺序返回答案。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [2,7,11,15], target = 9
 * 输出：[0,1]
 * 解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [3,2,4], target = 6
 * 输出：[1,2]
 *
 *
 * 示例 3：
 *
 *
 * 输入：nums = [3,3], target = 6
 * 输出：[0,1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 2 <= nums.length <= 10^4
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= target <= 10^9
 * 只会存在一个有效答案
 *
 *
 *
 *
 * 进阶：你可以想出一个时间复杂度小于 O(n^2) 的算法吗？
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
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    // 这样我们创建一个哈希表，对于每一个 x，我们首先查询哈希表中是否存在 target - x
    // 然后将 x 插入到哈希表中，即可保证不会让 x 和自己匹配。
    std::unordered_map<int, int> idxs;
    for (int i = 0; i < nums.size(); ++i) {
      int x = target - nums[i];
      auto it = idxs.find(x);
      if (it != idxs.end()) {
        return std::vector<int>{i, it->second};
      }
      idxs[nums[i]] = i;
    }
    return std::vector<int>();
  }
  std::vector<int> twoSum2(std::vector<int>& nums, int target) {
    std::unordered_map<int, std::vector<int>> idxs;
    for (int i = 0; i < nums.size(); ++i) {
      idxs[nums[i]].emplace_back(i);
    }
    for (int i = 0; i < nums.size(); ++i) {
      int x = target - nums[i];
      auto it = idxs.find(x);
      if (it != idxs.end() && it->second.size() > 1) {
        for (int j = 0; j < it->second.size(); ++j) {
          if (it->second[j] != i) {
            return std::vector<int>{i, it->second[j]};
          }
        }
      }
    }
    return std::vector<int>();
  }
  std::vector<int> twoSum1(std::vector<int>& nums, int target) {
    std::vector<int> idxs(nums.size());
    std::iota(idxs.begin(), idxs.end(), 0);
    std::sort(idxs.begin(), idxs.end(), [&idxs, &nums](int i, int j) { return nums[i] < nums[j]; });
    // for (int idx : idxs) {
    //   printf("%d ", nums[idx]);
    // }
    // printf("\n");
    int l = 0;
    int r = nums.size() - 1;
    while (l < r) {
      int sum = nums[idxs[l]] + nums[idxs[r]];
      if (sum == target) {
        return std::vector<int>{idxs[l], idxs[r]};
      } else if (sum > target) {
        --r;
      } else {
        ++l;
      }
    }
    return std::vector<int>();
  }
};