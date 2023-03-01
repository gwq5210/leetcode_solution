/*
 * @lc app=leetcode.cn id=460 lang=cpp
 *
 * [460] LFU 缓存
 *
 * https://leetcode.cn/problems/lfu-cache/description/
 *
 * algorithms
 * Hard (44.42%)
 * Likes:    632
 * Dislikes: 0
 * Total Accepted:    60.7K
 * Total Submissions: 136.5K
 * Testcase Example:  '["LFUCache","put","put","get","put","get","get","put","get","get","get"]\n' +
  '[[2],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]'
 *
 * 请你为 最不经常使用（LFU）缓存算法设计并实现数据结构。
 *
 * 实现 LFUCache 类：
 *
 *
 * LFUCache(int capacity) - 用数据结构的容量 capacity 初始化对象
 * int get(int key) - 如果键 key 存在于缓存中，则获取键的值，否则返回 -1 。
 * void put(int key, int value) - 如果键 key 已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量
 * capacity
 时，则应该在插入新项之前，移除最不经常使用的项。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除
 最近最久未使用
 * 的键。
 *
 *
 * 为了确定最不常使用的键，可以为缓存中的每个键维护一个 使用计数器 。使用计数最小的键是最久未使用的键。
 *
 * 当一个键首次插入到缓存中时，它的使用计数器被设置为 1 (由于 put 操作)。对缓存中的键执行 get 或 put
 操作，使用计数器的值将会递增。
 *
 * 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
 *
 *
 *
 * 示例：
 *
 *
 * 输入：
 * ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get",
 * "get"]
 * [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
 * 输出：
 * [null, null, null, 1, null, -1, 3, null, -1, 3, 4]
 *
 * 解释：
 * // cnt(x) = 键 x 的使用计数
 * // cache=[] 将显示最后一次使用的顺序（最左边的元素是最近的）
 * LFUCache lfu = new LFUCache(2);
 * lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
 * lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
 * lfu.get(1);      // 返回 1
 * ⁠                // cache=[1,2], cnt(2)=1, cnt(1)=2
 * lfu.put(3, 3);   // 去除键 2 ，因为 cnt(2)=1 ，使用计数最小
 * ⁠                // cache=[3,1], cnt(3)=1, cnt(1)=2
 * lfu.get(2);      // 返回 -1（未找到）
 * lfu.get(3);      // 返回 3
 * ⁠                // cache=[3,1], cnt(3)=2, cnt(1)=2
 * lfu.put(4, 4);   // 去除键 1 ，1 和 3 的 cnt 相同，但 1 最久未使用
 * ⁠                // cache=[4,3], cnt(4)=1, cnt(3)=2
 * lfu.get(1);      // 返回 -1（未找到）
 * lfu.get(3);      // 返回 3
 * ⁠                // cache=[3,4], cnt(4)=1, cnt(3)=3
 * lfu.get(4);      // 返回 4
 * ⁠                // cache=[3,4], cnt(4)=2, cnt(3)=3
 *
 *
 *
 * 提示：
 *
 *
 * 0 <= capacity <= 10^4
 * 0 <= key <= 10^5
 * 0 <= value <= 10^9
 * 最多调用 2 * 10^5 次 get 和 put 方法
 *
 *
 */

#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// 
class LFUCacheHash {
 public:
  struct Node {
    int key = 0;
    int value = 0;
    int freq = 0;
  };
  LFUCacheHash(int capacity) : capacity_(capacity) {}

  int get(int key) {
    // printf("get key %d\n", key);
    auto it = Find(key);
    if (it == values_.end()) {
      return -1;
    }
    // printf("get key %d, value %d, freq %d\n", key, it->second->value, it->second->freq);
    return it->second->value;
  }

  void put(int key, int value) {
    // printf("put key %d, value %d\n", key, value);
    auto it = Find(key);
    if (it == values_.end()) {
      if (values_.size() == capacity_) {
        // 容量已满，则将访问频次最低的链表尾部的元素移除
        // min_freq_ 在更新时，已经确保其对应的链表上至少包含一个元素，因此该链表不为空
        auto& min_freq_lru = lfu_[min_freq_];
        // printf("size %zu, min_freq %d\n", lfu_[min_freq_].size(), min_freq_);
        // printf("erase min_freq %d, key %d, value %d, freq %d\n", min_freq_, std::prev(min_freq_lru.end())->key,
        //        std::prev(min_freq_lru.end())->value, std::prev(min_freq_lru.end())->freq);
        values_.erase(std::prev(min_freq_lru.end())->key);
        min_freq_lru.erase(std::prev(min_freq_lru.end()));
        if (min_freq_lru.empty()) {
          lfu_.erase(min_freq_);
        }
      }
      // 新插入的元素放在访问频次为 1 的链表头部
      // 同时最小的访问频次就是 1
      lfu_[1].emplace_front(Node{key, value, 1});
      values_[key] = lfu_[1].begin();
      min_freq_ = 1;
      // printf("put new key %d, value %d\n", key, value);
    } else {
      // printf("overwrite put key %d, value %d, old_value %d, freq %d\n", key, value, it->second->value,
      //        it->second->freq);
      // 找到对应的元素后，直接更新对应的值即可
      it->second->value = value;
    }
  }

  // 访问 key 所在的元素，如果不存在直接返回
  // 如果存在则更新访问频次，和最小的访问频次
  std::unordered_map<int, std::list<Node>::iterator>::iterator Find(int key) {
    auto it = values_.find(key);
    if (it == values_.end()) {
      return values_.end();
    }
    // 直接将 old_freq 对应的元素移动到 old_freq+1 对应的链表头部
    // splice 不会导致迭代器失效，只是元素对应的迭代器指向 old_freq+1 对应的链表
    int old_freq = it->second->freq;
    auto& new_list = lfu_[old_freq + 1];
    new_list.splice(new_list.begin(), lfu_[old_freq], it->second);
    it->second->freq++;

    // 如果 old_freq 对应的链表没有元素，则从 lfu_ 哈希表中移除
    // 同时更新 min_freq_
    if (lfu_[old_freq].empty()) {
      if (min_freq_ == old_freq) {
        min_freq_ = old_freq + 1;
      }
      lfu_.erase(old_freq);
    }
    return it;
  }

 private:
  int capacity_ = 0;
  int min_freq_ = 1;
  std::unordered_map<int, std::list<Node>> lfu_;
  std::unordered_map<int, std::list<Node>::iterator> values_;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */