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


# :heavy_check_mark: other/cartesian_product_monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/cartesian_product_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-14 17:46:13+09:00




## Required by

* :heavy_check_mark: <a href="sum_affine_action.cpp.html">other/sum_affine_action.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/lazy_segment_tree.yosupo.test.cpp.html">test/lazy_segment_tree.yosupo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <utility>

template <class M, class N> class cartesian_product_monoid {
  using T = std::pair<typename M::value_type, typename N::value_type>;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return T(M::operation(l.first, r.first), N::operation(l.second, r.second));
  }
  static constexpr T identity{M::identity, N::identity};
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/cartesian_product_monoid.cpp"
#include <utility>

template <class M, class N> class cartesian_product_monoid {
  using T = std::pair<typename M::value_type, typename N::value_type>;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return T(M::operation(l.first, r.first), N::operation(l.second, r.second));
  }
  static constexpr T identity{M::identity, N::identity};
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

