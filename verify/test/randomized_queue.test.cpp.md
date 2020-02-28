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


# :heavy_check_mark: test/randomized_queue.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/randomized_queue.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-28 14:18:18+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/randomized_queue.cpp.html">Randomized Queue <small>(data_structure/randomized_queue.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/random_integer.cpp.html">other/random_integer.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include "data_structure/randomized_queue.cpp"
#include "other/random_integer.cpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int main() {
  const int n = 1 << 20;

  std::vector<int> a(n);
  for (int &e : a)
    e = random_integer(std::numeric_limits<int>::lowest(),
                       std::numeric_limits<int>::max());

  randomized_queue<int> rq;
  for (const int e : a)
    rq.push(e);

  assert(!rq.empty());

  std::vector<int> b(n);
  for (int &e : b)
    e = rq.pop();

  assert(rq.empty());
  assert(a != b);
  std::reverse(b.begin(), b.end());
  assert(a != b);
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  assert(a == b);

  std::cout << "Hello World" << std::endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/randomized_queue.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

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
#line 2 "data_structure/randomized_queue.cpp"

#include <cassert>
#include <cstddef>
#include <random>
#include <vector>

template <class T> class randomized_queue {
  using size_t = std::size_t;

public:
  using value_type = T;

private:
  std::vector<T> c;

  void select() {
    std::swap(c.back(), c[random_integer<size_t>(0, c.size() - 1)]);
  }

public:
  randomized_queue() = default;

  bool empty() const { return c.empty(); }

  T front() {
    assert(!empty());
    select();
    return c.back();
  }

  void push(const T x) { c.push_back(x); }
  T pop() {
    assert(!empty());
    select();
    const T ret = c.back();
    c.pop_back();
    return ret;
  }
};

/**
 * @brief Randomized Queue
 */
#line 6 "test/randomized_queue.test.cpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int main() {
  const int n = 1 << 20;

  std::vector<int> a(n);
  for (int &e : a)
    e = random_integer(std::numeric_limits<int>::lowest(),
                       std::numeric_limits<int>::max());

  randomized_queue<int> rq;
  for (const int e : a)
    rq.push(e);

  assert(!rq.empty());

  std::vector<int> b(n);
  for (int &e : b)
    e = rq.pop();

  assert(rq.empty());
  assert(a != b);
  std::reverse(b.begin(), b.end());
  assert(a != b);
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  assert(a == b);

  std::cout << "Hello World" << std::endl;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

