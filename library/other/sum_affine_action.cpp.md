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


# :heavy_check_mark: other/sum_affine_action.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/sum_affine_action.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-14 17:46:13+09:00




## Depends on

* :heavy_check_mark: <a href="affine.cpp.html">other/affine.cpp</a>
* :heavy_check_mark: <a href="cartesian_product_monoid.cpp.html">other/cartesian_product_monoid.cpp</a>
* :heavy_check_mark: <a href="plus_monoid.cpp.html">other/plus_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/lazy_segment_tree.yosupo.test.cpp.html">test/lazy_segment_tree.yosupo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/affine.cpp"
#include "other/cartesian_product_monoid.cpp"
#include "other/plus_monoid.cpp"

template <class T> class sum_affine_action {
public:
  using value_structure =
      cartesian_product_monoid<plus_monoid<T>, plus_monoid<T>>;
  using operator_structure = affine_composite_monoid<T>;

private:
  using U = typename value_structure::value_type;
  using E = typename operator_structure::value_type;

public:
  static constexpr U operation(const U &l, const E &r) {
    return U(l.first * r.a + l.second * r.b, l.second);
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/affine.cpp"
template <class T> class affine {
public:
  T a;
  T b;

  constexpr affine(const T &a = 1, const T &b = 0) noexcept : a(a), b(b) {}

  constexpr T evaluate(const T &x) const noexcept { return x * a + b; }
  friend constexpr affine operator+(const affine &l, const affine &r) noexcept {
    return affine(l.a + r.a, l.b + r.b);
  }
  constexpr affine composite(const affine &r) const noexcept {
    return affine(a * r.a, b * r.a + r.b);
  }
};

template <class T> class affine_composite_monoid {
public:
  using value_type = affine<T>;
  static constexpr value_type operation(const value_type &l,
                                        const value_type &r) noexcept {
    return l.composite(r);
  }
  static constexpr value_type identity{};
};
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
#line 1 "other/plus_monoid.cpp"
template <class T> class plus_monoid {
public:
  using value_type = T;
  static T operation(const T l, const T r) { return l + r; }
  static constexpr T identity = 0;
};
#line 4 "other/sum_affine_action.cpp"

template <class T> class sum_affine_action {
public:
  using value_structure =
      cartesian_product_monoid<plus_monoid<T>, plus_monoid<T>>;
  using operator_structure = affine_composite_monoid<T>;

private:
  using U = typename value_structure::value_type;
  using E = typename operator_structure::value_type;

public:
  static constexpr U operation(const U &l, const E &r) {
    return U(l.first * r.a + l.second * r.b, l.second);
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

