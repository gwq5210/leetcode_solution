/*
 * @lc app=leetcode.cn id=1144 lang=cpp
 *
 * [1144] 递减元素使数组呈锯齿状
 *
 * https://leetcode.cn/problems/decrease-elements-to-make-array-zigzag/description/
 *
给你一个整数数组 nums，每次 操作 会从中选择一个元素并 将该元素的值减少 1。

如果符合下列情况之一，则数组 A 就是 锯齿数组：

每个偶数索引对应的元素都大于相邻的元素，即 A[0] > A[1] < A[2] > A[3] < A[4] > ...
或者，每个奇数索引对应的元素都大于相邻的元素，即 A[0] < A[1] > A[2] < A[3] > A[4] < ...
返回将数组 nums 转换为锯齿数组所需的最小操作次数。



示例 1：

输入：nums = [1,2,3]
输出：2
解释：我们可以把 2 递减到 0，或把 3 递减到 1。
示例 2：

输入：nums = [9,6,1,6,2]
输出：4


提示：

1 <= nums.length <= 1000
1 <= nums[i] <= 1000
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
  static constexpr int kInf = std::numeric_limits<int>::max() / 2;
  int movesToMakeZigzag(std::vector<int>& nums) {
    int a = 0;
    int b = 0;
    // 每次操作只能使一个元素减 1，因此如果想使得每个偶数索引的元素都大于相邻的元素
    // 则必然无需操作偶数索引的元素，只需要减小奇数索引的元素即可，减小到比相邻元素的最小值再小 1 即可
    // 使得每个奇数索引的元素都大于相邻的元素，原理同上
    // 只需要统计上述两者的操作次数，取最小值就是答案
    // 注意边界情况即可
    for (int i = 0; i < nums.size(); ++i) {
      int prev = i - 1 >= 0 ? nums[i - 1] : kInf;
      int next = i + 1 < nums.size() ? nums[i + 1] : kInf;
      int x = nums[i] - std::min(prev, next);
      if (x < 0) {
        continue;
      }
      if (i % 2 == 0) {
        a += x + 1;
      } else {
        b += x + 1;
      }
    }
    return std::min(a, b);
  }
};