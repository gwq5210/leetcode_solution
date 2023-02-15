/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 *
 * https://leetcode.cn/problems/sliding-window-maximum/description/
 *
 * algorithms
 * Hard (49.91%)
 * Likes:    2111
 * Dislikes: 0
 * Total Accepted:    400.2K
 * Total Submissions: 801.7K
 * Testcase Example:  '[1,3,-1,-3,5,3,6,7]\n3'
 *
 * 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k
 * 个数字。滑动窗口每次只向右移动一位。
 *
 * 返回 滑动窗口中的最大值 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
 * 输出：[3,3,5,5,6,7]
 * 解释：
 * 滑动窗口的位置                最大值
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       3
 * ⁠1 [3  -1  -3] 5  3  6  7       3
 * ⁠1  3 [-1  -3  5] 3  6  7       5
 * ⁠1  3  -1 [-3  5  3] 6  7       5
 * ⁠1  3  -1  -3 [5  3  6] 7       6
 * ⁠1  3  -1  -3  5 [3  6  7]      7
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [1], k = 1
 * 输出：[1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 1 <= k <= nums.length
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
  std::vector<int> maxSlidingWindowDQ(std::vector<int>& nums, int k) {
    // 如果i<j, nums[i] <= nums[j], 则nums[i]永远不会成为最大值
    // 因此可能的最大值是一个严格递减的序列
    int n = nums.size();
    std::deque<int> s;
    std::vector<int> result;
    for (int i = 0; i < n; ++i) {
      while (!s.empty() && nums[i] >= nums[s.front()]) {
        s.pop_front();
      }
      s.push_front(i);
      if (i >= k - 1) {
        while (!s.empty() && s.back() < i + 1 - k) {
          s.pop_back();
        }
        result.emplace_back(nums[s.back()]);
      }
    }
    return result;
  }
  std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) { return maxSlidingWindowPQ(nums, k); }
  std::vector<int> maxSlidingWindowPQ(std::vector<int>& nums, int k) {
    int n = nums.size();
    std::priority_queue<std::pair<int, int>> pq;
    std::vector<int> result;
    for (int i = 0; i < n; ++i) {
      pq.push(std::make_pair(nums[i], i));
      if (i >= k - 1) {
        while (pq.top().second < i + 1 - k) {
          pq.pop();
        }
        result.emplace_back(pq.top().first);
      }
    }
    return result;
  }
};