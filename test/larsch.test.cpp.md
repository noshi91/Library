---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algorithm/larsch.cpp
    title: LARSCH Algorithm
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree.cpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/less_equal_ordered_set.cpp
    title: other/less_equal_ordered_set.cpp
  - icon: ':heavy_check_mark:'
    path: other/min_semigroup.cpp
    title: other/min_semigroup.cpp
  - icon: ':heavy_check_mark:'
    path: other/opposite_ordered_set.cpp
    title: other/opposite_ordered_set.cpp
  - icon: ':heavy_check_mark:'
    path: other/semigroup_to_monoid.cpp
    title: other/semigroup_to_monoid.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3086
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3086
  bundledCode: "#line 1 \"test/larsch.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3086\"\
    \r\n\r\n#line 1 \"algorithm/larsch.cpp\"\n#include <functional>\r\n#include <memory>\r\
    \n#include <vector>\r\n\r\ntemplate <class T> class larsch {\r\n  struct reduce_row;\r\
    \n  struct reduce_col;\r\n\r\n  struct reduce_row {\r\n    int n;\r\n    std::function<T(int,\
    \ int)> f;\r\n    int cur_row;\r\n    int state;\r\n    std::unique_ptr<reduce_col>\
    \ rec;\r\n\r\n    reduce_row(int n_) : n(n_), f(), cur_row(0), state(0), rec()\
    \ {\r\n      const int m = n / 2;\r\n      if (m != 0) {\r\n        rec = std::make_unique<reduce_col>(m);\r\
    \n      }\r\n    }\r\n\r\n    void set_f(std::function<T(int, int)> f_) {\r\n\
    \      f = f_;\r\n      if (rec) {\r\n        rec->set_f([&](int i, int j) ->\
    \ T { return f(2 * i + 1, j); });\r\n      }\r\n    }\r\n\r\n    int get_argmin()\
    \ {\r\n      const int cur_row_ = cur_row;\r\n      cur_row += 1;\r\n      if\
    \ (cur_row_ % 2 == 0) {\r\n        const int prev_argmin = state;\r\n        const\
    \ int next_argmin = [&]() {\r\n          if (cur_row_ + 1 == n) {\r\n        \
    \    return n - 1;\r\n          } else {\r\n            return rec->get_argmin();\r\
    \n          }\r\n        }();\r\n        state = next_argmin;\r\n        int ret\
    \ = prev_argmin;\r\n        for (int j = prev_argmin + 1; j <= next_argmin; j\
    \ += 1) {\r\n          if (f(cur_row_, ret) > f(cur_row_, j)) {\r\n          \
    \  ret = j;\r\n          }\r\n        }\r\n        return ret;\r\n      } else\
    \ {\r\n        if (f(cur_row_, state) <= f(cur_row_, cur_row_)) {\r\n        \
    \  return state;\r\n        } else {\r\n          return cur_row_;\r\n       \
    \ }\r\n      }\r\n    }\r\n  };\r\n\r\n  struct reduce_col {\r\n    int n;\r\n\
    \    std::function<T(int, int)> f;\r\n    int cur_row;\r\n    std::vector<int>\
    \ cols;\r\n    reduce_row rec;\r\n\r\n    reduce_col(int n_) : n(n_), f(), cur_row(0),\
    \ cols(), rec(n) {}\r\n\r\n    void set_f(std::function<T(int, int)> f_) {\r\n\
    \      f = f_;\r\n      rec.set_f([&](int i, int j) -> T { return f(i, cols[j]);\
    \ });\r\n    }\r\n\r\n    int get_argmin() {\r\n      const int cur_row_ = cur_row;\r\
    \n      cur_row += 1;\r\n      const auto cs = [&]() -> std::vector<int> {\r\n\
    \        if (cur_row_ == 0) {\r\n          return {{0}};\r\n        } else {\r\
    \n          return {{2 * cur_row_ - 1, 2 * cur_row_}};\r\n        }\r\n      }();\r\
    \n      for (const int j : cs) {\r\n        while ([&]() {\r\n          const\
    \ int size = cols.size();\r\n          return size != cur_row_ && f(size - 1,\
    \ cols.back()) > f(size - 1, j);\r\n        }()) {\r\n          cols.pop_back();\r\
    \n        }\r\n        if (cols.size() != n) {\r\n          cols.push_back(j);\r\
    \n        }\r\n      }\r\n      return cols[rec.get_argmin()];\r\n    }\r\n  };\r\
    \n\r\n  std::unique_ptr<reduce_row> base;\r\n\r\npublic:\r\n  larsch(int n, std::function<T(int,\
    \ int)> f)\r\n      : base(std::make_unique<reduce_row>(n)) {\r\n    base->set_f(f);\r\
    \n  }\r\n\r\n  int get_argmin() { return base->get_argmin(); }\r\n};\r\n\r\n/**\r\
    \n * @brief LARSCH Algorithm\r\n * @docs docs/larsch.md\r\n */\r\n#line 2 \"other/int_alias.cpp\"\
    \n\n#include <cstddef>\n#include <cstdint>\n\nusing i32 = std::int32_t;\nusing\
    \ i64 = std::int64_t;\nusing u32 = std::uint32_t;\nusing u64 = std::uint64_t;\n\
    using isize = std::ptrdiff_t;\nusing usize = std::size_t;\n#line 2 \"data_structure/segment_tree.cpp\"\
    \n\n#include <cassert>\n#line 6 \"data_structure/segment_tree.cpp\"\n\ntemplate\
    \ <class M> class segment_tree {\n  using T = typename M::value_type;\n\npublic:\n\
    \  using value_type = T;\n\nprivate:\n  std::vector<T> tree;\n\n  template <class\
    \ F>\n  usize search_subtree(usize index, const F f, T fold_l) const {\n    while\
    \ (index < size()) {\n      const T temp = M::operation(fold_l, tree[index * 2]);\n\
    \      if (!f(temp)) {\n        index = index * 2;\n      } else {\n        fold_l\
    \ = temp;\n        index = index * 2 + 1;\n      }\n    }\n    return index -\
    \ size();\n  }\n\npublic:\n  segment_tree() = default;\n\n  explicit segment_tree(const\
    \ usize n) : tree(n * 2, M::identity) {}\n\n  usize size() const noexcept { return\
    \ tree.size() / 2; }\n\n  T fold(usize first, usize last) const {\n    assert(first\
    \ <= last);\n    assert(last <= size());\n    first += size();\n    last += size();\n\
    \    T fold_l = M::identity;\n    T fold_r = M::identity;\n    while (first !=\
    \ last) {\n      if (first % 2 != 0) {\n        fold_l = M::operation(fold_l,\
    \ tree[first]);\n        first += 1;\n      }\n      first /= 2;\n      if (last\
    \ % 2 != 0) {\n        last -= 1;\n        fold_r = M::operation(tree[last], fold_r);\n\
    \      }\n      last /= 2;\n    }\n    return M::operation(fold_l, fold_r);\n\
    \  }\n  \n  template <class F> usize search(usize first, usize last, const F f)\
    \ const {\n    assert(first <= last);\n    assert(last <= size());\n    first\
    \ += size();\n    last += size();\n    const usize last_cp = last;\n    usize\
    \ shift = 0;\n    T fold_l = M::identity;\n    while (first != last) {\n     \
    \ if (first % 2 != 0) {\n        const T temp = M::operation(fold_l, tree[first]);\n\
    \        if (!f(temp))\n          return search_subtree(first, f, fold_l);\n \
    \       fold_l = temp;\n        first += 1;\n      }\n      first /= 2;\n    \
    \  last /= 2;\n      shift += 1;\n    }\n    while (shift != 0) {\n      shift\
    \ -= 1;\n      last = last_cp >> shift;\n      if (last % 2 != 0) {\n        last\
    \ -= 1;\n        const T temp = M::operation(fold_l, tree[last]);\n        if\
    \ (!f(temp))\n          return search_subtree(last, f, fold_l);\n        fold_l\
    \ = temp;\n      }\n    }\n    return last_cp - size();\n  }\n\n  void update(usize\
    \ index, const T x) {\n    assert(index < size());\n    index += size();\n   \
    \ tree[index] = x;\n    while (index != 1) {\n      index /= 2;\n      tree[index]\
    \ = M::operation(tree[index * 2], tree[index * 2 + 1]);\n    }\n  }\n};\n\n/**\n\
    \ * @brief Segment Tree\n * @docs docs/segment_tree.md\n * @see https://scrapbox.io/data-structures/Segment_Tree\n\
    \ */\n#line 1 \"other/less_equal_ordered_set.cpp\"\ntemplate <class T> class less_equal_ordered_set\
    \ {\npublic:\n  using value_type = T;\n  static constexpr bool compare(const T\
    \ &x, const T &y) noexcept {\n    return x <= y;\n  }\n};\n#line 1 \"other/min_semigroup.cpp\"\
    \ntemplate <class W> class min_semigroup {\n  using T = typename W::value_type;\n\
    \npublic:\n  using value_type = T;\n  static constexpr T operation(const T &l,\
    \ const T &r) noexcept {\n    return W::compare(l, r) ? l : r;\n  }\n};\n#line\
    \ 1 \"other/opposite_ordered_set.cpp\"\ntemplate <class W> class opposite_ordered_set\
    \ {\n  using T = typename W::value_type;\n\npublic:\n  using value_type = T;\n\
    \  static constexpr bool compare(const T &l, const T &r) noexcept {\n    return\
    \ W::compare(r, l);\n  }\n};\n#line 1 \"other/semigroup_to_monoid.cpp\"\n#include\
    \ <optional>\n#include <utility>\n\ntemplate <class S> class semigroup_to_monoid\
    \ {\n  using T = std::optional<typename S::value_type>;\n\npublic:\n  using value_type\
    \ = T;\n  static constexpr T operation(const T &l, const T &r) noexcept {\n  \
    \  if (!l)\n      return r;\n    if (!r)\n      return l;\n    return T(std::in_place,\
    \ S::operation(*l, *r));\n  }\n  static constexpr T identity{std::nullopt};\n\
    };\n#line 10 \"test/larsch.test.cpp\"\n\r\n#include <iostream>\r\n#include <limits>\r\
    \n\r\nint main() {\r\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 16 \"test/larsch.test.cpp\"\n\r\n  static constexpr\
    \ i64 inf = std::numeric_limits<i64>::max() / 2;\r\n\r\n  usize n, l;\r\n  std::cin\
    \ >> n >> l;\r\n\r\n  segment_tree<semigroup_to_monoid<\r\n      min_semigroup<opposite_ordered_set<less_equal_ordered_set<i64>>>>>\r\
    \n      seg(n);\r\n  for (usize i = 0; i != n; ++i) {\r\n    i64 a;\r\n    std::cin\
    \ >> a;\r\n    seg.update(i, a);\r\n  }\r\n\r\n  std::vector<i64> dp(n + 1);\r\
    \n  dp[0] = 0;\r\n\r\n  const auto f = [&](const usize to_, const usize from)\
    \ -> i64 {\r\n    const usize to = to_ + 1;\r\n    if (to - from < l) {\r\n  \
    \    return -inf;\r\n    } else {\r\n      return dp[from] + *seg.fold(from, to);\r\
    \n    }\r\n  };\r\n\r\n  larsch<i64> larsch_(n, [&](int i, int j) { return -f(i,\
    \ j); });\r\n  for (usize i = 0; i != n; i += 1) {\r\n    dp[i + 1] = f(i, larsch_.get_argmin());\r\
    \n  }\r\n\r\n  std::cout << dp[n] << \"\\n\";\r\n\r\n  return 0;\r\n}\r\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3086\"\
    \r\n\r\n#include \"algorithm/larsch.cpp\"\r\n#include \"data_structure/segment_tree.cpp\"\
    \r\n#include \"other/int_alias.cpp\"\r\n#include \"other/less_equal_ordered_set.cpp\"\
    \r\n#include \"other/min_semigroup.cpp\"\r\n#include \"other/opposite_ordered_set.cpp\"\
    \r\n#include \"other/semigroup_to_monoid.cpp\"\r\n\r\n#include <iostream>\r\n\
    #include <limits>\r\n\r\nint main() {\r\n#include \"other/fast_ios.cpp\"\r\n\r\
    \n  static constexpr i64 inf = std::numeric_limits<i64>::max() / 2;\r\n\r\n  usize\
    \ n, l;\r\n  std::cin >> n >> l;\r\n\r\n  segment_tree<semigroup_to_monoid<\r\n\
    \      min_semigroup<opposite_ordered_set<less_equal_ordered_set<i64>>>>>\r\n\
    \      seg(n);\r\n  for (usize i = 0; i != n; ++i) {\r\n    i64 a;\r\n    std::cin\
    \ >> a;\r\n    seg.update(i, a);\r\n  }\r\n\r\n  std::vector<i64> dp(n + 1);\r\
    \n  dp[0] = 0;\r\n\r\n  const auto f = [&](const usize to_, const usize from)\
    \ -> i64 {\r\n    const usize to = to_ + 1;\r\n    if (to - from < l) {\r\n  \
    \    return -inf;\r\n    } else {\r\n      return dp[from] + *seg.fold(from, to);\r\
    \n    }\r\n  };\r\n\r\n  larsch<i64> larsch_(n, [&](int i, int j) { return -f(i,\
    \ j); });\r\n  for (usize i = 0; i != n; i += 1) {\r\n    dp[i + 1] = f(i, larsch_.get_argmin());\r\
    \n  }\r\n\r\n  std::cout << dp[n] << \"\\n\";\r\n\r\n  return 0;\r\n}\r\n"
  dependsOn:
  - algorithm/larsch.cpp
  - data_structure/segment_tree.cpp
  - other/int_alias.cpp
  - other/less_equal_ordered_set.cpp
  - other/min_semigroup.cpp
  - other/opposite_ordered_set.cpp
  - other/semigroup_to_monoid.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/larsch.test.cpp
  requiredBy: []
  timestamp: '2021-04-07 08:01:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/larsch.test.cpp
layout: document
redirect_from:
- /verify/test/larsch.test.cpp
- /verify/test/larsch.test.cpp.html
title: test/larsch.test.cpp
---
