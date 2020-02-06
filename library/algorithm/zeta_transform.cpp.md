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


# :warning: algorithm/zeta_transform.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/zeta_transform.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-30 01:00:01+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cstddef>
#include <vector>

template <class S>
void subset_zeta_transform(std::vector<typename S::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  for (size_t i = 1; i < n; i *= 2) {
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j] = S::operation(a[j & ~i], a[j]);
    }
  }
}

template <class S>
void superset_zeta_transform(std::vector<typename S::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  for (size_t i = 1; i < n; i *= 2) {
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j & ~i] = S::operation(a[j & ~i], a[j]);
    }
  }
}

template <class G>
void subset_mobius_transform(std::vector<typename G::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  size_t i = 1;
  while (i < n)
    i *= 2;
  while (i != 1) {
    i /= 2;
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j] = G::operation(G::inverse(a[j & ~i]), a[j]);
    }
  }
}

template <class G>
void superset_mobius_transform(std::vector<typename G::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  size_t i = 1;
  while (i < n)
    i *= 2;
  while (i != 1) {
    i /= 2;
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j & ~i] = G::operation(a[j & ~i], G::inverse(a[j]));
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/zeta_transform.cpp"
#include <cstddef>
#include <vector>

template <class S>
void subset_zeta_transform(std::vector<typename S::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  for (size_t i = 1; i < n; i *= 2) {
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j] = S::operation(a[j & ~i], a[j]);
    }
  }
}

template <class S>
void superset_zeta_transform(std::vector<typename S::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  for (size_t i = 1; i < n; i *= 2) {
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j & ~i] = S::operation(a[j & ~i], a[j]);
    }
  }
}

template <class G>
void subset_mobius_transform(std::vector<typename G::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  size_t i = 1;
  while (i < n)
    i *= 2;
  while (i != 1) {
    i /= 2;
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j] = G::operation(G::inverse(a[j & ~i]), a[j]);
    }
  }
}

template <class G>
void superset_mobius_transform(std::vector<typename G::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  size_t i = 1;
  while (i < n)
    i *= 2;
  while (i != 1) {
    i /= 2;
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j & ~i] = G::operation(a[j & ~i], G::inverse(a[j]));
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

