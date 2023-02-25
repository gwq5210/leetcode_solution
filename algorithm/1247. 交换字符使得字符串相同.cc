/*
 * @lc app=leetcode.cn id=1247 lang=cpp
 *
 * [1247] 交换字符使得字符串相同
 *
 * https://leetcode-cn.com/problems/minimum-swaps-to-make-strings-equal/description/
 *
 * algorithms
 * Medium (61.75%)
 * Likes:    134
 * Dislikes: 0
 * Total Accepted:    24.3K
 * Total Submissions: 35.8K
 * Testcase Example:  '"xx"\n"yy"'
 *
 * 有两个长度相同的字符串 s1 和 s2，且它们其中 只含有 字符 "x" 和 "y"，你需要通过「交换字符」的方式使这两个字符串相同。
 *
 * 每次「交换字符」的时候，你都可以在两个字符串中各选一个字符进行交换。
 *
 * 交换只能发生在两个不同的字符串之间，绝对不能发生在同一个字符串内部。也就是说，我们可以交换 s1[i]
 * 和 s2[j]，但不能交换 s1[i] 和 s1[j]。
 *
 * 最后，请你返回使 s1 和 s2 相同的最小交换次数，如果没有方法能够使得这两个字符串相同，则返回 -1 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：s1 = "xx", s2 = "yy"
 * 输出：1
 * 解释：
 * 交换 s1[0] 和 s2[1]，得到 s1 = "yx"，s2 = "yx"。
 *
 * 示例 2：
 *
 * 输入：s1 = "xy", s2 = "yx"
 * 输出：2
 * 解释：
 * 交换 s1[0] 和 s2[0]，得到 s1 = "yy"，s2 = "xx" 。
 * 交换 s1[0] 和 s2[1]，得到 s1 = "xy"，s2 = "xy" 。
 * 注意，你不能交换 s1[0] 和 s1[1] 使得 s1 变成 "yx"，因为我们只能交换属于两个不同字符串的字符。
 *
 * 示例 3：
 *
 * 输入：s1 = "xx", s2 = "xy"
 * 输出：-1
 *
 *
 * 示例 4：
 *
 * 输入：s1 = "xxyyxyxyxx", s2 = "xyyxyxxxyx"
 * 输出：4
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s1.length, s2.length <= 1000
 * s1, s2 只包含 'x' 或 'y'。
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
  int minimumSwap(std::string s1, std::string s2) {
    int count = 0;
    int y1_count = 0;
    int y2_count = 0;
    for (int i = 0; i < s1.size(); ++i) {
      if (s1[i] != s2[i]) {
        ++count;
        if (s1[i] == 'y') {
          ++y1_count;
        }
        if (s2[i] == 'y') {
          ++y2_count;
        }
      }
    }
    // 如果两个字符串的不同的字符中 y 字符的数量是奇数，则不可能通过交换使得两个字符串相同
    if ((y1_count + y2_count) % 2 != 0) {
      return -1;
    }
    // s1: yyxxxx
    // s2: xxyyyy
    // 两个字符串中 y 字符的差异数量为 c，c 必定是 2 的倍数
    // 则可以通过 c/2 次交换使得两个字符串中的 y 字符数量相同
    // 同时交换的时候，可以使得 s1 和 s2 的这 c 个字符相等
    int c = std::abs(y1_count - y2_count);
    // 通过以上交换，剩余位置的 y 个字符数量为 d
    // 剩余位置的字符数量中 y 的个数是相同的只是位置错位
    // 如果 d 是偶数，则可以通过 d 次交换使得两个字符串相等
    // 如果 d 是奇数，多余的一个则需要通过两次交换才可以相等
    // s1: yxyx yx -> yxxy yy -> yxxy xy
    // s2: xyxy xy -> yxxy xx -> yxxy yy
    int d = std::max(y1_count, y2_count) - c;
    // return c / 2 + (d / 2 * 2) + (d % 2 ? 2 : 0);
    // 如果不相同，则有两种情况，一是 s1[i] 为 x，s2[i] 为 y 使用 xy(y1_count) 表示这种情况出现的次数。
    // 一是 s1[i] 为 y，s2[i] 为 x 使用 yx(y2_count) 表示这种情况出现的次数。
    // 现在需要通过最少次数的交换，使得 xy 和 yx 都为 0。
    // 交换的方法有两种：
    // xx -> xy
    // yy -> xy
    // 示例 1：可以通过一次交换，使得 xy 或 yx 的值减少 2。
    // yx -> yy -> xy
    // xy -> xx -> xy
    // 示例 2：可以通过两次交换，使得 xy 和 yx 的值各减少 1。
    // 为了使用尽可能少的交换次数，需要从以下顺序考虑
    // 第一种交换方式更有效率，应该尽可能采用第一种交换方式。
    // 如果还未能使 xy 和 yx 都为 0，则应该采用第二种交换方式。
    // 如果 xy 和 yx 都为 1，则可以通过两次第二种交换，来使得 xy 和 yx 都为 0
    // 可以预先判断，如果 xy 和 yx 之和为奇数，则没有方法能够使得字符串相等。
    return y1_count / 2 + y2_count / 2 + y1_count % 2 + y2_count % 2;
  }
};
