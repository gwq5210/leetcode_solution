/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 *
 * https://leetcode.cn/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (41.66%)
 * Likes:    6303
 * Dislikes: 0
 * Total Accepted:    896K
 * Total Submissions: 2.2M
 * Testcase Example:  '[1,3]\n[2]'
 *
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
 *
 * 算法的时间复杂度应该为 O(log (m+n)) 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums1 = [1,3], nums2 = [2]
 * 输出：2.00000
 * 解释：合并数组 = [1,2,3] ，中位数 2
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums1 = [1,2], nums2 = [3,4]
 * 输出：2.50000
 * 解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 *
 *
 *
 *
 *
 *
 * 提示：
 *
 *
 * nums1.length == m
 * nums2.length == n
 * 0 <= m <= 1000
 * 0 <= n <= 1000
 * 1 <= m + n <= 2000
 * -10^6 <= nums1[i], nums2[i] <= 10^6
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
  static constexpr int kInf = std::numeric_limits<int>::max();
  // 1,2,3
  // 1,2,3,4
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
      return findMedianSortedArrays(nums2, nums1);
    }
    // 元素总数
    int n = nums1.size() + nums2.size();
    // 前半部分数的数量
    int target_count = (n + 1) / 2;
    // 前半部分数的最大值和后半部分数的最小值
    int left_max = 0;
    int right_min = 0;
    // 枚举 nums1 的区间下标，其取值范围是 [-1, nums1.size())
    // 取值 -1 表示前半部分数全部在 nums2 中
    // 取值 nums1.size()-1 表示前半部分数全部在 nums1 中
    int l = -1;
    int r = nums1.size();
    while (l <= r) {
      // [0, mid] 和 [0, rmid] 组成的 target_count 个数是否满足要求
      int mid = l + (r - l) / 2;
      int rmid = target_count - (mid + 1) - 1;
      // l_max1 分别 l_max2 表示 nums1 和 nums2 前半部分的最大值
      // 边界条件时取 -kInf
      int l_max1 = mid >= 0 ? nums1[mid] : -kInf;
      int l_max2 = rmid >= 0 ? nums2[rmid] : -kInf;
      // r_min1 分别 r_min2 表示 nums1 和 nums2 后半部分的最小值
      // 边界条件时取 kInf
      int r_min1 = mid + 1 < nums1.size() ? nums1[mid + 1] : kInf;
      int r_min2 = rmid + 1 < nums2.size() ? nums2[rmid + 1] : kInf;
      // 已经满足要求，则直接返回结果即可
      // 因为数组 nums1 和 nums2 递增，则一定有 l_max1 <= r_min1, l_max2 <= r_min2
      if (l_max1 <= r_min2 && l_max2 <= r_min1) {
        left_max = std::max(l_max1, l_max2);
        right_min = std::min(r_min1, r_min2);
        break;
      // 如果 l_max1 > r_min2，则满足要求的下标一定在 [l, mid) 之间
      } else if (l_max1 > r_min2) {
        r = mid;
      // 如果 l_max2 > r_min1，则满足要求的下标一定在 [mid+1, r) 之间
      } else {
        l = mid + 1;
      }
    }
    // 分别针对元素总数为奇数或偶数进行处理
    double res = left_max;
    if (n % 2 == 0) {
      res = (res + right_min) / 2.0;
    }
    return res;
  }
  // 1,2,3
  // 1,2,3,4
  double findMedianSortedArrays2(std::vector<int>& nums1, std::vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
      return findMedianSortedArrays(nums2, nums1);
    }
    // 元素总数
    int n = nums1.size() + nums2.size();
    // 前半部分数的数量
    int target_count = (n + 1) / 2;
    // 表示 [0, res_l1], [0, res_l2] 组成的区间包含 target_count 数量的数
    // 并且且小于或等于区间 [res_l1+1, nums1.size()), [res_l2+1, nums2.size()) 中的数
    int res_l1 = -1;
    int res_l2 = -1;
    // 枚举 nums1 的区间下标，其取值范围是 [-1, nums1.size())
    // 取值 -1 表示前半部分数全部在 nums2 中
    // 取值 nums1.size()-1 表示前半部分数全部在 nums1 中
    int l = -1;
    int r = nums1.size();
    while (l <= r) {
      // [0, mid] 和 [0, rmid] 组成的 target_count 个数是否满足要求
      int mid = l + (r - l) / 2;
      int rmid = target_count - (mid + 1) - 1;
      // l_max1 分别 l_max2 表示 nums1 和 nums2 前半部分的最大值
      // 边界条件时取 -kInf
      int l_max1 = mid >= 0 ? nums1[mid] : -kInf;
      int l_max2 = rmid >= 0 ? nums2[rmid] : -kInf;
      // r_min1 分别 r_min2 表示 nums1 和 nums2 后半部分的最小值
      // 边界条件时取 kInf
      int r_min1 = mid + 1 < nums1.size() ? nums1[mid + 1] : kInf;
      int r_min2 = rmid + 1 < nums2.size() ? nums2[rmid + 1] : kInf;
      // 已经满足要求，则直接返回结果即可
      // 因为数组 nums1 和 nums2 递增，则一定有 l_max1 <= r_min1, l_max2 <= r_min2
      if (l_max1 <= r_min2 && l_max2 <= r_min1) {
        res_l1 = mid;
        res_l2 = rmid;
        break;
      // 如果 l_max1 > r_min2，则满足要求的下标一定在 [l, mid) 之间
      } else if (l_max1 > r_min2) {
        r = mid;
      // 如果 l_max2 > r_min1，则满足要求的下标一定在 [mid+1, r) 之间
      } else {
        l = mid + 1;
      }
    }
    // 分别针对元素总数为奇数或偶数进行处理
    int l_max1 = res_l1 >= 0 ? nums1[res_l1] : -kInf;
    int l_max2 = res_l2 >= 0 ? nums2[res_l2] : -kInf;
    double res = std::max(l_max1, l_max2);
    if (n % 2 == 0) {
      int r_min1 = res_l1 + 1 < nums1.size() ? nums1[res_l1 + 1] : kInf;
      int r_min2 = res_l2 + 1 < nums2.size() ? nums2[res_l2 + 1] : kInf;
      res = (res + std::min(r_min1, r_min2)) / 2.0;
    }
    return res;
  }
  // 1,2,3
  // 1,2,3,4
  double findMedianSortedArrays1(std::vector<int>& nums1, std::vector<int>& nums2) {
    int n = nums1.size() + nums2.size();
    int count = n / 2 + 1;
    int prev = 0;
    int curr = 0;
    int l = 0;
    int r = 0;
    while (count--) {
      prev = curr;
      if (r >= nums2.size() || (l < nums1.size() && nums1[l] <= nums2[r])) {
        curr = nums1[l++];
      } else {
        curr = nums2[r++];
      }
    }
    double res = curr;
    if (n % 2 == 0) {
      res = (res + prev) / 2.0;
    }
    return res;
  }
};