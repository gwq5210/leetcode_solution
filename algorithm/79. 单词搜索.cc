/*
 * @lc app=leetcode.cn id=79 lang=cpp
 *
 * [79] 单词搜索
 *
 * https://leetcode.cn/problems/word-search/description/
 *
 * algorithms
 * Medium (46.48%)
 * Likes:    1536
 * Dislikes: 0
 * Total Accepted:    401.9K
 * Total Submissions: 865K
 * Testcase Example:  '[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]\n"ABCCED"'
 *
 * 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false
 * 。
 *
 * 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
 * "ABCCED"
 * 输出：true
 *
 *
 * 示例 2：
 *
 *
 * 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
 * "SEE"
 * 输出：true
 *
 *
 * 示例 3：
 *
 *
 * 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
 * "ABCB"
 * 输出：false
 *
 *
 *
 *
 * 提示：
 *
 *
 * m == board.length
 * n = board[i].length
 * 1
 * 1
 * board 和 word 仅由大小写英文字母组成
 *
 *
 *
 *
 * 进阶：你可以使用搜索剪枝的技术来优化解决方案，使其在 board 更大的情况下可以更快解决问题？
 *
 */

#include <deque>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  bool DFS(std::vector<std::vector<char>>& board, const std::string& word, int index, int x, int y, int m, int n,
           int left_count) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    if (left_count < word.size() - index) {
      return false;
    }
    // 回溯时注意边界条件
    if (index == word.size() - 1) {
      return board[x][y] == word[index];
    }
    if (board[x][y] != word[index]) {
      return false;
    }
    // 更好的写法，因为 index 一定不会等于 word.size()
    // if (board[x][y] != word[index]) {
    //   return false;
    // } else if (index == word.size() - 1) {
    //   return true;
    // }
    --left_count;
    char c = board[x][y];
    board[x][y] = '\0';
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
        if (DFS(board, word, index + 1, nx, ny, m, n, left_count)) {
          return true;
        }
      }
    }
    ++left_count;
    board[x][y] = c;
    return false;
  }
  bool exist(std::vector<std::vector<char>>& board, std::string word) {
    int m = board.size();
    int n = board[0].size();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (DFS(board, word, 0, i, j, m, n, m * n)) {
          return true;
        }
      }
    }
    return false;
  }
};