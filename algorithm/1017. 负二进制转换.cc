/*
 * @lc app=leetcode.cn id=1017 lang=cpp
 *
 * [1017] 负二进制转换
 *
 * https://leetcode.cn/problems/convert-to-base-2/description/
 *
 * algorithms
 * Medium (57.18%)
 * Likes:    66
 * Dislikes: 0
 * Total Accepted:    5K
 * Total Submissions: 8.8K
 * Testcase Example:  '2'
 *
 * 给你一个整数 n ，以二进制字符串的形式返回该整数的 负二进制（base -2）表示。
 * 
 * 注意，除非字符串就是 "0"，否则返回的字符串中不能含有前导零。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 2
 * 输出："110"
 * 解释：(-2)^2 + (-2)^1 = 2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 3
 * 输出："111"
 * 解释：(-2)^2 + (-2)^1 + (-2)^0 = 3
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：n = 4
 * 输出："100"
 * 解释：(-2)^2 = 4
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= n <= 10^9
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
    std::string baseNeg2(int n) {
        if (n == 0) {
            return "0";
        }
        std::string res;
        int m = 0;
        int y = 1;
        int x = n;
        while (x != 0) {
            if (x % 2 == 0) {
                res += "0";
            } else {
                res += "1";
            }
        }
        return res;
    }
};