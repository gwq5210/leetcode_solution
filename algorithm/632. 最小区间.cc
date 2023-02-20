/*
 * @lc app=leetcode.cn id=632 lang=cpp
 *
 * [632] 最小区间
 *
 * https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/description/
 *
 * algorithms
 * Hard (60.79%)
 * Likes:    392
 * Dislikes: 0
 * Total Accepted:    24.5K
 * Total Submissions: 40.2K
 * Testcase Example:  '[[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]'
 *
 * 你有 k 个 非递减排列 的整数列表。找到一个 最小 区间，使得 k 个列表中的每个列表至少有一个数包含在其中。
 *
 * 我们定义如果 b-a < d-c 或者在 b-a == d-c 时 a < c，则区间 [a,b] 比 [c,d] 小。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
 * 输出：[20,24]
 * 解释：
 * 列表 1：[4, 10, 15, 24, 26]，24 在区间 [20,24] 中。
 * 列表 2：[0, 9, 12, 20]，20 在区间 [20,24] 中。
 * 列表 3：[5, 18, 22, 30]，22 在区间 [20,24] 中。
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [[1,2,3],[1,2,3],[1,2,3]]
 * 输出：[1,1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * nums.length == k
 * 1 <= k <= 3500
 * 1 <= nums[i].length <= 50
 * -10^5 <= nums[i][j] <= 10^5
 * nums[i] 按非递减顺序排列
 *
 *
 *
 *
 */

#include <deque>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  static constexpr int kInf = std::numeric_limits<int>::max() / 2;
  struct Node {
    int m = 0;
    int x = 0;
    int y = 0;
    bool operator<(const Node& node) const {
      return m > node.m;
    }
  };
  std::vector<int> smallestRange(std::vector<std::vector<int>>& nums) {
    std::priority_queue<Node> pq;
    int res_start = kInf;
    int res_end = -kInf;
    int start = kInf;
    int end = -kInf;
    for (int i = 0; i < nums.size(); ++i) {
      pq.push(Node{nums[i][0], i, 0});
      start = std::min(start, nums[i][0]);
      end = std::max(end, nums[i][0]);
    }
    res_start = start;
    res_end = end;
    while (!pq.empty()) {
      Node node = pq.top();
      pq.pop();
      if (res_end - res_start > end - node.m) {
        res_end = end;
        res_start = node.m;
      }
      if (node.y >= nums[node.x].size()) {
        break;
      }
      end = std::max(end, nums[node.x][node.y]);
      pq.push({nums[node.x][node.y], node.x, node.y + 1});
    }
    return std::vector<int>{res_start, res_end};
  }
};