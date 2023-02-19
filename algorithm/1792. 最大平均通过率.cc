/*
 * @lc app=leetcode.cn id=1792 lang=cpp
 *
 * [1792] 最大平均通过率
 *
 * https://leetcode-cn.com/problems/maximum-average-pass-ratio/description/
 *
 * algorithms
 * Medium (51.34%)
 * Likes:    125
 * Dislikes: 0
 * Total Accepted:    19.1K
 * Total Submissions: 32.9K
 * Testcase Example:  '[[1,2],[3,5],[2,2]]\n2'
 *
 * 一所学校里有一些班级，每个班级里有一些学生，现在每个班都会进行一场期末考试。给你一个二维数组
 * classes ，其中 classes[i] = [passi,
 * totali] ，表示你提前知道了第 i 个班级总共有 totali 个学生，其中只有 passi 个学生可以通过考试。
 *
 * 给你一个整数 extraStudents ，表示额外有 extraStudents 个聪明的学生，他们 一定 能通过任何班级的期末考。你需要给这
 * extraStudents 个学生每人都安排一个班级，使得 所有 班级的 平均 通过率 最大 。
 *
 * 一个班级的 通过率 等于这个班级通过考试的学生人数除以这个班级的总人数。平均通过率 是所有班级的通过率之和除以班级数目。
 *
 * 请你返回在安排这 extraStudents 个学生去对应班级后的 最大 平均通过率。与标准答案误差范围在 10^-5
 * 以内的结果都会视为正确结果。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：classes = [[1,2],[3,5],[2,2]], extraStudents = 2
 * 输出：0.78333
 * 解释：你可以将额外的两个学生都安排到第一个班级，平均通过率为 (3/4 + 3/5 + 2/2) / 3 = 0.78333 。
 *
 *
 * 示例 2：
 *
 *
 * 输入：classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
 * 输出：0.53485
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 * classes[i].length == 2
 * 1 i i
 * 1
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
  struct Node {
    double p = 0;
    double t = 0;
    double Calc(int x) const {
      double res = x * (t - p);
      res /= t * (t + x);
      return res;
    }
    bool operator<(const Node& node) const { return Calc(1) < node.Calc(1); }
  };
  double maxAverageRatio(std::vector<std::vector<int>>& classes, int extraStudents) {
    double res = 0.0;
    // 使用优先队列存储通过率增加最多的班级
    std::priority_queue<Node> pq;
    for (auto& c : classes) {
      pq.push(Node{(double)c[0], (double)c[1]});
    }
    for (int i = 0; i < extraStudents; ++i) {
      Node top = pq.top();
      pq.pop();
      pq.push(Node{top.p + 1, top.t + 1});
    }
    while (!pq.empty()) {
      Node top = pq.top();
      pq.pop();
      res += top.p / top.t;
    }
    return res / classes.size();
  }
};