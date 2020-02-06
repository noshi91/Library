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


# :warning: data_structure/ternary_treap.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/ternary_treap.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-07 00:19:08+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
reference: https://arxiv.org/abs/1606.04042
*/

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <random>
#include <utility>
#include <vector>

template <class W> class ternary_treap {
  using size_t = std::size_t;
  using T = typename W::value_type;

public:
  using key_type = std::vector<T>;

private:
  using key_itr = typename key_type::const_iterator;
  class node_type;
  using node_ptr = std::unique_ptr<node_type>;
  class mid_type {
    friend ternary_treap;

    size_t prio_;
    size_t key_prio;
    node_ptr ptr;

    void fix() { prio_ = std::max(key_prio, prio(ptr)); }

  public:
    mid_type() : prio_(0), key_prio(0), ptr() {}
  };
  class node_type {
    friend ternary_treap;

    T key;
    node_ptr left;
    mid_type mid;
    node_ptr right;

    size_t prio() const { return mid.prio_; }

  public:
    node_type(const T key) : key(key), left(), mid(), right() {}
  };

  static size_t rand() {
    static std::default_random_engine rng(91);
    static std::uniform_int_distribution<size_t> uid(
        1, std::numeric_limits<size_t>::max());
    return uid(rng);
  }
  static size_t prio(const node_ptr &ptr) { return ptr ? ptr->prio() : 0; }
  static void rot_left(node_ptr &ptr) {
    node_ptr right = std::move(ptr->right);
    ptr->right = std::move(right->left);
    right->left = std::move(ptr);
    ptr = std::move(right);
  }
  static void rot_right(node_ptr &ptr) {
    node_ptr left = std::move(ptr->left);
    ptr->left = std::move(left->right);
    left->right = std::move(ptr);
    ptr = std::move(left);
  }

  static bool contains(const mid_type &mid, const key_itr f, const key_itr l) {
    if (f == l)
      return mid.key_prio != 0;
    return contains(mid.ptr, f, l);
  }
  static bool contains(const node_ptr &ptr, const key_itr f, const key_itr l) {
    if (!ptr)
      return false;
    if (!W::compare(ptr->key, *f))
      return contains(ptr->left, f, l);
    else if (!W::compare(*f, ptr->key))
      return contains(ptr->right, f, l);
    else
      return contains(ptr->mid, std::next(f), l);
  }
  static void insert(mid_type &mid, const key_itr f, const key_itr l) {
    if (f == l) {
      if (mid.key_prio == 0)
        mid.key_prio = rand();
    } else {
      insert(mid.ptr, f, l);
    }
    mid.fix();
  }
  static void insert(node_ptr &ptr, const key_itr f, const key_itr l) {
    if (!ptr)
      ptr = std::make_unique<node_type>(*f);
    if (!W::compare(ptr->key, *f)) {
      insert(ptr->left, f, l);
      if (ptr->left->prio() > ptr->prio())
        rot_right(ptr);
    } else if (!W::compare(*f, ptr->key)) {
      insert(ptr->right, f, l);
      if (ptr->right->prio() > ptr->prio())
        rot_left(ptr);
    } else {
      insert(ptr->mid, std::next(f), l);
    }
  }
  static void erase(mid_type &mid, const key_itr f, const key_itr l) {
    if (f == l) {
      if (mid.key_prio != 0)
        mid.key_prio = 0;
    } else {
      erase(mid.ptr, f, l);
    }
    mid.fix();
  }
  static void erase(node_ptr &ptr, const key_itr f, const key_itr l) {
    if (!ptr)
      return;
    if (!W::compare(ptr->key, *f)) {
      erase(ptr->left, f, l);
    } else if (!W::compare(*f, ptr->key)) {
      erase(ptr->right, f, l);
    } else {
      erase(ptr->mid, std::next(f), l);
      heapify(ptr);
    }
  }
  static void heapify(node_ptr &ptr) {
    if (prio(ptr->left) > ptr->prio() || prio(ptr->right) > ptr->prio()) {
      if (prio(ptr->left) >= prio(ptr->right)) {
        rot_right(ptr);
        heapify(ptr->right);
      } else {
        rot_left(ptr);
        heapify(ptr->left);
      }
    } else {
      if (ptr->prio() == 0)
        ptr.reset();
    }
  }

  mid_type root;

public:
  ternary_treap() = default;

  bool empty() const { return root.prio == 0; }

  bool contains(const key_type x) const {
    return contains(root, x.cbegin(), x.cend());
  }

  void insert(const std::vector<T> x) { insert(root, x.cbegin(), x.cend()); }
  void erase(const std::vector<T> x) { erase(root, x.cbegin(), x.cend()); }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/ternary_treap.cpp"
/*
reference: https://arxiv.org/abs/1606.04042
*/

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <random>
#include <utility>
#include <vector>

template <class W> class ternary_treap {
  using size_t = std::size_t;
  using T = typename W::value_type;

public:
  using key_type = std::vector<T>;

private:
  using key_itr = typename key_type::const_iterator;
  class node_type;
  using node_ptr = std::unique_ptr<node_type>;
  class mid_type {
    friend ternary_treap;

    size_t prio_;
    size_t key_prio;
    node_ptr ptr;

    void fix() { prio_ = std::max(key_prio, prio(ptr)); }

  public:
    mid_type() : prio_(0), key_prio(0), ptr() {}
  };
  class node_type {
    friend ternary_treap;

    T key;
    node_ptr left;
    mid_type mid;
    node_ptr right;

    size_t prio() const { return mid.prio_; }

  public:
    node_type(const T key) : key(key), left(), mid(), right() {}
  };

  static size_t rand() {
    static std::default_random_engine rng(91);
    static std::uniform_int_distribution<size_t> uid(
        1, std::numeric_limits<size_t>::max());
    return uid(rng);
  }
  static size_t prio(const node_ptr &ptr) { return ptr ? ptr->prio() : 0; }
  static void rot_left(node_ptr &ptr) {
    node_ptr right = std::move(ptr->right);
    ptr->right = std::move(right->left);
    right->left = std::move(ptr);
    ptr = std::move(right);
  }
  static void rot_right(node_ptr &ptr) {
    node_ptr left = std::move(ptr->left);
    ptr->left = std::move(left->right);
    left->right = std::move(ptr);
    ptr = std::move(left);
  }

  static bool contains(const mid_type &mid, const key_itr f, const key_itr l) {
    if (f == l)
      return mid.key_prio != 0;
    return contains(mid.ptr, f, l);
  }
  static bool contains(const node_ptr &ptr, const key_itr f, const key_itr l) {
    if (!ptr)
      return false;
    if (!W::compare(ptr->key, *f))
      return contains(ptr->left, f, l);
    else if (!W::compare(*f, ptr->key))
      return contains(ptr->right, f, l);
    else
      return contains(ptr->mid, std::next(f), l);
  }
  static void insert(mid_type &mid, const key_itr f, const key_itr l) {
    if (f == l) {
      if (mid.key_prio == 0)
        mid.key_prio = rand();
    } else {
      insert(mid.ptr, f, l);
    }
    mid.fix();
  }
  static void insert(node_ptr &ptr, const key_itr f, const key_itr l) {
    if (!ptr)
      ptr = std::make_unique<node_type>(*f);
    if (!W::compare(ptr->key, *f)) {
      insert(ptr->left, f, l);
      if (ptr->left->prio() > ptr->prio())
        rot_right(ptr);
    } else if (!W::compare(*f, ptr->key)) {
      insert(ptr->right, f, l);
      if (ptr->right->prio() > ptr->prio())
        rot_left(ptr);
    } else {
      insert(ptr->mid, std::next(f), l);
    }
  }
  static void erase(mid_type &mid, const key_itr f, const key_itr l) {
    if (f == l) {
      if (mid.key_prio != 0)
        mid.key_prio = 0;
    } else {
      erase(mid.ptr, f, l);
    }
    mid.fix();
  }
  static void erase(node_ptr &ptr, const key_itr f, const key_itr l) {
    if (!ptr)
      return;
    if (!W::compare(ptr->key, *f)) {
      erase(ptr->left, f, l);
    } else if (!W::compare(*f, ptr->key)) {
      erase(ptr->right, f, l);
    } else {
      erase(ptr->mid, std::next(f), l);
      heapify(ptr);
    }
  }
  static void heapify(node_ptr &ptr) {
    if (prio(ptr->left) > ptr->prio() || prio(ptr->right) > ptr->prio()) {
      if (prio(ptr->left) >= prio(ptr->right)) {
        rot_right(ptr);
        heapify(ptr->right);
      } else {
        rot_left(ptr);
        heapify(ptr->left);
      }
    } else {
      if (ptr->prio() == 0)
        ptr.reset();
    }
  }

  mid_type root;

public:
  ternary_treap() = default;

  bool empty() const { return root.prio == 0; }

  bool contains(const key_type x) const {
    return contains(root, x.cbegin(), x.cend());
  }

  void insert(const std::vector<T> x) { insert(root, x.cbegin(), x.cend()); }
  void erase(const std::vector<T> x) { erase(root, x.cbegin(), x.cend()); }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

