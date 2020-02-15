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


# :heavy_check_mark: test/wavelet_matrix.aoj.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/wavelet_matrix.aoj.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-15 22:44:53+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/bit_vector.cpp.html">data_structure/bit_vector.cpp</a>
* :heavy_check_mark: <a href="../../library/data_structure/wavelet_matrix.cpp.html">data_structure/wavelet_matrix.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426&lang=ja"

#include "data_structure/wavelet_matrix.cpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  constexpr int offset = 1000000000;

  int n, m;
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> ps(n);
  for (auto &[x, y] : ps)
    std::cin >> x >> y;
  std::sort(ps.begin(), ps.end());
  const auto wm = [&] {
    std::vector<int> ys(n);
    std::transform(ps.cbegin(), ps.cend(), ys.begin(),
                   [](const auto &p) { return offset + p.second; });
    return wavelet_matrix<int>(31, ys);
  }();
  const auto idx = [&](const int xt) -> int {
    return std::partition_point(ps.cbegin(), ps.cend(),
                                [&](const auto &p) { return p.first < xt; }) -
           ps.cbegin();
  };
  for (int i = 0; i != m; i += 1) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    x2 += 1;
    y2 += 1;
    std::cout << wm.rangefreq(idx(x1), idx(x2), offset + y1, offset + y2)
              << std::endl;
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/wavelet_matrix.aoj.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426&lang=ja"

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
#line 2 "data_structure/wavelet_matrix.cpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

template <class Key> class wavelet_matrix {
  using size_t = std::size_t;

public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;

private:
  static bool test(const key_type x, const size_t k) {
    return (x & static_cast<key_type>(1) << k) != 0;
  }
  static void set(key_type &x, const size_t k) {
    x |= static_cast<key_type>(1) << k;
  }

  size_t size_;
  std::vector<bit_vector> mat;

  size_t less(size_t first, size_t last, const key_type key) const {
    size_t ret = 0;
    for (size_t p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p)) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        ret += v.rank0(last) - v.rank0(first);
        const size_t b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }

public:
  wavelet_matrix() = default;
  explicit wavelet_matrix(const size_t bit_length, std::vector<key_type> a)
      : size_(a.size()), mat(bit_length, bit_vector()) {
    const size_t s = size();
    for (size_t p = bit_length; p != 0;) {
      p -= 1;
      {
        std::vector<bool> t(s);
        for (size_t i = 0; i != s; i += 1)
          t[i] = test(a[i], p);
        mat[p] = bit_vector(t);
      }
      {
        std::vector<key_type> v0, v1;
        for (const size_t e : a)
          (test(e, p) ? v1 : v0).push_back(e);
        const auto itr = std::copy(v0.cbegin(), v0.cend(), a.begin());
        std::copy(v1.cbegin(), v1.cend(), itr);
      }
    }
  }

  size_t size() const { return size_; }

  size_t rangefreq(const size_t first, const size_t last, const key_type lower,
                   const key_type upper) const {
    assert(first <= last);
    assert(last <= size());
    assert(lower <= upper);

    return less(first, last, upper) - less(first, last, lower);
  }
  key_type quantile(size_t first, size_t last, size_t k) const {
    assert(first <= last);
    assert(last <= size());
    assert(k < last - first);

    key_type ret = 0;
    for (size_t p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      const size_t z = v.rank0(last) - v.rank0(first);
      if (k < z) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        k -= z;
        const size_t b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }
};
#line 5 "test/wavelet_matrix.aoj.test.cpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  constexpr int offset = 1000000000;

  int n, m;
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> ps(n);
  for (auto &[x, y] : ps)
    std::cin >> x >> y;
  std::sort(ps.begin(), ps.end());
  const auto wm = [&] {
    std::vector<int> ys(n);
    std::transform(ps.cbegin(), ps.cend(), ys.begin(),
                   [](const auto &p) { return offset + p.second; });
    return wavelet_matrix<int>(31, ys);
  }();
  const auto idx = [&](const int xt) -> int {
    return std::partition_point(ps.cbegin(), ps.cend(),
                                [&](const auto &p) { return p.first < xt; }) -
           ps.cbegin();
  };
  for (int i = 0; i != m; i += 1) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    x2 += 1;
    y2 += 1;
    std::cout << wm.rangefreq(idx(x1), idx(x2), offset + y1, offset + y2)
              << std::endl;
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

