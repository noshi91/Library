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


# :warning: data_structure/persistent_forward_list.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/persistent_forward_list.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-11 20:43:35+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <memory>
#include <utility>

template <class T> class persistent_forward_list {
  using Self = persistent_forward_list;

  class node_type;
  using node_ptr = std::shared_ptr<const node_type>;
  class node_type {
  public:
    T value;
    node_ptr next;

    node_type(const T value, const node_ptr next) : value(value), next(next) {}
  };

  template <class... Args> static node_ptr make_node(Args &&... args) {
    return std::make_shared<const node_type>(std::forward<Args>(args)...);
  }

  node_ptr root;

  persistent_forward_list(const node_ptr root) : root(root) {}

public:
  persistent_forward_list() = default;

  bool empty() const { return !root; }

  T front() const {
    assert(!empty());
    return root->value;
  }

  Self push_front(const T x) const { return Self(make_node(x, root)); }
  Self pop_front() const {
    assert(!empty());
    return Self(root->next);
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/persistent_forward_list.cpp"
#include <cassert>
#include <memory>
#include <utility>

template <class T> class persistent_forward_list {
  using Self = persistent_forward_list;

  class node_type;
  using node_ptr = std::shared_ptr<const node_type>;
  class node_type {
  public:
    T value;
    node_ptr next;

    node_type(const T value, const node_ptr next) : value(value), next(next) {}
  };

  template <class... Args> static node_ptr make_node(Args &&... args) {
    return std::make_shared<const node_type>(std::forward<Args>(args)...);
  }

  node_ptr root;

  persistent_forward_list(const node_ptr root) : root(root) {}

public:
  persistent_forward_list() = default;

  bool empty() const { return !root; }

  T front() const {
    assert(!empty());
    return root->value;
  }

  Self push_front(const T x) const { return Self(make_node(x, root)); }
  Self pop_front() const {
    assert(!empty());
    return Self(root->next);
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

