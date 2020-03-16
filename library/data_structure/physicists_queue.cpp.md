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


# :warning: Physicist's Queue <small>(data_structure/physicists_queue.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/physicists_queue.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-16 22:45:32+09:00


* see: <a href="https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf">https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf</a>


## Depends on

* :warning: <a href="persistent_stack.cpp.html">Persistent Stack <small>(data_structure/persistent_stack.cpp)</small></a>
* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>
* :warning: <a href="../other/suspension.cpp.html">Suspension <small>(other/suspension.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "data_structure/persistent_stack.cpp"
#include "other/int_alias.cpp"
#include "other/suspension.cpp"

#include <cassert>
#include <utility>

template <class T> class physicists_queue {
  using Self = physicists_queue<T>;
  using stack_type = persistent_stack<T>;
  using susp_stack = suspension<stack_type>;

  stack_type working;
  susp_stack front_;
  usize f_size;
  stack_type back_;
  usize b_size;

  physicists_queue(stack_type working, susp_stack front_, usize f_size,
                   stack_type back_, usize b_size)
      : working(working), front_(front_), f_size(f_size), back_(back_),
        b_size(b_size) {}

  Self check_r() const {
    if (f_size >= b_size)
      return *this;
    stack_type temp = front_.force();
    auto f = [l = temp, r = back_]() mutable {
      r = r.reverse();
      l = l.reverse();
      while (not l.empty()) {
        r = r.push(l.top());
        l = l.pop();
      }
      return r;
    };
    return Self(temp, susp_stack(f), f_size + b_size, stack_type(), 0);
  }

  Self check_w() const {
    if (working.empty())
      return Self(front_.force(), front_, f_size, back_, b_size);
    else
      return *this;
  }

  Self check() const { return check_r().check_w(); }

public:
  physicists_queue()
      : working(), front_(std::in_place, stack_type()), f_size(0), back_(),
        b_size(0) {}

  bool empty() const { return f_size == 0; }

  T front() const {
    assert(not empty());

    return working.top();
  }

  Self push(T x) const {
    return Self(working, front_, f_size, back_.push(x), b_size + 1).check();
  }

  Self pop() const {
    assert(not empty());

    return Self(working.pop(),
                susp_stack([f = front_]() { return f.force().pop(); }),
                f_size - 1, back_, b_size)
        .check();
  }
};

/**
 * @brief Physicist's Queue
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
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
#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 1 "other/suspension.cpp"
#include <functional>
#line 4 "other/suspension.cpp"
#include <variant>

template <class T>
class suspension
    : private std::shared_ptr<std::variant<T, std::function<T()>>> {
public:
  using value_type = T;
  using func_type = std::function<T()>;
  using node_type = std::variant<T, func_type>;

private:
  using base_type = std::shared_ptr<node_type>;

  static T get(node_type &x) {
    if (x.index() != 0)
      x = std::get<1>(x)();
    return std::get<0>(x);
  }

  template <class... Args> static base_type make_node(Args &&... args) {
    return std::make_shared<node_type>(std::forward<Args>(args)...);
  }

public:
  suspension(std::in_place_t, T x)
      : base_type(make_node(std::in_place_index<0>, x)) {}

  suspension(func_type f) : base_type(make_node(std::in_place_index<1>, f)) {}

  T force() const { return get(**this); }
};

/**
 * @brief Suspension
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */
#line 4 "data_structure/physicists_queue.cpp"

#line 7 "data_structure/physicists_queue.cpp"

template <class T> class physicists_queue {
  using Self = physicists_queue<T>;
  using stack_type = persistent_stack<T>;
  using susp_stack = suspension<stack_type>;

  stack_type working;
  susp_stack front_;
  usize f_size;
  stack_type back_;
  usize b_size;

  physicists_queue(stack_type working, susp_stack front_, usize f_size,
                   stack_type back_, usize b_size)
      : working(working), front_(front_), f_size(f_size), back_(back_),
        b_size(b_size) {}

  Self check_r() const {
    if (f_size >= b_size)
      return *this;
    stack_type temp = front_.force();
    auto f = [l = temp, r = back_]() mutable {
      r = r.reverse();
      l = l.reverse();
      while (not l.empty()) {
        r = r.push(l.top());
        l = l.pop();
      }
      return r;
    };
    return Self(temp, susp_stack(f), f_size + b_size, stack_type(), 0);
  }

  Self check_w() const {
    if (working.empty())
      return Self(front_.force(), front_, f_size, back_, b_size);
    else
      return *this;
  }

  Self check() const { return check_r().check_w(); }

public:
  physicists_queue()
      : working(), front_(std::in_place, stack_type()), f_size(0), back_(),
        b_size(0) {}

  bool empty() const { return f_size == 0; }

  T front() const {
    assert(not empty());

    return working.top();
  }

  Self push(T x) const {
    return Self(working, front_, f_size, back_.push(x), b_size + 1).check();
  }

  Self pop() const {
    assert(not empty());

    return Self(working.pop(),
                susp_stack([f = front_]() { return f.force().pop(); }),
                f_size - 1, back_, b_size)
        .check();
  }
};

/**
 * @brief Physicist's Queue
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

