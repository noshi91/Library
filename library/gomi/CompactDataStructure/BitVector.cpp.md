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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: gomi/CompactDataStructure/BitVector.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#a55307e5cbe2b6bd3e0de2bb8cae60d9">gomi/CompactDataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/gomi/CompactDataStructure/BitVector.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-11 20:43:35+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <cstdint>
#include <vector>

class BitVector {
  using uintl32 = std::uint_least32_t;
  using uint32 = std::uint_fast32_t;
  const uint32 size_;
  std::vector<uintl32> b, r, sh[2], sd[2];
  static uint32 get(const uint32 size) { return (size >> 5) + 1; }
#ifdef __GNUC__
  static uint32 popcount32(uint32 c) { return __builtin_popcount(c); }
#else
  static uint32 popcount32(uint32 c) {
    c = (c & 0x55555555) + (c >> 1 & 0x55555555);
    c = (c & 0x33333333) + (c >> 2 & 0x33333333);
    c = (c + (c >> 4)) & 0x0F0F0F0F;
    c += c >> 8;
    c += c >> 16;
    return c & 0x3F;
  }
#endif
  static uint32 select32(uint32 c, uint32 k) {
    uint32 t2 = (c & 0x55555555) + (c >> 1 & 0x55555555),
           t4 = (t2 & 0x33333333) + (t2 >> 2 & 0x33333333),
           t8 = (t4 + (t4 >> 4)) & 0x0F0F0F0F,
           t16 = (t8 + (t8 >> 8)) & 0x000000FF;
    uint32 ret = 0;
    if (k >= t16) {
      k -= t16;
      ret |= 16;
    }
    t8 = t8 >> ret & 0xf;
    if (k >= t8) {
      k -= t8;
      ret |= 8;
    }
    t4 = t4 >> ret & 0x7;
    if (k >= t4) {
      k -= t4;
      ret |= 4;
    }
    t2 = t2 >> ret & 0x3;
    if (k >= t2) {
      k -= t2;
      ret |= 2;
    }
    return k >= (c >> ret & 1) ? ret + 1 : ret;
  }

public:
  BitVector(const uint32 size)
      : size_(get(size)), b(size_, 0),
        r(size_, 0), sd{std::vector<uintl32>(size_, 0),
                        std::vector<uintl32>(size_, 0)} {}
  void set(const uint32 index) {
    assert(index < size_ << 5);
    b[index >> 5] |= (uintl32)1 << (index & 0x1f);
  }
  void build() {
    for (uint32 i = 1; i < size_; ++i)
      r[i] = r[i - 1] + popcount32(b[i - 1]);
    for (uint32 i = 0, cnt = 0; i < size_ << 5; ++i)
      if (~b[i >> 5] >> (i & 0x1f) & 1 && !((cnt++) & 0x1f))
        sh[0].push_back(i);
    sh[0].push_back(size_ << 5);
    const uint32 s0 = sh[0].size() - 1;
    for (uint32 i = 0; i < s0; ++i) {
      const uint32 left = (sh[0][i] + 31) >> 5;
      if ((sh[0][i + 1] >> 5) - left < 32)
        continue;
      for (uint32 j = sh[0][i], cnt = 0; j < sh[0][i + 1]; ++j)
        if (~b[j >> 5] >> (j & 0x1f) & 1)
          sd[0][left + (cnt++)] = j;
    }
    for (uint32 i = 0, cnt = 0; i < size_ << 5; ++i)
      if (b[i >> 5] >> (i & 0x1f) & 1 && !((cnt++) & 0x1f))
        sh[1].push_back(i);
    sh[1].push_back(size_ << 5);
    const uint32 s1 = sh[1].size() - 1;
    for (uint32 i = 0; i < s1; ++i) {
      const uint32 left = (sh[1][i] + 31) >> 5;
      if ((sh[1][i + 1] >> 5) - left < 32)
        continue;
      for (uint32 j = sh[1][i], cnt = 0; j < sh[1][i + 1]; ++j)
        if (b[j >> 5] >> (j & 0x1f) & 1)
          sd[1][left + (cnt++)] = j;
    }
  }
  bool operator[](const uint32 index) const {
    assert(index < size_ << 5);
    return b[index >> 5] >> (index & 0x1f) & 1;
  }
  uint32 rank(const uint32 index) const {
    assert(index < size_ << 5);
    return r[index >> 5] +
           popcount32(b[index >> 5] & ((uint32)1 << (index & 0x1f)) - 1);
  }
  uint32 select(const uint32 k, const bool bit) const {
    assert(bit || k < (size_ << 5) - rank((size_ << 5) - 1));
    assert(!bit || k < rank((size_ << 5) - 1));
    const auto &head = sh[bit];
    uint32 left = head[k >> 5] + 31 >> 5, right = head[(k >> 5) + 1] >> 5;
    if (right - left >= 32)
      return sd[bit][left + (k & 0x1f)];
    left = head[k >> 5] >> 5;
    right = head[(k >> 5) + 1] + 31 >> 5;
    while (right - left != 1) {
      uint32 mid = (left + right) >> 1;
      ((bit ? r[mid] : (mid << 5) - r[mid]) > k ? right : left) = mid;
    }
    return (left << 5) + select32(bit ? b[left] : ~b[left], k - r[left]);
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "gomi/CompactDataStructure/BitVector.cpp"
#include <cassert>
#include <cstdint>
#include <vector>

class BitVector {
  using uintl32 = std::uint_least32_t;
  using uint32 = std::uint_fast32_t;
  const uint32 size_;
  std::vector<uintl32> b, r, sh[2], sd[2];
  static uint32 get(const uint32 size) { return (size >> 5) + 1; }
#ifdef __GNUC__
  static uint32 popcount32(uint32 c) { return __builtin_popcount(c); }
#else
  static uint32 popcount32(uint32 c) {
    c = (c & 0x55555555) + (c >> 1 & 0x55555555);
    c = (c & 0x33333333) + (c >> 2 & 0x33333333);
    c = (c + (c >> 4)) & 0x0F0F0F0F;
    c += c >> 8;
    c += c >> 16;
    return c & 0x3F;
  }
#endif
  static uint32 select32(uint32 c, uint32 k) {
    uint32 t2 = (c & 0x55555555) + (c >> 1 & 0x55555555),
           t4 = (t2 & 0x33333333) + (t2 >> 2 & 0x33333333),
           t8 = (t4 + (t4 >> 4)) & 0x0F0F0F0F,
           t16 = (t8 + (t8 >> 8)) & 0x000000FF;
    uint32 ret = 0;
    if (k >= t16) {
      k -= t16;
      ret |= 16;
    }
    t8 = t8 >> ret & 0xf;
    if (k >= t8) {
      k -= t8;
      ret |= 8;
    }
    t4 = t4 >> ret & 0x7;
    if (k >= t4) {
      k -= t4;
      ret |= 4;
    }
    t2 = t2 >> ret & 0x3;
    if (k >= t2) {
      k -= t2;
      ret |= 2;
    }
    return k >= (c >> ret & 1) ? ret + 1 : ret;
  }

public:
  BitVector(const uint32 size)
      : size_(get(size)), b(size_, 0),
        r(size_, 0), sd{std::vector<uintl32>(size_, 0),
                        std::vector<uintl32>(size_, 0)} {}
  void set(const uint32 index) {
    assert(index < size_ << 5);
    b[index >> 5] |= (uintl32)1 << (index & 0x1f);
  }
  void build() {
    for (uint32 i = 1; i < size_; ++i)
      r[i] = r[i - 1] + popcount32(b[i - 1]);
    for (uint32 i = 0, cnt = 0; i < size_ << 5; ++i)
      if (~b[i >> 5] >> (i & 0x1f) & 1 && !((cnt++) & 0x1f))
        sh[0].push_back(i);
    sh[0].push_back(size_ << 5);
    const uint32 s0 = sh[0].size() - 1;
    for (uint32 i = 0; i < s0; ++i) {
      const uint32 left = (sh[0][i] + 31) >> 5;
      if ((sh[0][i + 1] >> 5) - left < 32)
        continue;
      for (uint32 j = sh[0][i], cnt = 0; j < sh[0][i + 1]; ++j)
        if (~b[j >> 5] >> (j & 0x1f) & 1)
          sd[0][left + (cnt++)] = j;
    }
    for (uint32 i = 0, cnt = 0; i < size_ << 5; ++i)
      if (b[i >> 5] >> (i & 0x1f) & 1 && !((cnt++) & 0x1f))
        sh[1].push_back(i);
    sh[1].push_back(size_ << 5);
    const uint32 s1 = sh[1].size() - 1;
    for (uint32 i = 0; i < s1; ++i) {
      const uint32 left = (sh[1][i] + 31) >> 5;
      if ((sh[1][i + 1] >> 5) - left < 32)
        continue;
      for (uint32 j = sh[1][i], cnt = 0; j < sh[1][i + 1]; ++j)
        if (b[j >> 5] >> (j & 0x1f) & 1)
          sd[1][left + (cnt++)] = j;
    }
  }
  bool operator[](const uint32 index) const {
    assert(index < size_ << 5);
    return b[index >> 5] >> (index & 0x1f) & 1;
  }
  uint32 rank(const uint32 index) const {
    assert(index < size_ << 5);
    return r[index >> 5] +
           popcount32(b[index >> 5] & ((uint32)1 << (index & 0x1f)) - 1);
  }
  uint32 select(const uint32 k, const bool bit) const {
    assert(bit || k < (size_ << 5) - rank((size_ << 5) - 1));
    assert(!bit || k < rank((size_ << 5) - 1));
    const auto &head = sh[bit];
    uint32 left = head[k >> 5] + 31 >> 5, right = head[(k >> 5) + 1] >> 5;
    if (right - left >= 32)
      return sd[bit][left + (k & 0x1f)];
    left = head[k >> 5] >> 5;
    right = head[(k >> 5) + 1] + 31 >> 5;
    while (right - left != 1) {
      uint32 mid = (left + right) >> 1;
      ((bit ? r[mid] : (mid << 5) - r[mid]) > k ? right : left) = mid;
    }
    return (left << 5) + select32(bit ? b[left] : ~b[left], k - r[left]);
  }
};
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

