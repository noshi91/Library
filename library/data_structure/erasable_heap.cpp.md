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


# :heavy_check_mark: data_structure/erasable_heap.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/erasable_heap.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-16 01:11:55+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/erasable_heap.aoj.test.cpp.html">test/erasable_heap.aoj.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>

template <class Heap> class erasable_heap {
  using W = typename Heap::value_compare;
  using T = typename W::value_type;

public:
  using value_compare = W;

private:
  static bool equivalent(const T x, const T y) {
    return W::compare(x, y) && W::compare(y, x);
  }

  Heap base;
  Heap erased;

  void normalize() {
    while (!base.empty() && !erased.empty() &&
           equivalent(base.top(), erased.top())) {
      base.pop();
      erased.pop();
    }
  }

public:
  erasable_heap() = default;

  bool empty() const { return base.empty(); }

  T top() const {
    assert(!empty());
    return base.top();
  }

  void push(const T x) {
    base.push(x);
    normalize();
  }
  void pop() {
    assert(!empty());
    base.pop();
    normalize();
  }
  void erase(const T x) {
    erased.push(x);
    normalize();
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/erasable_heap.cpp"
#include <cassert>

template <class Heap> class erasable_heap {
  using W = typename Heap::value_compare;
  using T = typename W::value_type;

public:
  using value_compare = W;

private:
  static bool equivalent(const T x, const T y) {
    return W::compare(x, y) && W::compare(y, x);
  }

  Heap base;
  Heap erased;

  void normalize() {
    while (!base.empty() && !erased.empty() &&
           equivalent(base.top(), erased.top())) {
      base.pop();
      erased.pop();
    }
  }

public:
  erasable_heap() = default;

  bool empty() const { return base.empty(); }

  T top() const {
    assert(!empty());
    return base.top();
  }

  void push(const T x) {
    base.push(x);
    normalize();
  }
  void pop() {
    assert(!empty());
    base.pop();
    normalize();
  }
  void erase(const T x) {
    erased.push(x);
    normalize();
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

