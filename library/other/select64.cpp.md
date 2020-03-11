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


# :heavy_check_mark: other/select64.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/select64.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:58:19+09:00




## Depends on

* :heavy_check_mark: <a href="int_alias.cpp.html">other/int_alias.cpp</a>


## Required by

* :heavy_check_mark: <a href="../data_structure/bit_vector.cpp.html">Bit Vector <small>(data_structure/bit_vector.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/wavelet_matrix.cpp.html">Wavelet Matrix <small>(data_structure/wavelet_matrix.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.quantile.test.cpp.html">test/wavelet_matrix.quantile.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.rangefreq.test.cpp.html">test/wavelet_matrix.rangefreq.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.select.test.cpp.html">test/wavelet_matrix.select.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

