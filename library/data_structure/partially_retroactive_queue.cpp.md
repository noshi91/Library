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


# :warning: data_structure/partially_retroactive_queue.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/partially_retroactive_queue.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-17 00:25:31+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <iterator>
#include <list>

template <class T> class partially_retroactive_queue {
  class node_type;

public:
  using time_type = typename std::list<node_type>::const_iterator;

private:
  class node_type {
    friend partially_retroactive_queue;

    T value;
    bool in_queue;
    node_type(const T value) : value(value), in_queue() {}
  };

  std::list<node_type> list;
  typename std::list<node_type>::iterator front_itr;

public:
  partially_retroactive_queue() : list(), front_itr(list.end()) {}

  time_type now() const { return list.cend(); }

  bool empty() const { return front_itr == list.end(); }

  T front() const {
    assert(!empty());
    return front_itr->value;
  }

  time_type insert_push(const time_type time, const T x) {
    const auto itr = list.insert(time, node_type(x));
    if (itr == list.begin() || !std::prev(itr)->in_queue) {
      itr->in_queue = false;
      --front_itr;
      front_itr->in_queue = true;
    } else {
      itr->in_queue = true;
    }
    return time_type(itr);
  }
  void erase_push(const time_type time) {
    assert(time != now());
    if (time == list.cbegin() || !std::prev(time)->in_queue) {
      front_itr->in_queue = false;
      ++front_itr;
    }
    list.erase(time);
  }
  void insert_pop() {
    assert(!empty());
    front_itr->in_queue = false;
    ++front_itr;
  }
  void erase_pop() {
    assert(front_itr != list.begin());
    --front_itr;
    front_itr->in_queue = true;
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/partially_retroactive_queue.cpp"
#include <cassert>
#include <iterator>
#include <list>

template <class T> class partially_retroactive_queue {
  class node_type;

public:
  using time_type = typename std::list<node_type>::const_iterator;

private:
  class node_type {
    friend partially_retroactive_queue;

    T value;
    bool in_queue;
    node_type(const T value) : value(value), in_queue() {}
  };

  std::list<node_type> list;
  typename std::list<node_type>::iterator front_itr;

public:
  partially_retroactive_queue() : list(), front_itr(list.end()) {}

  time_type now() const { return list.cend(); }

  bool empty() const { return front_itr == list.end(); }

  T front() const {
    assert(!empty());
    return front_itr->value;
  }

  time_type insert_push(const time_type time, const T x) {
    const auto itr = list.insert(time, node_type(x));
    if (itr == list.begin() || !std::prev(itr)->in_queue) {
      itr->in_queue = false;
      --front_itr;
      front_itr->in_queue = true;
    } else {
      itr->in_queue = true;
    }
    return time_type(itr);
  }
  void erase_push(const time_type time) {
    assert(time != now());
    if (time == list.cbegin() || !std::prev(time)->in_queue) {
      front_itr->in_queue = false;
      ++front_itr;
    }
    list.erase(time);
  }
  void insert_pop() {
    assert(!empty());
    front_itr->in_queue = false;
    ++front_itr;
  }
  void erase_pop() {
    assert(front_itr != list.begin());
    --front_itr;
    front_itr->in_queue = true;
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

