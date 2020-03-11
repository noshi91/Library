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


# :heavy_check_mark: test/pairing_heap.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/pairing_heap.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:42:07+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170&lang=en">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170&lang=en</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/pairing_heap.cpp.html">Pairing Heap <small>(data_structure/pairing_heap.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/fast_ios.cpp.html">other/fast_ios.cpp</a>
* :heavy_check_mark: <a href="../../library/other/less_equal_ordered_set.cpp.html">other/less_equal_ordered_set.cpp</a>
* :heavy_check_mark: <a href="../../library/other/opposite_ordered_set.cpp.html">other/opposite_ordered_set.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170&lang=en"

#include "data_structure/pairing_heap.cpp"
#include "other/less_equal_ordered_set.cpp"
#include "other/opposite_ordered_set.cpp"

#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

void solve(const int n, const int q) {
  using heap_type =
      pairing_heap<opposite_ordered_set<less_equal_ordered_set<int>>>;

  std::vector<int> p(n), deg(n, 0);
  for (int i = 1; i != n; i += 1) {
    std::cin >> p[i];
    p[i] -= 1;
    deg[p[i]] += 1;
  }
  std::vector<heap_type> ph(n);
  std::vector<int> time(n, q);
  time[0] = -1;
  for (int i = 0; i != q; i += 1) {
    char c;
    std::cin >> c;
    switch (c) {
    case 'M': {
      int v;
      std::cin >> v;
      v -= 1;
      time[v] = std::min(time[v], i);
    } break;
    case 'Q': {
      int v;
      std::cin >> v;
      v -= 1;
      ph[v].push(i);
    } break;
    }
  }
  std::stack<int> st;
  for (int i = 0; i != n; i += 1) {
    if (deg[i] == 0)
      st.push(i);
  }
  long long ans = 0;
  while (!st.empty()) {
    const int v = st.top();
    st.pop();
    auto &pv = ph[v];
    while (!pv.empty() && time[v] < pv.top()) {
      pv.pop();
      ans += v + 1;
    }
    if (v == 0)
      continue;
    ph[p[v]] = heap_type::meld(std::move(ph[p[v]]), std::move(pv));
    deg[p[v]] -= 1;
    if (deg[p[v]] == 0)
      st.push(p[v]);
  }
  std::cout << ans << "\n";
}

int main() {
#include "other/fast_ios.cpp"

  while (true) {
    int n, q;
    std::cin >> n >> q;
    if (n == 0 && q == 0)
      break;
    solve(n, q);
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/pairing_heap.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170&lang=en"

#line 1 "data_structure/pairing_heap.cpp"
#include <cassert>
#include <memory>
#include <utility>

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
#line 1 "other/opposite_ordered_set.cpp"
template <class W> class opposite_ordered_set {
  using T = typename W::value_type;

public:
  using value_type = T;
  static constexpr bool compare(const T &l, const T &r) noexcept {
    return W::compare(r, l);
  }
};
#line 7 "test/pairing_heap.test.cpp"

#include <algorithm>
#include <iostream>
#include <stack>
#line 12 "test/pairing_heap.test.cpp"
#include <vector>

void solve(const int n, const int q) {
  using heap_type =
      pairing_heap<opposite_ordered_set<less_equal_ordered_set<int>>>;

  std::vector<int> p(n), deg(n, 0);
  for (int i = 1; i != n; i += 1) {
    std::cin >> p[i];
    p[i] -= 1;
    deg[p[i]] += 1;
  }
  std::vector<heap_type> ph(n);
  std::vector<int> time(n, q);
  time[0] = -1;
  for (int i = 0; i != q; i += 1) {
    char c;
    std::cin >> c;
    switch (c) {
    case 'M': {
      int v;
      std::cin >> v;
      v -= 1;
      time[v] = std::min(time[v], i);
    } break;
    case 'Q': {
      int v;
      std::cin >> v;
      v -= 1;
      ph[v].push(i);
    } break;
    }
  }
  std::stack<int> st;
  for (int i = 0; i != n; i += 1) {
    if (deg[i] == 0)
      st.push(i);
  }
  long long ans = 0;
  while (!st.empty()) {
    const int v = st.top();
    st.pop();
    auto &pv = ph[v];
    while (!pv.empty() && time[v] < pv.top()) {
      pv.pop();
      ans += v + 1;
    }
    if (v == 0)
      continue;
    ph[p[v]] = heap_type::meld(std::move(ph[p[v]]), std::move(pv));
    deg[p[v]] -= 1;
    if (deg[p[v]] == 0)
      st.push(p[v]);
  }
  std::cout << ans << "\n";
}

int main() {
#line 1 "other/fast_ios.cpp"
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
#line 71 "test/pairing_heap.test.cpp"

  while (true) {
    int n, q;
    std::cin >> n >> q;
    if (n == 0 && q == 0)
      break;
    solve(n, q);
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

