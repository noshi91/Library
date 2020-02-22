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


# :heavy_check_mark: test/wavelet_matrix.select.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/wavelet_matrix.select.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-22 12:01:43+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/bit_vector.cpp.html">data_structure/bit_vector.cpp</a>
* :heavy_check_mark: <a href="../../library/data_structure/wavelet_matrix.cpp.html">data_structure/wavelet_matrix.cpp</a>
* :heavy_check_mark: <a href="../../library/other/popcount64.cpp.html">other/popcount64.cpp</a>
* :heavy_check_mark: <a href="../../library/other/random_integer.cpp.html">other/random_integer.cpp</a>
* :heavy_check_mark: <a href="../../library/other/select64.cpp.html">other/select64.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include "data_structure/wavelet_matrix.cpp"
#include "other/random_integer.cpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
  const int n = 1 << 18;
  const int b = 10;

  std::vector<int> a(n);
  for (int &e : a)
    e = random_integer(0, (1 << b) - 1);
  const wavelet_matrix<int> wm(b, a);
  std::vector<int> count(1 << b, 0);
  for (int i = 0; i != n; i += 1) {
    const int e = a[i];
    assert(wm.select(e, count[e]) == i);
    count[e] += 1;
  }

  std::cout << "Hello World" << std::endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/wavelet_matrix.select.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#line 1 "other/popcount64.cpp"
#include <cstddef>
#include <cstdint>

std::size_t popcount64(std::uint_fast64_t x) {
#ifdef __GNUC__
  return __builtin_popcountll(x);
#else
  x -= x >> 1 & 0x5555555555555555;
  x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
  x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;
  return x * 0x0101010101010101 >> 56 & 0x7f;
#endif
}
#line 1 "other/select64.cpp"
#include <cstddef>
#include <cstdint>

std::size_t select64(const std::uint_fast64_t x0, size_t k) {
  using size_t = std::size_t;
  using u64 = std::uint_fast64_t;

  const u64 x1 = (x0 & 0x5555555555555555) + (x0 >> 1 & 0x5555555555555555);
  const u64 x2 = (x1 & 0x3333333333333333) + (x1 >> 2 & 0x3333333333333333);
  const u64 x3 = (x2 & 0x0F0F0F0F0F0F0F0F) + (x2 >> 4 & 0x0F0F0F0F0F0F0F0F);
  const u64 x4 = (x3 & 0x00FF00FF00FF00FF) + (x3 >> 8 & 0x00FF00FF00FF00FF);
  const u64 x5 = (x4 & 0x0000FFFF0000FFFF) + (x4 >> 16 & 0x0000FFFF0000FFFF);
  size_t ret = 0;
  size_t t;
  t = x5 >> ret & 0xFFFFFFFF;
  if (t <= k) {
    k -= t;
    ret += 32;
  }
  t = x4 >> ret & 0xFFFF;
  if (t <= k) {
    k -= t;
    ret += 16;
  }
  t = x3 >> ret & 0xFF;
  if (t <= k) {
    k -= t;
    ret += 8;
  }
  t = x2 >> ret & 0xF;
  if (t <= k) {
    k -= t;
    ret += 4;
  }
  t = x1 >> ret & 0x3;
  if (t <= k) {
    k -= t;
    ret += 2;
  }
  t = x0 >> ret & 0x1;
  if (t <= k) {
    k -= t;
    ret += 1;
  }
  return ret;
}
#line 3 "data_structure/bit_vector.cpp"

#include <cstddef>
#include <limits>
#include <vector>

class bit_vector {
  using size_t = std::size_t;

  static constexpr size_t wordsize = std::numeric_limits<size_t>::digits;

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
        v[i].sum = v[i - 1].sum + popcount64(v[i - 1].bit);
    }
  }

  size_t rank0(const size_t index) const { return index - rank1(index); }
  size_t rank1(const size_t index) const {
    return v[index / wordsize].sum +
           popcount64(v[index / wordsize].bit &
                      ~(~static_cast<size_t>(0) << index % wordsize));
  }
  size_t select0(const size_t k) const {
    size_t l = 0;
    size_t r = v.size();
    while (l != r) {
      const size_t m = (l + r) / 2;
      if (m * wordsize - v[m].sum <= k)
        l = m + 1;
      else
        r = m;
    }
    const size_t i = l - 1;
    return i * wordsize + select64(~v[i].bit, k - (i * wordsize - v[i].sum));
  }
  size_t select1(const size_t k) const {
    size_t l = 0;
    size_t r = v.size();
    while (l != r) {
      const size_t m = (l + r) / 2;
      if (v[m].sum <= k)
        l = m + 1;
      else
        r = m;
    }
    const size_t i = l - 1;
    return i * wordsize + select64(v[i].bit, k - v[i].sum);
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
  size_t select(const key_type key, const size_t k) const {
    size_t index = 0;
    for (size_t p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.rank0(index);
      else
        index = v.rank0(size()) + v.rank1(index);
    }
    index += k;
    for (size_t p = 0; p != mat.size(); p += 1) {
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.select0(index);
      else
        index = v.select1(index - v.rank0(size()));
    }
    return index;
  }
};
#line 1 "other/random_integer.cpp"
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
#line 6 "test/wavelet_matrix.select.test.cpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
  const int n = 1 << 18;
  const int b = 10;

  std::vector<int> a(n);
  for (int &e : a)
    e = random_integer(0, (1 << b) - 1);
  const wavelet_matrix<int> wm(b, a);
  std::vector<int> count(1 << b, 0);
  for (int i = 0; i != n; i += 1) {
    const int e = a[i];
    assert(wm.select(e, count[e]) == i);
    count[e] += 1;
  }

  std::cout << "Hello World" << std::endl;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

