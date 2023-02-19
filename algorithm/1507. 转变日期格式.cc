/*
 * @lc app=leetcode.cn id=1507 lang=cpp
 *
 * [1507] 转变日期格式
 *
 * https://leetcode.cn/problems/reformat-date/description/
 *
 * algorithms
 * Easy (58.90%)
 * Likes:    20
 * Dislikes: 0
 * Total Accepted:    14.5K
 * Total Submissions: 24.6K
 * Testcase Example:  '"20th Oct 2052"'
 *
 * 给你一个字符串 date ，它的格式为 Day Month Year ，其中：
 *
 *
 * Day 是集合 {"1st", "2nd", "3rd", "4th", ..., "30th", "31st"} 中的一个元素。
 * Month 是集合 {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
 * "Oct", "Nov", "Dec"} 中的一个元素。
 * Year 的范围在 ​[1900, 2100] 之间。
 *
 *
 * 请你将字符串转变为 YYYY-MM-DD 的格式，其中：
 *
 *
 * YYYY 表示 4 位的年份。
 * MM 表示 2 位的月份。
 * DD 表示 2 位的天数。
 *
 *
 *
 *
 * 示例 1：
 *
 * 输入：date = "20th Oct 2052"
 * 输出："2052-10-20"
 *
 *
 * 示例 2：
 *
 * 输入：date = "6th Jun 1933"
 * 输出："1933-06-06"
 *
 *
 * 示例 3：
 *
 * 输入：date = "26th May 1960"
 * 输出："1960-05-26"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 给定日期保证是合法的，所以不需要处理异常输入。
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
  std::string reformatDate(std::string date) {
    std::unordered_map<std::string, std::string> months{{"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"},
                                                        {"May", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"},
                                                        {"Sep", "09"}, {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}};
    int i = 0;
    int l = 0;
    std::string day, month, year;
    int count = 0;
    while (i < date.size()) {
      int r = i;
      while (r < date.size() && date[r] != ' ') {
        ++r;
      }
      if (count == 0) {
        day = date.substr(i, r - i - 2);
        if (day.size() == 1) {
          day = "0" + day;
        }
      } else if (count == 1) {
        month = months[date.substr(i, r - i)];
      } else {
        year = date.substr(i, r - i);
      }
      ++count;
      i = r + 1;
    }
    return year + "-" + month + "-" + day;
  }
};