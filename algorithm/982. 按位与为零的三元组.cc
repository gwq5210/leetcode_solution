/*
 * @lc app=leetcode.cn id=982 lang=cpp
 *
 * [982] 按位与为零的三元组
 *
 * https://leetcode.cn/problems/triples-with-bitwise-and-equal-to-zero/description/
 *
 * algorithms
 * Hard (57.62%)
 * Likes:    141
 * Dislikes: 0
 * Total Accepted:    19.3K
 * Total Submissions: 28.8K
 * Testcase Example:  '[2,1,3]'
 *
 * 给你一个整数数组 nums ，返回其中 按位与三元组 的数目。
 *
 * 按位与三元组 是由下标 (i, j, k) 组成的三元组，并满足下述全部条件：
 *
 *
 * 0 <= i < nums.length
 * 0 <= j < nums.length
 * 0 <= k < nums.length
 * nums[i] & nums[j] & nums[k] == 0 ，其中 & 表示按位与运算符。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [2,1,3]
 * 输出：12
 * 解释：可以选出如下 i, j, k 三元组：
 * (i=0, j=0, k=1) : 2 & 2 & 1
 * (i=0, j=1, k=0) : 2 & 1 & 2
 * (i=0, j=1, k=1) : 2 & 1 & 1
 * (i=0, j=1, k=2) : 2 & 1 & 3
 * (i=0, j=2, k=1) : 2 & 3 & 1
 * (i=1, j=0, k=0) : 1 & 2 & 2
 * (i=1, j=0, k=1) : 1 & 2 & 1
 * (i=1, j=0, k=2) : 1 & 2 & 3
 * (i=1, j=1, k=0) : 1 & 1 & 2
 * (i=1, j=2, k=0) : 1 & 3 & 2
 * (i=2, j=0, k=1) : 3 & 2 & 1
 * (i=2, j=1, k=0) : 3 & 1 & 2
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [0,0,0]
 * 输出：27
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 1000
 * 0 <= nums[i] < 2^16
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
  int countTriplets(std::vector<int>& nums) {
    std::unordered_map<int, int> stats;
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = 0; j < nums.size(); ++j) {
        int x = nums[i] & nums[j];
        ++stats[x];
      }
    }
    int r = 0;
    // 枚举第三个元素时，只枚举与 k & m 后可能为 0 的元素
    // 这些元素必然满足如下条件
    // 如果 k 的第 i 个 bit 是 0，则 m 的第 i 个 bit 可以是0或1
    // 如果 k 的第 i 个 bit 是 1，则 m 的第 i 个 bit 一定是0
    // 因此，我们可以将 k 与 2^16（即二进制表示下的 16 个 1）进行按位异或运算
    // 这样一来，满足要求的二元组的二进制表示中包含的 1 必须是该数的子集
    // 例如该数是 (100111)2，那么满足要求的二元组可以是 (100010)2
    // 或者 (000110)2，但不能是 (010001)2
    for (int k : nums) {
      int x = k ^ 0xffff;
      // 枚举 x 中 bit 为 1 的子集
      // 初始另 m 为 x
      // 不断另 m = (m - 1) & x，直到 m 为 0，其中 & x 的目的是使得为 1 的 bit 一定在 x 中
      // 需要注意 0 也是 x 的子集
      for (int m = x; m; m = (m - 1) & x) {
        r += stats[m];
      }
      r += stats[0];
    }
    return r;
  }
  // 朴素的暴力复杂度不满足要求
  // 首先枚举出 a & b 之后的元素的数量，不同的元素数量不会超过 2^16
  // 然后再将上述元素与 c 进行枚举，统计 a & b & c 为 0 的数量
  int countTriplets1(std::vector<int>& nums) {
    std::unordered_map<int, int> stats;
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = 0; j < nums.size(); ++j) {
        int x = nums[i] & nums[j];
        ++stats[x];
      }
    }
    int r = 0;
    for (auto [v, cnt] : stats) {
      for (int i = 0; i < nums.size(); ++i) {
        if ((v & nums[i]) == 0) {
          r += cnt;
        }
      }
    }
    return r;
  }
};
