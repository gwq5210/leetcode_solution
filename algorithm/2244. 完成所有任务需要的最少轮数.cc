/*
 * @lc app=leetcode.cn id=2244 lang=cpp
 *
 * [2244] 完成所有任务需要的最少轮数
 *
 * https://leetcode.cn/problems/minimum-rounds-to-complete-all-tasks/description/
 *
给你一个下标从 0 开始的整数数组 tasks ，其中 tasks[i] 表示任务的难度级别。在每一轮中，你可以完成 2 个或者 3 个
相同难度级别 的任务。

返回完成所有任务需要的 最少 轮数，如果无法完成所有任务，返回 -1 。

示例 1：

输入：tasks = [2,2,3,3,2,4,4,4,4,4]
输出：4
解释：要想完成所有任务，一个可能的计划是：
- 第一轮，完成难度级别为 2 的 3 个任务。
- 第二轮，完成难度级别为 3 的 2 个任务。
- 第三轮，完成难度级别为 4 的 3 个任务。
- 第四轮，完成难度级别为 4 的 2 个任务。
可以证明，无法在少于 4 轮的情况下完成所有任务，所以答案为 4 。
示例 2：

输入：tasks = [2,3,3]
输出：-1
解释：难度级别为 2 的任务只有 1 个，但每一轮执行中，只能选择完成 2 个或者 3
个相同难度级别的任务。因此，无法完成所有任务，答案为 -1 。


提示：

1 <= tasks.length <= 105
1 <= tasks[i] <= 109

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
  // 按每种任务的数量分类讨论：
  // 若这种任务只有 1 个，则无法完成；
  // 若这种任务只有 2 个，可以一次完成；
  // 若这种任务数量是 3 的倍数，显然每次完成 3 个是最快的；
  // 若这种任务数量除 3 余 1，需要每次完成 3 个，最后 4 个分两次完成；
  // 若这种任务数量除 3 余 2，需要每次完成 3 个，最后完成 2 个。
  int minimumRounds(std::vector<int>& tasks) {
    std::unordered_map<int, int> stats;
    for (int task : tasks) {
      ++stats[task];
    }
    int res = 0;
    for (auto [_, count] : stats) {
      if (count == 1) {
        return -1;
      }
      res += count / 3 + (count % 3 == 0 ? 0 : 1);
    }
    return res;
  }
};