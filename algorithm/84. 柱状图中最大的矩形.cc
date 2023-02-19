/*
 * @lc app=leetcode.cn id=84 lang=cpp
 *
 * [84] 柱状图中最大的矩形
 *
 * https://leetcode-cn.com/problems/largest-rectangle-in-histogram/description/
 *
 * algorithms
 * Hard (43.35%)
 * Likes:    2327
 * Dislikes: 0
 * Total Accepted:    318.6K
 * Total Submissions: 710K
 * Testcase Example:  '[2,1,5,6,2,3]'
 *
 * 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
 *
 * 求在该柱状图中，能够勾勒出来的矩形的最大面积。
 *
 *
 *
 * 示例 1:
 *
 *
 *
 *
 * 输入：heights = [2,1,5,6,2,3]
 * 输出：10
 * 解释：最大的矩形为图中红色区域，面积为 10
 *
 *
 * 示例 2：
 *
 *
 *
 *
 * 输入： heights = [2,4]
 * 输出： 4
 *
 *
 *
 * 提示：
 *
 *
 * 1
 * 0
 *
 *
 */

#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  // 如何确定当前高度的最大矩形？可以枚举矩形的左右边界
  // 也就是找到当前高度左右两侧比当前高度大或等于的柱子的数量
  // 换个思路就是找到左右两侧第一个比当前高度小的柱子的位置
  // 1. 可以使用单调栈从左到右和从右到左求出来
  // 2. 只遍历一次的话，其中有一侧求出的是比当前高度小于等于的柱子的位置
  // 但我们需要的是「一根柱子的左侧且最近的小于其高度的柱子」，但这里我们求的是小于等于，那么会造成什么影响呢？
  // 答案是：我们确实无法求出正确的右边界，但对最终的答案没有任何影响。
  // 这是因为在答案对应的矩形中，如果有若干个柱子的高度都等于矩形的高度，那么最右侧的那根柱子是可以求出正确的右边界的
  // 而我们没有对求出左边界的算法进行任何改动，因此最终的答案还是可以从最右侧的与矩形高度相同的柱子求得的。
  int largestRectangleArea1(std::vector<int>& heights) {
    int result = 0;
    std::vector<int> left_min(heights.size());
    std::vector<int> right_min(heights.size(), heights.size() - 1);
    std::stack<int> s;
    std::stack<int> s2;
    for (int i = 0; i < heights.size(); ++i) {
      while (!s.empty() && heights[i] < heights[s.top()]) {
        right_min[s.top()] = i - 1;
        s.pop();
      }
      s.push(i);
    }
    for (int i = heights.size() - 1; i >= 0; --i) {
      while (!s.empty() && heights[i] < heights[s.top()]) {
        left_min[s.top()] = i + 1;
        s.pop();
      }
      s.push(i);
    }
    for (int i = 0; i < heights.size(); ++i) {
      int area = (right_min[i] - left_min[i] + 1) * heights[i];
      result = std::max(area, result);
    }
    return result;
  }
  int largestRectangleArea(std::vector<int>& heights) {
    int result = 0;
    std::vector<int> left_min(heights.size());
    std::vector<int> right_min(heights.size(), heights.size() - 1);
    std::stack<int> s;
    std::stack<int> s2;
    for (int i = 0; i < heights.size(); ++i) {
      while (!s.empty() && heights[i] < heights[s.top()]) {
        right_min[s.top()] = i - 1;
        s.pop();
      }
      left_min[i] = s.empty() ? 0 : s.top() + 1;
      s.push(i);
    }
    for (int i = 0; i < heights.size(); ++i) {
      int area = (right_min[i] - left_min[i] + 1) * heights[i];
      result = std::max(area, result);
    }
    return result;
  }
};