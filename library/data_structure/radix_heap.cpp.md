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


# :heavy_check_mark: data_structure/radix_heap.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/radix_heap.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-22 20:51:34+09:00




## Depends on

* :heavy_check_mark: <a href="../other/countl_zero64.cpp.html">other/countl_zero64.cpp</a>
* :heavy_check_mark: <a href="../other/log2p164.cpp.html">other/log2p164.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/radix_heap.aoj.test.cpp.html">test/radix_heap.aoj.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/log2p164.cpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

template <class T> class radix_heap {
  using size_t = std::size_t;
  using u64 = std::uint_fast64_t;
  using V = std::pair<u64, T>;

public:
  using key_type = u64;
  using mapped_type = T;
  using value_type = V;

private:
  std::vector<std::vector<V>> u;
  u64 last;

public:
  radix_heap() : u(), last(0) {}

  void push(const V x) {
    assert(last <= x.first);

    const size_t i = log2p164(x.first ^ last);
    if (u.size() <= i)
      u.resize(i + 1);
    u[i].push_back(x);
  }
  V pop() {
    if (u[0].empty()) {
      size_t i = 1;
      while (u[i].empty())
        i += 1;
      last = std::numeric_limits<u64>::max();
      for (const V &e : u[i])
        last = std::min(last, e.first);
      for (const V &e : u[i])
        u[log2p164(e.first ^ last)].push_back(e);
      u[i].clear();
    }
    V ret = u[0].back();
    u[0].pop_back();
    return ret;
  }
};
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
#line 2 "other/log2p164.cpp"

#include <cstddef>
#include <cstdint>

std::size_t log2p164(const std::uint_fast64_t x) {
  return 64 - countl_zero64(x);
}
#line 2 "data_structure/radix_heap.cpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

template <class T> class radix_heap {
  using size_t = std::size_t;
  using u64 = std::uint_fast64_t;
  using V = std::pair<u64, T>;

public:
  using key_type = u64;
  using mapped_type = T;
  using value_type = V;

private:
  std::vector<std::vector<V>> u;
  u64 last;

public:
  radix_heap() : u(), last(0) {}

  void push(const V x) {
    assert(last <= x.first);

    const size_t i = log2p164(x.first ^ last);
    if (u.size() <= i)
      u.resize(i + 1);
    u[i].push_back(x);
  }
  V pop() {
    if (u[0].empty()) {
      size_t i = 1;
      while (u[i].empty())
        i += 1;
      last = std::numeric_limits<u64>::max();
      for (const V &e : u[i])
        last = std::min(last, e.first);
      for (const V &e : u[i])
        u[log2p164(e.first ^ last)].push_back(e);
      u[i].clear();
    }
    V ret = u[0].back();
    u[0].pop_back();
    return ret;
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

