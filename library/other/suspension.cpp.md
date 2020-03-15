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


# :warning: other/suspension.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/suspension.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-15 17:56:22+09:00




## Required by

* :warning: <a href="../data_structure/realtime_queue.cpp.html">data_structure/realtime_queue.cpp</a>
* :warning: <a href="../data_structure/stream.cpp.html">data_structure/stream.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <functional>
#include <memory>
#include <utility>
#include <variant>

template <class T>
class suspension
    : private std::shared_ptr<std::variant<T, std::function<T()>>> {
public:
  using value_type = T;

  using func_type = std::function<T()>;

  using node_type = std::variant<T, func_type>;

private:
  using base_type = std::shared_ptr<node_type>;

  static T get(node_type &x) {
    if (x.index() != 0)
      x = std::get<1>(x)();
    return std::get<0>(x);
  }

  template <class... Args> static base_type make_node(Args &&... args) {
    return std::make_shared<node_type>(std::forward<Args>(args)...);
  }

public:
  suspension(std::in_place_t, T x)
      : base_type(make_node(std::in_place_index<0>, x)) {}

  suspension(func_type f) : base_type(make_node(std::in_place_index<1>, f)) {}

  T force() const { return get(**this); }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/suspension.cpp"
#include <functional>
#include <memory>
#include <utility>
#include <variant>

template <class T>
class suspension
    : private std::shared_ptr<std::variant<T, std::function<T()>>> {
public:
  using value_type = T;

  using func_type = std::function<T()>;

  using node_type = std::variant<T, func_type>;

private:
  using base_type = std::shared_ptr<node_type>;

  static T get(node_type &x) {
    if (x.index() != 0)
      x = std::get<1>(x)();
    return std::get<0>(x);
  }

  template <class... Args> static base_type make_node(Args &&... args) {
    return std::make_shared<node_type>(std::forward<Args>(args)...);
  }

public:
  suspension(std::in_place_t, T x)
      : base_type(make_node(std::in_place_index<0>, x)) {}

  suspension(func_type f) : base_type(make_node(std::in_place_index<1>, f)) {}

  T force() const { return get(**this); }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

