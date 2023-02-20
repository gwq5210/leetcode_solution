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
  // 贪心 + 最小堆
  // 给定 k 个列表，需要找到最小区间，使得每个列表都至少有一个数在该区间中。
  // 该问题可以转化为，从 k 个列表中各取一个数，使得这 k 个数中的最大值与最小值的差最小。
  // 假设这 k 个数中的最小值是第 i 个列表中的 x，对于任意 j!=i，设第 j 个列表中被选为 k 个数之一的数是 y
  // 则为了找到最小区间，y 应该取第 j 个列表中大于等于 x 的最小的数，这是一个贪心的策略。
  // 贪心策略的正确性简单证明如下：假设 z 也是第 j 个列表中的数，且 z>y，则有 z−x>y−x，同时包含 x
  // 和 z 的区间一定不会小于同时包含 x 和 y 的区间。因此，其余 k−1 个列表中应该取大于等于 x 的最小的数。
  // 由于 k 个列表都是升序排列的，因此对每个列表维护一个指针，通过指针得到列表中的元素
  // 指针右移之后指向的元素一定大于或等于之前的元素。
  // 使用最小堆维护 k 个指针指向的元素中的最小值，同时维护堆中元素的最大值。初始时，k 个指针都指向下标 0
  // 最大元素即为所有列表的下标 0 位置的元素中的最大值。
  // 每次从堆中取出最小值，根据最大值和最小值计算当前区间，如果当前区间小于最小区间则用当前区间更新最小区间
  // 然后将对应列表的指针右移，将新元素加入堆中，并更新堆中元素的最大值。
  // 如果一个列表的指针超出该列表的下标范围，则说明该列表中的所有元素都被遍历过，堆中不会再有该列表中的元素，因此退出循环。
  std::vector<int> smallestRange1(std::vector<std::vector<int>>& nums) {
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
  // 哈希表 + 滑动窗口
  // 与76. 最小覆盖子串题目类似
  std::vector<int> smallestRange(std::vector<std::vector<int>>& nums) {
    // indexs 的 key 是 nums 中的值，value 是该值在 nums 中出现的下标
    std::unordered_map<int, std::vector<int>> indexs;
    // nmin 和 nmax 分别表示 nums 中的最大值和最小值
    int nmin = kInf;
    int nmax = -kInf;
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = 0; j < nums[i].size(); ++j) {
        indexs[nums[i][j]].emplace_back(i);
        nmin = std::min(nmin, nums[i][j]);
        nmax = std::max(nmax, nums[i][j]);
      }
    }
    // 我们需要找到最小的区间[res_start, res_end]，使得区间内的值对应的下标必须包括所有的[0, nums.size())
    // count 表示区间内不同下标的数量
    int count = 0;
    // stats 表示每个下标在区间 [nmin, i] 中出现元素的数目
    std::vector<int> stats(nums.size());
    // 表示答案的区间 [res_start, res_end]
    int res_start = nmin;
    int res_end = nmax;
    // 枚举区间的右边界
    for (int i = nmin; i <= nmax; ++i) {
      // 值不在nums中，直接跳过
      if (!indexs.count(i)) {
        continue;
      }
      // 更新 stats 的统计，如果某个下标的统计从 0 变为 1，则 count 需要加 1
      for (int index : indexs[i]) {
        ++stats[index];
        if (stats[index] == 1) {
          ++count;
        }
      }
      while (count == nums.size()) {
        // 满足条件时更新答案和统计，并向右移动 nmin
        if (i - nmin + 1 < res_end - res_start + 1) {
          res_start = nmin;
          res_end = i;
        }
        // 更新 stats 的统计，如果某个下标的统计从 1 变为 0，则 count 需要减 1
        for (int index : indexs[nmin]) {
          --stats[index];
          if (stats[index] == 0) {
            --count;
          }
        }
        ++nmin;
      }
    }
    return std::vector<int>{res_start, res_end};
  }
};