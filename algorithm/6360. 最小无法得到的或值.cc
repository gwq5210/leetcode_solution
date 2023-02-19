/*
 * @lc app=leetcode.cn id=6360 lang=cpp
 *
 * 6360. 最小无法得到的或值
 *
 * https://leetcode.cn/problems/minimum-impossible-or/description/
 *

给你一个下标从 0 开始的整数数组 nums 。

如果存在一些整数满足 0 <= index1 < index2 < ... < indexk < nums.length ，得到 nums[index1] | nums[index2] | ... |
nums[indexk] = x ，那么我们说 x 是 可表达的 。换言之，如果一个整数能由 nums
的某个子序列的或运算得到，那么它就是可表达的。

请你返回 nums 不可表达的 最小非零整数 。

示例 1：

输入：nums = [2,1]
输出：4
解释：1 和 2 已经在数组中，因为 nums[0] | nums[1] = 2 | 1 = 3 ，所以 3 是可表达的。由于 4 是不可表达的，所以我们返回 4
。 示例 2：

输入：nums = [5,3,2]
输出：1
解释：1 是最小不可表达的数字。


提示：

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9

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
  int minImpossibleOR(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    // 方法一：
    // 提示 1：暴力做法是从小到大枚举答案，但这显然会超时。
    // 如何利用「xxx 不是答案」这一信息呢？
    // 提示 2：如果 1 不是答案，说明 1 在 nums 中。
    // 继续枚举，如果 2 不是答案，说明 2 在 nums 中，因为 2 只有一个比特是 1。
    // 那么 3 肯定不是答案，因为 1∣2 = 3，同时根据已知信息，1 和 2 都在 nums 中。
    // 继续枚举，如果 4 不是答案，说明 4 在 nums 中，因为 4 只有一个比特是 1
    // 那么 5, 6, 7 肯定不是答案，因为 1, 2, 4 都在 nums 中，它们可以通过或运算组成 1 到 7 中的任意数字。
    // 提示 3： 因此，我们只需要从小到大挨个判断 2^i 是否在 nums 中，第一个不在 nums 中的就是答案。
    // 代码实现时，可以用哈希表可以加速这个判断过程。

    // 方法二：x表示当前可以表示的最大数, 整体是动态规划的思想
    // 方法三：由于只需要看 2 的幂次，我们可以用一个 mask 记录 nums 中是 2 的幂次的数。
    // 那么答案就是 mask 中的最低比特 0。这可以取反后，用 lowbit 得到。

    int x = nums[0] == 1;
    for (int i = 1; i < nums.size(); ++i) {
      if (x + 1 >= nums[i]) {
        x |= nums[i];
      }
    }
    return x + 1;
  }
  int minImpossibleOR3(std::vector<int>& nums) {
    int mask = 0;
    for (int x : nums) {
      if ((x & (x - 1)) == 0) {  // x 是 2 的幂次
        mask |= x;
      }
    }
    mask = ~mask;
    return mask & -mask;  // lowbit
  }
};