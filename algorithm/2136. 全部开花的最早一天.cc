/*
 * @lc app=leetcode.cn id=2136 lang=cpp
 *
 * [2136] 全部开花的最早一天
 *
 * https://leetcode.cn/problems/earliest-possible-day-of-full-bloom/description/
 *
你有 n 枚花的种子。每枚种子必须先种下，才能开始生长、开花。播种需要时间，种子的生长也是如此。给你两个下标从 0
开始的整数数组 plantTime 和 growTime ，每个数组的长度都是 n ：

plantTime[i] 是 播种 第 i 枚种子所需的 完整天数 。每天，你只能为播种某一枚种子而劳作。无须
连续几天都在种同一枚种子，但是种子播种必须在你工作的天数达到 plantTime[i] 之后才算完成。 growTime[i] 是第 i
枚种子完全种下后生长所需的 完整天数 。在它生长的最后一天 之后 ，将会开花并且永远 绽放 。 从第 0 开始，你可以按 任意
顺序播种种子。

返回所有种子都开花的 最早 一天是第几天。



示例 1：


输入：plantTime = [1,4,3], growTime = [2,3,1]
输出：9
解释：灰色的花盆表示播种的日子，彩色的花盆表示生长的日子，花朵表示开花的日子。
一种最优方案是：
第 0 天，播种第 0 枚种子，种子生长 2 整天。并在第 3 天开花。
第 1、2、3、4 天，播种第 1 枚种子。种子生长 3 整天，并在第 8 天开花。
第 5、6、7 天，播种第 2 枚种子。种子生长 1 整天，并在第 9 天开花。
因此，在第 9 天，所有种子都开花。
示例 2：


输入：plantTime = [1,2,3,2], growTime = [2,1,2,1]
输出：9
解释：灰色的花盆表示播种的日子，彩色的花盆表示生长的日子，花朵表示开花的日子。
一种最优方案是：
第 1 天，播种第 0 枚种子，种子生长 2 整天。并在第 4 天开花。
第 0、3 天，播种第 1 枚种子。种子生长 1 整天，并在第 5 天开花。
第 2、4、5 天，播种第 2 枚种子。种子生长 2 整天，并在第 8 天开花。
第 6、7 天，播种第 3 枚种子。种子生长 1 整天，并在第 9 天开花。
因此，在第 9 天，所有种子都开花。
示例 3：

输入：plantTime = [1], growTime = [1]
输出：2
解释：第 0 天，播种第 0 枚种子。种子需要生长 1 整天，然后在第 2 天开花。
因此，在第 2 天，所有种子都开花。


提示：

n == plantTime.length == growTime.length
1 <= n <= 10^5
1 <= plantTime[i], growTime[i] <= 10^4
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

class Solution {
 public:
  int earliestFullBloom(std::vector<int>& plantTime, std::vector<int>& growTime) {
    int n = plantTime.size();
    std::vector<int> idxs(n);
    // 生长时间越长，越早种植的话，开花时间最优
    // 对于两枚种子，设其播种所需天数为 p1 和 p2，生长所需天数为 g1 和 g2
    // 不妨设 g1 >= g2，我们来比较哪种播种顺序更优
    // 先 1 后 2 时的最晚开花时间: max(p1 + g1, p1 + p2 + g2)
    // 先 2 后 1 时的最晚开花时间: max(p2 + g2, p1 + p2 + g1)
    // 由于 p1 + g1 < p1 + pg + g1 且 p1 + p2 + g2 <= p1 + p2 + g1
    // 因此 max(p1+g1, p1+p2+g2) <= p1 + p2 + g1 = max(p1+p2+g1, p2+g2)
    // 上式表明，按照先 1 后 2 的顺序播种，最晚开花时间不会晚于按照先 2 后 1 播种时的最晚开花时间。
    // 这意味着按照生长天数从大到小排序后，交换任意两枚种子的播种顺序，不会让最晚开花时间提前。
    // 假设存在其他更优的种子排列，那么我们可以交换生长天数小且排在前面的种子，与生长天数大且排在后面的种子，这样可以得到更早的最晚开花时间，因此假设不成立
    // 按照生长天数从大到小的顺序播种是最优的。
    // 对于两枚生长天数相同的种子，由于无论按照何种顺序播种，这两枚种子的最晚开花时间都是相同的，因此无需考虑生长天数相同的种子的播种顺序
    // 所以在排序时，仅需对生长天数从大到小排序。
    std::iota(idxs.begin(), idxs.end(), 0);
    std::sort(idxs.begin(), idxs.end(), [&plantTime, &growTime](int i, int j) { return growTime[i] > growTime[j]; });
    int t = 0;
    int res = 0;
    for (int idx : idxs) {
      t += plantTime[idx];
      res = std::max(res, t + growTime[idx]);
    }
    return res;
  }
};