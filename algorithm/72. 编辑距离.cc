/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 *
 * https://leetcode.cn/problems/edit-distance/description/
 *
 * algorithms
 * Hard (62.83%)
 * Likes:    2773
 * Dislikes: 0
 * Total Accepted:    336.4K
 * Total Submissions: 535.4K
 * Testcase Example:  '"horse"\n"ros"'
 *
 * 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
 *
 * 你可以对一个单词进行如下三种操作：
 *
 *
 * 插入一个字符
 * 删除一个字符
 * 替换一个字符
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：word1 = "horse", word2 = "ros"
 * 输出：3
 * 解释：
 * horse -> rorse (将 'h' 替换为 'r')
 * rorse -> rose (删除 'r')
 * rose -> ros (删除 'e')
 *
 *
 * 示例 2：
 *
 *
 * 输入：word1 = "intention", word2 = "execution"
 * 输出：5
 * 解释：
 * intention -> inention (删除 't')
 * inention -> enention (将 'i' 替换为 'e')
 * enention -> exention (将 'n' 替换为 'x')
 * exention -> exection (将 'n' 替换为 'c')
 * exection -> execution (插入 'u')
 *
 *
 *
 *
 * 提示：
 *
 *
 * 0 <= word1.length, word2.length <= 500
 * word1 和 word2 由小写英文字母组成
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

// dp
//
// dp[i][j]: 代表 word1 到 i 位置转换成 word2 到 j 位置需要最少步数
//
// 当word1[i]==word2[j]时:
//      dp[i-1][j-1]：  word1的[0,i-1]位置与word2的[0,j-1]位置的字符已匹配, 又word1[i]==word2[j], 因此不用执行操作
// 当word1[i]!=word2[j]时:
//      dp[i-1][j-1]+1: word1的[0,i-1]位置与word2的[0,j-1]位置的字符已匹配, 加1代表执行word1[i]->word2[j]的替换操作
//      dp[i-1][j]+1:   word1的[0,i-1]位置与word2的[0,j]位置的字符已匹配, 加1代表执行word1[i]的删除操作
//      dp[i][j-1]+1：  word1的[0,i]位置与word2的[0,j-1]位置的字符已匹配, 加1代表执行word1[i]的插入操作
//
// (一)、当word1[i]==word2[j]时,由于遍历到了i和j,说明word1的0~i-1和word2的0~j-1的匹配结果已经生成,
// 由于当前两个字符相同,因此无需做任何操作,dp[i][j]=dp[i-1][j-1]
// (二)、当word1[i]!=word2[j]时,可以进行的操作有3个:
//       ① 替换操作:可能word1的0~i-1位置与word2的0~j-1位置的字符都相同,
//            只是当前位置的字符不匹配,进行替换操作后两者变得相同,
//            所以此时dp[i][j]=dp[i-1][j-1]+1(这个加1代表执行替换操作)
//       ②删除操作:若此时word1的0~i-1位置与word2的0~j位置已经匹配了,
//          此时多出了word1的i位置字符,应把它删除掉,才能使此时word1的0~i(这个i是执行了删除操作后新的i)
//          和word2的0~j位置匹配,因此此时dp[i][j]=dp[i-1][j]+1(这个加1代表执行删除操作)
//       ③插入操作:若此时word1的0~i位置只是和word2的0~j-1位置匹配,
//           此时只需要在原来的i位置后面插入一个和word2的j位置相同的字符使得
//           此时的word1的0~i(这个i是执行了插入操作后新的i)和word2的0~j匹配得上,
//           所以此时dp[i][j]=dp[i][j-1]+1(这个加1代表执行插入操作)
//       ④由于题目所要求的是要最少的操作数:所以当word1[i] != word2[j] 时,
//           需要在这三个操作中选取一个最小的值赋格当前的dp[i][j]
// (三)总结:状态方程为:
// if(word1[i] == word2[j]):
//       dp[i][j] = dp[i-1][j-1]
// else:
//        min(dp[i-1][j-1],dp[i-1][j],dp[i][j-1])+1

class Solution {
 public:
  static constexpr int kInf = std::numeric_limits<int>::max();
  int minDistance(std::string word1, std::string word2) {
    // word1[i - 1] == word2[j - 1]: dp[i][j] = dp[i - 1][j - 1]
    // word1[i - 1] != word2[j - 1]:
    // dp[i][j] = dp[i - 1][j - 1] + 1 word1[i - 1]替换为word2[j - 1]
    // dp[i - 1][j] + 1 删除word1[i - 1]
    // dp[i][j - 1] + 1 word1[i - 1]插入一个字符
    int l1 = word1.size();
    int l2 = word2.size();
    // 如果任意一个字符串长度为0，则可以直接返回
    if (l1 == 0 || l2 == 0) {
      return std::max(l1, l2);
    }
    std::vector<std::vector<int>> dp(l1 + 1, std::vector<int>(l2 + 1, 0));
    // 边界条件是长度为0的时候，编辑距离为另一个字符串的长度
    dp[0][0] = 0;
    for (int i = 0; i < l2; ++i) {
      dp[0][i + 1] = i + 1;
    }
    for (int i = 0; i < l1; ++i) {
      dp[i + 1][0] = i + 1;
    }

    for (int i = 1; i <= l1; ++i) {
      for (int j = 1; j <= l2; ++j) {
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = std::min(dp[i - 1][j - 1], dp[i - 1][j]);
          dp[i][j] = std::min(dp[i][j], dp[i][j - 1]) + 1;
        }
      }
    }
    return dp[l1][l2];
  }
};