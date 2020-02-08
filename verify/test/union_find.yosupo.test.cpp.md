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


# :heavy_check_mark: test/union_find.yosupo.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/union_find.yosupo.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-08 22:56:08+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/union_find.cpp.html">data_structure/union_find.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <iostream>
#include "data_structure/union_find.cpp"
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    union_find uft(n);
    while (q --) {
        int t, u, v; cin >> t >> u >> v;
        if (t == 0) {
            uft.unite(u, v);
        } else if (t == 1) {
            cout << uft.same(u, v) << endl;
        }
    }
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/union_find.yosupo.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <iostream>
#line 1 "data_structure/union_find.cpp"
#include <cassert>
#include <utility>
#include <vector>

class union_find {
private:
  using size_t = std::size_t;

  class node_type {
    friend union_find;

    size_t parent;
    size_t size;

    node_type(const size_t parent, const size_t size)
        : parent(parent), size(size) {}
  };

  std::vector<node_type> tree;

  size_t size() const { return tree.size(); }

public:
  union_find() = default;
  explicit union_find(const size_t n) : tree(n, node_type(n, 1)) {}

  size_t find(const size_t x) {
    assert(x < size());
    if (tree[x].parent == size())
      return x;
    else
      return tree[x].parent = find(tree[x].parent);
  }
  bool same(const size_t x, const size_t y) {
    assert(x < size());
    assert(y < size());
    return find(x) == find(y);
  }
  size_t size(const size_t x) {
    assert(x < size());
    return tree[find(x)].size;
  }

  void unite(size_t x, size_t y) {
    assert(x < size());
    assert(y < size());
    x = find(x);
    y = find(y);
    if (x != y) {
      if (tree[x].size < tree[y].size)
        std::swap(x, y);
      tree[x].size += tree[y].size;
      tree[y].parent = x;
    }
  }
};
#line 4 "test/union_find.yosupo.test.cpp"
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    union_find uft(n);
    while (q --) {
        int t, u, v; cin >> t >> u >> v;
        if (t == 0) {
            uft.unite(u, v);
        } else if (t == 1) {
            cout << uft.same(u, v) << endl;
        }
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

