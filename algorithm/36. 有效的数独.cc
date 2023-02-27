/*
 * @lc app=leetcode.cn id=36 lang=cpp
 *
 * [36] 有效的数独
 *
 * https://leetcode.cn/problems/valid-sudoku/description/
 *
 * algorithms
 * Medium (63.29%)
 * Likes:    1046
 * Dislikes: 0
 * Total Accepted:    353.1K
 * Total Submissions: 558.2K
 * Testcase Example:
 * '[["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]'
 *
 * 请你判断一个 9 x 9 的数独是否有效。只需要 根据以下规则 ，验证已经填入的数字是否有效即可。
 *
 *
 * 数字 1-9 在每一行只能出现一次。
 * 数字 1-9 在每一列只能出现一次。
 * 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
 *
 *
 *
 *
 * 注意：
 *
 *
 * 一个有效的数独（部分已被填充）不一定是可解的。
 * 只需要根据以上规则，验证已经填入的数字是否有效即可。
 * 空白格用 '.' 表示。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：board =
 * [["5","3",".",".","7",".",".",".","."]
 * ,["6",".",".","1","9","5",".",".","."]
 * ,[".","9","8",".",".",".",".","6","."]
 * ,["8",".",".",".","6",".",".",".","3"]
 * ,["4",".",".","8",".","3",".",".","1"]
 * ,["7",".",".",".","2",".",".",".","6"]
 * ,[".","6",".",".",".",".","2","8","."]
 * ,[".",".",".","4","1","9",".",".","5"]
 * ,[".",".",".",".","8",".",".","7","9"]]
 * 输出：true
 *
 *
 * 示例 2：
 *
 *
 * 输入：board =
 * [["8","3",".",".","7",".",".",".","."]
 * ,["6",".",".","1","9","5",".",".","."]
 * ,[".","9","8",".",".",".",".","6","."]
 * ,["8",".",".",".","6",".",".",".","3"]
 * ,["4",".",".","8",".","3",".",".","1"]
 * ,["7",".",".",".","2",".",".",".","6"]
 * ,[".","6",".",".",".",".","2","8","."]
 * ,[".",".",".","4","1","9",".",".","5"]
 * ,[".",".",".",".","8",".",".","7","9"]]
 * 输出：false
 * 解释：除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。 但由于位于左上角的 3x3 宫内有两个 8
 * 存在, 因此这个数独是无效的。
 *
 *
 *
 * 提示：
 *
 *
 * board.length == 9
 * board[i].length == 9
 * board[i][j] 是一位数字（1-9）或者 '.'
 *
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
  bool isValidSudoku(std::vector<std::vector<char>>& board) {
    int m = board.size();
    int n = board[0].size();
    std::vector<std::vector<int>> rows(, std::vector<int>(9));
    std::vector<std::vector<int>> cols(9, std::vector<int>(9));
    std::vector<std::vector<int>> subboxes(9, std::vector<int>(9));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] != '.') {
          int x = board[i][j] - '0' - 1;
          ++rows[i][x];
          ++cols[j][x];
          int idx = (i / 3) * 3 + j / 3;
          ++subboxes[idx][x];
          if (rows[i][x] > 1 || cols[j][x] > 1 || subboxes[idx][x] > 1) {
            return false;
          }
        }
      }
    }
    return true;
  }
  bool isValidSudoku1(std::vector<std::vector<char>>& board) {
    int m = board.size();
    int n = board[0].size();
    for (int i = 0; i < m; ++i) {
      std::unordered_set<int> nums;
      for (int j = 0; j < n; ++j) {
        if (board[i][j] != '.') {
          if (nums.count(board[i][j] - '0')) {
            return false;
          }
          nums.emplace(board[i][j] - '0');
        }
      }
    }
    for (int j = 0; j < n; ++j) {
      std::unordered_set<int> nums;
      for (int i = 0; i < m; ++i) {
        if (board[i][j] != '.') {
          if (nums.count(board[i][j] - '0')) {
            return false;
          }
          nums.emplace(board[i][j] - '0');
        }
      }
    }
    for (int k = 0; k < 9; ++k) {
      int x = (k / 3) * 3;
      int y = (k % 3) * 3;
      std::unordered_set<int> nums;
      for (int i = x; i < x + 3; ++i) {
        for (int j = y; j < y + 3; ++j) {
          if (board[i][j] != '.') {
            if (nums.count(board[i][j] - '0')) {
              return false;
            }
            nums.emplace(board[i][j] - '0');
          }
        }
      }
    }
    return true;
  }
};