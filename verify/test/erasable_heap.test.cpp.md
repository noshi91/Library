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


# :heavy_check_mark: test/erasable_heap.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/erasable_heap.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:42:07+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/erasable_heap.cpp.html">Erasable Heap <small>(data_structure/erasable_heap.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/data_structure/pairing_heap.cpp.html">Pairing Heap <small>(data_structure/pairing_heap.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/fast_ios.cpp.html">other/fast_ios.cpp</a>
* :heavy_check_mark: <a href="../../library/other/less_equal_ordered_set.cpp.html">other/less_equal_ordered_set.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include "data_structure/erasable_heap.cpp"
#include "data_structure/pairing_heap.cpp"
#include "other/less_equal_ordered_set.cpp"

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

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
  erasable_heap<pairing_heap<less_equal_ordered_set<std::pair<int, int>>>> heap;
  heap.push({0, r});
  while (!heap.empty()) {
    const auto [c, v] = heap.top();
    heap.pop();
    for (const auto &[d, u] : g[v]) {
      if (c + d < dist[u]) {
        if (dist[u] != Inf)
          heap.erase({dist[u], u});
        dist[u] = c + d;
        heap.push({dist[u], u});
      }
    }
  }
  for (int i = 0; i != n; i += 1) {
    if (dist[i] < Inf)
      std::cout << dist[i];
    else
      std::cout << "INF";
    std::cout << "\n";
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/erasable_heap.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#line 1 "data_structure/erasable_heap.cpp"
#include <cassert>
#include <utility>

template <class Heap> class erasable_heap {
  using W = typename Heap::value_compare;
  using T = typename Heap::value_type;

public:
  using value_compare = W;
  using value_type = T;

private:
  static bool equivalent(const T &x, const T &y) {
    return W::compare(x, y) && W::compare(y, x);
  }

  Heap base;
  Heap erased;

  void normalize() {
    while (!base.empty() && !erased.empty() &&
           equivalent(base.top(), erased.top())) {
      base.pop();
      erased.pop();
    }
  }

public:
  erasable_heap() = default;

  bool empty() const { return base.empty(); }

  const T &top() const {
    assert(!empty());

    return base.top();
  }

  void push(T x) {
    base.push(std::move(x));
    normalize();
  }

  T pop() {
    assert(!empty());

    T ret = base.pop();
    normalize();
    return ret;
  }

  void erase(T x) {
    erased.push(std::move(x));
    normalize();
  }
};

/**
 * @brief Erasable Heap
 */
#line 2 "data_structure/pairing_heap.cpp"
#include <memory>
#line 4 "data_structure/pairing_heap.cpp"

template <class W> class pairing_heap {
  using Self = pairing_heap;
  using T = typename W::value_type;

public:
  using value_compare = W;
  using value_type = T;

private:
  class node_type;
  using node_ptr = std::unique_ptr<node_type>;
  class node_type {
  public:
    T value;
    node_ptr head;
    node_ptr next;

    node_type(T value) : value(std::move(value)), head(), next() {}
  };

  static node_ptr merge(node_ptr x, node_ptr y) {
    if (!x)
      return y;
    if (!y)
      return x;
    if (!W::compare(x->value, y->value))
      std::swap(x, y);
    y->next = std::move(x->head);
    x->head = std::move(y);
    return x;
  }

  static node_ptr merge_list(node_ptr list) {
    if (!list || !list->next)
      return list;
    node_ptr next = std::move(list->next);
    node_ptr rem = std::move(next->next);
    return merge(merge(std::move(list), std::move(next)),
                 merge_list(std::move(rem)));
  }

  node_ptr root;

  pairing_heap(node_ptr root) : root(std::move(root)) {}

public:
  pairing_heap() = default;

  bool empty() const { return !root; }

  const T &top() const {
    assert(!empty());

    return root->value;
  }

  void push(T x) {
    root = merge(std::move(root), std::make_unique<node_type>(std::move(x)));
  }

  T pop() {
    assert(!empty());

    T ret = std::move(root->value);
    root = merge_list(std::move(root->head));
    return ret;
  }

  static Self meld(Self x, Self y) {
    return Self(merge(std::move(x.root), std::move(y.root)));
  }
};

/**
 * @brief Pairing Heap
 */
#line 1 "other/less_equal_ordered_set.cpp"
template <class T> class less_equal_ordered_set {
public:
  using value_type = T;
  static constexpr bool compare(const T &x, const T &y) noexcept {
    return x <= y;
  }
};
#line 7 "test/erasable_heap.test.cpp"

#include <iostream>
#include <limits>
#line 11 "test/erasable_heap.test.cpp"
#include <vector>

int main() {
#line 1 "other/fast_ios.cpp"
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
#line 15 "test/erasable_heap.test.cpp"

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
  erasable_heap<pairing_heap<less_equal_ordered_set<std::pair<int, int>>>> heap;
  heap.push({0, r});
  while (!heap.empty()) {
    const auto [c, v] = heap.top();
    heap.pop();
    for (const auto &[d, u] : g[v]) {
      if (c + d < dist[u]) {
        if (dist[u] != Inf)
          heap.erase({dist[u], u});
        dist[u] = c + d;
        heap.push({dist[u], u});
      }
    }
  }
  for (int i = 0; i != n; i += 1) {
    if (dist[i] < Inf)
      std::cout << dist[i];
    else
      std::cout << "INF";
    std::cout << "\n";
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

