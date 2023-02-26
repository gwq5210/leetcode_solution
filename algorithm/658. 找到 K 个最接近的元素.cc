/*
 * @lc app=leetcode.cn id=658 lang=cpp
 *
 * [658] 找到 K 个最接近的元素
 *
 * https://leetcode-cn.com/problems/find-k-closest-elements/description/
 *
 * algorithms
 * Medium (45.49%)
 * Likes:    477
 * Dislikes: 0
 * Total Accepted:    85.7K
 * Total Submissions: 178.1K
 * Testcase Example:  '[1,2,3,4,5]\n4\n3'
 *
 * 给定一个 排序好 的数组 arr ，两个整数 k 和 x ，从数组中找到最靠近 x（两数之差最小）的 k
 * 个数。返回的结果必须要是按升序排好的。
 *
 * 整数 a 比整数 b 更接近 x 需要满足：
 *
 *
 * |a - x| < |b - x| 或者
 * |a - x| == |b - x| 且 a < b
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：arr = [1,2,3,4,5], k = 4, x = 3
 * 输出：[1,2,3,4]
 *
 *
 * 示例 2：
 *
 *
 * 输入：arr = [1,2,3,4,5], k = 4, x = -1
 * 输出：[1,2,3,4]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= k <= arr.length
 * 1 <= arr.length <= 10^4
 * arr 按 升序 排列
 * -10^4 <= arr[i], x <= 10^4
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
  std::vector<int> findClosestElements4(std::vector<int>& arr, int k, int x) {
    // 一个一个删，因为数组有序，且返回的是连续升序子数组，所以 每一次删除的元素一定位于边界 ；
    // 一共 7 个元素，要保留 3 个元素，因此要删除 4 个元素；
    // 因为要删除的元素都位于边界，于是可以使用 双指针 对撞的方式确定保留的区间」。
    int l = 0;
    int r = arr.size() - 1;
    int c = arr.size() - k;
    while (c--) {
      // 相等时需要保留左侧的元素
      if (std::abs(arr[l] - x) <= std::abs(arr[r] - x)) {
        --r;
      } else {
        ++l;
      }
    }
    return std::vector<int>(arr.begin() + l, arr.begin() + r + 1);
  }
  std::vector<int> findClosestElements4(std::vector<int>& arr, int k, int x) {
    int l = 0;
    int r = arr.size() - k;
    // 目的是通过二分找到区间 [l, l+k)
    // 我们通过判断题目中给出的是有序数组，并且题目要求返回的是区间，并且是连续区间；
    // 区间长度是固定的，并且 k 的值为正数，且总是小于给定排序数组的长度，即 k 的值是合法、有效的。
    // 因此，只要我们找到了「合适的」左边界的下标，从左边界开始数 k个数，返回就好了。
    // 我们把这件事情定义为「寻找最优区间」，「寻找最优区间」等价于「寻找最优区间的左边界」。
    // 因此本题使用二分查找法在有序数组中定位含有 k 个元素的连续子区间的左边界
    // 即使用二分法找「最优区间的左边界」。
    // 「最优区间的左边界」的取值范围，至少需要 l 的右侧有 k 个数，因此取值范围是 [0, arr.size()-k]
    // 具体解释参见
    // https://leetcode.cn/problems/find-k-closest-elements/solutions/12476/pai-chu-fa-shuang-zhi-zhen-er-fen-fa-python-dai-ma/
    while (l < r) {
      int mid = l + (r - l) / 2;
      // 尝试从长度为 k + 1 的连续子区间删除一个元素
      // 从而定位左区间端点的边界值
      if (x - arr[mid] > arr[mid + k] - x) {
        // 下一轮搜索区间是 [mid + 1..right]
        l = mid + 1;
      } else {
        // 下一轮搜索区间是 [left..mid]
        r = mid;
      }
    }
    return std::vector<int>(arr.begin() + l, arr.begin() + l + k);
  }
  // 检查下标 a 是否比下标 b 更优
  bool Check(const std::vector<int>& arr, int a, int b, int x) {
    if (a < 0 || a >= arr.size()) {
      return false;
    } else if (b < 0 || b >= arr.size()) {
      return true;
    }
    int x1 = std::abs(arr[a] - x);
    int x2 = std::abs(arr[b] - x);
    if (x1 == x2) {
      return arr[a] < arr[b];
    } else {
      return x1 < x2;
    }
  }
  std::vector<int> findClosestElements2(std::vector<int>& arr, int k, int x) {
    int l = 0;
    int r = arr.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (arr[mid] < x) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    std::vector<int> result;
    --l;

    // [0, l] 表示小于 x 的元素区间
    // [r, arr.size()) 表示大于等于 x的元素区间
    while (result.size() < k) {
      if (Check(arr, l, r, x)) {
        result.emplace_back(arr[l]);
        --l;
      } else {
        result.emplace_back(arr[r]);
        ++r;
      }
    }
    std::sort(result.begin(), result.end());
    return result;
  }
  std::vector<int> findClosestElements3(std::vector<int>& arr, int k, int x) {
    int l = 0;
    int r = arr.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (arr[mid] < x) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    --l;
    // [0, l] 表示小于 x 的元素区间
    // [r, arr.size()) 表示大于等于 x的元素区间
    while (k--) {
      if (Check(arr, l, r, x)) {
        --l;
      } else {
        ++r;
      }
    }
    return std::vector<int>(arr.begin() + l + 1, arr.begin() + r);
  }
};