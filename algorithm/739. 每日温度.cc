/*
 * @lc app=leetcode.cn id=739 lang=cpp
 *
 * [739] 每日温度
 *
 * https://leetcode-cn.com/problems/daily-temperatures/description/
 *
 * algorithms
 * Medium (68.04%)
 * Likes:    1404
 * Dislikes: 0
 * Total Accepted:    394.8K
 * Total Submissions: 569.6K
 * Testcase Example:  '[73,74,75,71,69,72,76,73]'
 *
 * 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i
 * 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: temperatures = [73,74,75,71,69,72,76,73]
 * 输出: [1,1,4,2,1,1,0,0]
 *
 *
 * 示例 2:
 *
 *
 * 输入: temperatures = [30,40,50,60]
 * 输出: [1,1,1,0]
 *
 *
 * 示例 3:
 *
 *
 * 输入: temperatures = [30,60,90]
 * 输出: [1,1,0]
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= temperatures.length <= 10^5
 * 30 <= temperatures[i] <= 100
 *
 *
 */

#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
    std::vector<int> result(temperatures.size());
    std::stack<int> s;
    // 单调栈，栈中的元素从栈底到栈顶依次递减
    // 使用单调栈可以在O(n)的时间内求出元素左侧和右侧第一个比当前元素大或小的值
    for (int i = 0; i < temperatures.size(); ++i) {
      while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
        result[s.top()] = i - s.top();
        s.pop();
      }
      s.push(i);
    }
    return result;
  }
};