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


# :heavy_check_mark: data_structure/queue_aggregation.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/queue_aggregation.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-18 14:50:00+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/data_structure/queue_aggregation.yosupo.test.cpp.html">data_structure/queue_aggregation.yosupo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*

アルゴリズムの一部は https://twitter.com/259_Momone/status/1199559095243530240
に影響を受けたものです

*/

#include <cassert>
#include <stack>

template <class Monoid> class queue_aggregation {
public:
  using T = typename Monoid::value_type;

private:
  std::stack<T> front_stack;
  std::stack<T> back_stack;
  T fold_back;

  T fold_front() const {
    if (!front_stack.empty()) {
      return front_stack.top();
    } else {
      return Monoid::identity;
    }
  }

public:
  queue_aggregation()
      : front_stack(), back_stack(), fold_back(Monoid::identity) {}

  bool empty() const { return front_stack.empty() && back_stack.empty(); }

  T fold_all() const { return Monoid::operation(fold_front(), fold_back); }

  void push(const T x) {
    fold_back = Monoid::operation(fold_back, x);
    back_stack.push(x);
  }
  void pop() {
    assert(!empty());
    if (front_stack.empty()) {
      while (!back_stack.empty()) {
        front_stack.push(Monoid::operation(back_stack.top(), fold_front()));
        back_stack.pop();
      }
      fold_back = Monoid::identity;
    }
    front_stack.pop();
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/queue_aggregation.cpp"
/*

アルゴリズムの一部は https://twitter.com/259_Momone/status/1199559095243530240
に影響を受けたものです

*/

#include <cassert>
#include <stack>

template <class Monoid> class queue_aggregation {
public:
  using T = typename Monoid::value_type;

private:
  std::stack<T> front_stack;
  std::stack<T> back_stack;
  T fold_back;

  T fold_front() const {
    if (!front_stack.empty()) {
      return front_stack.top();
    } else {
      return Monoid::identity;
    }
  }

public:
  queue_aggregation()
      : front_stack(), back_stack(), fold_back(Monoid::identity) {}

  bool empty() const { return front_stack.empty() && back_stack.empty(); }

  T fold_all() const { return Monoid::operation(fold_front(), fold_back); }

  void push(const T x) {
    fold_back = Monoid::operation(fold_back, x);
    back_stack.push(x);
  }
  void pop() {
    assert(!empty());
    if (front_stack.empty()) {
      while (!back_stack.empty()) {
        front_stack.push(Monoid::operation(back_stack.top(), fold_front()));
        back_stack.pop();
      }
      fold_back = Monoid::identity;
    }
    front_stack.pop();
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

