/*
 * @lc app=leetcode.cn id=1723 lang=cpp
 *
 * [1723] 完成所有工作的最短时间
 *
 * https://leetcode.cn/problems/find-minimum-time-to-finish-all-jobs/description/
 *
 * algorithms
 * Hard (50.91%)
 * Likes:    305
 * Dislikes: 0
 * Total Accepted:    30.1K
 * Total Submissions: 59.1K
 * Testcase Example:  '[3,2,3]\n3'
 *
 * 给你一个整数数组 jobs ，其中 jobs[i] 是完成第 i 项工作要花费的时间。
 *
 * 请你将这些工作分配给 k 位工人。所有工作都应该分配给工人，且每项工作只能分配给一位工人。工人的 工作时间
 * 是完成分配给他们的所有工作花费时间的总和。请你设计一套最佳的工作分配方案，使工人的 最大工作时间 得以 最小化 。
 *
 * 返回分配方案中尽可能 最小 的 最大工作时间 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：jobs = [3,2,3], k = 3
 * 输出：3
 * 解释：给每位工人分配一项工作，最大工作时间是 3 。
 *
 *
 * 示例 2：
 *
 *
 * 输入：jobs = [1,2,4,7,8], k = 2
 * 输出：11
 * 解释：按下述方式分配工作：
 * 1 号工人：1、2、8（工作时间 = 1 + 2 + 8 = 11）
 * 2 号工人：4、7（工作时间 = 4 + 7 = 11）
 * 最大工作时间是 11 。
 *
 *
 *
 * 提示：
 *
 *
1 <= k <= jobs.length <= 12
1 <= jobs[i] <= 107
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
  static constexpr int kInf = std::numeric_limits<int>::max() / 2;
  int minimumTimeRequired(std::vector<int>& jobs, int k) {
    int n = jobs.size();
    int count = 1 << n;
    int mask = (1 << n) - 1;
    // dp[i][j] 表示前 i 个工人分配状态为 j 的工作时，表示的答案
    // dp[i][j] = min(dp[i][j],max(sum(j), dp[i - 1][x]))，x 表示 j^((1<<n) - 1) 中 bit 为 1 的子集
    std::vector<std::vector<int>> dp(k, std::vector<int>(count));
    std::vector<int> sums(count);
    for (int i = 0; i < count; ++i) {
      for (int j = 0; j < n; ++j) {
        if ((i >> j) & 1) {
          sums[i] += jobs[j];
        }
      }
    }
    for (int i = 0; i < k; ++i) {
      for (int j = 0; j < count; ++j) {
        if (i == 0) {
          dp[i][j] = sums[j];
          continue;
        }
        int x = j;
        int min_v = kInf;
        for (int y = x; y; y = (y - 1) & x) {
          min_v = std::min(min_v, std::max(sums[j - y], dp[i - 1][y]));
        }
        dp[i][j] = min_v;
      }
    }
    return dp[k - 1][mask];
  }
  int minimumTimeRequired1(std::vector<int>& jobs, int k) {
    std::vector<int> schs(k);
    int res = kInf;
    DFSJobs(jobs, 0, k, 0, res, schs, 0);
    return res;
  }
  // 按照工作开始选择
  // index 表示当前选到第几个工作
  // curr 表示当前的最大值
  // res 表示已经得到的最大值
  // used 当前分配给了多少个工人了
  // 每一轮选择枚举将工作分配给哪个工人
  // 优先将工作分配给没有工作的工人
  // 在「剪枝 DFS」中为什么「优先分配空闲工人」的做法是对的？
  // 首先要明确，递归树还是那棵递归树。
  // 所谓的「优先分配空闲工人」它并不是「贪心模拟」思路，而只是一个「调整搜索顺序」的做法。
  // 「优先分配空闲工人」不代表不会将任务分配给有工作的工人，仅仅代表我们先去搜索那些「优先分配空闲工人」的方案。
  // 然后将得到的「合法解」配合 max >= ans 去剪枝掉那些「必然不是最优解」的方案。
  void DFSJobs(std::vector<int>& jobs, int index, int k, int curr, int& res, std::vector<int>& schs, int used) {
    if (curr >= res) {
      return;
    }
    if (index >= jobs.size()) {
      res = curr;
      return;
    }
    // 优先分配给「空闲工人」
    if (used < k) {
      schs[used] += jobs[index];
      DFSJobs(jobs, index + 1, k, std::max(curr, schs[used]), res, schs, used + 1);
      schs[used] -= jobs[index];
    }
    // 不需要搜索所有的 k 个工人
    // 搜索已经分配的工人
    for (int i = 0; i < used; ++i) {
      schs[i] += jobs[index];
      DFSJobs(jobs, index + 1, k, std::max(curr, schs[i]), res, schs, used);
      schs[i] -= jobs[index];
    }
  }
};