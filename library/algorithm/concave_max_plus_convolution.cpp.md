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


# :warning: Concave Max Plus Convlution <small>(algorithm/concave_max_plus_convolution.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/concave_max_plus_convolution.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-29 00:05:54+09:00


* see: <a href="https://arxiv.org/abs/1802.06440">https://arxiv.org/abs/1802.06440</a>


## Depends on

* :warning: <a href="smawk.cpp.html">SMAWK Algorithm <small>(algorithm/smawk.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "algorithm/smawk.cpp"

#include <cstddef>
#include <vector>

template <class T>
std::vector<T> concave_max_plus_convolution(const std::vector<T> &a,
                                            const std::vector<T> &b) {
  using size_t = std::size_t;

  const size_t n = a.size();
  const size_t m = b.size();
  const auto get = [&](const size_t i, const size_t j) {
    return a[j] + b[i - j];
  };
  const std::vector<size_t> amax =
      smawk(n + m - 1, n, [&](const size_t i, const size_t j, const size_t k) {
        if (i < k)
          return false;
        if (i - j >= m)
          return true;
        return get(i, j) <= get(i, k);
      });
  std::vector<T> c(n + m - 1);
  for (size_t i = 0; i != n + m - 1; i += 1)
    c[i] = get(i, amax[i]);
  return c;
}

/**
 * @brief Concave Max Plus Convlution
 * @see https://arxiv.org/abs/1802.06440
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/smawk.cpp"
#include <cstddef>
#include <functional>
#include <numeric>
#include <vector>

template <class Select>
std::vector<std::size_t> smawk(const std::size_t row_size,
                               const std::size_t col_size,
                               const Select &select) {
  using size_t = std::size_t;
  using vec_zu = std::vector<size_t>;

  const std::function<vec_zu(const vec_zu &, const vec_zu &)> solve =
      [&](const vec_zu &row, const vec_zu &col) -> vec_zu {
    const size_t n = row.size();
    if (n == 0)
      return {};
    vec_zu c2;
    for (const size_t i : col) {
      while (!c2.empty() && select(row[c2.size() - 1], c2.back(), i))
        c2.pop_back();
      if (c2.size() < n)
        c2.push_back(i);
    }
    vec_zu r2;
    for (size_t i = 1; i < n; i += 2)
      r2.push_back(row[i]);
    const vec_zu a2 = solve(r2, c2);
    vec_zu ans(n);
    for (size_t i = 0; i != a2.size(); i += 1)
      ans[i * 2 + 1] = a2[i];
    size_t j = 0;
    for (size_t i = 0; i < n; i += 2) {
      ans[i] = c2[j];
      const size_t end = i + 1 == n ? c2.back() : ans[i + 1];
      while (c2[j] != end) {
        j += 1;
        if (select(row[i], ans[i], c2[j]))
          ans[i] = c2[j];
      }
    }
    return ans;
  };
  vec_zu row(row_size);
  std::iota(row.begin(), row.end(), 0);
  vec_zu col(col_size);
  std::iota(col.begin(), col.end(), 0);
  return solve(row, col);
}

/**
 * @brief SMAWK Algorithm
 * @see http://www.cs.ust.hk/mjg_lib/bibs/DPSu/DPSu.Files/p285-aggarwal.pdf
 */
#line 2 "algorithm/concave_max_plus_convolution.cpp"

#include <cstddef>
#include <vector>

template <class T>
std::vector<T> concave_max_plus_convolution(const std::vector<T> &a,
                                            const std::vector<T> &b) {
  using size_t = std::size_t;

  const size_t n = a.size();
  const size_t m = b.size();
  const auto get = [&](const size_t i, const size_t j) {
    return a[j] + b[i - j];
  };
  const std::vector<size_t> amax =
      smawk(n + m - 1, n, [&](const size_t i, const size_t j, const size_t k) {
        if (i < k)
          return false;
        if (i - j >= m)
          return true;
        return get(i, j) <= get(i, k);
      });
  std::vector<T> c(n + m - 1);
  for (size_t i = 0; i != n + m - 1; i += 1)
    c[i] = get(i, amax[i]);
  return c;
}

/**
 * @brief Concave Max Plus Convlution
 * @see https://arxiv.org/abs/1802.06440
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

