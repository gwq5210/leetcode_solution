/*
 * @lc app=leetcode.cn id=127 lang=cpp
 *
 * [127] 单词接龙
 *
 * https://leetcode.cn/problems/word-ladder/description/
 *
 * algorithms
 * Hard (48.14%)
 * Likes:    1198
 * Dislikes: 0
 * Total Accepted:    176.5K
 * Total Submissions: 366.7K
 * Testcase Example:  '"hit"\n"cog"\n["hot","dot","dog","lot","log","cog"]'
 *
 * 字典 wordList 中从单词 beginWord 和 endWord 的 转换序列 是一个按下述规格形成的序列 beginWord -> s1 ->
 * s2 -> ... -> sk：
 *
 *
 * 每一对相邻的单词只差一个字母。
 * 对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在 wordList 中。
 * sk == endWord
 *
 *
 * 给你两个单词 beginWord 和 endWord 和一个字典 wordList ，返回 从 beginWord 到 endWord 的 最短转换序列
 * 中的 单词数目 。如果不存在这样的转换序列，返回 0 。
 *
 *
 * 示例 1：
 *
 *
 * 输入：beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log","cog"]
 * 输出：5
 * 解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。
 *
 *
 * 示例 2：
 *
 *
 * 输入：beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log"]
 * 输出：0
 * 解释：endWord "cog" 不在字典中，所以无法进行转换。
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= beginWord.length <= 10
 * endWord.length == beginWord.length
 * 1 <= wordList.length <= 5000
 * wordList[i].length == beginWord.length
 * beginWord、endWord 和 wordList[i] 由小写英文字母组成
 * beginWord != endWord
 * wordList 中的所有字符串 互不相同
 *
 *
 */

#include <queue>
#include <string>
#include <vector>

class Solution {
 public:
  bool Check(const std::string& start, const std::string& end) {
    int count = 0;
    for (int i = 0; i < start.size() && count <= 1; ++i) {
      if (start[i] != end[i]) {
        ++count;
      }
    }
    return count <= 1;
  }
  int BBFS(int from, int to, std::vector<std::string>& word_list) {
    std::queue<int> to_q;
    std::queue<int> from_q;
    std::vector<int> to_dis(word_list.size() + 1);
    std::vector<int> from_dis(word_list.size() + 1);
    from_dis[from] = 1;
    to_dis[to] = 1;
    to_q.push(to);
    from_q.push(from);
    while (!from_q.empty() && !to_q.empty()) {
      int from_count = from_q.size();
      int to_count = to_q.size();
      if (from_count < to_count) {
        for (int i = 0; i < from_count; ++i) {
          int u = from_q.front();
          from_q.pop();
          if (to_dis[u] != 0) {
            return from_dis[u] + to_dis[u] - 1;
          }
          for (int v : adjs_[u]) {
            if (from_dis[v] == 0) {
              from_q.push(v);
              from_dis[v] = from_dis[u] + 1;
            }
          }
        }
      } else {
        for (int i = 0; i < to_count; ++i) {
          int u = to_q.front();
          to_q.pop();
          if (from_dis[u] != 0) {
            return from_dis[u] + to_dis[u] - 1;
          }
          for (int v : adjs_[u]) {
            if (to_dis[v] == 0) {
              to_q.push(v);
              to_dis[v] = to_dis[u] + 1;
            }
          }
        }
      }
    }
    return 0;
  }
  int BFS(int from, int to, std::vector<std::string>& word_list) {
    std::queue<int> q;
    std::vector<int> dis(word_list.size() + 1);
    dis[from] = 1;
    q.push(from);
    while (!q.empty()) {
      int count = q.size();
      for (int i = 0; i < count; ++i) {
        int u = q.front();
        q.pop();
        if (u == to) {
          return dis[u];
        }
        for (int v : adjs_[u]) {
          if (dis[v] == 0) {
            q.push(v);
            dis[v] = dis[u] + 1;
          }
        }
      }
    }
    return 0;
  }
  int ladderLength(std::string begin_word, std::string end_word, std::vector<std::string>& word_list) {
    int target = -1;
    int from = 0;
    adjs_ = std::vector<std::vector<int>>(word_list.size() + 1);
    for (int i = 0; i < word_list.size(); ++i) {
      if (word_list[i] == end_word) {
        target = i + 1;
      }
      if (Check(begin_word, word_list[i])) {
        adjs_[from].emplace_back(i + 1);
        adjs_[i + 1].emplace_back(from);
      }
      for (int j = i + 1; j < word_list.size(); ++j) {
        if (Check(word_list[i], word_list[j])) {
          adjs_[i + 1].emplace_back(j + 1);
          adjs_[j + 1].emplace_back(i + 1);
        }
      }
    }
    if (target < 0) {
      return 0;
    }
    // return BFS(from, target, word_list);
    return BBFS(from, target, word_list);
  }

 private:
  std::vector<std::vector<int>> adjs_;
};
