#include "algorithm/concave_max_plus_convolution.cpp"
#include "other/ceildiv.cpp"
#include "other/int_alias.cpp"

#include <algorithm>
#include <cassert>
#include <functional>
#include <utility>
#include <vector>

template <class I>
u64 axiotis_tzamos_knapsack(const usize t, const std::vector<I> &item) {
  std::vector<std::vector<i64>> bucket(t + 1);
  for (const I &e : item) {
    assert(e.w > 0);
    assert(e.v >= 0);

    if (e.w <= t)
      bucket[e.w].push_back(e.v);
  }

  std::vector<i64> dp(t + 1, std::numeric_limits<i64>::lowest());
  dp[0] = 0;
  for (usize w = 1; w <= t; w += 1) {
    std::vector<i64> &list = bucket[w];
    if (list.empty())
      continue;
    std::sort(list.begin(), list.end(), std::greater<i64>());
    const usize m = std::min(list.size(), t / w);
    std::vector<i64> sum(m + 1);
    sum[0] = 0;
    for (usize i = 0; i != m; i += 1)
      sum[i + 1] = sum[i] + list[i];
    for (usize k = 0; k != w; k += 1) {
      const usize n = (t - k) / w + 1;
      std::vector<i64> v(n);
      for (usize i = 0; i != n; i += 1)
        v[i] = dp[i * w + k];
      const std::vector<i64> res = concave_max_plus_convolution(v, sum);
      for (usize i = 0; i != n; i += 1)
        dp[i * w + k] = res[i];
    }
  }
  return *std::max_element(dp.begin(), dp.end());
}

/**
 * @brief Axiotis-Tzamos Knapsack
 * @see https://arxiv.org/abs/1802.06440
 */
