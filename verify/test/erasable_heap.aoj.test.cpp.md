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


# :heavy_check_mark: test/erasable_heap.aoj.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/erasable_heap.aoj.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-28 14:18:18+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/erasable_heap.cpp.html">Erasable Heap <small>(data_structure/erasable_heap.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/data_structure/pairing_heap.cpp.html">Pairing Heap <small>(data_structure/pairing_heap.cpp)</small></a>
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
    std::cout << std::endl;
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/erasable_heap.aoj.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#line 1 "data_structure/erasable_heap.cpp"
#include <cassert>

template <class Heap> class erasable_heap {
  using W = typename Heap::value_compare;
  using T = typename W::value_type;

public:
  using value_compare = W;

private:
  static bool equivalent(const T x, const T y) {
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

  T top() const {
    assert(!empty());
    return base.top();
  }

  void push(const T x) {
    base.push(x);
    normalize();
  }
  void pop() {
    assert(!empty());
    base.pop();
    normalize();
  }
  void erase(const T x) {
    erased.push(x);
    normalize();
  }
};

/**
 * @brief Erasable Heap
 */
#line 1 "data_structure/pairing_heap.cpp"
#include <cassert>
#include <memory>
#include <utility>

template <class W> class pairing_heap {
  using T = typename W::value_type;

public:
  using value_compare = W;

private:
  class node_type;
  using node_ptr = std::unique_ptr<node_type>;
  class node_type {
  public:
    T value;
    node_ptr head;
    node_ptr next;

    node_type(const T value) : value(value), head(), next() {}
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
  T top() const {
    assert(!empty());
    return root->value;
  }

  void push(const T x) {
    root = merge(std::move(root), std::make_unique<node_type>(x));
  }
  void pop() {
    assert(!empty());
    root = merge_list(std::move(root->head));
  }

  static pairing_heap meld(pairing_heap x, pairing_heap y) {
    return pairing_heap(merge(std::move(x.root), std::move(y.root)));
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
#line 7 "test/erasable_heap.aoj.test.cpp"

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
    std::cout << std::endl;
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
