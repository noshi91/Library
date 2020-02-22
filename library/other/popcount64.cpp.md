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


# :heavy_check_mark: other/popcount64.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/popcount64.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-22 11:33:14+09:00




## Required by

* :heavy_check_mark: <a href="../data_structure/bit_vector.cpp.html">data_structure/bit_vector.cpp</a>
* :heavy_check_mark: <a href="../data_structure/wavelet_matrix.cpp.html">data_structure/wavelet_matrix.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.aoj.test.cpp.html">test/wavelet_matrix.aoj.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.select.test.cpp.html">test/wavelet_matrix.select.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

