/*
 * @lc app=leetcode.cn id=297 lang=cpp
 *
 * [297] 二叉树的序列化与反序列化
 *
 * https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/description/
 *
 * algorithms
 * Hard (58.72%)
 * Likes:    1067
 * Dislikes: 0
 * Total Accepted:    203.1K
 * Total Submissions: 345.7K
 * Testcase Example:  '[1,2,3,null,null,4,5]'
 *
 *
 * 序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
 *
 * 请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 /
 * 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
 *
 * 提示: 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode
 * 序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：root = [1,2,3,null,null,4,5]
 * 输出：[1,2,3,null,null,4,5]
 *
 *
 * 示例 2：
 *
 *
 * 输入：root = []
 * 输出：[]
 *
 *
 * 示例 3：
 *
 *
 * 输入：root = [1]
 * 输出：[1]
 *
 *
 * 示例 4：
 *
 *
 * 输入：root = [1,2]
 * 输出：[1,2]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 树中结点数在范围 [0, 10^4] 内
 * -1000 <= Node.val <= 1000
 *
 *
 */

#include <cstdio>
#include <iterator>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec1 {
 public:
  struct EdgeInfo {
    int from_id = 0;
    int to_id = 0;
    bool is_left = false;
  };

  // Encodes a tree to a single string.
  void AddEdge(int from_id, int to_id, bool is_left, std::string& result) {
    if (!result.empty()) {
      result += ",";
    }
    result += std::to_string(from_id);
    result += is_left ? "-" : "=";
    result += std::to_string(to_id);
  }
  std::string serialize(TreeNode* root) {
    if (root == nullptr) {
      return "";
    }
    int cnt = 0;
    std::queue<std::pair<TreeNode*, int>> q;
    q.push(std::make_pair(root, cnt));
    cnt++;
    std::string nodes_str;
    std::string edges_str;
    while (!q.empty()) {
      auto [node, from_id] = q.front();
      if (!nodes_str.empty()) {
        nodes_str += ",";
      }
      nodes_str += std::to_string(from_id) + ":" + std::to_string(node->val);
      if (node->left != nullptr) {
        AddEdge(from_id, cnt, true, edges_str);
        q.push(std::make_pair(node->left, cnt));
        cnt++;
      }
      if (node->right != nullptr) {
        AddEdge(from_id, cnt, false, edges_str);
        q.push(std::make_pair(node->right, cnt));
        cnt++;
      }
      q.pop();
    }
    return nodes_str + "|" + edges_str;
  }

  void ParseNodes(std::string_view nodes_str, std::unordered_map<int, int>& values) {
    int left = 0;
    while (left < nodes_str.size()) {
      int right = left;
      while (right < nodes_str.size() && nodes_str[right] != ',') {
        ++right;
      }
      ParseNode(std::string_view(nodes_str.data() + left, right - left), values);
      left = right + 1;
    }
  }

  int ParseNode(std::string_view node_str, std::unordered_map<int, int>& values) {
    int id = 0;
    int value = 0;
    int i = 0;
    while (i < node_str.size() && std::isdigit(node_str[i])) {
      id = id * 10 + node_str[i] - '0';
      ++i;
    }
    ++i;
    int flag = 1;
    if (node_str[i] == '-') {
      flag = -1;
      ++i;
    } else if (node_str[i] == '+') {
      ++i;
    }
    while (i < node_str.size()) {
      value = value * 10 + node_str[i] - '0';
      ++i;
    }
    values[id] = value * flag;
    return id;
  }

  void ParseEdges(std::string_view edges_str, std::vector<EdgeInfo>& edges) {
    int left = 0;
    while (left < edges_str.size()) {
      int right = left;
      while (right < edges_str.size() && edges_str[right] != ',') {
        ++right;
      }
      ParseEdge(std::string_view(edges_str.data() + left, right - left), edges);
      left = right + 1;
    }
  }
  void ParseEdge(std::string_view edge_str, std::vector<EdgeInfo>& edges) {
    int from_id = 0;
    int to_id = 0;
    int i = 0;
    while (i < edge_str.size() && std::isdigit(edge_str[i])) {
      from_id = from_id * 10 + edge_str[i] - '0';
      ++i;
    }
    int idx = i++;
    while (i < edge_str.size()) {
      to_id = to_id * 10 + edge_str[i] - '0';
      ++i;
    }
    edges.emplace_back(EdgeInfo{from_id, to_id, edge_str[idx] == '-'});
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(std::string data) {
    if (data.empty()) {
      return nullptr;
    }

    // printf("%s\n", data.c_str());
    size_t idx = data.find("|");
    std::string_view nodes_str(data.c_str(), idx);
    std::string_view edges_str(data.c_str() + idx + 1, data.size() - idx - 1);
    std::unordered_map<int, int> values;
    std::vector<EdgeInfo> edges;
    ParseNodes(nodes_str, values);
    ParseEdges(edges_str, edges);
    // printf("values count %zu\n", values.size());
    std::unordered_map<int, TreeNode*> nodes;
    for (auto [id, value] : values) {
      // printf("%d:%d\n", id, value);
      nodes[id] = new TreeNode(value);
    }
    for (auto [from_id, to_id, is_left] : edges) {
      // printf("%d %c %d\n", from_id, is_left ? '-' : '=', to_id);
      if (is_left) {
        nodes[from_id]->left = nodes[to_id];
      } else {
        nodes[from_id]->right = nodes[to_id];
      }
    }
    // std::string tree_str = serialize(nodes[0]);
    // printf("tree_str %s\n", tree_str.c_str());
    return nodes[0];
  }
};

class Codec {
 public:
  // 选择前序遍历，是因为 根∣左∣右 的打印顺序，在反序列化时更容易定位出根节点的值。
  // 遇到 null 节点也要翻译成特定符号，反序列化时才知道这里是 null。
  // Encodes a tree to a single string.
  std::string serialize(TreeNode* root) {
    if (root == nullptr) {
      return "X";
    }
    std::string left_result = serialize(root->left);
    std::string right_result = serialize(root->right);
    std::string result = std::to_string(root->val) + "," + left_result + "," + right_result;
    // printf("%s\n", result.c_str());
    return result;
  }

  // 序列化的过程，左右子树一定是以两个 X 结尾（两个空节点结尾），因此 index 一定不会超过 tokens 的大小
  TreeNode* DeserializeDFS(std::vector<std::string_view>& tokens, int& index) {
    if (tokens[index] == "X") {
      ++index;
      return nullptr;
    }
    std::string_view token = tokens[index];
    int i = 0;
    int flag = 1;
    int value = 0;
    if (token[i] == '-') {
      flag = -1;
      ++i;
    } else if (token[i] == '+') {
      ++i;
    }
    while (i < token.size()) {
      value = value * 10 + token[i] - '0';
      ++i;
    }
    value *= flag;
    TreeNode* root = new TreeNode(value);
    ++index;
    root->left = DeserializeDFS(tokens, index);
    root->right = DeserializeDFS(tokens, index);
    return root;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(std::string data) {
    if (data == "X") {
      return nullptr;
    }
    std::vector<std::string_view> tokens;
    int left = 0;
    while (left < data.size()) {
      int right = left;
      while (right < data.size() && data[right] != ',') {
        ++right;
      }
      tokens.emplace_back(data.c_str() + left, right - left);
      left = right + 1;
    }
  
    int index = 0;
    return DeserializeDFS(tokens, index);
  }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));