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


# :heavy_check_mark: data_structure/bit_vector.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/bit_vector.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-15 22:44:53+09:00




## Required by

* :heavy_check_mark: <a href="wavelet_matrix.cpp.html">data_structure/wavelet_matrix.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.aoj.test.cpp.html">test/wavelet_matrix.aoj.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cstddef>
#include <limits>
#include <vector>

class bit_vector {
  using size_t = std::size_t;

  static constexpr size_t wordsize = std::numeric_limits<size_t>::digits;

  static size_t popcount(size_t x) { return __builtin_popcountll(x); }

  class node_type {
  public:
    size_t bit;
    size_t sum;

    node_type() : bit(0), sum(0) {}
  };

  std::vector<node_type> v;

public:
  bit_vector() = default;
  explicit bit_vector(const std::vector<bool> a) : v(a.size() / wordsize + 1) {
    {
      const size_t s = a.size();
      for (size_t i = 0; i != s; i += 1)
        v[i / wordsize].bit |= static_cast<size_t>(a[i] ? 1 : 0)
                               << i % wordsize;
    }
    {
      const size_t s = v.size();
      for (size_t i = 1; i != s; i += 1)
        v[i].sum = v[i - 1].sum + popcount(v[i - 1].bit);
    }
  }

  size_t rank0(const size_t index) const { return index - rank1(index); }
  size_t rank1(const size_t index) const {
    return v[index / wordsize].sum +
           popcount(v[index / wordsize].bit &
                    ~(~static_cast<size_t>(0) << index % wordsize));
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/bit_vector.cpp"
#include <cstddef>
#include <limits>
#include <vector>

class bit_vector {
  using size_t = std::size_t;

  static constexpr size_t wordsize = std::numeric_limits<size_t>::digits;

  static size_t popcount(size_t x) { return __builtin_popcountll(x); }

  class node_type {
  public:
    size_t bit;
    size_t sum;

    node_type() : bit(0), sum(0) {}
  };

  std::vector<node_type> v;

public:
  bit_vector() = default;
  explicit bit_vector(const std::vector<bool> a) : v(a.size() / wordsize + 1) {
    {
      const size_t s = a.size();
      for (size_t i = 0; i != s; i += 1)
        v[i / wordsize].bit |= static_cast<size_t>(a[i] ? 1 : 0)
                               << i % wordsize;
    }
    {
      const size_t s = v.size();
      for (size_t i = 1; i != s; i += 1)
        v[i].sum = v[i - 1].sum + popcount(v[i - 1].bit);
    }
  }

  size_t rank0(const size_t index) const { return index - rank1(index); }
  size_t rank1(const size_t index) const {
    return v[index / wordsize].sum +
           popcount(v[index / wordsize].bit &
                    ~(~static_cast<size_t>(0) << index % wordsize));
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

