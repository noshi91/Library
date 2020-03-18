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


# :heavy_check_mark: test/bankers_queue.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/bankers_queue.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-18 22:48:14+09:00


* see: <a href="https://judge.yosupo.jp/problem/persistent_queue">https://judge.yosupo.jp/problem/persistent_queue</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/bankers_queue.cpp.html">Banker's Queue <small>(data_structure/bankers_queue.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/data_structure/stream.cpp.html">Stream <small>(data_structure/stream.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/fast_ios.cpp.html">other/fast_ios.cpp</a>
* :heavy_check_mark: <a href="../../library/other/int_alias.cpp.html">other/int_alias.cpp</a>
* :heavy_check_mark: <a href="../../library/other/suspension.cpp.html">Suspension <small>(other/suspension.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include "data_structure/bankers_queue.cpp"

#include <iostream>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  int q;
  std::cin >> q;

  std::vector<bankers_queue<int>> s_(q + 1);
  const auto s = s_.begin() + 1;

  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int t, x;
      std::cin >> t >> x;
      s[i] = s[t].push(x);
    } break;
    case 1: {
      int t;
      std::cin >> t;
      std::cout << s[t].front() << "\n";
      s[i] = s[t].pop();
    }
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/bankers_queue.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

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
    return Self([x = *this]() mutable {
      Self ret;
      while (not x.empty()) {
        ret = ret.push(x.top());
        x = x.pop();
      }
      return ret.force();
    });
  }

  friend Self operator+(Self l, Self r) {
    return Self([l, r]() {
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
#line 4 "test/bankers_queue.test.cpp"

#include <iostream>
#include <vector>

int main() {
#line 1 "other/fast_ios.cpp"
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
#line 10 "test/bankers_queue.test.cpp"

  int q;
  std::cin >> q;

  std::vector<bankers_queue<int>> s_(q + 1);
  const auto s = s_.begin() + 1;

  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int t, x;
      std::cin >> t >> x;
      s[i] = s[t].push(x);
    } break;
    case 1: {
      int t;
      std::cin >> t;
      std::cout << s[t].front() << "\n";
      s[i] = s[t].pop();
    }
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

