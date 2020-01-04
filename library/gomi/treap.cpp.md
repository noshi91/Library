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


# :warning: gomi/treap.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c25e426f9a94f83968c77e7d5480c159">gomi</a>
* <a href="{{ site.github.repository_url }}/blob/master/gomi/treap.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-11 20:43:35+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>

template <class T> class treap {
public:
  using size_type = std::size_t;

private:
  using u64 = std::uint64_t;
  static u64 xorshift() {
    static u64 seed = 91;
    seed ^= seed << 7;
    seed ^= seed >> 9;
    return seed;
  }

  class node_type;
  using pointer = std::unique_ptr<node_type>;
  class node_type {
    friend treap;

    pointer left;
    pointer right;
    size_type size;
    u64 priority;
    T key;

  public:
    node_type(const T &key)
        : left(), right(), size(1), priority(xorshift()), key(key) {}
  };

  static size_type size(const pointer &ptr) { return ptr ? ptr->size : 0; }

  static u64 priority(const pointer &ptr) { return ptr ? ptr->priority : 0; }

  static void fix(const pointer &ptr) {
    ptr->size = size(ptr->left) + 1 + size(ptr->right);
  }

  static void rotate_left(pointer &ptr) {
    pointer right = std::move(ptr->right);
    ptr->right = std::move(right->left);
    fix(ptr);
    right->left = std::move(ptr);
    fix(right);
    ptr = std::move(right);
  }

  static void rotate_right(pointer &ptr) {
    pointer left = std::move(ptr->left);
    ptr->left = std::move(left->right);
    fix(ptr);
    left->right = std::move(ptr);
    fix(left);
    ptr = std::move(left);
  }

  static const T &find_by_order(const pointer &ptr, const size_type index) {
    const size_type left_size = size(ptr->left);
    if (index == left_size) {
      return ptr->key;
    } else if (index < left_size) {
      return find_by_order(ptr->left, index);
    } else {
      return find_by_order(ptr->right, index - left_size - 1);
    }
  }

  static void insert(pointer &ptr, const T &key) {
    if (!ptr) {
      ptr = std::make_unique<node_type>(key);
      return;
    }
    if (key == ptr->key) {
      return;
    }
    if (key < ptr->key) {
      insert(ptr->left, key);
      fix(ptr);
      if (ptr->left->priority > ptr->priority) {
        rotate_right(ptr);
      }
    } else {
      insert(ptr->right, key);
      fix(ptr);
      if (ptr->right->priority > ptr->priority) {
        rotate_left(ptr);
      }
    }
  }

  static void erase(pointer &ptr, const T &key) {
    if (!ptr) {
      return;
    }
    if (key == ptr->key) {
      if (!ptr->left && !ptr->right) {
        ptr.reset();
        return;
      }
      if (priority(ptr->left) > priority(ptr->right)) {
        rotate_right(ptr);
      } else {
        rotate_left(ptr);
      }
    }
    if (key < ptr->key) {
      erase(ptr->left, key);
      fix(ptr);
    } else {
      erase(ptr->right, key);
      fix(ptr);
    }
  }

  pointer root;

public:
  treap() : root() {}

  const T &find_by_order(const size_type index) const {
    return find_by_order(root, index);
  }

  void insert(const T &key) { insert(root, key); }

  void erase(const T &key) { erase(root, key); }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "gomi/treap.cpp"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>

template <class T> class treap {
public:
  using size_type = std::size_t;

private:
  using u64 = std::uint64_t;
  static u64 xorshift() {
    static u64 seed = 91;
    seed ^= seed << 7;
    seed ^= seed >> 9;
    return seed;
  }

  class node_type;
  using pointer = std::unique_ptr<node_type>;
  class node_type {
    friend treap;

    pointer left;
    pointer right;
    size_type size;
    u64 priority;
    T key;

  public:
    node_type(const T &key)
        : left(), right(), size(1), priority(xorshift()), key(key) {}
  };

  static size_type size(const pointer &ptr) { return ptr ? ptr->size : 0; }

  static u64 priority(const pointer &ptr) { return ptr ? ptr->priority : 0; }

  static void fix(const pointer &ptr) {
    ptr->size = size(ptr->left) + 1 + size(ptr->right);
  }

  static void rotate_left(pointer &ptr) {
    pointer right = std::move(ptr->right);
    ptr->right = std::move(right->left);
    fix(ptr);
    right->left = std::move(ptr);
    fix(right);
    ptr = std::move(right);
  }

  static void rotate_right(pointer &ptr) {
    pointer left = std::move(ptr->left);
    ptr->left = std::move(left->right);
    fix(ptr);
    left->right = std::move(ptr);
    fix(left);
    ptr = std::move(left);
  }

  static const T &find_by_order(const pointer &ptr, const size_type index) {
    const size_type left_size = size(ptr->left);
    if (index == left_size) {
      return ptr->key;
    } else if (index < left_size) {
      return find_by_order(ptr->left, index);
    } else {
      return find_by_order(ptr->right, index - left_size - 1);
    }
  }

  static void insert(pointer &ptr, const T &key) {
    if (!ptr) {
      ptr = std::make_unique<node_type>(key);
      return;
    }
    if (key == ptr->key) {
      return;
    }
    if (key < ptr->key) {
      insert(ptr->left, key);
      fix(ptr);
      if (ptr->left->priority > ptr->priority) {
        rotate_right(ptr);
      }
    } else {
      insert(ptr->right, key);
      fix(ptr);
      if (ptr->right->priority > ptr->priority) {
        rotate_left(ptr);
      }
    }
  }

  static void erase(pointer &ptr, const T &key) {
    if (!ptr) {
      return;
    }
    if (key == ptr->key) {
      if (!ptr->left && !ptr->right) {
        ptr.reset();
        return;
      }
      if (priority(ptr->left) > priority(ptr->right)) {
        rotate_right(ptr);
      } else {
        rotate_left(ptr);
      }
    }
    if (key < ptr->key) {
      erase(ptr->left, key);
      fix(ptr);
    } else {
      erase(ptr->right, key);
      fix(ptr);
    }
  }

  pointer root;

public:
  treap() : root() {}

  const T &find_by_order(const size_type index) const {
    return find_by_order(root, index);
  }

  void insert(const T &key) { insert(root, key); }

  void erase(const T &key) { erase(root, key); }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

