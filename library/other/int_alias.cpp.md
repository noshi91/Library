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


# :heavy_check_mark: other/int_alias.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/int_alias.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-02 16:21:18+09:00




## Required by

* :heavy_check_mark: <a href="../algorithm/axiotis_tzamos_knapsack.cpp.html">Axiotis-Tzamos Knapsack <small>(algorithm/axiotis_tzamos_knapsack.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/axiotis_tzamos_unbounded_knapsack.cpp.html">Axiotis-Tzamos Unbounded Knapsack <small>(algorithm/axiotis_tzamos_unbounded_knapsack.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/concave_max_plus_convolution.cpp.html">Concave Max Plus Convolution <small>(algorithm/concave_max_plus_convolution.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/max_plus_convolution.cpp.html">Max Plus Convolution <small>(algorithm/max_plus_convolution.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/smawk.cpp.html">SMAWK Algorithm <small>(algorithm/smawk.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/three_edge_connected_component_decomposition.cpp.html">algorithm/three_edge_connected_component_decomposition.cpp</a>
* :heavy_check_mark: <a href="../algorithm/zeta_transform.cpp.html">Zeta Transform <small>(algorithm/zeta_transform.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/randomized_queue.cpp.html">Randomized Queue <small>(data_structure/randomized_queue.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/union_enumerate.cpp.html">Union Enumerate <small>(data_structure/union_enumerate.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/axiotis_tzamos_knapsack.test.cpp.html">test/axiotis_tzamos_knapsack.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/axiotis_tzamos_unbounded_knapsack.test.cpp.html">test/axiotis_tzamos_unbounded_knapsack.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/randomized_queue.test.cpp.html">test/randomized_queue.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/three_edge_connected_component_decomposition.test.cpp.html">test/three_edge_connected_component_decomposition.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/zeta_transform.aoj.test.cpp.html">test/zeta_transform.aoj.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

