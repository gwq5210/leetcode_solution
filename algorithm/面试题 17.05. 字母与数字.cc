/*
 * @lc app=leetcode.cn id= lang=cpp
 *
 * 面试题 17.05. 字母与数字
 *
 * https://leetcode.cn/problems/find-longest-subarray-lcci/
 *
给定一个放有字母和数字的数组，找到最长的子数组，且包含的字母和数字的个数相同。

返回该子数组，若存在多个最长子数组，返回左端点下标值最小的子数组。若不存在这样的数组，返回一个空数组。

示例 1:

输入: ["A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"]

输出: ["A","1","B","C","D","2","3","4","E","5","F","G","6","7"]
示例 2:

输入: ["A","A"]

输出: []
提示：

array.length <= 100000
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
  std::vector<std::string> findLongestSubarray(std::vector<std::string>& array) {
    // 分别表示数字和字母的数量
    int a = 0;
    int b = 0;
    // key 是字母比数字多的数量
    // value 是区间 [0, i) 中字母比数字多 key 个的下标中最小的 i
    std::unordered_map<int, int> idxs;
    int left = 0;
    int len = 0;
    for (int i = 0; i < array.size(); ++i) {
      if (!idxs.count(b - a)) {
        idxs[b - a] = i;
      }
      char c = array[i][0];
      if (std::isdigit(c)) {
        ++a;
      } else {
        ++b;
      }
      if (idxs.count(b - a)) {
        if (len < i - idxs[b - a] + 1) {
          len = i - idxs[b - a] + 1;
          left = idxs[b - a];
        }
      }
    }
    std::vector<std::string> res(array.begin() + left, array.begin() + len + left);
    return res;
  }
};