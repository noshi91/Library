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


# :heavy_check_mark: Segment Tree <small>(data_structure/segment_tree.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/segment_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:58:19+09:00


* see: <a href="https://scrapbox.io/data-structures/Segment_Tree">https://scrapbox.io/data-structures/Segment_Tree</a>


## Operations

モノイド$M$の列$(a_1, a_2, \dots, a_n)$を扱う.
空間計算量$\Theta(n)$

-   $\mathtt{new}()$
    -   列の項がすべて$M$の単位元であるSegment Treeを作成する.
    -   時間計算量[$ \Theta(n)$]
-   $\mathtt{build}(a_1, a_2, \dots, a_n)$
    -   与えられた列を表現するSegment Treeを作成する.
    -   時間計算量$\Theta(n)$
-   $\mathtt{set}(i, x)$
    -   $a_i$に$x$を代入する.
    -   時間計算量$O(\log n)$
-   $\mathtt{fold}(l, r)$
    -   $a_l \cdot a_{l+1} \cdot \dots \cdot a_r$を計算する.
    -   時間計算量$O(\log n)$


## Depends on

* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/segment_tree.test.cpp.html">test/segment_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <vector>

template <class M> class segment_tree {
  using T = typename M::value_type;

public:
  using value_type = T;

private:
  std::vector<T> tree;

  template <class F>
  usize search_subtree(usize index, const F f, T fold_l) const {
    while (index < size()) {
      const T temp = M::operation(fold_l, tree[index * 2]);
      if (!f(temp)) {
        index = index * 2;
      } else {
        fold_l = temp;
        index = index * 2 + 1;
      }
    }
    return index - size();
  }

public:
  segment_tree() = default;

  explicit segment_tree(const usize n) : tree(n * 2, M::identity) {}

  usize size() const noexcept { return tree.size() / 2; }

  T fold(usize first, usize last) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    T fold_l = M::identity;
    T fold_r = M::identity;
    while (first != last) {
      if (first % 2 != 0) {
        fold_l = M::operation(fold_l, tree[first]);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        fold_r = M::operation(tree[last], fold_r);
      }
      last /= 2;
    }
    return M::operation(fold_l, fold_r);
  }
  
  template <class F> usize search(usize first, usize last, const F f) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    const usize last_cp = last;
    usize shift = 0;
    T fold_l = M::identity;
    while (first != last) {
      if (first % 2 != 0) {
        const T temp = M::operation(fold_l, tree[first]);
        if (!f(temp))
          return search_subtree(first, f, fold_l);
        fold_l = temp;
        first += 1;
      }
      first /= 2;
      last /= 2;
      shift += 1;
    }
    while (shift != 0) {
      shift -= 1;
      last = last_cp >> shift;
      if (last % 2 != 0) {
        last -= 1;
        const T temp = M::operation(fold_l, tree[last]);
        if (!f(temp))
          return search_subtree(last, f, fold_l);
        fold_l = temp;
      }
    }
    return last_cp - size();
  }

  void update(usize index, const T x) {
    assert(index < size());
    index += size();
    tree[index] = x;
    while (index != 1) {
      index /= 2;
      tree[index] = M::operation(tree[index * 2], tree[index * 2 + 1]);
    }
  }
};

/**
 * @brief Segment Tree
 * @docs docs/segment_tree.md
 * @see https://scrapbox.io/data-structures/Segment_Tree
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
#line 2 "data_structure/segment_tree.cpp"

#include <cassert>
#line 5 "data_structure/segment_tree.cpp"
#include <vector>

template <class M> class segment_tree {
  using T = typename M::value_type;

public:
  using value_type = T;

private:
  std::vector<T> tree;

  template <class F>
  usize search_subtree(usize index, const F f, T fold_l) const {
    while (index < size()) {
      const T temp = M::operation(fold_l, tree[index * 2]);
      if (!f(temp)) {
        index = index * 2;
      } else {
        fold_l = temp;
        index = index * 2 + 1;
      }
    }
    return index - size();
  }

public:
  segment_tree() = default;

  explicit segment_tree(const usize n) : tree(n * 2, M::identity) {}

  usize size() const noexcept { return tree.size() / 2; }

  T fold(usize first, usize last) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    T fold_l = M::identity;
    T fold_r = M::identity;
    while (first != last) {
      if (first % 2 != 0) {
        fold_l = M::operation(fold_l, tree[first]);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        fold_r = M::operation(tree[last], fold_r);
      }
      last /= 2;
    }
    return M::operation(fold_l, fold_r);
  }
  
  template <class F> usize search(usize first, usize last, const F f) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    const usize last_cp = last;
    usize shift = 0;
    T fold_l = M::identity;
    while (first != last) {
      if (first % 2 != 0) {
        const T temp = M::operation(fold_l, tree[first]);
        if (!f(temp))
          return search_subtree(first, f, fold_l);
        fold_l = temp;
        first += 1;
      }
      first /= 2;
      last /= 2;
      shift += 1;
    }
    while (shift != 0) {
      shift -= 1;
      last = last_cp >> shift;
      if (last % 2 != 0) {
        last -= 1;
        const T temp = M::operation(fold_l, tree[last]);
        if (!f(temp))
          return search_subtree(last, f, fold_l);
        fold_l = temp;
      }
    }
    return last_cp - size();
  }

  void update(usize index, const T x) {
    assert(index < size());
    index += size();
    tree[index] = x;
    while (index != 1) {
      index /= 2;
      tree[index] = M::operation(tree[index * 2], tree[index * 2 + 1]);
    }
  }
};

/**
 * @brief Segment Tree
 * @docs docs/segment_tree.md
 * @see https://scrapbox.io/data-structures/Segment_Tree
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

