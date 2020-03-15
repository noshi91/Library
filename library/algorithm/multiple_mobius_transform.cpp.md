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


# :warning: Multiple Möbius Transform <small>(algorithm/multiple_mobius_transform.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/multiple_mobius_transform.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 23:32:43+09:00




## Depends on

* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"

#include <vector>

template <class G>
void multiple_mobius_transform(std::vector<typename G::value_type> &a) {
  const usize n = a.size();
  std::vector<bool> sieve(n, true);
  for (usize p = 2; p < n; p += 1) {
    if (!sieve[p])
      continue;
    for (usize k = 1; k * p < n; k += 1) {
      sieve[k * p] = false;
      a[k] = G::operation(a[k], G::inverse(a[k * p]));
    }
  }
}

/**
 * @brief Multiple Möbius Transform
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
#line 2 "algorithm/multiple_mobius_transform.cpp"

#include <vector>

template <class G>
void multiple_mobius_transform(std::vector<typename G::value_type> &a) {
  const usize n = a.size();
  std::vector<bool> sieve(n, true);
  for (usize p = 2; p < n; p += 1) {
    if (!sieve[p])
      continue;
    for (usize k = 1; k * p < n; k += 1) {
      sieve[k * p] = false;
      a[k] = G::operation(a[k], G::inverse(a[k * p]));
    }
  }
}

/**
 * @brief Multiple Möbius Transform
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
