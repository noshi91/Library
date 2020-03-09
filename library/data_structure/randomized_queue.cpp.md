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


# :heavy_check_mark: Randomized Queue <small>(data_structure/randomized_queue.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/randomized_queue.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-09 21:14:06+09:00




## Depends on

* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>
* :heavy_check_mark: <a href="../other/random_integer.cpp.html">other/random_integer.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/randomized_queue.test.cpp.html">test/randomized_queue.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"
#include "other/random_integer.cpp"

#include <cassert>
#include <cstddef>
#include <random>
#include <vector>

template <class T> class randomized_queue {
public:
  using value_type = T;

private:
  std::vector<T> c;

  void select() {
    std::swap(c.back(), c[random_integer<usize>(0, c.size() - 1)]);
  }

public:
  randomized_queue() = default;

  bool empty() const { return c.empty(); }
  usize size() const { return c.size(); }
  T &front() {
    assert(!empty());
    select();
    return c.back();
  }

  void push(T x) { c.push_back(std::move(x)); }
  T pop() {
    assert(!empty());
    select();
    const T ret = std::move(c.back());
    c.pop_back();
    return ret;
  }
};

/**
 * @brief Randomized Queue
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
#line 2 "other/random_integer.cpp"

#include <random>
#include <type_traits>

template <class T, class... Args>
using any_of_is_same = std::disjunction<std::is_same<T, Args>...>;

template <class IntType = int>
IntType random_integer(const IntType a, const IntType b) {
  static_assert(
      any_of_is_same<IntType, short, int, long, long long, unsigned short,
                     unsigned int, unsigned long, unsigned long long>::value);
  static std::default_random_engine g(91);
  return std::uniform_int_distribution<IntType>(a, b)(g);
}
#line 3 "data_structure/randomized_queue.cpp"

#include <cassert>
#include <cstddef>
#include <random>
#include <vector>

template <class T> class randomized_queue {
public:
  using value_type = T;

private:
  std::vector<T> c;

  void select() {
    std::swap(c.back(), c[random_integer<usize>(0, c.size() - 1)]);
  }

public:
  randomized_queue() = default;

  bool empty() const { return c.empty(); }
  usize size() const { return c.size(); }
  T &front() {
    assert(!empty());
    select();
    return c.back();
  }

  void push(T x) { c.push_back(std::move(x)); }
  T pop() {
    assert(!empty());
    select();
    const T ret = std::move(c.back());
    c.pop_back();
    return ret;
  }
};

/**
 * @brief Randomized Queue
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

