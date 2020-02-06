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


# :warning: data_structure/partially_persistent_union_find.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/partially_persistent_union_find.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-18 15:53:51+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <limits>
#include <vector>

class partially_persistent_union_find {
  using size_t = std::size_t;

public:
  using time_type = size_t;

private:
  class node_type {
    friend partially_persistent_union_find;

    time_type time;
    size_t parent;
    size_t size;

    node_type(const time_type time, const size_t parent, const size_t size)
        : time(time), parent(parent), size(size) {}
  };
  class sh_node {
    friend partially_persistent_union_find;

    time_type time;
    size_t size;

    sh_node(const time_type time, const size_t size) : time(time), size(size) {}
  };

  std::vector<node_type> tree;
  std::vector<std::vector<sh_node>> size_history;
  time_type time_count;

  size_t size() const { return tree.size(); }

public:
  partially_persistent_union_find() = default;
  explicit partially_persistent_union_find(const size_t n)
      : tree(n, node_type(std::numeric_limits<time_type>::max(), 0, 1)),
        size_history(n, std::vector<sh_node>({sh_node(0, 1)})), time_count(0) {
    for (size_t i = 0; i != n; i += 1)
      tree[i].parent = i;
  }

  time_type now() const { return time_count; }

  size_t find(const time_type time, size_t x) const {
    assert(x < size());
    while (tree[x].time <= time)
      x = tree[x].parent;
    return x;
  }
  bool same(const time_type time, const size_t x, const size_t y) const {
    assert(x < size());
    assert(y < size());
    return find(time, x) == find(time, y);
  }
  size_t size(const time_type time, size_t x) const {
    assert(x < size());
    x = find(time, x);
    return std::prev(std::partition_point(
                         size_history[x].cbegin(), size_history[x].cend(),
                         [time](const sh_node &h) { return h.time <= time; }))
        ->size;
  }

  time_type unite(size_t x, size_t y) {
    assert(x < tree.size());
    assert(y < tree.size());
    x = find(now(), x);
    y = find(now(), y);
    time_count += 1;
    if (x != y) {
      if (tree[x].size < tree[y].size)
        std::swap(x, y);
      tree[x].size += tree[y].size;
      tree[y].parent = x;
      tree[y].time = time_count;
      size_history[x].push_back(sh_node(time_count, tree[x].size));
    }
    return time_count - 1;
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/partially_persistent_union_find.cpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <limits>
#include <vector>

class partially_persistent_union_find {
  using size_t = std::size_t;

public:
  using time_type = size_t;

private:
  class node_type {
    friend partially_persistent_union_find;

    time_type time;
    size_t parent;
    size_t size;

    node_type(const time_type time, const size_t parent, const size_t size)
        : time(time), parent(parent), size(size) {}
  };
  class sh_node {
    friend partially_persistent_union_find;

    time_type time;
    size_t size;

    sh_node(const time_type time, const size_t size) : time(time), size(size) {}
  };

  std::vector<node_type> tree;
  std::vector<std::vector<sh_node>> size_history;
  time_type time_count;

  size_t size() const { return tree.size(); }

public:
  partially_persistent_union_find() = default;
  explicit partially_persistent_union_find(const size_t n)
      : tree(n, node_type(std::numeric_limits<time_type>::max(), 0, 1)),
        size_history(n, std::vector<sh_node>({sh_node(0, 1)})), time_count(0) {
    for (size_t i = 0; i != n; i += 1)
      tree[i].parent = i;
  }

  time_type now() const { return time_count; }

  size_t find(const time_type time, size_t x) const {
    assert(x < size());
    while (tree[x].time <= time)
      x = tree[x].parent;
    return x;
  }
  bool same(const time_type time, const size_t x, const size_t y) const {
    assert(x < size());
    assert(y < size());
    return find(time, x) == find(time, y);
  }
  size_t size(const time_type time, size_t x) const {
    assert(x < size());
    x = find(time, x);
    return std::prev(std::partition_point(
                         size_history[x].cbegin(), size_history[x].cend(),
                         [time](const sh_node &h) { return h.time <= time; }))
        ->size;
  }

  time_type unite(size_t x, size_t y) {
    assert(x < tree.size());
    assert(y < tree.size());
    x = find(now(), x);
    y = find(now(), y);
    time_count += 1;
    if (x != y) {
      if (tree[x].size < tree[y].size)
        std::swap(x, y);
      tree[x].size += tree[y].size;
      tree[y].parent = x;
      tree[y].time = time_count;
      size_history[x].push_back(sh_node(time_count, tree[x].size));
    }
    return time_count - 1;
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

