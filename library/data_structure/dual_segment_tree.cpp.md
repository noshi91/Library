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


# :warning: data_structure/dual_segment_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/dual_segment_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-19 16:46:57+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <cstddef>
#include <vector>

template <class Monoid> class dual_segment_tree {
  using size_t = std::size_t;
  using T = typename Monoid::value_type;

public:
  using value_type = T;
  using size_type = size_t;

private:
  static size_t lsb(const size_t x) { return __builtin_ctz(x); }
  static size_t msb(const size_t x) { return 31 - __builtin_clz(x); }
  static void add(T &x, const T y) { x = Monoid::operation(x, y); }

  std::vector<T> tree;

  void push(const size_t index) {
    add(tree[index * 2], tree[index]);
    add(tree[index * 2 + 1], tree[index]);
    tree[index] = Monoid::identity;
  }
  void propagate(const size_t index) {
    if (index == 0)
      return;
    const size_t lsb_ = lsb(index);
    for (size_t h = msb(index); h != lsb_; h -= 1)
      push(index >> h);
  }

public:
  dual_segment_tree() = default;
  explicit dual_segment_tree(const size_t n) : tree(n * 2, Monoid::identity) {}

  size_t size() const noexcept { return tree.size() / 2; }

  T fold(size_t index) const {
    assert(index < size());
    index += size();
    T ret = tree[index];
    while (index != 1) {
      index /= 2;
      add(ret, tree[index]);
    }
    return ret;
  }

  void update(size_t first, size_t last, const T x) {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    propagate(first);
    propagate(last);
    while (first != last) {
      if (first % 2 != 0) {
        add(tree[first], x);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        add(tree[last], x);
      }
      last /= 2;
    }
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/dual_segment_tree.cpp"
#include <cassert>
#include <cstddef>
#include <vector>

template <class Monoid> class dual_segment_tree {
  using size_t = std::size_t;
  using T = typename Monoid::value_type;

public:
  using value_type = T;
  using size_type = size_t;

private:
  static size_t lsb(const size_t x) { return __builtin_ctz(x); }
  static size_t msb(const size_t x) { return 31 - __builtin_clz(x); }
  static void add(T &x, const T y) { x = Monoid::operation(x, y); }

  std::vector<T> tree;

  void push(const size_t index) {
    add(tree[index * 2], tree[index]);
    add(tree[index * 2 + 1], tree[index]);
    tree[index] = Monoid::identity;
  }
  void propagate(const size_t index) {
    if (index == 0)
      return;
    const size_t lsb_ = lsb(index);
    for (size_t h = msb(index); h != lsb_; h -= 1)
      push(index >> h);
  }

public:
  dual_segment_tree() = default;
  explicit dual_segment_tree(const size_t n) : tree(n * 2, Monoid::identity) {}

  size_t size() const noexcept { return tree.size() / 2; }

  T fold(size_t index) const {
    assert(index < size());
    index += size();
    T ret = tree[index];
    while (index != 1) {
      index /= 2;
      add(ret, tree[index]);
    }
    return ret;
  }

  void update(size_t first, size_t last, const T x) {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    propagate(first);
    propagate(last);
    while (first != last) {
      if (first % 2 != 0) {
        add(tree[first], x);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        add(tree[last], x);
      }
      last /= 2;
    }
  }
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>
