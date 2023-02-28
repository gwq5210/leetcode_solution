/*
 * @lc app=leetcode.cn id=211 lang=cpp
 *
 * [211] 添加与搜索单词 - 数据结构设计
 *
 * https://leetcode-cn.com/problems/design-add-and-search-words-data-structure/description/
 *
 * algorithms
 * Medium (48.05%)
 * Likes:    234
 * Dislikes: 0
 * Total Accepted:    23.2K
 * Total Submissions: 48.2K
 * Testcase Example:  '["WordDictionary","addWord","addWord","addWord","search","search","search","search"]\n' +
  '[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]'
 *
 * 请你设计一个数据结构，支持 添加新单词 和 查找字符串是否与任何先前添加的字符串匹配 。
 *
 * 实现词典类 WordDictionary ：
 *
 *
 * WordDictionary() 初始化词典对象
 * void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
 * bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true ；否则，返回  false 。word 中可能包含一些
 * '.' ，每个 . 都可以表示任何一个字母。
 *
 *
 *
 *
 * 示例：
 *
 *
 * 输入：
 *
 * ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
 * [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
 * 输出：
 * [null,null,null,null,false,true,true,true]
 *
 * 解释：
 * WordDictionary wordDictionary = new WordDictionary();
 * wordDictionary.addWord("bad");
 * wordDictionary.addWord("dad");
 * wordDictionary.addWord("mad");
 * wordDictionary.search("pad"); // return False
 * wordDictionary.search("bad"); // return True
 * wordDictionary.search(".ad"); // return True
 * wordDictionary.search("b.."); // return True
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= word.length <= 25
 * addWord 中的 word 由小写英文字母组成
 * search 中的 word 由 '.' 或小写英文字母组成
 * 最多调用 50000 次 addWord 和 search
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

// 使用 std::shared_ptr 会超时
class WordDictionarySharedPtr {
 public:
  static int CharToIndex(char c) { return c - 'a'; }
  struct Node {
    Node() : children(26) {}
    bool is_end = false;
    std::vector<std::shared_ptr<Node>> children;
  };
  /** Initialize your data structure here. */
  WordDictionarySharedPtr() : root_(std::make_shared<Node>()) {}

  void addWord(std::string word) {
    std::shared_ptr<Node> node = root_;
    for (char& c : word) {
      int index = CharToIndex(c);
      if (node->children[index] == nullptr) {
        node->children[index] = std::make_shared<Node>();
      }
      node = node->children[index];
    }
    node->is_end = true;
  }

  // bool search(std::string word) { return search(word, root_, 0); }
  bool search(std::string word) { return search2(word, root_, 0); }
  bool search2(const std::string& word, std::shared_ptr<Node> node, int l) {
    if (l >= word.size()) {
      return node->is_end;
    }
    char c = word[l];
    if (c != '.') {
      return node->children[CharToIndex(c)] && search2(word, node->children[CharToIndex(c)], l + 1);
    } else {
      for (int i = 0; i < node->children.size(); ++i) {
        if (node->children[i] && search2(word, node->children[i], l + 1)) {
          return true;
        }
      }
    }
    return false;
  }
  bool search(const std::string& word, std::shared_ptr<Node> node, int l) {
    if (node == nullptr) {
      return false;
    }
    if (l >= word.size()) {
      return node->is_end;
    }
    char c = word[l];
    if (c != '.') {
      return search(word, node->children[CharToIndex(c)], l + 1);
    } else {
      for (int i = 0; i < node->children.size(); ++i) {
        if (search(word, node->children[i], l + 1)) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  std::shared_ptr<Node> root_;
};

class WordDictionary {
 public:
  static int CharToIndex(char c) { return c - 'a'; }
  struct Node {
    Node() : children(26) {}
    ~Node() {
      for (auto* node : children) {
        delete node;
      }
    }
    bool is_end = false;
    std::vector<Node*> children;
  };
  /** Initialize your data structure here. */
  WordDictionary() : root_(new Node()) {}

  void addWord(std::string word) {
    Node* node = root_;
    for (char& c : word) {
      int index = CharToIndex(c);
      if (node->children[index] == nullptr) {
        node->children[index] = new Node();
      }
      node = node->children[index];
    }
    node->is_end = true;
  }

  // bool search(std::string word) { return search(word, root_, 0); }
  bool search(std::string word) { return search2(word, root_, 0); }
  bool search2(const std::string& word, Node* node, int l) {
    if (l >= word.size()) {
      return node->is_end;
    }
    char c = word[l];
    if (c != '.') {
      return node->children[CharToIndex(c)] && search2(word, node->children[CharToIndex(c)], l + 1);
    } else {
      for (int i = 0; i < node->children.size(); ++i) {
        if (node->children[i] && search2(word, node->children[i], l + 1)) {
          return true;
        }
      }
    }
    return false;
  }
  bool search(const std::string& word, Node* node, int l) {
    if (node == nullptr) {
      return false;
    }
    if (l >= word.size()) {
      return node->is_end;
    }
    char c = word[l];
    if (c != '.') {
      return search(word, node->children[CharToIndex(c)], l + 1);
    } else {
      for (int i = 0; i < node->children.size(); ++i) {
        if (search(word, node->children[i], l + 1)) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  Node* root_;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */