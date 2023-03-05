/*
 * @lc app=leetcode.cn id=6313 lang=cpp
 *
 * [6313] 统计将重叠区间合并成组的方案数
 *
 * https://leetcode.cn/problems/count-ways-to-group-overlapping-ranges/description/
 *
给你一个二维整数数组 ranges ，其中 ranges[i] = [starti, endi] 表示 starti 到 endi 之间（包括二者）的所有整数都包含在第 i
个区间中。

你需要将 ranges 分成 两个 组（可以为空），满足：

每个区间只属于一个组。
两个有 交集 的区间必须在 同一个 组内。
如果两个区间有至少 一个 公共整数，那么这两个区间是 有交集 的。

比方说，区间 [1, 3] 和 [2, 5] 有交集，因为 2 和 3 在两个区间中都被包含。
请你返回将 ranges 划分成两个组的 总方案数 。由于答案可能很大，将它对 109 + 7 取余 后返回。



示例 1：

输入：ranges = [[6,10],[5,15]]
输出：2
解释：
两个区间有交集，所以它们必须在同一个组内。
所以有两种方案：
- 将两个区间都放在第 1 个组中。
- 将两个区间都放在第 2 个组中。
示例 2：

输入：ranges = [[1,3],[10,20],[2,5],[4,8]]
输出：4
解释：
区间 [1,3] 和 [2,5] 有交集，所以它们必须在同一个组中。
同理，区间 [2,5] 和 [4,8] 也有交集，所以它们也必须在同一个组中。
所以总共有 4 种分组方案：
- 所有区间都在第 1 组。
- 所有区间都在第 2 组。
- 区间 [1,3] ，[2,5] 和 [4,8] 在第 1 个组中，[10,20] 在第 2 个组中。
- 区间 [1,3] ，[2,5] 和 [4,8] 在第 2 个组中，[10,20] 在第 1 个组中。


提示：

1 <= ranges.length <= 105
ranges[i].length == 2
0 <= starti <= endi <= 109
 *
 *
 */

#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

long long fact[200200];
long long inv[200200];
const int mod = 1e9 + 7;
long long qpow(long long x, long long n) {
  long long ans = 1;
  while (n) {
    if (n & 1) ans = ans * x % mod;
    x = x * x % mod;
    n >>= 1;
  }
  return ans;
}

void init() {
  fact[0] = 1;
  for (int i = 1; i < 200005; i++) fact[i] = fact[i - 1] * i % mod;
  for (int i = 0; i < 200005; i++) inv[i] = qpow(fact[i], mod - 2);
}

long long C(int n, int m) { return fact[n] * inv[n - m] % mod * inv[m] % mod; }

class Solution {
 public:
  static constexpr int kMod = 1e9 + 7;
  // range 有交集的一定在同一组内，因此先统计处没有交集的 range 数量 m
  // 对于每一个没有交集的 range，其都可以独立选择分在第一组或第二组
  // 因此总方案数是 2^m
  // 另一个解释是，若前 m-1 个可以选的方案数是 x，则第 m 个 range 分在第一组
  // 方案数是 x，分在第二组方案数也是 x，第 m 个的方案数是 2*x
  int countWays(std::vector<std::vector<int>>& ranges) {
    std::sort(ranges.begin(), ranges.end());
    long long res = 1;
    int max_r = -1;
    for (auto& range : ranges) {
      int l = range[0];
      int r = range[1];
      if (l <= max_r) {
        max_r = std::max(max_r, r);
      } else {
        max_r = r;
        res = (res * 2) % kMod;
      }
    }
    return res;
  }
  int countWays1(std::vector<std::vector<int>>& ranges) {
    init();
    int kMod = 1e9 + 7;
    int c = 0;
    std::sort(ranges.begin(), ranges.end());
    int max_r = -1;
    for (auto& range : ranges) {
      int l = range[0];
      int r = range[1];
      if (l <= max_r) {
        max_r = std::max(max_r, r);
      } else {
        max_r = r;
        ++c;
      }
    }
    // 不同 range 的数量为 c
    // 第一组为空，或第二组为空，总共两种方案
    long long res = 2;
    // 奇葩的思路
    // 计算第一组可以选择 i 个元素的方案数
    // 选择 i 个元素是没有顺序的，因此是组合数 C(n, i)
    // 需要求 C(n, i) % kMod
    // 使用Lucas 定理用于求解大组合数取模的问题
    for (int i = 1; i < c; ++i) {
      res = (res + C(c, i)) % kMod;
    }
    return res;
  }
};