/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
 *
 * https://leetcode-cn.com/problems/longest-increasing-subsequence/description/
 *
 * algorithms
 * Medium (51.73%)
 * Likes:    3009
 * Dislikes: 0
 * Total Accepted:    678.2K
 * Total Submissions: 1.2M
 * Testcase Example:  '[10,9,2,5,3,7,101,18]'
 *
 * 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
 *
 * 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组
 * [0,3,1,6,2,2,7] 的子序列。
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [10,9,2,5,3,7,101,18]
 * 输出：4
 * 解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [0,1,0,3,2,3]
 * 输出：4
 *
 *
 * 示例 3：
 *
 *
 * 输入：nums = [7,7,7,7,7,7,7]
 * 输出：1
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 2500
 * -10^4 <= nums[i] <= 10^4
 *
 *
 *
 *
 * 进阶：
 *
 *
 * 你能将算法的时间复杂度降低到 O(n log(n)) 吗?
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
  static constexpr int kInf = std::numeric_limits<int>::max() / 2;
  int lengthOfLIS(std::vector<int>& nums) {
    // dp[i] 表示长度为 i+1 的子序列的尾部元素的最小值
    // 同时我们可以注意到 d[i] 是关于 i 单调递增的。因为如果 d[j]>=d[i] 且 j<i
    // 我们考虑从长度为 i 的最长上升子序列的末尾删除 i−j 个元素，那么这个序列长度变为 j ，且第 j 个元素
    // x（末尾元素）必然小于 d[i]，也就小于 d[j]。那么我们就找到了一个长度为 j
    // 的最长上升子序列，并且末尾元素比 d[j] 小，从而产生了矛盾。因此数组 d 的单调性得证。
    std::vector<int> dp(nums.size());
    int res = 1;
    dp[0] = nums[0];
    // 针对后续每个元素，我们寻找最大的下标 i 使得 dp[i] >= nums[j]，同时更新 dp[i] = nums[i]
    // 当 dp[i] >= nums[j] 时，必然有 dp[i - 1] < nums[j]，则可以将 nums[j] 放在 dp[i - 1] 后
    // 则当前的以 nums[j] 结尾的最长递增子序列长度为 i+1
    // 同时，由于 dp[i] >= nums[j]，则用 nums[j] 当做长度为 i+1 的结尾更优，因此使用 nums[j] 更新 dp[i]
    for (int i = 1; i < nums.size(); ++i) {
      // 这里其实是求 lower_bound
      // int l = 0;
      // int r = i;
      // while (l < r) {
      //   int mid = l + (r - l) / 2;
      //   if (dp[mid] < nums[i]) {
      //     l = mid + 1;
      //   } else {
      //     r = mid;
      //   }
      // }
      auto it = std::lower_bound(dp.begin(), dp.end() + i, nums[i]);
      int l = std::distance(dp.begin(), it);
      res = std::max(res, l + 1);
      dp[l] = nums[i];
    }
    return res;
  }
  int lengthOfLIS2(std::vector<int>& nums) {
    // dp[i] 表示以 nums[i] 结尾的最长递增子序列的长度
    std::vector<int> dp(nums.size());
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
      int index = -1;
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j] && (index == -1 || dp[j] > dp[index])) {
          index = j;
        }
      }
      dp[i] = 1;
      if (index >= 0) {
        dp[i] += dp[index];
      }
      res = std::max(res, dp[i]);
    }
    return res;
  }
};