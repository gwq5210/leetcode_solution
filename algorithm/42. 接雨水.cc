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
    int trap(std::vector<int>& height) {
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
        for (int i = 1; i < n - 1; ++i) {
            int x = std::min(left_max, rmax[i + 1]);
            if (x > height[i]) {
                res += x - height[i];
            }
            left_max = std::max(left_max, height[i]);
        }
        return res;
    }
};