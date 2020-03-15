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


# :heavy_check_mark: Wavelet Matrix <small>(data_structure/wavelet_matrix.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/wavelet_matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:58:19+09:00




## Depends on

* :heavy_check_mark: <a href="bit_vector.cpp.html">Bit Vector <small>(data_structure/bit_vector.cpp)</small></a>
* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>
* :heavy_check_mark: <a href="../other/popcount.cpp.html">other/popcount.cpp</a>
* :heavy_check_mark: <a href="../other/select64.cpp.html">other/select64.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.quantile.test.cpp.html">test/wavelet_matrix.quantile.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.rangefreq.test.cpp.html">test/wavelet_matrix.rangefreq.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.select.test.cpp.html">test/wavelet_matrix.select.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "data_structure/bit_vector.cpp"
#include "other/int_alias.cpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

template <class Key> class wavelet_matrix {
public:
  using key_type = Key;
  using value_type = Key;

private:
  static bool test(const key_type x, const usize k) {
    return (x & static_cast<key_type>(1) << k) != 0;
  }
  static void set(key_type &x, const usize k) {
    x |= static_cast<key_type>(1) << k;
  }

  usize size_;
  std::vector<bit_vector> mat;

  usize less(usize first, usize last, const key_type key) const {
    usize ret = 0;
    for (usize p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p)) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        ret += v.rank0(last) - v.rank0(first);
        const usize b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }

public:
  wavelet_matrix() = default;
  explicit wavelet_matrix(const usize bit_length, std::vector<key_type> a)
      : size_(a.size()), mat(bit_length, bit_vector()) {
    const usize s = size();
    for (usize p = bit_length; p != 0;) {
      p -= 1;
      {
        std::vector<bool> t(s);
        for (usize i = 0; i != s; i += 1)
          t[i] = test(a[i], p);
        mat[p] = bit_vector(t);
      }
      {
        std::vector<key_type> v0, v1;
        for (const usize e : a)
          (test(e, p) ? v1 : v0).push_back(e);
        const auto itr = std::copy(v0.cbegin(), v0.cend(), a.begin());
        std::copy(v1.cbegin(), v1.cend(), itr);
      }
    }
  }

  usize size() const { return size_; }

  usize rangefreq(const usize first, const usize last, const key_type lower,
                  const key_type upper) const {
    assert(first <= last);
    assert(last <= size());
    assert(lower <= upper);

    return less(first, last, upper) - less(first, last, lower);
  }
  key_type quantile(usize first, usize last, usize k) const {
    assert(first <= last);
    assert(last <= size());
    assert(k < last - first);

    key_type ret = 0;
    for (usize p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      const usize z = v.rank0(last) - v.rank0(first);
      if (k < z) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        set(ret, p);
        k -= z;
        const usize b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }
  usize select(const key_type key, const usize k) const {
    usize index = 0;
    for (usize p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.rank0(index);
      else
        index = v.rank0(size()) + v.rank1(index);
    }
    index += k;
    for (usize p = 0; p != mat.size(); p += 1) {
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.select0(index);
      else
        index = v.select1(index - v.rank0(size()));
    }
    return index;
  }
};

/**
 * @brief Wavelet Matrix
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
#line 2 "other/popcount.cpp"

#line 4 "other/popcount.cpp"

usize popcount(u64 x) {
#ifdef __GNUC__
  return __builtin_popcountll(x);
#else
  x -= x >> 1 & 0x5555555555555555;
  x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
  x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;
  return x * 0x0101010101010101 >> 56 & 0x7f;
#endif
}
#line 2 "other/select64.cpp"

#line 5 "other/select64.cpp"

usize select64(const u64 x0, usize k) {
  const u64 x1 = (x0 & 0x5555555555555555) + (x0 >> 1 & 0x5555555555555555);
  const u64 x2 = (x1 & 0x3333333333333333) + (x1 >> 2 & 0x3333333333333333);
  const u64 x3 = (x2 & 0x0F0F0F0F0F0F0F0F) + (x2 >> 4 & 0x0F0F0F0F0F0F0F0F);
  const u64 x4 = (x3 & 0x00FF00FF00FF00FF) + (x3 >> 8 & 0x00FF00FF00FF00FF);
  const u64 x5 = (x4 & 0x0000FFFF0000FFFF) + (x4 >> 16 & 0x0000FFFF0000FFFF);
  usize ret = 0;
  usize t;
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
#line 4 "data_structure/bit_vector.cpp"

#line 6 "data_structure/bit_vector.cpp"
#include <limits>
#include <vector>

class bit_vector {
  static constexpr usize wordsize = std::numeric_limits<usize>::digits;

  class node_type {
  public:
    usize bit;
    usize sum;

    node_type() : bit(0), sum(0) {}
  };

  std::vector<node_type> v;

public:
  bit_vector() = default;
  explicit bit_vector(const std::vector<bool> a) : v(a.size() / wordsize + 1) {
    {
      const usize s = a.size();
      for (usize i = 0; i != s; i += 1)
        v[i / wordsize].bit |= static_cast<usize>(a[i] ? 1 : 0) << i % wordsize;
    }
    {
      const usize s = v.size();
      for (usize i = 1; i != s; i += 1)
        v[i].sum = v[i - 1].sum + popcount(v[i - 1].bit);
    }
  }

  usize rank0(const usize index) const { return index - rank1(index); }
  usize rank1(const usize index) const {
    return v[index / wordsize].sum +
           popcount(v[index / wordsize].bit &
                    ~(~static_cast<usize>(0) << index % wordsize));
  }
  usize select0(const usize k) const {
    usize l = 0;
    usize r = v.size();
    while (l != r) {
      const usize m = (l + r) / 2;
      if (m * wordsize - v[m].sum <= k)
        l = m + 1;
      else
        r = m;
    }
    const usize i = l - 1;
    return i * wordsize + select64(~v[i].bit, k - (i * wordsize - v[i].sum));
  }
  usize select1(const usize k) const {
    usize l = 0;
    usize r = v.size();
    while (l != r) {
      const usize m = (l + r) / 2;
      if (v[m].sum <= k)
        l = m + 1;
      else
        r = m;
    }
    const usize i = l - 1;
    return i * wordsize + select64(v[i].bit, k - v[i].sum);
  }
};

/**
 * @brief Bit Vector
 */
#line 3 "data_structure/wavelet_matrix.cpp"

#include <algorithm>
#include <cassert>
#line 8 "data_structure/wavelet_matrix.cpp"

template <class Key> class wavelet_matrix {
public:
  using key_type = Key;
  using value_type = Key;

private:
  static bool test(const key_type x, const usize k) {
    return (x & static_cast<key_type>(1) << k) != 0;
  }
  static void set(key_type &x, const usize k) {
    x |= static_cast<key_type>(1) << k;
  }

  usize size_;
  std::vector<bit_vector> mat;

  usize less(usize first, usize last, const key_type key) const {
    usize ret = 0;
    for (usize p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p)) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        ret += v.rank0(last) - v.rank0(first);
        const usize b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }

public:
  wavelet_matrix() = default;
  explicit wavelet_matrix(const usize bit_length, std::vector<key_type> a)
      : size_(a.size()), mat(bit_length, bit_vector()) {
    const usize s = size();
    for (usize p = bit_length; p != 0;) {
      p -= 1;
      {
        std::vector<bool> t(s);
        for (usize i = 0; i != s; i += 1)
          t[i] = test(a[i], p);
        mat[p] = bit_vector(t);
      }
      {
        std::vector<key_type> v0, v1;
        for (const usize e : a)
          (test(e, p) ? v1 : v0).push_back(e);
        const auto itr = std::copy(v0.cbegin(), v0.cend(), a.begin());
        std::copy(v1.cbegin(), v1.cend(), itr);
      }
    }
  }

  usize size() const { return size_; }

  usize rangefreq(const usize first, const usize last, const key_type lower,
                  const key_type upper) const {
    assert(first <= last);
    assert(last <= size());
    assert(lower <= upper);

    return less(first, last, upper) - less(first, last, lower);
  }
  key_type quantile(usize first, usize last, usize k) const {
    assert(first <= last);
    assert(last <= size());
    assert(k < last - first);

    key_type ret = 0;
    for (usize p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      const usize z = v.rank0(last) - v.rank0(first);
      if (k < z) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        set(ret, p);
        k -= z;
        const usize b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }
  usize select(const key_type key, const usize k) const {
    usize index = 0;
    for (usize p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.rank0(index);
      else
        index = v.rank0(size()) + v.rank1(index);
    }
    index += k;
    for (usize p = 0; p != mat.size(); p += 1) {
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.select0(index);
      else
        index = v.select1(index - v.rank0(size()));
    }
    return index;
  }
};

/**
 * @brief Wavelet Matrix
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
