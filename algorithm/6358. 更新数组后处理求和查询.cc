/*
 * @lc app=leetcode.cn id=6358 lang=cpp
 *
 * 6358. 更新数组后处理求和查询
 *
 * https://leetcode.cn/problems/handling-sum-queries-after-update/description/
 *
给你两个下标从 0 开始的数组 nums1 和 nums2 ，和一个二维数组 queries 表示一些操作。总共有 3 种类型的操作：

操作类型 1 为 queries[i] = [1, l, r] 。你需要将 nums1 从下标 l 到下标 r 的所有 0 反转成 1 或将 1 反转成 0 。l 和 r
下标都从 0 开始。 操作类型 2 为 queries[i] = [2, p, 0] 。对于 0 <= i < n 中的所有下标，令 nums2[i] = nums2[i] + nums1[i]
* p 。 操作类型 3 为 queries[i] = [3, 0, 0] 。求 nums2 中所有元素的和。 请你返回一个数组，包含所有第三种操作类型的答案。



示例 1：

输入：nums1 = [1,0,1], nums2 = [0,0,0], queries = [[1,1,1],[2,1,0],[3,0,0]]
输出：[3]
解释：第一个操作后 nums1 变为 [1,1,1] 。第二个操作后，nums2 变成 [1,1,1] ，所以第三个操作的答案为 3 。所以返回 [3] 。
示例 2：

输入：nums1 = [1], nums2 = [5], queries = [[2,0,0],[3,0,0]]
输出：[5]
解释：第一个操作后，nums2 保持不变为 [5] ，所以第二个操作的答案是 5 。所以返回 [5] 。


提示：

1 <= nums1.length,nums2.length <= 10^5
nums1.length = nums2.length
1 <= queries.length <= 10^5
queries[i].length = 3
0 <= l <= r <= nums1.length - 1
0 <= p <= 10^6
0 <= nums1[i] <= 1
0 <= nums2[i] <= 10^9

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

template <typename T>
class SegTree {
 public:
  struct Node {
    T val = 0;
    T lazy = 0;
  };

  SegTree(const std::vector<int>& arr) : arr_(arr) {
    // 根节点区间范围是[0, end_]
    end_ = arr.size() - 1;
    // 线段树节点的数量是4*arr.size()
    nodes_.resize(arr.size() * 4);
    // 递归建树
    Build(0, end_, root_);
  }

  // 对 [l,r] 区间建立线段树,当前根的编号为 p
  void Build(int l, int r, int p) {
    // 如果区间数目为1，则直接更新树节点的值
    if (l == r) {
      nodes_[p].val = arr_[l];
      return;
    }

    // 如果写成 (l + r) / 2 可能会超出 int 范围
    int mid = l + (r - l) / 2;
    // 递归对左[l, mid]右[mid + 1, r]区间建树
    Build(l, mid, p * 2);
    Build(mid + 1, r, p * 2 + 1);
    // 从子节点更新当前节点p
    PushUp(p);
  }

  // 从子节点更新当前节点p
  void PushUp(int p) { nodes_[p].val = nodes_[p * 2].val + nodes_[p * 2 + 1].val; }
  // 如果当前节点 p 的懒标记非空,则更新当前节点两个子节点的值和懒标记值
  void PushDown(int pl, int pr, int p) {
    if (!nodes_[p].lazy) {
      return;
    }
    int mid = pl + (pr - pl) / 2;
    UpdateNode(pl, mid, p * 2, nodes_[p].lazy);
    UpdateNode(mid + 1, pr, p * 2 + 1, nodes_[p].lazy);
    nodes_[p].lazy = 0;
  }
  void UpdateNode(int pl, int pr, int p, T val) {
    nodes_[p].val = (pr - pl + 1) * val - nodes_[p].val;
    nodes_[p].lazy ^= val;
  }

  // 返回区间[0, end_]的结果
  int Query() { return Query(0, end_, 0, end_, root_); }
  // 返回区间[l, r]的结果
  int Query(int l, int r) { return Query(l, r, 0, end_, root_); }

  // [l, r] 为查询区间, [pl, pr] 为当前节点包含的区间, p 为当前节点的编号
  int Query(int l, int r, int pl, int pr, int p) {
    // 当前区间为询问区间的子集时直接返回当前区间的结果
    if (pl >= l && pr <= r) {
      return nodes_[p].val;
    }

    //
    PushDown(pl, pr, p);

    // 递归求左右区间的结果
    int sum = 0;
    int mid = pl + (pr - pl) / 2;
    if (mid >= l) {
      // 如果左儿子代表的区间 [pl, mid] 与询问区间有交集, 则递归查询左儿子
      sum += Query(l, r, pl, mid, p * 2);
    }
    if (mid + 1 <= r) {
      // 如果右儿子代表的区间 [mid + 1, pr] 与询问区间有交集, 则递归查询右儿子
      sum += Query(l, r, mid + 1, pr, p * 2 + 1);
    }
    return sum;
  }

  // 修改区间[l, r]的值
  void Modify(int l, int r, int val) { Modify(l, r, val, 0, end_, root_); }
  // [l, r] 为修改区间, val 为被修改的元素的变化量
  // [pl, pr] 为当前节点包含的区间, p 为当前节点的编号
  void Modify(int l, int r, T val, int pl, int pr, int p) {
    if (pl >= l && pr <= r) {
      // 当前区间为修改区间的子集时直接修改当前节点的值,然后打标记,结束修改
      UpdateNode(pl, pr, p, val);
      return;
    }

    // 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
    PushDown(pl, pr, p);

    // 递归更新左右区间的值
    int mid = pl + (pr - pl) / 2;
    if (mid >= l) {
      // 如果左儿子代表的区间 [pl, mid] 与更新区间有交集, 则递归更新左儿子
      Modify(l, r, val, pl, mid, p * 2);
    }
    if (mid + 1 <= r) {
      // 如果右儿子代表的区间 [mid + 1, pr] 与更新区间有交集, 则递归更新右儿子
      Modify(l, r, val, mid + 1, pr, p * 2 + 1);
    }

    // 使用左右子节点的值更新当前节点的值
    PushUp(p);
  }

  // 根节点，表示的范围为[0, end_]
  int root_ = 1;
  int end_ = 0;
  std::vector<Node> nodes_;
  const std::vector<T>& arr_;
};

class Solution {
 public:
  std::vector<long long> handleQuery(std::vector<int>& nums1, std::vector<int>& nums2,
                                     std::vector<std::vector<int>>& queries) {
    // 区间修改和区间查询问题，使用线段树
    // 由于操作 2 和操作 3 更新和统计的是所有 nums2[i]的值，那么我们其实只需要维护 nums1 中 1 的个数。
    // 用线段树维护区间内 1 的个数 cnt1 ​，以及区间反转标记 rev。
    // lazy更新时，需要根据当前lazy的值来确定，1->0或0->1可以通过异或1实现
    std::vector<long long> result;
    int n = nums1.size();
    long long sum = 0;
    for (int num : nums2) {
      sum += num;
    }
    SegTree<int> seg_tree(nums1);
    for (auto& query : queries) {
      int type = query[0];
      if (type == 1) {
        seg_tree.Modify(query[1], query[2], 1);
      } else if (type == 2) {
        long long count = seg_tree.Query(0, n - 1);
        sum += query[1] * count;
      } else {
        result.emplace_back(sum);
      }
    }
    return result;
  }
};