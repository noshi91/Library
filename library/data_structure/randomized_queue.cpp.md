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


# :warning: data_structure/randomized_queue.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/randomized_queue.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-01 23:09:18+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
    static std::default_random_engine drg(91);

    const size_t index =
        std::uniform_int_distribution<size_t>(0, c.size() - 1)(drg);
    std::swap(c.back(), c[index]);
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/randomized_queue.cpp"
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
    static std::default_random_engine drg(91);

    const size_t index =
        std::uniform_int_distribution<size_t>(0, c.size() - 1)(drg);
    std::swap(c.back(), c[index]);
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

