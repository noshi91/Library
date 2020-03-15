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


# :warning: Realtime Queue <small>(data_structure/realtime_queue.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/realtime_queue.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-15 20:02:36+09:00


* see: <a href="https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf">https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf</a>


## Depends on

* :warning: <a href="persistent_stack.cpp.html">Persistent Stack <small>(data_structure/persistent_stack.cpp)</small></a>
* :warning: <a href="stream.cpp.html">Stream <small>(data_structure/stream.cpp)</small></a>
* :warning: <a href="../other/suspension.cpp.html">Suspension <small>(other/suspension.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "data_structure/persistent_stack.cpp"
#include "data_structure/stream.cpp"

#include <cassert>
#include <utility>

template <class T> class realtime_queue {
  using Self = realtime_queue<T>;
  using stream_type = stream<T>;
  using cell_type = typename stream_type::cell_type;
  using stack_type = persistent_stack<T>;

public:
  using value_type = T;

private:
  static stream_type rotate(stream_type f, stack_type b, stream_type t) {
    return stream_type([f, b, t] {
      if (f.empty())
        return cell_type(std::in_place, b.top(), t);
      else
        return cell_type(std::in_place, f.top(),
                         rotate(f.pop(), b.pop(), t.push(b.top())));
    });
  }

  static Self make_queue(stream_type f, stack_type b, stream_type s) {
    if (not s.empty())
      return Self(f, b, s.pop());
    stream_type temp = rotate(f, b, stream_type());
    return Self(temp, stack_type(), temp);
  }

  stream_type front_;
  stack_type back_;
  stream_type schedule;

  realtime_queue(stream_type f, stack_type b, stream_type s)
      : front_(f), back_(b), schedule(s) {}

public:
  realtime_queue() = default;

  bool empty() const { return front_.empty(); }

  T front() const {
    assert(not empty());

    return front_.top();
  }

  Self push(T x) const { return make_queue(front_, back_.push(x), schedule); }

  Self pop() const {
    assert(not empty());

    return make_queue(front_.pop(), back_, schedule);
  }
};

/**
 * @brief Realtime Queue
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
};

/**
 * @brief Persistent Stack
 */
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
#line 2 "data_structure/stream.cpp"

#line 4 "data_structure/stream.cpp"
#include <optional>
#line 6 "data_structure/stream.cpp"

template <class T>
class stream : private suspension<std::optional<std::pair<T, stream<T>>>> {
  using Self = stream<T>;

public:
  using value_type = T;

  using cell_type = std::optional<std::pair<T, Self>>;

private:
  using base_type = suspension<cell_type>;

  static Self reverse_sub(Self x) {
    Self ret;
    while (not x.empty()) {
      ret = ret.push(x.top());
      x = x.pop();
    }
    return ret;
  }

  stream(T x, Self s)
      : base_type(std::in_place, cell_type(std::in_place, x, s)) {}

public:
  stream() : base_type(std::in_place, cell_type(std::nullopt)) {}

  stream(std::function<cell_type()> f) : base_type(f) {}

  using base_type::force;

  bool empty() const { return not force().has_value(); }

  T top() const {
    assert(not empty());

    return (*force()).first;
  }

  Self push(T x) const { return Self(x, *this); }

  Self pop() const {
    assert(not empty());

    return (*force()).second;
  }

  Self reverse() const {
    return Self([x = *this] { return reverse_sub(x).force(); });
  }

  friend Self operator+(Self l, Self r) {
    return Self([l, r] {
      if (l.empty())
        return r.force();
      else
        return cell_type(std::in_place, l.top(), l.pop() + r);
    });
  }
};

/**
 * @brief Stream
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */
#line 3 "data_structure/realtime_queue.cpp"

#line 6 "data_structure/realtime_queue.cpp"

template <class T> class realtime_queue {
  using Self = realtime_queue<T>;
  using stream_type = stream<T>;
  using cell_type = typename stream_type::cell_type;
  using stack_type = persistent_stack<T>;

public:
  using value_type = T;

private:
  static stream_type rotate(stream_type f, stack_type b, stream_type t) {
    return stream_type([f, b, t] {
      if (f.empty())
        return cell_type(std::in_place, b.top(), t);
      else
        return cell_type(std::in_place, f.top(),
                         rotate(f.pop(), b.pop(), t.push(b.top())));
    });
  }

  static Self make_queue(stream_type f, stack_type b, stream_type s) {
    if (not s.empty())
      return Self(f, b, s.pop());
    stream_type temp = rotate(f, b, stream_type());
    return Self(temp, stack_type(), temp);
  }

  stream_type front_;
  stack_type back_;
  stream_type schedule;

  realtime_queue(stream_type f, stack_type b, stream_type s)
      : front_(f), back_(b), schedule(s) {}

public:
  realtime_queue() = default;

  bool empty() const { return front_.empty(); }

  T front() const {
    assert(not empty());

    return front_.top();
  }

  Self push(T x) const { return make_queue(front_, back_.push(x), schedule); }

  Self pop() const {
    assert(not empty());

    return make_queue(front_.pop(), back_, schedule);
  }
};

/**
 * @brief Realtime Queue
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

