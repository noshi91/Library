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


# :warning: Xor Linked List <small>(data_structure/xor_linked_list.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/xor_linked_list.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:42:07+09:00


* see: <a href="https://en.wikipedia.org/wiki/XOR_linked_list">https://en.wikipedia.org/wiki/XOR_linked_list</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <cstdint>
#include <utility>

template <class T> class xor_linked_list {
public:
  using value_type = T;

private:
  class node_type {
  public:
    T value;
    std::uintptr_t link;

    node_type(T value, const std::uintptr_t link)
        : value(std::move(value)), link(link) {}
  };

  static std::uintptr_t ptoi(node_type *const ptr) {
    return reinterpret_cast<std::uintptr_t>(ptr);
  }

  static node_type *itop(const std::uintptr_t id) {
    return reinterpret_cast<node_type *>(id);
  }

  node_type *front_;
  node_type *back_;

  void release() {
    front_ = nullptr;
    back_ = nullptr;
  }

public:
  xor_linked_list() : front_(nullptr), back_(nullptr) {}

  xor_linked_list(const xor_linked_list &) = delete;

  xor_linked_list(xor_linked_list &&r) noexcept
      : front_(r.front_), back_(r.back_) {
    r.release();
  }

  ~xor_linked_list() { clear(); }

  xor_linked_list &operator=(const xor_linked_list &) = delete;

  xor_linked_list &operator=(xor_linked_list &&r) noexcept {
    front_ = r.front_;
    back_ = r.back_;
    r.release();
    return *this;
  }

  bool empty() const { return front_ == nullptr; }

  T &front() {
    assert(!empty());

    return front_->value;
  }

  T &back() {
    assert(!empty());

    return back_->value;
  }

  void push_back(T x) {
    if (empty()) {
      node_type *const next = new node_type(std::move(x), 0);
      front_ = next;
      back_ = next;
    } else {
      node_type *const next = new node_type(std::move(x), ptoi(back_));
      back_->link ^= ptoi(next);
      back_ = next;
    }
  }

  void pop_back() {
    assert(!empty());

    if (front_ == back_) {
      delete front_;
      front_ = nullptr;
      back_ = nullptr;
    } else {
      node_type *const next = itop(back_->link);
      next->link ^= ptoi(back_);
      delete back_;
      back_ = next;
    }
  }

  void push_front(T x) {
    reverse();
    push_back(std::move(x));
    reverse();
  }

  void pop_front() {
    assert(!empty());

    reverse();
    pop_back();
    reverse();
  }

  void clear() {
    if (empty())
      return;
    node_type *itr = front_;
    std::uintptr_t prev = 0;
    while (itr != back_) {
      node_type *const next = itop(itr->link ^ prev);
      prev = ptoi(itr);
      delete itr;
      itr = next;
    }
    delete itr;
    release();
  }

  void reverse() { std::swap(front_, back_); }

  static xor_linked_list catenate(xor_linked_list left, xor_linked_list right) {
    if (left.empty())
      return right;
    if (right.empty())
      return left;
    left.back_->link ^= ptoi(right.front_);
    right.front_->link ^= ptoi(left.back_);
    xor_linked_list ret;
    ret.front_ = left.front_;
    ret.back_ = right.back_;
    left.release();
    right.release();
    return ret;
  }
};

/**
 * @brief Xor Linked List
 * @see https://en.wikipedia.org/wiki/XOR_linked_list
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/xor_linked_list.cpp"
#include <cassert>
#include <cstdint>
#include <utility>

template <class T> class xor_linked_list {
public:
  using value_type = T;

private:
  class node_type {
  public:
    T value;
    std::uintptr_t link;

    node_type(T value, const std::uintptr_t link)
        : value(std::move(value)), link(link) {}
  };

  static std::uintptr_t ptoi(node_type *const ptr) {
    return reinterpret_cast<std::uintptr_t>(ptr);
  }

  static node_type *itop(const std::uintptr_t id) {
    return reinterpret_cast<node_type *>(id);
  }

  node_type *front_;
  node_type *back_;

  void release() {
    front_ = nullptr;
    back_ = nullptr;
  }

public:
  xor_linked_list() : front_(nullptr), back_(nullptr) {}

  xor_linked_list(const xor_linked_list &) = delete;

  xor_linked_list(xor_linked_list &&r) noexcept
      : front_(r.front_), back_(r.back_) {
    r.release();
  }

  ~xor_linked_list() { clear(); }

  xor_linked_list &operator=(const xor_linked_list &) = delete;

  xor_linked_list &operator=(xor_linked_list &&r) noexcept {
    front_ = r.front_;
    back_ = r.back_;
    r.release();
    return *this;
  }

  bool empty() const { return front_ == nullptr; }

  T &front() {
    assert(!empty());

    return front_->value;
  }

  T &back() {
    assert(!empty());

    return back_->value;
  }

  void push_back(T x) {
    if (empty()) {
      node_type *const next = new node_type(std::move(x), 0);
      front_ = next;
      back_ = next;
    } else {
      node_type *const next = new node_type(std::move(x), ptoi(back_));
      back_->link ^= ptoi(next);
      back_ = next;
    }
  }

  void pop_back() {
    assert(!empty());

    if (front_ == back_) {
      delete front_;
      front_ = nullptr;
      back_ = nullptr;
    } else {
      node_type *const next = itop(back_->link);
      next->link ^= ptoi(back_);
      delete back_;
      back_ = next;
    }
  }

  void push_front(T x) {
    reverse();
    push_back(std::move(x));
    reverse();
  }

  void pop_front() {
    assert(!empty());

    reverse();
    pop_back();
    reverse();
  }

  void clear() {
    if (empty())
      return;
    node_type *itr = front_;
    std::uintptr_t prev = 0;
    while (itr != back_) {
      node_type *const next = itop(itr->link ^ prev);
      prev = ptoi(itr);
      delete itr;
      itr = next;
    }
    delete itr;
    release();
  }

  void reverse() { std::swap(front_, back_); }

  static xor_linked_list catenate(xor_linked_list left, xor_linked_list right) {
    if (left.empty())
      return right;
    if (right.empty())
      return left;
    left.back_->link ^= ptoi(right.front_);
    right.front_->link ^= ptoi(left.back_);
    xor_linked_list ret;
    ret.front_ = left.front_;
    ret.back_ = right.back_;
    left.release();
    right.release();
    return ret;
  }
};

/**
 * @brief Xor Linked List
 * @see https://en.wikipedia.org/wiki/XOR_linked_list
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

