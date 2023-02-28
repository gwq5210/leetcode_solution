/*
 * @lc app=leetcode.cn id=15 lang=cpp
 *
 * [15] 三数之和
 *
 * https://leetcode.cn/problems/3sum/description/
 *
 * algorithms
 * Medium (36.76%)
 * Likes:    5682
 * Dislikes: 0
 * Total Accepted:    1.3M
 * Total Submissions: 3.5M
 * Testcase Example:  '[-1,0,1,2,-1,-4]'
 *
 * 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j !=
 * k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请
 *
 * 你返回所有和为 0 且不重复的三元组。
 *
 * 注意：答案中不可以包含重复的三元组。
 *
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [-1,0,1,2,-1,-4]
 * 输出：[[-1,-1,2],[-1,0,1]]
 * 解释：
 * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
 * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
 * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
 * 不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
 * 注意，输出的顺序和三元组的顺序并不重要。
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [0,1,1]
 * 输出：[]
 * 解释：唯一可能的三元组和不为 0 。
 *
 *
 * 示例 3：
 *
 *
 * 输入：nums = [0,0,0]
 * 输出：[[0,0,0]]
 * 解释：唯一可能的三元组和为 0 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 3 <= nums.length <= 3000
 * -10^5 <= nums[i] <= 10^5
 *
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
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> result;
    for (int i = 0; i < nums.size(); ++i) {
      // 需要和上一次枚举的数不相同
      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }
      int target = -nums[i];
      // 枚举 b 所在的指针
      int l = i + 1;
      // 枚举 c 所在的指针
      int r = nums.size() - 1;
      while (l < r) {
        // 需要和上一次枚举的数不相同
        // 这一个保证了 c 也不会枚举到相同的数
        if (l > i + 1 && nums[l] == nums[l - 1]) {
          ++l;
          continue;
        } else if (nums[l] + nums[r] == target) {
          // 和相等就记录答案，同时移动 l 和 r
          result.emplace_back(std::vector<int>{nums[i], nums[l], nums[r]});
          ++l;
          --r;
        } else if (nums[l] + nums[r] < target) {
          // 和较小的话移动 l 使得和变大
          ++l;
        } else {
          // 和较大的话移动 r 使得和变小
          --r;
        }
      }
    }
    return result;
  }
  std::vector<std::vector<int>> threeSum1(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::sort(nums.begin(), nums.end());
    std::unordered_map<int, std::vector<int>> stats;
    for (int i = 0; i < nums.size(); ++i) {
      stats[nums[i]].emplace_back(i);
    }

    // 枚举第一个数字
    for (int i = 0; i < nums.size() - 2; ++i) {
      // 去掉重复的数字
      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }
      int a = nums[i];
      // 枚举第二个数字
      for (int j = i + 1; j < nums.size() - 1; ++j) {
        // 去掉重复的数字
        if (j > i + 1 && nums[j] == nums[j - 1]) {
          continue;
        }
        int b = nums[j];
        // 如果已经大于0，则直接 break
        if (a + b > 0) {
          break;
        }
        // 使用哈希表查找，是否可以找到一个下标满足要求
        auto it = stats.find(-a - b);
        if (it != stats.end() && it->second.back() >= j + 1) {
          result.emplace_back(std::vector<int>{a, b, -a - b});
        }
      }
    }
    return result;
  }
};