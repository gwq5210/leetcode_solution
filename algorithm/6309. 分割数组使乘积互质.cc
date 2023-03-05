/*
 * @lc app=leetcode.cn id=6309 lang=cpp
 *
 * [6309] 分割数组使乘积互质
 *
 * https://leetcode.cn/problems/split-the-array-to-make-coprime-products/
 *
给你一个长度为 n 的整数数组 nums ，下标从 0 开始。

如果在下标 i 处 分割 数组，其中 0 <= i <= n - 2 ，使前 i + 1 个元素的乘积和剩余元素的乘积互质，则认为该分割 有效 。

例如，如果 nums = [2, 3, 3] ，那么在下标 i = 0 处的分割有效，因为 2 和 9 互质，而在下标 i = 1 处的分割无效，因为 6 和 3
不互质。在下标 i = 2 处的分割也无效，因为 i == n - 1 。 返回可以有效分割数组的最小下标 i ，如果不存在有效分割，则返回 -1
。

当且仅当 gcd(val1, val2) == 1 成立时，val1 和 val2 这两个值才是互质的，其中 gcd(val1, val2) 表示 val1 和 val2
的最大公约数。



示例 1：



输入：nums = [4,7,8,15,3,5]
输出：2
解释：上表展示了每个下标 i 处的前 i + 1 个元素的乘积、剩余元素的乘积和它们的最大公约数的值。
唯一一个有效分割位于下标 2 。
示例 2：



输入：nums = [4,7,15,8,3,5]
输出：-1
解释：上表展示了每个下标 i 处的前 i + 1 个元素的乘积、剩余元素的乘积和它们的最大公约数的值。
不存在有效分割。


提示：

n == nums.length
1 <= n <= 104
1 <= nums[i] <= 106
 *
 *
 */

#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool is_init = false;
int max_v = 1000001;

class Solution {
 public:
  static void Init(std::vector<std::vector<int>>& arr) {
    // 预先打表
    if (is_init) {
      return;
    }
    is_init = true;
    std::vector<int> is_primes(max_v, 1);
    is_primes[0] = is_primes[1] = 0;
    int y = 0;
    // 这里是求质因子，与一般素数筛法不同
    // 一般素数筛法，筛选到 i * i <= n 即可
    for (int i = 2; i < max_v; ++i) {
      if (is_primes[i]) {
        arr[i].emplace_back(i);
        // 一般的素数筛法，j 初始值为 i * i
        // 2*i, 3*i, ... 这些数已经被前面的素数筛选出去了
        for (long long j = (long long)2 * i; j < max_v; j += i) {
          is_primes[j] = false;
          arr[j].emplace_back(i);
        }
      }
    }
  }
  int findValidSplit1(std::vector<int>& nums) {
    // 保存某一个数的质因子
    static std::vector<std::vector<int>> arr(max_v);
    Init(arr);

    // 分别保存 [0, i] 和 (i, nums.size()) 区间内包含的质因子
    std::unordered_map<int, int> prefix_stats, suffix_stats;
    for (int num : nums) {
      for (int v : arr[num]) {
        ++suffix_stats[v];
      }
    }
    int n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
      for (int v : arr[nums[i]]) {
        --suffix_stats[v];
        ++prefix_stats[v];
        if (suffix_stats[v] == 0) {
          suffix_stats.erase(v);
        }
      }
      // 如果两者的质因子没有重合，则找到了答案
      bool flag = true;
      for (auto [k, c] : prefix_stats) {
        if (suffix_stats.count(k)) {
          flag = false;
          break;
        }
      }
      if (flag) {
        return i;
      }
    }
    return -1;
  }
  int findValidSplit2(std::vector<int>& nums) {
    int n = nums.size();
    int max_element = *std::max_element(nums.begin(), nums.end()) + 1;
    int limit = std::sqrt(max_element) + 5;
    std::vector<int> primes;
    std::vector<int> is_primes(limit, 1);
    is_primes[0] = is_primes[1] = 0;
    for (int i = 2; i * i < limit; ++i) {
      if (is_primes[i]) {
        for (int j = i * i; j < limit; j += i) {
          is_primes[j] = false;
        }
      }
    }
    for (int i = 2; i < limit; ++i) {
      if (is_primes[i]) {
        primes.emplace_back(i);
      }
    }
    // 保存第 i 个数对应的质因子
    // 这里使用 nums[i] 当做下标需要去重才可以
    std::vector<std::vector<int>> arr(n);
    for (int i = 0; i < nums.size(); ++i) {
      int x = nums[i];
      for (int p : primes) {
        if (p * p > x) {
          break;
        }
        if (x % p == 0) {
          arr[i].emplace_back(p);
        }
        while (x % p == 0) {
          x /= p;
        }
      }
      if (x > 1) {
        arr[i].emplace_back(x);
      }
    }

    // 分别保存 [0, i] 和 (i, nums.size()) 区间内包含的质因子
    std::unordered_map<int, int> prefix_stats, suffix_stats;
    for (int i = 0; i < nums.size(); ++i) {
      for (int v : arr[i]) {
        ++suffix_stats[v];
      }
    }
    for (int i = 0; i < n - 1; ++i) {
      for (int v : arr[i]) {
        --suffix_stats[v];
        ++prefix_stats[v];
        if (suffix_stats[v] == 0) {
          suffix_stats.erase(v);
        }
      }
      // 如果两者的质因子没有重合，则找到了答案
      bool flag = true;
      for (auto [k, c] : prefix_stats) {
        if (suffix_stats.count(k)) {
          flag = false;
          break;
        }
      }
      if (flag) {
        return i;
      }
    }
    return -1;
  }

  // 若两个乘积互质，说明两个乘积的质因数分解不包含公共的质数。因此题目可以转化为：
  // 求最小的分割点，使得分割点左边所有数的质因数分解，和分割点右边所有数的质因数分解，不包含公共的质数。
  // 我们考虑一个质数 p，为了满足以上条件，分割点左边要么不包含 p，要么必须包含所有 p。
  // 枚举分割点并检查是否所有质数都满足条件
  int findValidSplit(std::vector<int>& nums) {
    int n = nums.size();
    int max_element = *std::max_element(nums.begin(), nums.end()) + 1;
    int limit = std::sqrt(max_element) + 5;
    std::vector<int> primes;
    std::vector<int> is_primes(limit, 1);
    is_primes[0] = is_primes[1] = 0;
    for (int i = 2; i * i < limit; ++i) {
      if (is_primes[i]) {
        for (int j = i * i; j < limit; j += i) {
          is_primes[j] = false;
        }
      }
    }
    for (int i = 2; i < limit; ++i) {
      if (is_primes[i]) {
        primes.emplace_back(i);
      }
    }
    // 保存第 i 个数对应的质因子
    // 这里使用 nums[i] 当做下标需要去重才可以
    std::vector<std::vector<int>> arr(n);
    for (int i = 0; i < nums.size(); ++i) {
      int x = nums[i];
      for (int p : primes) {
        if (p * p > x) {
          break;
        }
        if (x % p == 0) {
          arr[i].emplace_back(p);
        }
        while (x % p == 0) {
          x /= p;
        }
      }
      if (x > 1) {
        arr[i].emplace_back(x);
      }
    }

    // 保存所有元素的质因子的总数
    std::unordered_map<int, int> stats;
    // 分隔到 [0,i] 时，元素的质因子总数
    std::unordered_map<int, int> prefix_stats;
    for (int i = 0; i < nums.size(); ++i) {
      for (int p : arr[i]) {
        ++stats[p];
      }
    }

    // good 表示有几个质数 p 满足“分割点左边要么不包含 p，要么包含所有 p”
    // 假设分割点一开始是 -1，那么分割点左边就是空的，肯定所有 p 都满足条件，
    // 因此 good 初始值就是 stats.size()，即质数的总数
    int good = stats.size();
    for (int i = 0; i < n - 1; ++i) {
      // 分割点前进到了 i，把第 i 个数里所有的质数都加入分割点左边
      for (int p : arr[i]) {
        ++prefix_stats[p];
        // prefix_stats[p] 从 0 到 1，不满足“分割点左边不包含 p”
        if (prefix_stats[p] == 1) {
          good--;
        }
        // prefix_stats[p] 从 stats[p] - 1 到 stats[p]，满足“包含所有 p”
        // 注意这里是 if 而不是 else if，这是为了处理 stats[p] == 1 的情况
        if (prefix_stats[p] == stats[p]) {
          ++good;
        }
      }
      // 所有质数都满足条件，返回答案
      if (good == stats.size()) {
        return i;
      }
    }
    return -1;
  }
};