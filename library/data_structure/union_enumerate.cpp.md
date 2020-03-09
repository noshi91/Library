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


# :heavy_check_mark: Union Enumerate <small>(data_structure/union_enumerate.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/union_enumerate.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 01:49:05+09:00


* see: <a href="http://noshi91.hatenablog.com/entry/2019/07/19/180606">http://noshi91.hatenablog.com/entry/2019/07/19/180606</a>


## Depends on

* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Required by

* :heavy_check_mark: <a href="../algorithm/three_edge_connected_component_decomposition.cpp.html">algorithm/three_edge_connected_component_decomposition.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/three_edge_connected_component_decomposition.test.cpp.html">test/three_edge_connected_component_decomposition.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

class union_enumerate {
  std::vector<usize> next;

public:
  union_enumerate() = default;
  union_enumerate(const usize size) : next(size) {
    std::iota(next.begin(), next.end(), static_cast<usize>(0));
  }

  usize size() const { return next.size(); }

  std::vector<usize> enumerate(const usize x) const {
    assert(x < size());

    std::vector<usize> ret;
    usize y = x;
    do {
      ret.push_back(y);
      y = next[y];
    } while (y != x);
    return ret;
  }

  std::vector<std::vector<usize>> get_all() const {
    const usize n = size();
    std::vector<std::vector<usize>> res;
    std::vector<bool> visited(n, false);
    for (usize i = 0; i != n; i += 1) {
      if (!visited[i]) {
        const std::vector<usize> list = enumerate(i);
        for (const usize j : list)
          visited[j] = true;
        res.push_back(list);
      }
    }
    return res;
  }

  void unite(const usize x, const usize y) {
    assert(x < size());
    assert(y < size());

    std::swap(next[x], next[y]);
  }
};

/**
 * @brief Union Enumerate
 * @see http://noshi91.hatenablog.com/entry/2019/07/19/180606
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
#line 2 "data_structure/union_enumerate.cpp"

#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

class union_enumerate {
  std::vector<usize> next;

public:
  union_enumerate() = default;
  union_enumerate(const usize size) : next(size) {
    std::iota(next.begin(), next.end(), static_cast<usize>(0));
  }

  usize size() const { return next.size(); }

  std::vector<usize> enumerate(const usize x) const {
    assert(x < size());

    std::vector<usize> ret;
    usize y = x;
    do {
      ret.push_back(y);
      y = next[y];
    } while (y != x);
    return ret;
  }

  std::vector<std::vector<usize>> get_all() const {
    const usize n = size();
    std::vector<std::vector<usize>> res;
    std::vector<bool> visited(n, false);
    for (usize i = 0; i != n; i += 1) {
      if (!visited[i]) {
        const std::vector<usize> list = enumerate(i);
        for (const usize j : list)
          visited[j] = true;
        res.push_back(list);
      }
    }
    return res;
  }

  void unite(const usize x, const usize y) {
    assert(x < size());
    assert(y < size());

    std::swap(next[x], next[y]);
  }
};

/**
 * @brief Union Enumerate
 * @see http://noshi91.hatenablog.com/entry/2019/07/19/180606
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

