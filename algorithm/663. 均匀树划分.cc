/*
 * @lc app=leetcode.cn id=663 lang=cpp
 *
 * [663] 均匀树划分
 *
 * https://leetcode.cn/problems/equal-tree-partition/description/
 *
 * algorithms
 * Medium (45.89%)
 * Likes:    54
 * Dislikes: 0
 * Total Accepted:    2.7K
 * Total Submissions: 6K
 * Testcase Example:  '[5,10,10,null,null,2,3]'
 *
 * 给定一棵有 n 个结点的二叉树，你的任务是检查是否可以通过去掉树上的一条边将树分成两棵，且这两棵树结点之和相等。
 *
 * 样例 1:
 *
 * 输入:
 * ⁠   5
 * ⁠  / \
 * ⁠ 10 10
 * ⁠   /  \
 * ⁠  2   3
 *
 * 输出: True
 * 解释:
 * ⁠   5
 * ⁠  /
 * ⁠ 10
 * ⁠
 * 和: 15
 *
 * ⁠  10
 * ⁠ /  \
 * ⁠2    3
 *
 * 和: 15
 *
 *
 *
 *
 * 样例 2:
 *
 * 输入:
 * ⁠   1
 * ⁠  / \
 * ⁠ 2  10
 * ⁠   /  \
 * ⁠  2   20
 *
 * 输出: False
 * 解释: 无法通过移除一条树边将这棵树划分成结点之和相等的两棵子树。
 *
 *
 *
 *
 * 注释 :
 *
 *
 * 树上结点的权值范围 [-100000, 100000]。
 * 1 <= n <= 10000
 *
 *
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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
 public:
  // 两次遍历，第一次计算出所有节点的和
  // 第二次检查某个子树的和是否为总和的一半
  bool checkEqualTree(TreeNode* root) {
    if (root == nullptr) {
      return false;
    }
    int sum = GetSum(root);
    if (sum % 2 == 1 || sum % 2 == -1) {
      return false;
    }
    bool res = false;
    Check(root, sum / 2, res);
    return res;
  }
  int Check(TreeNode* root, int target, bool& res) {
    int sum = root->val;
    if (root->left) {
      int lsum = Check(root->left, target, res);
      sum += lsum;
      if (lsum == target) {
        res = true;
        return lsum;
      }
    }
    if (root->right) {
      int rsum = Check(root->right, target, res);
      sum += rsum;
      if (rsum == target) {
        res = true;
        return rsum;
      }
    }
    return sum;
  }
  int GetSum(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    return root->val + GetSum(root->left) + GetSum(root->right);
  }
};
