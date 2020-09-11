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


# :warning: Multiple Zeta Transform <small>(algorithm/multiple_zeta_transform.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/multiple_zeta_transform.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-11 14:24:32+09:00




## Depends on

* :heavy_check_mark: <a href="../other/ceildiv.cpp.html">other/ceildiv.cpp</a>
* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/ceildiv.cpp"
#include "other/int_alias.cpp"

#include <vector>

template <class S>
void multiple_zeta_transform(std::vector<typename S::value_type> &a) {
  const usize n = a.size();
  std::vector<bool> sieve(n, true);
  for (usize p = 2; p < n; p += 1) {
    if (!sieve[p])
      continue;
    for (usize k = ceildiv(n, p); k != 1) {
      k -= 1;
      sieve[k * p] = false;
      a[k] = S::operation(a[k], a[k * p]);
    }
  }
}

/**
 * @brief Multiple Zeta Transform
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/ceildiv.cpp"
template <class T> constexpr T ceildiv(const T &n, const T &d) {
  return n / d + (n % d != 0 ? 1 : 0);
}
#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 3 "algorithm/multiple_zeta_transform.cpp"

#include <vector>

template <class S>
void multiple_zeta_transform(std::vector<typename S::value_type> &a) {
  const usize n = a.size();
  std::vector<bool> sieve(n, true);
  for (usize p = 2; p < n; p += 1) {
    if (!sieve[p])
      continue;
    for (usize k = ceildiv(n, p); k != 1) {
      k -= 1;
      sieve[k * p] = false;
      a[k] = S::operation(a[k], a[k * p]);
    }
  }
}

/**
 * @brief Multiple Zeta Transform
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

