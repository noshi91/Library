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


# :heavy_check_mark: Fenwick Tree <small>(data_structure/fenwick_tree.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/fenwick_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:42:07+09:00


* see: <a href="https://scrapbox.io/data-structures/Fenwick_Tree">https://scrapbox.io/data-structures/Fenwick_Tree</a>


## Depends on

* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/fenwick_tree.test.cpp.html">test/fenwick_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <vector>

template <class M> class fenwick_tree {
  using T = typename M::value_type;

public:
  using value_type = T;

private:
  std::vector<T> tree;

public:
  fenwick_tree() = default;

  explicit fenwick_tree(const usize size) : tree(size + 1, M::identity) {}

  bool empty() const { return size() == 0; }
  
  usize size() const { return tree.size() - 1; }

  T fold_prefix(usize last) const {
    assert(last <= size());
    T ret = M::identity;
    while (last != 0) {
      ret = M::operation(tree[last], ret);
      last &= last - 1;
    }
    return ret;
  }

  void add(usize index, const T value) {
    assert(index < size());
    index += 1;
    while (index < tree.size()) {
      tree[index] = M::operation(tree[index], value);
      index += index & ~index + 1;
    }
  }
};

/**
 * @brief Fenwick Tree
 * @see https://scrapbox.io/data-structures/Fenwick_Tree
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 2 "data_structure/fenwick_tree.cpp"

#include <cassert>
#line 5 "data_structure/fenwick_tree.cpp"
#include <vector>

template <class M> class fenwick_tree {
  using T = typename M::value_type;

public:
  using value_type = T;

private:
  std::vector<T> tree;

public:
  fenwick_tree() = default;

  explicit fenwick_tree(const usize size) : tree(size + 1, M::identity) {}

  bool empty() const { return size() == 0; }
  
  usize size() const { return tree.size() - 1; }

  T fold_prefix(usize last) const {
    assert(last <= size());
    T ret = M::identity;
    while (last != 0) {
      ret = M::operation(tree[last], ret);
      last &= last - 1;
    }
    return ret;
  }

  void add(usize index, const T value) {
    assert(index < size());
    index += 1;
    while (index < tree.size()) {
      tree[index] = M::operation(tree[index], value);
      index += index & ~index + 1;
    }
  }
};

/**
 * @brief Fenwick Tree
 * @see https://scrapbox.io/data-structures/Fenwick_Tree
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

