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


# :warning: gomi/assign_segment_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c25e426f9a94f83968c77e7d5480c159">gomi</a>
* <a href="{{ site.github.repository_url }}/blob/master/gomi/assign_segment_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-11 20:43:35+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <vector>

using T = int;
T op(T l, T r) { return l * r; }
T id() { return 1; }

class assign_segment_tree {
private:
  class node {
  public:
    T sum;
    T *lazy;
    node() : sum(id()), lazy(nullptr) {}
    T get() {
      if (lazy) {
        return *lazy;
      } else {
        return sum;
      }
    }
  };

  int height;
  std::vector<node> tree;
  std::vector<T> table;

  void push(int index) {
    if (tree[index].lazy) {
      tree[index * 2].lazy = tree[index].lazy - 1;
      tree[index * 2 + 1].lazy = tree[index].lazy - 1;
      tree[index].sum = *tree[index].lazy;
      tree[index].lazy = nullptr;
    }
  }

  T fold(int index, int n_left, int n_right, int q_left, int q_right) {
    if (q_left <= n_left && n_right <= q_right) {
      return tree[index].get();
    }
    if (n_right <= q_left || q_right <= n_left) {
      return id();
    }
    push(index);
    int n_mid = (n_left + n_right) / 2;
    return op(fold(index * 2, n_left, n_mid, q_left, q_right),
              fold(index * 2 + 1, n_mid, n_right, q_left, q_right));
  }

  void assign(int index, int n_left, int n_right, int q_left, int q_right,
              T *lazy) {
    if (q_left <= n_left && n_right <= q_right) {
      tree[index].lazy = lazy;
      return;
    }
    if (n_right <= q_left || q_right <= n_left) {
      return;
    }
    push(index);
    int n_mid = (n_left + n_right) / 2;
    assign(index * 2, n_left, n_mid, q_left, q_right, lazy - 1);
    assign(index * 2 + 1, n_mid, n_right, q_left, q_right, lazy - 1);
    tree[index].sum = op(tree[index * 2].get(), tree[index * 2 + 1].get());
  }

public:
  assign_segment_tree(int n) {
    height = 1;
    int s = 1;
    while (s < n) {
      s *= 2;
      ++height;
    }
    tree.assign(s * 2, node());
    table.reserve(s * 2);
  }

  int size() { return tree.size() / 2; }

  T fold(int first, int last) { return fold(1, 0, size(), first, last); }

  void assign(int first, int last, T value) {
    for (int i = 0; i < height; ++i) {
      table.push_back(value);
      value = op(value, value);
    }
    assign(1, 0, size(), first, last, &table.back());
    if (table.capacity() - table.size() < height) {
      for (int i = 1; i < size(); ++i) {
        push(i);
      }
      for (int i = size(); i != tree.size(); ++i) {
        if (tree[i].lazy) {
          tree[i].sum = *tree[i].lazy;
          tree[i].lazy = nullptr;
        }
      }
      table.clear();
    }
  }
};

/*

http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja

#include <algorithm>
using T = int;
T op(T l, T r) { return std::min(l, r); }
T id() { return 2147483647; }

*/
/*

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  assign_segment_tree seg(n);
  for (int j = 0; j < q; ++j) {
    int c;
    std::cin >> c;
    if (c == 0) {
      int s, t, x;
      std::cin >> s >> t >> x;
      seg.assign(s, t + 1, x);
    } else {
      int i;
      std::cin >> i;
      std::cout << seg.fold(i, i + 1) << std::endl;
    }
  }
}

//*/

/*

http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja

#include <algorithm>
using T = int;
T op(T l, T r) { return std::min(l, r); }
T id() { return 2147483647; }

*/
/*

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  assign_segment_tree seg(n);
  for (int i = 0; i < q; ++i) {
    int c;
    std::cin >> c;
    if (c == 0) {
      int s, t, x;
      std::cin >> s >> t >> x;
      seg.assign(s, t + 1, x);
    } else {
      int s, t;
      std::cin >> s >> t;
      std::cout << seg.fold(s, t + 1) << std::endl;
    }
  }
}

//*/

/*

http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I&lang=ja

using T = int;
T op(T l, T r) { return l + r; }
T id() { return 0; }

*/
/*

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  assign_segment_tree seg(n);
  for (int i = 0; i < q; ++i) {
    int c;
    std::cin >> c;
    if (c == 0) {
      int s, t, x;
      std::cin >> s >> t >> x;
      seg.assign(s, t + 1, x);
    } else {
      int s, t;
      std::cin >> s >> t;
      std::cout << seg.fold(s, t + 1) << std::endl;
    }
  }
}

//*/

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "gomi/assign_segment_tree.cpp"
#include <vector>

using T = int;
T op(T l, T r) { return l * r; }
T id() { return 1; }

class assign_segment_tree {
private:
  class node {
  public:
    T sum;
    T *lazy;
    node() : sum(id()), lazy(nullptr) {}
    T get() {
      if (lazy) {
        return *lazy;
      } else {
        return sum;
      }
    }
  };

  int height;
  std::vector<node> tree;
  std::vector<T> table;

  void push(int index) {
    if (tree[index].lazy) {
      tree[index * 2].lazy = tree[index].lazy - 1;
      tree[index * 2 + 1].lazy = tree[index].lazy - 1;
      tree[index].sum = *tree[index].lazy;
      tree[index].lazy = nullptr;
    }
  }

  T fold(int index, int n_left, int n_right, int q_left, int q_right) {
    if (q_left <= n_left && n_right <= q_right) {
      return tree[index].get();
    }
    if (n_right <= q_left || q_right <= n_left) {
      return id();
    }
    push(index);
    int n_mid = (n_left + n_right) / 2;
    return op(fold(index * 2, n_left, n_mid, q_left, q_right),
              fold(index * 2 + 1, n_mid, n_right, q_left, q_right));
  }

  void assign(int index, int n_left, int n_right, int q_left, int q_right,
              T *lazy) {
    if (q_left <= n_left && n_right <= q_right) {
      tree[index].lazy = lazy;
      return;
    }
    if (n_right <= q_left || q_right <= n_left) {
      return;
    }
    push(index);
    int n_mid = (n_left + n_right) / 2;
    assign(index * 2, n_left, n_mid, q_left, q_right, lazy - 1);
    assign(index * 2 + 1, n_mid, n_right, q_left, q_right, lazy - 1);
    tree[index].sum = op(tree[index * 2].get(), tree[index * 2 + 1].get());
  }

public:
  assign_segment_tree(int n) {
    height = 1;
    int s = 1;
    while (s < n) {
      s *= 2;
      ++height;
    }
    tree.assign(s * 2, node());
    table.reserve(s * 2);
  }

  int size() { return tree.size() / 2; }

  T fold(int first, int last) { return fold(1, 0, size(), first, last); }

  void assign(int first, int last, T value) {
    for (int i = 0; i < height; ++i) {
      table.push_back(value);
      value = op(value, value);
    }
    assign(1, 0, size(), first, last, &table.back());
    if (table.capacity() - table.size() < height) {
      for (int i = 1; i < size(); ++i) {
        push(i);
      }
      for (int i = size(); i != tree.size(); ++i) {
        if (tree[i].lazy) {
          tree[i].sum = *tree[i].lazy;
          tree[i].lazy = nullptr;
        }
      }
      table.clear();
    }
  }
};

/*

http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja

#include <algorithm>
using T = int;
T op(T l, T r) { return std::min(l, r); }
T id() { return 2147483647; }

*/
/*

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  assign_segment_tree seg(n);
  for (int j = 0; j < q; ++j) {
    int c;
    std::cin >> c;
    if (c == 0) {
      int s, t, x;
      std::cin >> s >> t >> x;
      seg.assign(s, t + 1, x);
    } else {
      int i;
      std::cin >> i;
      std::cout << seg.fold(i, i + 1) << std::endl;
    }
  }
}

//*/

/*

http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja

#include <algorithm>
using T = int;
T op(T l, T r) { return std::min(l, r); }
T id() { return 2147483647; }

*/
/*

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  assign_segment_tree seg(n);
  for (int i = 0; i < q; ++i) {
    int c;
    std::cin >> c;
    if (c == 0) {
      int s, t, x;
      std::cin >> s >> t >> x;
      seg.assign(s, t + 1, x);
    } else {
      int s, t;
      std::cin >> s >> t;
      std::cout << seg.fold(s, t + 1) << std::endl;
    }
  }
}

//*/

/*

http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I&lang=ja

using T = int;
T op(T l, T r) { return l + r; }
T id() { return 0; }

*/
/*

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  assign_segment_tree seg(n);
  for (int i = 0; i < q; ++i) {
    int c;
    std::cin >> c;
    if (c == 0) {
      int s, t, x;
      std::cin >> s >> t >> x;
      seg.assign(s, t + 1, x);
    } else {
      int s, t;
      std::cin >> s >> t;
      std::cout << seg.fold(s, t + 1) << std::endl;
    }
  }
}

//*/

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

