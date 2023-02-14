/*
 * @lc app=leetcode.cn id=1124 lang=cpp
 *
 * [1124] 表现良好的最长时间段
 *
 * https://leetcode.cn/problems/longest-well-performing-interval/description/
 *
 * algorithms
 * Medium (34.84%)
 * Likes:    394
 * Dislikes: 0
 * Total Accepted:    33.5K
 * Total Submissions: 89.1K
 * Testcase Example:  '[9,9,6,0,6,6,9]'
 *
 * 给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数。
 *
 * 我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是「劳累的一天」。
 *
 * 所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」。
 *
 * 请你返回「表现良好时间段」的最大长度。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：hours = [9,9,6,0,6,6,9]
 * 输出：3
 * 解释：最长的表现良好时间段是 [9,9,6]。
 *
 * 示例 2：
 *
 *
 * 输入：hours = [6,6,6]
 * 输出：0
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= hours.length <= 10^4
 * 0 <= hours[i] <= 16
 *
 *
 */

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
  int longestWPI(std::vector<int>& hours) {
    int n = hours.size();
    std::vector<int> prefix_sum(n + 1);
    int res = 0;
    std::stack<int> s;
    s.push(0);
    for (int i = 1; i <= n; ++i) {
      prefix_sum[i] = prefix_sum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
      if (prefix_sum[i] < prefix_sum[s.top()]) {
        s.push(i);
      }
    }
    for (int i = n; i >= 1; --i) {
      while (!s.empty() && prefix_sum[s.top()] < prefix_sum[i]) {
        res = std::max(res, i - s.top());
        s.pop();
      }
    }
    return res;
  }
  int longestWPI2(std::vector<int>& hours) {
    int n = hours.size();
    // prefix_sum[i] 表示下标[0,i)中超过8小时的个数和小于8小时个数的差
    int sum = 0;
    std::unordered_map<int, int> idxs;
    idxs[0] = 0;
    int result = 0;
    for (int i = 0; i < hours.size(); ++i) {
      if (hours[i] > 8) {
        ++sum;
      } else {
        --sum;
      }
      if (sum > 0) {
        result = std::max(result, i + 1);
      } else {
        auto it = idxs.find(sum - 1);
        if (it != idxs.end()) {
          result = std::max(result, i - it->second + 1);
        }
      }
      if (!idxs.count(sum)) {
        idxs[sum] = i + 1;
      }
    }
    return result;
  }
};