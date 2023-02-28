/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 *
 * https://leetcode.cn/problems/kth-largest-element-in-an-array/description/
 *
 * algorithms
 * Medium (64.05%)
 * Likes:    2071
 * Dislikes: 0
 * Total Accepted:    813.9K
 * Total Submissions: 1.3M
 * Testcase Example:  '[3,2,1,5,6,4]\n2'
 *
 * 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
 *
 * 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 *
 * 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: [3,2,1,5,6,4], k = 2
 * 输出: 5
 *
 *
 * 示例 2:
 *
 *
 * 输入: [3,2,3,1,2,4,5,5,6], k = 4
 * 输出: 4
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= k <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 *
 *
 */

#include <algorithm>
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
  int Partition2(std::vector<int>& nums, int l, int r) {
    int k = nums[l];
    --r;
    while (l < r) {
      while (l < r && nums[r] >= k) {
        --r;
      }
      nums[l] = nums[r];
      while (l < r && nums[l] <= k) {
        ++l;
      }
      nums[r] = nums[l];
    }
    nums[l] = k;
    return l;
  }
  // 7, 5, 2, 3, 1
  // 5, 7, 2, 3, 1
  // 5, 2, 7, 3, 1
  // 5, 2, 3, 7, 1
  // 5, 2, 3, 1, 7
  int Partition(std::vector<int>& nums, int l, int r) {
    int k = nums[l];
    int x = l;
    for (int i = l; i < r; ++i) {
      if (nums[i] <= k) {
        std::swap(nums[i], nums[x]);
        ++x;
      }
    }
    std::swap(nums[x - 1], nums[l]);
    // printf("partition l %d, r %d, k %d\n", l, r, k);
    // for (int i = l; i < r; ++i) {
    //   printf("%d,", nums[i]);
    // }
    // printf("\n");
    // printf("res = %d\n", x - 1);
    return x - 1;
  }
  int findKthLargest(std::vector<int>& nums, int k) {
    int target_index = nums.size() - k;
    int l = 0;
    int r = nums.size();
    while (l < r) {
      // int mid = Partition(nums, l, r);
      int mid = Partition2(nums, l, r);
      if (mid == target_index) {
        return nums[mid];
      } else if (mid < target_index) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return nums[l];
  }
};