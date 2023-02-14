/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存
 *
 * https://leetcode.cn/problems/lru-cache/description/
 *
 * algorithms
 * Medium (53.44%)
 * Likes:    2541
 * Dislikes: 0
 * Total Accepted:    446K
 * Total Submissions: 834.6K
 * Testcase Example:  '["LRUCache","put","put","get","put","get","put","get","get","get"]\n' +
  '[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]'
 *
 * 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
 *
 * 实现 LRUCache 类：
 *
 *
 *
 *
 * LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
 * int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
 * void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组
 * key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
 *
 *
 * 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
 *
 *
 *
 *
 *
 * 示例：
 *
 *
 * 输入
 * ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
 * [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
 * 输出
 * [null, null, null, 1, null, -1, null, -1, 3, 4]
 *
 * 解释
 * LRUCache lRUCache = new LRUCache(2);
 * lRUCache.put(1, 1); // 缓存是 {1=1}
 * lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
 * lRUCache.get(1);    // 返回 1
 * lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
 * lRUCache.get(2);    // 返回 -1 (未找到)
 * lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
 * lRUCache.get(1);    // 返回 -1 (未找到)
 * lRUCache.get(3);    // 返回 3
 * lRUCache.get(4);    // 返回 4
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= capacity <= 3000
 * 0 <= key <= 10000
 * 0 <= value <= 10^5
 * 最多调用 2 * 10^5 次 get 和 put
 *
 *
 */

#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// LRU是Least Recently Used的缩写，即最近最少使用
// 是一种常用的页面置换算法，选择最近最久未使用的页面予以淘汰。该算法赋予每个页面一个访问字段，用来记录一个页面自上次被访问以来所经历的时间
// t，当须淘汰一个页面时，选择现有页面中其 t 值最大的，即最近最少使用的页面予以淘汰。
class LRUCache {
 public:
  LRUCache(int capacity) : capacity_(capacity) {}

  int get(int key) {
    // printf("get %d\n", key);
    auto it = Find(key);
    if (it == kvs_.end()) {
      return -1;
    }
    // printf("get %d %d\n", key, it->second->second);
    return it->second->second;
  }

  void put(int key, int value) {
    auto it = Find(key);
    if (it != kvs_.end()) {
      // printf("put key %d, value %d -> %d\n", key, *it->second, value);
      it->second->second = value;
    } else {
      if (kvs_.size() >= capacity_) {
        // printf("del key %d, value %d\n", key, value);
        kvs_.erase(lru_.back().first);
        lru_.pop_back();
      }
      // printf("put key %d, value %d\n", key, value);
      lru_.emplace_front(std::make_pair(key, value));
      kvs_.emplace(key, lru_.begin());
    }
  }

  std::unordered_map<int, std::list<std::pair<int, int>>::iterator>::iterator Find(int key) {
    auto it = kvs_.find(key);
    if (it == kvs_.end()) {
      return it;
    }
    lru_.splice(lru_.begin(), lru_, it->second);
    // auto kv = *it->second;
    // lru_.erase(it->second);
    // lru_.emplace_front(kv);
    // it->second = lru_.begin();
    return it;
  }

 private:
  int capacity_ = 0;
  std::list<std::pair<int, int>> lru_;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> kvs_;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
