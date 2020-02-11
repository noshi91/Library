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
    - Last commit date: 2020-02-11 11:45:48+09:00




## Depends on

* :heavy_check_mark: <a href="stack_aggregation.cpp.html">data_structure/stack_aggregation.cpp</a>
* :heavy_check_mark: <a href="../other/opposite_monoid.cpp.html">other/opposite_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/queue_aggregation.yosupo.test.cpp.html">test/queue_aggregation.yosupo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "data_structure/stack_aggregation.cpp"
#include "other/opposite_monoid.cpp"

template <class M> class queue_aggregation {
  using T = typename M::value_type;

  stack_aggregation<opposite_monoid<M>> front_st;
  stack_aggregation<M> back_st;

public:
  queue_aggregation() = default;

  bool empty() const { return front_st.empty(); }
  T fold() const { return M::operation(front_st.fold(), back_st.fold()); }

  void push(const T x) {
    if (empty())
      front_st.push(x);
    else
      back_st.push(x);
  }
  void pop() {
    assert(!empty());
    front_st.pop();
    if (front_st.empty()) {
      while (!back_st.empty()) {
        front_st.push(back_st.top());
        back_st.pop();
      }
    }
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/stack_aggregation.cpp"
#include <cassert>
#include <stack>

template <class M> class stack_aggregation {
  using T = typename M::value_type;

  class node_type {
  public:
    T value;
    T fold;

    node_type(const T value, const T fold) : value(value), fold(fold) {}
  };

  std::stack<node_type> st;

public:
  stack_aggregation() = default;

  bool empty() const { return st.empty(); }
  T top() const {
    assert(!empty());
    return st.top().value;
  }
  T fold() const { return st.empty() ? M::identity : st.top().fold; }

  void push(const T x) { st.push(node_type(x, M::operation(fold(), x))); }
  void pop() {
    assert(!empty());
    st.pop();
  }
};
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
#line 3 "data_structure/queue_aggregation.cpp"

template <class M> class queue_aggregation {
  using T = typename M::value_type;

  stack_aggregation<opposite_monoid<M>> front_st;
  stack_aggregation<M> back_st;

public:
  queue_aggregation() = default;

  bool empty() const { return front_st.empty(); }
  T fold() const { return M::operation(front_st.fold(), back_st.fold()); }

  void push(const T x) {
    if (empty())
      front_st.push(x);
    else
      back_st.push(x);
  }
  void pop() {
    assert(!empty());
    front_st.pop();
    if (front_st.empty()) {
      while (!back_st.empty()) {
        front_st.push(back_st.top());
        back_st.pop();
      }
    }
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

