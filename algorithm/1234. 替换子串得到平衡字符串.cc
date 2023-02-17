/*
 * @lc app=leetcode.cn id=1234 lang=cpp
 *
 * [1234] 替换子串得到平衡字符串
 *
 * https://leetcode-cn.com/problems/replace-the-substring-for-balanced-string/description/
 *
 * algorithms
 * Medium (34.43%)
 * Likes:    222
 * Dislikes: 0
 * Total Accepted:    27.5K
 * Total Submissions: 61.8K
 * Testcase Example:  '"QWER"'
 *
 * 有一个只含有 'Q', 'W', 'E', 'R' 四种字符，且长度为 n 的字符串。
 *
 * 假如在该字符串中，这四个字符都恰好出现 n/4 次，那么它就是一个「平衡字符串」。
 *
 *
 *
 * 给你一个这样的字符串 s，请通过「替换一个子串」的方式，使原字符串 s 变成一个「平衡字符串」。
 *
 * 你可以用和「待替换子串」长度相同的 任何 其他字符串来完成替换。
 *
 * 请返回待替换子串的最小可能长度。
 *
 * 如果原字符串自身就是一个平衡字符串，则返回 0。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "QWER"
 * 输出：0
 * 解释：s 已经是平衡的了。
 *
 * 示例 2：
 *
 *
 * 输入：s = "QQWE"
 * 输出：1
 * 解释：我们需要把一个 'Q' 替换成 'R'，这样得到的 "RQWE" (或 "QRWE") 是平衡的。
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = "QQQW"
 * 输出：2
 * 解释：我们可以把前面的 "QQ" 替换成 "ER"。
 *
 *
 * 示例 4：
 *
 *
 * 输入：s = "QQQQ"
 * 输出：3
 * 解释：我们可以替换后 3 个 'Q'，使 s = "QWER"。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 10^5
 * s.length 是 4 的倍数
 * s 中只含有 'Q', 'W', 'E', 'R' 四种字符
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
  int ToIndex(char c) {
    std::unordered_map<int, int> idxs{
        {'Q', 0},
        {'W', 1},
        {'E', 2},
        {'R', 3},
    };
    return idxs[c];
  }
  int balancedString(std::string s) {
    int n = s.size();
    int m = n / 4;

    // 计算每个字符串的数量
    std::vector<int> cnts(4);
    for (char c : s) {
      ++cnts[ToIndex(c)];
    }
    // 如果已经平衡则直接返回0
    if (cnts[0] == m && cnts[1] == m && cnts[2] == m && cnts[3] == 3) {
      return 0;
    }
    // 计算多出的字符的数量
    // 则找到的子串应该满足至少包含多出的字符的数量
    // 另一个理解是，除子串外任意字符的出现次数不能超过m次
    // 答案则是所有满足上述要求的子串的最短长度
    std::vector<int> ecnts(4);
    for (int i = 0; i < 4; ++i) {
      if (cnts[i] > m) {
        ecnts[i] = cnts[i] - m;
      }
    }
    // 枚举子串的左右边界[l, r)
    // 这是一个同向双指针的题目
    int l = 0;
    int r = 0;
    std::vector<int> rcnts(4);
    int res = 1000000;
    while (l < n && r <= n) {
      if (!(rcnts[0] < ecnts[0] || rcnts[1] < ecnts[1] || rcnts[2] < ecnts[2] || rcnts[3] < ecnts[3])) {
        res = std::min(res, r - l);
        --rcnts[ToIndex(s[l])];
        ++l;
      } else {
        ++rcnts[ToIndex(s[r])];
        ++r;
      }
    }
    return res;
  }
};