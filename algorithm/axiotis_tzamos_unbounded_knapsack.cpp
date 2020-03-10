#include "algorithm/max_plus_convolution.cpp"
#include "other/bit_width.cpp"
#include "other/int_alias.cpp"

#include <algorithm>
#include <cassert>
#include <vector>

template <class I>
u64 axiotis_tzamos_unbounded_knapsack(const u64 t, const std::vector<I> &item) {
  assert(!item.empty());

  constexpr i64 minf = std::numeric_limits<i64>::lowest() / 2;

  usize m = 0;
  for (const I &e : item) {
    assert(e.w > 0);
    assert(e.v >= 0);

    m = std::max<usize>(m, e.w);
  }
  std::vector<i64> dp(m + 1, minf);
  dp[0] = 0;
  for (const I &e : item)
    dp[e.w] = std::max(dp[e.w], e.v);
  for (usize z = 1; z < m; z *= 2) {
    dp = max_plus_convolution(dp, dp);
    dp.resize(m + 1);
  }
  {
    const std::vector<i64> temp(m, minf);
    dp.insert(dp.begin(), temp.begin(), temp.end());
  }

  for (usize i = bit_width(t); i != 0; i -= 1) {
    dp = max_plus_convolution(dp, dp);
    auto itr = dp.begin() + 2 * m;
    if ((t >> i - 1) % 2 == 1)
      itr += 1;
    dp = std::vector<i64>(itr - m, itr + m + 1);
  }
  return *std::max_element(dp.begin(), dp.begin() + m + 1);
}

/**
 * @brief Axiotis-Tzamos Unbounded Knapsack
 * @see https://arxiv.org/abs/1802.06440
 */
