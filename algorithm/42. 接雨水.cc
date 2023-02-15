/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 *
 * https://leetcode-cn.com/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (58.29%)
 * Likes:    2823
 * Dislikes: 0
 * Total Accepted:    343.8K
 * Total Submissions: 587.8K
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]'
 *
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 *
 *
 *
 * 示例 1：
 *
 *
 *
 *
 * 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * 输出：6
 * 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。
 *
 *
 * 示例 2：
 *
 *
 * 输入：height = [4,2,0,3,2,5]
 * 输出：9
 *
 *
 *
 *
 * 提示：
 *
 *
 * n == height.length
 * 1 <= n <= 2 * 10^4
 * 0 <= height[i] <= 10^5
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
  int trap1(std::vector<int>& height) {
    int n = height.size();
    if (n <= 2) {
      return 0;
    }
    std::vector<int> rmax(n + 1);
    for (int i = n - 1; i >= 0; --i) {
      rmax[i] = std::max(rmax[i + 1], height[i]);
    }
    int left_max = height[0];
    int res = 0;
    // 当前能够接到的雨水和左侧元素的最大值与右侧元素的最大值两者的最小值有关系
    // 可以预先求出左侧元素和右侧元素的最大值，依次遍历即可得到答案
    // 从左到右遍历，左侧的最大值可以边遍历，边求出，因此只需要预先求出右侧元素的最大值即可
    for (int i = 1; i < n - 1; ++i) {
      int x = std::min(left_max, rmax[i + 1]);
      if (x > height[i]) {
        res += x - height[i];
      }
      left_max = std::max(left_max, height[i]);
    }
    return res;
  }

  int trap(std::vector<int>& height) {
    int n = height.size();
    if (n <= 2) {
      return 0;
    }

    int l = 0;
    int r = height.size() - 1;
    int left_max = height[0];
    int right_max = height[r];
    int res = 0;
    // 上述解法中rmax数组中的每个元素都只使用了一次，可以尝试将其进行优化
    // 由于rmax数组是从右往左进行遍历，则需要用到两个指针，l 和 r，从两个方向去遍历。
    // 重要的是判断是从左侧进行遍历还是右侧进行遍历
    // left从左向右遍历，right从右向左遍历；
    // 则对left来说，left_max一定准确，right_max不一定准确
    // 因为区间（left, right）的值还没有遍历
    // 但是left的right_max一定 >= right的right_max
    // 所以只要 left_max < right_max时，我们不关心 left 的 right_max 是多少了
    // 因为它肯定比 left_max 大，我们可以直接计算出left的存水量 left_max - nums[left];
    // 对right来说，right_max一定准确，left_max不一定准确
    // 因为区间（left, right）的值还没有遍历，但是right的left_max一定 >= left的left_max
    // 所以只要left_max >= right_max时，我们不关心 right 的 left_max 是多少了
    // 因为它肯定比right_max大，我们可以直接计算出right的存水量right_max - nums[right];
    while (l <= r) {
      left_max = std::max(left_max, height[l]);
      right_max = std::max(right_max, height[r]);
      // height[left] < height[right] 换成 left_max < right_max 也行，也容易理解一点，当前位置取决于左右挡板的高度
      if (height[l] < height[r]) {
        res += left_max - height[l];
        ++l;
      } else {
        res += right_max - height[r];
        --r;
      }
    }
    return res;
  }
};