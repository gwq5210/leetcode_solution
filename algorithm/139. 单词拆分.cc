/*
 * @lc app=leetcode.cn id=139 lang=cpp
 *
 * [139] 单词拆分
 *
 * https://leetcode-cn.com/problems/word-break/description/
 *
 * algorithms
 * Medium (51.64%)
 * Likes:    1948
 * Dislikes: 0
 * Total Accepted:    402.2K
 * Total Submissions: 744.4K
 * Testcase Example:  '"leetcode"\n["leet","code"]'
 *
 * 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。
 *
 * 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入: s = "leetcode", wordDict = ["leet", "code"]
 * 输出: true
 * 解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
 *
 *
 * 示例 2：
 *
 *
 * 输入: s = "applepenapple", wordDict = ["apple", "pen"]
 * 输出: true
 * 解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
 * 注意，你可以重复使用字典中的单词。
 *
 *
 * 示例 3：
 *
 *
 * 输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
 * 输出: false
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 300
 * 1 <= wordDict.length <= 1000
 * 1 <= wordDict[i].length <= 20
 * s 和 wordDict[i] 仅有小写英文字母组成
 * wordDict 中的所有字符串 互不相同
 *
 *
 */

#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class Trie {
 public:
  static int CharToIndex(char c) { return c - 'a'; }
  struct Node {
    Node() : children(26) {}
    bool is_word = false;
    std::vector<std::shared_ptr<Node>> children;
  };

  Trie() : root_(std::make_shared<Node>()), vis_(302) {}
  void Insert(const std::string& str) {
    std::shared_ptr<Node> node = root_;
    for (int i = 0; i < str.size(); ++i) {
      char c = str[i];
      // printf("insert %c\n", c);
      int idx = CharToIndex(c);
      if (node->children[idx] == nullptr) {
        node->children[idx] = std::make_shared<Node>();
      }
      node = node->children[idx];
    }
    node->is_word = true;
  }
  bool Find(const std::string& str, int start) {
    if (vis_[start]) {
      return false;
    }
    if (start >= str.size()) {
      return true;
    }
    std::shared_ptr<Node> node = root_;
    for (int i = start; i < str.size(); ++i) {
      char c = str[i];
      int idx = CharToIndex(c);
      node = node->children[idx];
      if (node == nullptr) {
        return false;
      }
      if (node->is_word) {
        if (Find(str, i + 1)) {
          return true;
        }
        vis_[i + 1] = true;
      }
    }
    return false;
  }

 private:
  std::shared_ptr<Node> root_;
  std::vector<int> vis_;
};

class Solution {
 public:
  bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
    Trie trie;
    for (auto& str : wordDict) {
      trie.Insert(str);
    }
    return trie.Find(s, 0);
  }
};
