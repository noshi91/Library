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


# :heavy_check_mark: data_structure/pairing_heap.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/pairing_heap.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-16 01:11:55+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/erasable_heap.aoj.test.cpp.html">test/erasable_heap.aoj.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/pairing_heap.aoj.test.cpp.html">test/pairing_heap.aoj.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

