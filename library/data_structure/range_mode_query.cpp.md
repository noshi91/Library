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


# :warning: Range Mode Query <small>(data_structure/range_mode_query.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/range_mode_query.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:58:19+09:00


* see: <a href="https://scrapbox.io/data-structures/Range_Mode_Query">https://scrapbox.io/data-structures/Range_Mode_Query</a>


## Depends on

* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <vector>

class range_mode_query {
  class b_node {
  public:
    usize value;
    usize rank;

    b_node(const usize value, const usize rank) : value(value), rank(rank) {}
  };

  class s_node {
  public:
    usize mode;
    usize freq;

    s_node(const usize mode, const usize freq) : mode(mode), freq(freq) {}
  };

  std::vector<b_node> b;
  std::vector<std::vector<usize>> q;
  std::vector<std::vector<s_node>> s;
  usize t;

public:
  range_mode_query() = default;

  range_mode_query(const std::vector<usize> a) : t(1) {
    const usize n = a.size();
    b.assign(n, b_node(0, 0));
    q.assign(n, {});
    while (t * t < n)
      t += 1;
    for (usize i = 0; i != n; i += 1) {
      const usize e = a[i];
      assert(e < n);
      b[i] = b_node(e, q[e].size());
      q[e].push_back(i);
    }
    s.assign(n / t + 1, std::vector<s_node>(n / t + 1, s_node(0, 0)));
    for (usize f = 0; f * t <= n; f += 1) {
      std::vector<usize> freq(n, 0);
      s_node cur(0, 0);
      for (usize l = f + 1; l * t <= n; l += 1) {
        for (usize i = (l - 1) * t; i != l * t; i += 1) {
          const usize e = a[i];
          freq[e] += 1;
          if (freq[e] > cur.freq)
            cur = s_node(e, freq[e]);
        }
        s[f][l] = cur;
      }
    }
  }

  usize query(const usize first, const usize last) const {
    assert(first < last);
    assert(last <= b.size());
    usize bf = first / t + 1;
    usize bl = last / t;
    if (bf >= bl) {
      s_node cur(0, 0);
      for (usize i = first; i != last; i += 1) {
        const b_node &e = b[i];
        const std::vector<usize> &v = q[e.value];
        usize idx;
        while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
          cur = s_node(e.value, cur.freq + 1);
      }
      return cur.mode;
    }
    s_node cur = s[bf][bl];
    for (usize i = first; i != bf * t; i += 1) {
      const b_node &e = b[i];
      const std::vector<usize> &v = q[e.value];
      usize idx;
      while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
        cur = s_node(e.value, cur.freq + 1);
    }
    for (usize i = bl * t; i != last; i += 1) {
      const b_node &e = b[i];
      const std::vector<usize> &v = q[e.value];
      usize idx;
      while ((idx = e.rank - cur.freq) < v.size() && v[idx] >= first)
        cur = s_node(e.value, cur.freq + 1);
    }
    return cur.mode;
  }
};

/**
 * @brief Range Mode Query
 * @see https://scrapbox.io/data-structures/Range_Mode_Query
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
#line 2 "data_structure/range_mode_query.cpp"

#include <cassert>
#line 5 "data_structure/range_mode_query.cpp"
#include <vector>

class range_mode_query {
  class b_node {
  public:
    usize value;
    usize rank;

    b_node(const usize value, const usize rank) : value(value), rank(rank) {}
  };

  class s_node {
  public:
    usize mode;
    usize freq;

    s_node(const usize mode, const usize freq) : mode(mode), freq(freq) {}
  };

  std::vector<b_node> b;
  std::vector<std::vector<usize>> q;
  std::vector<std::vector<s_node>> s;
  usize t;

public:
  range_mode_query() = default;

  range_mode_query(const std::vector<usize> a) : t(1) {
    const usize n = a.size();
    b.assign(n, b_node(0, 0));
    q.assign(n, {});
    while (t * t < n)
      t += 1;
    for (usize i = 0; i != n; i += 1) {
      const usize e = a[i];
      assert(e < n);
      b[i] = b_node(e, q[e].size());
      q[e].push_back(i);
    }
    s.assign(n / t + 1, std::vector<s_node>(n / t + 1, s_node(0, 0)));
    for (usize f = 0; f * t <= n; f += 1) {
      std::vector<usize> freq(n, 0);
      s_node cur(0, 0);
      for (usize l = f + 1; l * t <= n; l += 1) {
        for (usize i = (l - 1) * t; i != l * t; i += 1) {
          const usize e = a[i];
          freq[e] += 1;
          if (freq[e] > cur.freq)
            cur = s_node(e, freq[e]);
        }
        s[f][l] = cur;
      }
    }
  }

  usize query(const usize first, const usize last) const {
    assert(first < last);
    assert(last <= b.size());
    usize bf = first / t + 1;
    usize bl = last / t;
    if (bf >= bl) {
      s_node cur(0, 0);
      for (usize i = first; i != last; i += 1) {
        const b_node &e = b[i];
        const std::vector<usize> &v = q[e.value];
        usize idx;
        while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
          cur = s_node(e.value, cur.freq + 1);
      }
      return cur.mode;
    }
    s_node cur = s[bf][bl];
    for (usize i = first; i != bf * t; i += 1) {
      const b_node &e = b[i];
      const std::vector<usize> &v = q[e.value];
      usize idx;
      while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
        cur = s_node(e.value, cur.freq + 1);
    }
    for (usize i = bl * t; i != last; i += 1) {
      const b_node &e = b[i];
      const std::vector<usize> &v = q[e.value];
      usize idx;
      while ((idx = e.rank - cur.freq) < v.size() && v[idx] >= first)
        cur = s_node(e.value, cur.freq + 1);
    }
    return cur.mode;
  }
};

/**
 * @brief Range Mode Query
 * @see https://scrapbox.io/data-structures/Range_Mode_Query
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

