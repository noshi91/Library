---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: test/w_ary_tree_set.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/w_ary_tree_set.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-11 14:24:32+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/w_ary_tree_set.cpp.html">w-ary Tree Set <small>(data_structure/w_ary_tree_set.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/ceildiv.cpp.html">other/ceildiv.cpp</a>
* :heavy_check_mark: <a href="../../library/other/fast_ios.cpp.html">other/fast_ios.cpp</a>
* :heavy_check_mark: <a href="../../library/other/int_alias.cpp.html">other/int_alias.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C&lang=ja"

#include "data_structure/w_ary_tree_set.cpp"

#include "other/int_alias.cpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  static constexpr usize max_q = 2000000;

  struct query_t {
    bool t;
    u32 key;
  };
  std::vector<query_t> q;
  q.reserve(max_q);
  std::vector<u32> v;
  v.reserve(max_q);
  std::string s;

  while (true) {
    std::cin >> s;
    if (s[2] == 's') {
      u32 x;
      std::cin >> x;
      q.push_back({true, x});
      v.push_back(x);
    } else if (s[2] == 't') {
      q.push_back({false, 0});
    } else {
      break;
    }
  }

  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
  std::vector<usize> count(v.size(), 0);

  w_ary_tree_set<max_q> wats;
  for (const auto &e : q) {
    if (e.t) {
      const usize i = std::lower_bound(v.begin(), v.end(), e.key) - v.begin();
      if (count[i] == 0) {
        wats.insert(i);
      }
      ++count[i];
    } else {
      const usize i = wats.max();
      std::cout << v[i] << "\n";
      --count[i];
      if (count[i] == 0) {
        wats.erase(i);
      }
    }
  }

  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/w_ary_tree_set.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C&lang=ja"

#line 1 "other/ceildiv.cpp"
template <class T> constexpr T ceildiv(const T &n, const T &d) {
  return n / d + (n % d != 0 ? 1 : 0);
}
#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 3 "data_structure/w_ary_tree_set.cpp"

#include <array>
#include <type_traits>

namespace w_ary_tree_set_impl {
constexpr usize calc_c(usize n) {
  usize ret = 1;
  while (n > 64) {
    ret *= 64;
    n /= 64;
  }
  return ret;
}
usize bsf(const u64 x) {
#ifdef __GNUC__
  return __builtin_ctzll(x);
#else
  unsigned long ret;
  if (_BitScanForward(&ret, x & ~(~static_cast<u64>(0) << 32))) {
    return ret;
  } else {
    _BitScanForward(&ret, x >> 32);
    return ret + 32;
  }
#endif
}
usize bsr(const u64 x) {
#ifdef __GNUC__
  return 63 - __builtin_clzll(x);
#else
  unsigned long ret;
  if (_BitScanReverse(&ret, x >> 32)) {
    return ret + 32;
  } else {
    _BitScanReverse(&ret, x & ~(~static_cast<u64>(0) << 32));
    return ret;
  }
#endif
}

template <usize N, class D = void> class w_ary_tree_set {
  static constexpr usize C = calc_c(N);

  u64 map;
  std::array<w_ary_tree_set<C>, ceildiv(N, C)> child;

public:
  w_ary_tree_set() : map(0), child() {}

  bool insert(const usize key) {
    const usize pos = key / C;
    map |= static_cast<u64>(1) << pos;
    return child[pos].insert(key % C);
  }

  bool erase(const usize key) {
    const usize pos = key / C;
    const bool ret = child[pos].erase(key % C);
    if (child[pos]._get_map() == 0) {
      map &= ~(static_cast<u64>(1) << pos);
    }
    return ret;
  }

  bool contains(const usize key) const {
    return child[key / C].contains(key % C);
  }

  usize min() const {
    const usize pos = bsf(map);
    return pos * C + child[pos].min();
  }

  usize max() const {
    const usize pos = bsr(map);
    return pos * C + child[pos].max();
  }

  u64 _get_map() const { return map; }
};

template <usize N>
class w_ary_tree_set<N, typename std::enable_if<(N <= 64)>::type> {
  u64 map;

public:
  w_ary_tree_set() : map(0) {}

  bool insert(const usize key) {
    const u64 pop = static_cast<u64>(1) << key;
    if ((map & pop) != 0) {
      return false;
    } else {
      map |= pop;
      return true;
    }
  }

  bool erase(const usize key) {
    const u64 pop = static_cast<u64>(1) << key;
    if ((map & pop) != 0) {
      map &= ~pop;
      return true;
    } else {
      return false;
    }
  }

  usize min() const { return bsf(map); }

  usize max() const { return bsr(map); }

  u64 _get_map() const { return map; }
};

} // namespace w_ary_tree_set_impl

template <usize N>
using w_ary_tree_set = w_ary_tree_set_impl::w_ary_tree_set<N>;

/**
 * @brief w-ary Tree Set
 */
#line 5 "test/w_ary_tree_set.test.cpp"

#line 7 "test/w_ary_tree_set.test.cpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
#line 1 "other/fast_ios.cpp"
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
#line 14 "test/w_ary_tree_set.test.cpp"

  static constexpr usize max_q = 2000000;

  struct query_t {
    bool t;
    u32 key;
  };
  std::vector<query_t> q;
  q.reserve(max_q);
  std::vector<u32> v;
  v.reserve(max_q);
  std::string s;

  while (true) {
    std::cin >> s;
    if (s[2] == 's') {
      u32 x;
      std::cin >> x;
      q.push_back({true, x});
      v.push_back(x);
    } else if (s[2] == 't') {
      q.push_back({false, 0});
    } else {
      break;
    }
  }

  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
  std::vector<usize> count(v.size(), 0);

  w_ary_tree_set<max_q> wats;
  for (const auto &e : q) {
    if (e.t) {
      const usize i = std::lower_bound(v.begin(), v.end(), e.key) - v.begin();
      if (count[i] == 0) {
        wats.insert(i);
      }
      ++count[i];
    } else {
      const usize i = wats.max();
      std::cout << v[i] << "\n";
      --count[i];
      if (count[i] == 0) {
        wats.erase(i);
      }
    }
  }

  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

