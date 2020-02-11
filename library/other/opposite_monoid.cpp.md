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


# :heavy_check_mark: other/opposite_monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/opposite_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-11 11:45:48+09:00




## Required by

* :heavy_check_mark: <a href="../data_structure/queue_aggregation.cpp.html">data_structure/queue_aggregation.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/queue_aggregation.yosupo.test.cpp.html">test/queue_aggregation.yosupo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class M> class opposite_monoid {
  using T = typename M::value_type;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return M::operation(r, l);
  }
  static constexpr T identity = M::identity;
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/opposite_monoid.cpp"
template <class M> class opposite_monoid {
  using T = typename M::value_type;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return M::operation(r, l);
  }
  static constexpr T identity = M::identity;
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

