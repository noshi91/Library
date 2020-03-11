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
* :heavy_check_mark: <a href="../algorithm/three_edge_connected_component_decomposition.cpp.html">3-Edge-Connected Component Decomposition <small>(algorithm/three_edge_connected_component_decomposition.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/zeta_transform.cpp.html">Zeta Transform <small>(algorithm/zeta_transform.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/bit_vector.cpp.html">Bit Vector <small>(data_structure/bit_vector.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/dual_segment_tree.cpp.html">Dual Segment Tree <small>(data_structure/dual_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/fenwick_tree.cpp.html">Fenwick Tree <small>(data_structure/fenwick_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/incremental_bridge_connectivity.cpp.html">Incremental Bridge-Connectivity <small>(data_structure/incremental_bridge_connectivity.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/lazy_segment_tree.cpp.html">Lazy Segment Tree <small>(data_structure/lazy_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/potentialized_union_find.cpp.html">Potentialized Union Find <small>(data_structure/potentialized_union_find.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/radix_heap.cpp.html">Radix Heap <small>(data_structure/radix_heap.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/randomized_queue.cpp.html">Randomized Queue <small>(data_structure/randomized_queue.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/union_enumerate.cpp.html">Union Enumerate <small>(data_structure/union_enumerate.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/wavelet_matrix.cpp.html">Wavelet Matrix <small>(data_structure/wavelet_matrix.cpp)</small></a>
* :heavy_check_mark: <a href="bit_width.cpp.html">other/bit_width.cpp</a>
* :heavy_check_mark: <a href="countl_zero.cpp.html">other/countl_zero.cpp</a>
* :heavy_check_mark: <a href="countr_zero.cpp.html">other/countr_zero.cpp</a>
* :heavy_check_mark: <a href="popcount.cpp.html">other/popcount.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/axiotis_tzamos_knapsack.test.cpp.html">test/axiotis_tzamos_knapsack.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/axiotis_tzamos_unbounded_knapsack.test.cpp.html">test/axiotis_tzamos_unbounded_knapsack.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/dual_segment_tree.test.cpp.html">test/dual_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/fenwick_tree.test.cpp.html">test/fenwick_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/incremental_bridge_connectivity.test.cpp.html">test/incremental_bridge_connectivity.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/lazy_segment_tree.test.cpp.html">test/lazy_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/potentialized_union_find.test.cpp.html">test/potentialized_union_find.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/radix_heap.test.cpp.html">test/radix_heap.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/randomized_queue.test.cpp.html">test/randomized_queue.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/three_edge_connected_component_decomposition.test.cpp.html">test/three_edge_connected_component_decomposition.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.quantile.test.cpp.html">test/wavelet_matrix.quantile.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.rangefreq.test.cpp.html">test/wavelet_matrix.rangefreq.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/wavelet_matrix.select.test.cpp.html">test/wavelet_matrix.select.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/zeta_transform.test.cpp.html">test/zeta_transform.test.cpp</a>


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

