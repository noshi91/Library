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


# :warning: Banker's Queue <small>(data_structure/bankers_queue.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/bankers_queue.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-15 20:02:36+09:00


* see: <a href="https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf">https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf</a>


## Depends on

* :warning: <a href="stream.cpp.html">Stream <small>(data_structure/stream.cpp)</small></a>
* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>
* :warning: <a href="../other/suspension.cpp.html">Suspension <small>(other/suspension.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "data_structure/stream.cpp"
#include "other/int_alias.cpp"

#include <cassert>

template <class T> class bankers_queue {
  using Self = bankers_queue<T>;
  using stream_type = stream<T>;

  stream_type front_;
  usize f_size;
  stream_type back_;
  usize b_size;

  bankers_queue(stream_type front_, usize f_size, stream_type back_,
                usize b_size)
      : front_(front_), f_size(f_size), back_(back_), b_size(b_size) {}

  Self normalize() const {
    if (f_size >= b_size)
      return *this;
    else
      return Self(front_ + back_.reverse(), f_size + b_size, stream_type(), 0);
  }

public:
  bankers_queue() : front_(), f_size(0), back_(), b_size(0) {}

  bool empty() const { return f_size == 0; }

  T front() const {
    assert(not empty());

    return front_.top();
  }

  Self push(T x) const {
    return Self(front_, f_size, back_.push(x), b_size + 1).normalize();
  }

  Self pop() const {
    assert(not empty());

    return Self(front_.pop(), f_size - 1, back_, b_size).normalize();
  }
};

/**
 * @brief Banker's Queue
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/suspension.cpp"
#include <functional>
#include <memory>
#include <utility>
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

#include <cassert>
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
#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 3 "data_structure/bankers_queue.cpp"

#line 5 "data_structure/bankers_queue.cpp"

template <class T> class bankers_queue {
  using Self = bankers_queue<T>;
  using stream_type = stream<T>;

  stream_type front_;
  usize f_size;
  stream_type back_;
  usize b_size;

  bankers_queue(stream_type front_, usize f_size, stream_type back_,
                usize b_size)
      : front_(front_), f_size(f_size), back_(back_), b_size(b_size) {}

  Self normalize() const {
    if (f_size >= b_size)
      return *this;
    else
      return Self(front_ + back_.reverse(), f_size + b_size, stream_type(), 0);
  }

public:
  bankers_queue() : front_(), f_size(0), back_(), b_size(0) {}

  bool empty() const { return f_size == 0; }

  T front() const {
    assert(not empty());

    return front_.top();
  }

  Self push(T x) const {
    return Self(front_, f_size, back_.push(x), b_size + 1).normalize();
  }

  Self pop() const {
    assert(not empty());

    return Self(front_.pop(), f_size - 1, back_, b_size).normalize();
  }
};

/**
 * @brief Banker's Queue
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

