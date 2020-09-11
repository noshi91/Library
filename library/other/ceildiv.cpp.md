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


# :heavy_check_mark: other/ceildiv.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/ceildiv.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-11 14:24:32+09:00




## Required by

* :warning: <a href="../algorithm/divisor_mobius_transform.cpp.html">Divisor Möbius Transform <small>(algorithm/divisor_mobius_transform.cpp)</small></a>
* :warning: <a href="../algorithm/multiple_zeta_transform.cpp.html">Multiple Zeta Transform <small>(algorithm/multiple_zeta_transform.cpp)</small></a>
* :heavy_check_mark: <a href="../data_structure/w_ary_tree_set.cpp.html">w-ary Tree Set <small>(data_structure/w_ary_tree_set.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/w_ary_tree_set.test.cpp.html">test/w_ary_tree_set.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class T> constexpr T ceildiv(const T &n, const T &d) {
  return n / d + (n % d != 0 ? 1 : 0);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/ceildiv.cpp"
template <class T> constexpr T ceildiv(const T &n, const T &d) {
  return n / d + (n % d != 0 ? 1 : 0);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

