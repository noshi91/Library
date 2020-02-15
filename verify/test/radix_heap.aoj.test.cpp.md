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


# :x: test/radix_heap.aoj.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/radix_heap.aoj.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-16 01:31:24+09:00




## Depends on

* :x: <a href="../../library/data_structure/radix_heap.cpp.html">data_structure/radix_heap.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include "data_structure/radix_heap.cpp"

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
  int n, m, r;
  std::cin >> n >> m >> r;
  std::vector<std::vector<std::pair<int, int>>> g(n);
  for (int i = 0; i != m; i += 1) {
    int s, t, d;
    std::cin >> s >> t >> d;
    g[s].emplace_back(d, t);
  }
  constexpr int Inf = std::numeric_limits<int>::max();
  std::vector<int> dist(n, Inf);
  dist[r] = 0;
  radix_heap<int> heap(30);
  int size = 0;
  heap.push({0, r});
  size += 1;
  while (size != 0) {
    const auto [c_, v] = heap.pop();
    const int c = c_;
    size -= 1;
    if (dist[v] < c)
      continue;
    for (const auto &[d, u] : g[v]) {
      if (c + d < dist[u]) {
        dist[u] = c + d;
        heap.push({dist[u], u});
        size += 1;
      }
    }
  }
  for (int i = 0; i != n; i += 1) {
    if (dist[i] < Inf)
      std::cout << dist[i];
    else
      std::cout << "INF";
    std::cout << std::endl;
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/radix_heap.aoj.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#line 1 "data_structure/radix_heap.cpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

template <class T> class radix_heap {
  using size_t = std::size_t;
  using u64 = std::uint_fast64_t;
  using V = std::pair<u64, T>;

public:
  using key_type = u64;
  using mapped_type = T;
  using value_type = V;

private:
  static size_t log2p1(const u64 x) {
    if (x == 0)
      return 0;
    else
      return 64 - __builtin_clzll(x);
  }

  std::vector<std::vector<V>> u;
  u64 last;

public:
  radix_heap() = default;
  explicit radix_heap(const size_t bit_length) : u(bit_length + 1), last(0) {
    assert(bit_length <= 64);
  }

  void push(const V x) {
    assert(last <= x.first);

    u[log2p1(x.first - last)].push_back(x);
  }
  V pop() {
    if (u[0].empty()) {
      size_t i = 1;
      while (u[i].empty())
        i += 1;
      last = std::numeric_limits<u64>::max();
      for (const V &e : u[i])
        last = std::min(last, e.first);
      for (const V &e : u[i])
        u[log2p1(e.first - last)].push_back(e);
      u[i].clear();
    }
    V ret = u[0].back();
    u[0].pop_back();
    return ret;
  }
};
#line 5 "test/radix_heap.aoj.test.cpp"

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
  int n, m, r;
  std::cin >> n >> m >> r;
  std::vector<std::vector<std::pair<int, int>>> g(n);
  for (int i = 0; i != m; i += 1) {
    int s, t, d;
    std::cin >> s >> t >> d;
    g[s].emplace_back(d, t);
  }
  constexpr int Inf = std::numeric_limits<int>::max();
  std::vector<int> dist(n, Inf);
  dist[r] = 0;
  radix_heap<int> heap(30);
  int size = 0;
  heap.push({0, r});
  size += 1;
  while (size != 0) {
    const auto [c_, v] = heap.pop();
    const int c = c_;
    size -= 1;
    if (dist[v] < c)
      continue;
    for (const auto &[d, u] : g[v]) {
      if (c + d < dist[u]) {
        dist[u] = c + d;
        heap.push({dist[u], u});
        size += 1;
      }
    }
  }
  for (int i = 0; i != n; i += 1) {
    if (dist[i] < Inf)
      std::cout << dist[i];
    else
      std::cout << "INF";
    std::cout << std::endl;
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

