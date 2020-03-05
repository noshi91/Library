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


# :heavy_check_mark: other/countl_zero64.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/countl_zero64.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-22 20:51:34+09:00




## Required by

* :heavy_check_mark: <a href="../algorithm/axiotis_tzamos_unbounded_knapsack.cpp.html">Axiotis-Tzamos Unbounded Knapsack <small>(algorithm/axiotis_tzamos_unbounded_knapsack.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/radix_heap.cpp.html">Radix Heap <small>(data_structure/radix_heap.cpp)</small></a>
* :heavy_check_mark: <a href="log2p164.cpp.html">other/log2p164.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/axiotis_tzamos_unbounded_knapsack.test.cpp.html">test/axiotis_tzamos_unbounded_knapsack.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/radix_heap.aoj.test.cpp.html">test/radix_heap.aoj.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <array>
#include <cstddef>
#include <cstdint>

std::size_t countl_zero64(std::uint_fast64_t x) {
#ifdef __GNUC__
  return x == 0 ? 64 : __builtin_clzll(x);
#else
  if (x == 0)
    return 64;
  std::size_t ret = 0;
  if ((x & 0xFFFFFFFF00000000) != 0)
    x >>= 32;
  else
    ret += 32;
  if ((x & 0xFFFF0000) != 0)
    x >>= 16;
  else
    ret += 16;
  if ((x & 0xFF00) != 0)
    x >>= 8;
  else
    ret += 8;
  if ((x & 0xF0) != 0)
    x >>= 4;
  else
    ret += 4;
  if ((x & 0xC) != 0)
    x >>= 2;
  else
    ret += 2;
  if ((x & 0x2) != 0)
    x >>= 1;
  else
    ret += 1;
  return ret;
#endif
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/countl_zero64.cpp"
#include <array>
#include <cstddef>
#include <cstdint>

std::size_t countl_zero64(std::uint_fast64_t x) {
#ifdef __GNUC__
  return x == 0 ? 64 : __builtin_clzll(x);
#else
  if (x == 0)
    return 64;
  std::size_t ret = 0;
  if ((x & 0xFFFFFFFF00000000) != 0)
    x >>= 32;
  else
    ret += 32;
  if ((x & 0xFFFF0000) != 0)
    x >>= 16;
  else
    ret += 16;
  if ((x & 0xFF00) != 0)
    x >>= 8;
  else
    ret += 8;
  if ((x & 0xF0) != 0)
    x >>= 4;
  else
    ret += 4;
  if ((x & 0xC) != 0)
    x >>= 2;
  else
    ret += 2;
  if ((x & 0x2) != 0)
    x >>= 1;
  else
    ret += 1;
  return ret;
#endif
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
