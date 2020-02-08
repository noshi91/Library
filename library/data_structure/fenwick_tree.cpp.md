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


# :heavy_check_mark: data_structure/fenwick_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/fenwick_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-06 19:39:55+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/fenwick_tree.yosupo.test.cpp.html">test/fenwick_tree.yosupo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <cstddef>
#include <vector>

template <class M> class fenwick_tree {
  using size_t = std::size_t;

public:
  using T = typename M::value_type;

private:
  std::vector<T> tree;

public:
  fenwick_tree() = default;
  explicit fenwick_tree(const size_t size) : tree(size + 1, M::identity) {}

  bool empty() const { return size() == 0; }
  size_t size() const { return tree.size() - 1; }

  T fold_prefix(size_t last) const {
    assert(last <= size());
    T ret = M::identity;
    while (last != 0) {
      ret = M::operation(tree[last], ret);
      last &= last - 1;
    }
    return ret;
  }

  void add(size_t index, const T value) {
    assert(index < size());
    index += 1;
    while (index < tree.size()) {
      tree[index] = M::operation(tree[index], value);
      index += index & ~index + 1;
    }
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/fenwick_tree.cpp"
#include <cassert>
#include <cstddef>
#include <vector>

template <class M> class fenwick_tree {
  using size_t = std::size_t;

public:
  using T = typename M::value_type;

private:
  std::vector<T> tree;

public:
  fenwick_tree() = default;
  explicit fenwick_tree(const size_t size) : tree(size + 1, M::identity) {}

  bool empty() const { return size() == 0; }
  size_t size() const { return tree.size() - 1; }

  T fold_prefix(size_t last) const {
    assert(last <= size());
    T ret = M::identity;
    while (last != 0) {
      ret = M::operation(tree[last], ret);
      last &= last - 1;
    }
    return ret;
  }

  void add(size_t index, const T value) {
    assert(index < size());
    index += 1;
    while (index < tree.size()) {
      tree[index] = M::operation(tree[index], value);
      index += index & ~index + 1;
    }
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

