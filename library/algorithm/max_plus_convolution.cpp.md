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


# :heavy_check_mark: Max Plus Convolution <small>(algorithm/max_plus_convolution.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/max_plus_convolution.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 16:21:51+09:00




## Depends on

* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Required by

* :heavy_check_mark: <a href="axiotis_tzamos_unbounded_knapsack.cpp.html">Axiotis-Tzamos Unbounded Knapsack <small>(algorithm/axiotis_tzamos_unbounded_knapsack.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/axiotis_tzamos_unbounded_knapsack.test.cpp.html">test/axiotis_tzamos_unbounded_knapsack.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"

#include <algorithm>
#include <vector>

template <class T>
std::vector<T> max_plus_convolution(const std::vector<T> &a,
                                    const std::vector<T> &b) {
  const usize n = a.size();
  const usize m = b.size();
  std::vector<T> c(n + m - 1, std::numeric_limits<T>::lowest());
  for (usize i = 0; i != n; i += 1) {
    for (usize j = 0; j != m; j += 1)
      c[i + j] = std::max(c[i + j], a[i] + b[j]);
  }
  return c;
}

/**
 * @brief Max Plus Convolution
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
#line 2 "algorithm/max_plus_convolution.cpp"

#include <algorithm>
#include <vector>

template <class T>
std::vector<T> max_plus_convolution(const std::vector<T> &a,
                                    const std::vector<T> &b) {
  const usize n = a.size();
  const usize m = b.size();
  std::vector<T> c(n + m - 1, std::numeric_limits<T>::lowest());
  for (usize i = 0; i != n; i += 1) {
    for (usize j = 0; j != m; j += 1)
      c[i + j] = std::max(c[i + j], a[i] + b[j]);
  }
  return c;
}

/**
 * @brief Max Plus Convolution
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

