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


# :warning: data_structure/range_mode_query.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/range_mode_query.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-06 19:39:55+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
reference: https://arxiv.org/abs/1101.4068
*/

#include <cassert>
#include <cstddef>
#include <vector>

class range_mode_query {
  using size_t = std::size_t;

  class b_node {
  public:
    size_t value;
    size_t rank;

    b_node(const size_t value, const size_t rank) : value(value), rank(rank) {}
  };
  class s_node {
  public:
    size_t mode;
    size_t freq;

    s_node(const size_t mode, const size_t freq) : mode(mode), freq(freq) {}
  };

  std::vector<b_node> b;
  std::vector<std::vector<size_t>> q;
  std::vector<std::vector<s_node>> s;
  size_t t;

public:
  range_mode_query() = default;
  range_mode_query(const std::vector<size_t> a) : t(1) {
    const size_t n = a.size();
    b.assign(n, b_node(0, 0));
    q.assign(n, {});
    while (t * t < n)
      t += 1;
    for (size_t i = 0; i != n; i += 1) {
      const size_t e = a[i];
      assert(e < n);
      b[i] = b_node(e, q[e].size());
      q[e].push_back(i);
    }
    s.assign(n / t + 1, std::vector<s_node>(n / t + 1, s_node(0, 0)));
    for (size_t f = 0; f * t <= n; f += 1) {
      std::vector<size_t> freq(n, 0);
      s_node cur(0, 0);
      for (size_t l = f + 1; l * t <= n; l += 1) {
        for (size_t i = (l - 1) * t; i != l * t; i += 1) {
          const size_t e = a[i];
          freq[e] += 1;
          if (freq[e] > cur.freq)
            cur = s_node(e, freq[e]);
        }
        s[f][l] = cur;
      }
    }
  }

  size_t query(const size_t first, const size_t last) const {
    assert(first < last);
    assert(last <= b.size());
    size_t bf = first / t + 1;
    size_t bl = last / t;
    if (bf >= bl) {
      s_node cur(0, 0);
      for (size_t i = first; i != last; i += 1) {
        const b_node &e = b[i];
        const std::vector<size_t> &v = q[e.value];
        size_t idx;
        while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
          cur = s_node(e.value, cur.freq + 1);
      }
      return cur.mode;
    }
    s_node cur = s[bf][bl];
    for (size_t i = first; i != bf * t; i += 1) {
      const b_node &e = b[i];
      const std::vector<size_t> &v = q[e.value];
      size_t idx;
      while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
        cur = s_node(e.value, cur.freq + 1);
    }
    for (size_t i = bl * t; i != last; i += 1) {
      const b_node &e = b[i];
      const std::vector<size_t> &v = q[e.value];
      size_t idx;
      while ((idx = e.rank - cur.freq) < v.size() && v[idx] >= first)
        cur = s_node(e.value, cur.freq + 1);
    }
    return cur.mode;
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/range_mode_query.cpp"
/*
reference: https://arxiv.org/abs/1101.4068
*/

#include <cassert>
#include <cstddef>
#include <vector>

class range_mode_query {
  using size_t = std::size_t;

  class b_node {
  public:
    size_t value;
    size_t rank;

    b_node(const size_t value, const size_t rank) : value(value), rank(rank) {}
  };
  class s_node {
  public:
    size_t mode;
    size_t freq;

    s_node(const size_t mode, const size_t freq) : mode(mode), freq(freq) {}
  };

  std::vector<b_node> b;
  std::vector<std::vector<size_t>> q;
  std::vector<std::vector<s_node>> s;
  size_t t;

public:
  range_mode_query() = default;
  range_mode_query(const std::vector<size_t> a) : t(1) {
    const size_t n = a.size();
    b.assign(n, b_node(0, 0));
    q.assign(n, {});
    while (t * t < n)
      t += 1;
    for (size_t i = 0; i != n; i += 1) {
      const size_t e = a[i];
      assert(e < n);
      b[i] = b_node(e, q[e].size());
      q[e].push_back(i);
    }
    s.assign(n / t + 1, std::vector<s_node>(n / t + 1, s_node(0, 0)));
    for (size_t f = 0; f * t <= n; f += 1) {
      std::vector<size_t> freq(n, 0);
      s_node cur(0, 0);
      for (size_t l = f + 1; l * t <= n; l += 1) {
        for (size_t i = (l - 1) * t; i != l * t; i += 1) {
          const size_t e = a[i];
          freq[e] += 1;
          if (freq[e] > cur.freq)
            cur = s_node(e, freq[e]);
        }
        s[f][l] = cur;
      }
    }
  }

  size_t query(const size_t first, const size_t last) const {
    assert(first < last);
    assert(last <= b.size());
    size_t bf = first / t + 1;
    size_t bl = last / t;
    if (bf >= bl) {
      s_node cur(0, 0);
      for (size_t i = first; i != last; i += 1) {
        const b_node &e = b[i];
        const std::vector<size_t> &v = q[e.value];
        size_t idx;
        while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
          cur = s_node(e.value, cur.freq + 1);
      }
      return cur.mode;
    }
    s_node cur = s[bf][bl];
    for (size_t i = first; i != bf * t; i += 1) {
      const b_node &e = b[i];
      const std::vector<size_t> &v = q[e.value];
      size_t idx;
      while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
        cur = s_node(e.value, cur.freq + 1);
    }
    for (size_t i = bl * t; i != last; i += 1) {
      const b_node &e = b[i];
      const std::vector<size_t> &v = q[e.value];
      size_t idx;
      while ((idx = e.rank - cur.freq) < v.size() && v[idx] >= first)
        cur = s_node(e.value, cur.freq + 1);
    }
    return cur.mode;
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

