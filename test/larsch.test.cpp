#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3086"

#include "algorithm/larsch.cpp"
#include "data_structure/segment_tree.cpp"
#include "other/int_alias.cpp"
#include "other/less_equal_ordered_set.cpp"
#include "other/min_semigroup.cpp"
#include "other/opposite_ordered_set.cpp"
#include "other/semigroup_to_monoid.cpp"

#include <iostream>
#include <limits>

int main() {
#include "other/fast_ios.cpp"

  static constexpr i64 inf = std::numeric_limits<i64>::max() / 2;

  usize n, l;
  std::cin >> n >> l;

  segment_tree<semigroup_to_monoid<
      min_semigroup<opposite_ordered_set<less_equal_ordered_set<i64>>>>>
      seg(n);
  for (usize i = 0; i != n; ++i) {
    i64 a;
    std::cin >> a;
    seg.update(i, a);
  }

  std::vector<i64> dp(n + 1);
  dp[0] = 0;

  const auto f = [&](const usize to_, const usize from) -> i64 {
    const usize to = to_ + 1;
    if (to - from < l) {
      return -inf;
    } else {
      return dp[from] + *seg.fold(from, to);
    }
  };

  larsch<i64> larsch_(n, [&](int i, int j) { return -f(i, j); });
  for (usize i = 0; i != n; i += 1) {
    dp[i + 1] = f(i, larsch_.get_argmin());
  }

  std::cout << dp[n] << "\n";

  return 0;
}
