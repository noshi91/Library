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


# :warning: data_structure/union_enumerate.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/union_enumerate.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-21 00:19:47+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

class union_enumerate {
  using size_t = std::size_t;

  std::vector<size_t> next;

public:
  union_enumerate() = default;
  union_enumerate(const size_t size) : next(size) {
    std::iota(next.begin(), next.end(), static_cast<size_t>(0));
  }

  std::vector<size_t> enumerate(const size_t x) const {
    std::vector<size_t> ret;
    size_t y = x;
    do {
      ret.push_back(y);
      y = next[y];
    } while (y != x);
    return ret;
  }

  void unite(const size_t x, const size_t y) { std::swap(next[x], next[y]); }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/union_enumerate.cpp"
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

class union_enumerate {
  using size_t = std::size_t;

  std::vector<size_t> next;

public:
  union_enumerate() = default;
  union_enumerate(const size_t size) : next(size) {
    std::iota(next.begin(), next.end(), static_cast<size_t>(0));
  }

  std::vector<size_t> enumerate(const size_t x) const {
    std::vector<size_t> ret;
    size_t y = x;
    do {
      ret.push_back(y);
      y = next[y];
    } while (y != x);
    return ret;
  }

  void unite(const size_t x, const size_t y) { std::swap(next[x], next[y]); }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

