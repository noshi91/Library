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


# :warning: Persistent Stack <small>(data_structure/persistent_stack.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/persistent_stack.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-16 22:45:32+09:00




## Required by

* :warning: <a href="physicists_queue.cpp.html">Physicist's Queue <small>(data_structure/physicists_queue.cpp)</small></a>
* :warning: <a href="realtime_queue.cpp.html">Realtime Queue <small>(data_structure/realtime_queue.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <memory>
#include <utility>

template <class T> class persistent_stack {
  using Self = persistent_stack<T>;
  class node_type;
  using node_ptr = std::shared_ptr<const node_type>;

  class node_type {
  public:
    T value;
    node_ptr next;

    node_type(T value, node_ptr next) : value(value), next(next) {}
  };

  node_ptr root;

  persistent_stack(node_ptr root) : root(root) {}

public:
  persistent_stack() = default;

  bool empty() const { return not root; }

  T top() const {
    assert(not empty());

    return root->value;
  }

  Self push(T x) const {
    return Self(std::make_shared<const node_type>(x, root));
  }

  Self pop() const {
    assert(not empty());

    return Self(root->next);
  }

  Self reverse() const {
    Self ret;
    Self x = *this;
    while (not x.empty()) {
      ret = ret.push(x.top());
      x = x.pop();
    }
    return ret;
  }
};

/**
 * @brief Persistent Stack
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/persistent_stack.cpp"
#include <cassert>
#include <memory>
#include <utility>

template <class T> class persistent_stack {
  using Self = persistent_stack<T>;
  class node_type;
  using node_ptr = std::shared_ptr<const node_type>;

  class node_type {
  public:
    T value;
    node_ptr next;

    node_type(T value, node_ptr next) : value(value), next(next) {}
  };

  node_ptr root;

  persistent_stack(node_ptr root) : root(root) {}

public:
  persistent_stack() = default;

  bool empty() const { return not root; }

  T top() const {
    assert(not empty());

    return root->value;
  }

  Self push(T x) const {
    return Self(std::make_shared<const node_type>(x, root));
  }

  Self pop() const {
    assert(not empty());

    return Self(root->next);
  }

  Self reverse() const {
    Self ret;
    Self x = *this;
    while (not x.empty()) {
      ret = ret.push(x.top());
      x = x.pop();
    }
    return ret;
  }
};

/**
 * @brief Persistent Stack
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

