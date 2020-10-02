---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I&lang=ja
  bundledCode: "#line 1 \"gomi/assign_segment_tree.cpp\"\n#include <vector>\n\nusing\
    \ T = int;\nT op(T l, T r) { return l * r; }\nT id() { return 1; }\n\nclass assign_segment_tree\
    \ {\nprivate:\n  class node {\n  public:\n    T sum;\n    T *lazy;\n    node()\
    \ : sum(id()), lazy(nullptr) {}\n    T get() {\n      if (lazy) {\n        return\
    \ *lazy;\n      } else {\n        return sum;\n      }\n    }\n  };\n\n  int height;\n\
    \  std::vector<node> tree;\n  std::vector<T> table;\n\n  void push(int index)\
    \ {\n    if (tree[index].lazy) {\n      tree[index * 2].lazy = tree[index].lazy\
    \ - 1;\n      tree[index * 2 + 1].lazy = tree[index].lazy - 1;\n      tree[index].sum\
    \ = *tree[index].lazy;\n      tree[index].lazy = nullptr;\n    }\n  }\n\n  T fold(int\
    \ index, int n_left, int n_right, int q_left, int q_right) {\n    if (q_left <=\
    \ n_left && n_right <= q_right) {\n      return tree[index].get();\n    }\n  \
    \  if (n_right <= q_left || q_right <= n_left) {\n      return id();\n    }\n\
    \    push(index);\n    int n_mid = (n_left + n_right) / 2;\n    return op(fold(index\
    \ * 2, n_left, n_mid, q_left, q_right),\n              fold(index * 2 + 1, n_mid,\
    \ n_right, q_left, q_right));\n  }\n\n  void assign(int index, int n_left, int\
    \ n_right, int q_left, int q_right,\n              T *lazy) {\n    if (q_left\
    \ <= n_left && n_right <= q_right) {\n      tree[index].lazy = lazy;\n      return;\n\
    \    }\n    if (n_right <= q_left || q_right <= n_left) {\n      return;\n   \
    \ }\n    push(index);\n    int n_mid = (n_left + n_right) / 2;\n    assign(index\
    \ * 2, n_left, n_mid, q_left, q_right, lazy - 1);\n    assign(index * 2 + 1, n_mid,\
    \ n_right, q_left, q_right, lazy - 1);\n    tree[index].sum = op(tree[index *\
    \ 2].get(), tree[index * 2 + 1].get());\n  }\n\npublic:\n  assign_segment_tree(int\
    \ n) {\n    height = 1;\n    int s = 1;\n    while (s < n) {\n      s *= 2;\n\
    \      ++height;\n    }\n    tree.assign(s * 2, node());\n    table.reserve(s\
    \ * 2);\n  }\n\n  int size() { return tree.size() / 2; }\n\n  T fold(int first,\
    \ int last) { return fold(1, 0, size(), first, last); }\n\n  void assign(int first,\
    \ int last, T value) {\n    for (int i = 0; i < height; ++i) {\n      table.push_back(value);\n\
    \      value = op(value, value);\n    }\n    assign(1, 0, size(), first, last,\
    \ &table.back());\n    if (table.capacity() - table.size() < height) {\n     \
    \ for (int i = 1; i < size(); ++i) {\n        push(i);\n      }\n      for (int\
    \ i = size(); i != tree.size(); ++i) {\n        if (tree[i].lazy) {\n        \
    \  tree[i].sum = *tree[i].lazy;\n          tree[i].lazy = nullptr;\n        }\n\
    \      }\n      table.clear();\n    }\n  }\n};\n\n/*\n\nhttp://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja\n\
    \n#include <algorithm>\nusing T = int;\nT op(T l, T r) { return std::min(l, r);\
    \ }\nT id() { return 2147483647; }\n\n*/\n/*\n\n#include <iostream>\n\nint main()\
    \ {\n  int n, q;\n  std::cin >> n >> q;\n  assign_segment_tree seg(n);\n  for\
    \ (int j = 0; j < q; ++j) {\n    int c;\n    std::cin >> c;\n    if (c == 0) {\n\
    \      int s, t, x;\n      std::cin >> s >> t >> x;\n      seg.assign(s, t + 1,\
    \ x);\n    } else {\n      int i;\n      std::cin >> i;\n      std::cout << seg.fold(i,\
    \ i + 1) << std::endl;\n    }\n  }\n}\n\n//*/\n\n/*\n\nhttp://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja\n\
    \n#include <algorithm>\nusing T = int;\nT op(T l, T r) { return std::min(l, r);\
    \ }\nT id() { return 2147483647; }\n\n*/\n/*\n\n#include <iostream>\n\nint main()\
    \ {\n  int n, q;\n  std::cin >> n >> q;\n  assign_segment_tree seg(n);\n  for\
    \ (int i = 0; i < q; ++i) {\n    int c;\n    std::cin >> c;\n    if (c == 0) {\n\
    \      int s, t, x;\n      std::cin >> s >> t >> x;\n      seg.assign(s, t + 1,\
    \ x);\n    } else {\n      int s, t;\n      std::cin >> s >> t;\n      std::cout\
    \ << seg.fold(s, t + 1) << std::endl;\n    }\n  }\n}\n\n//*/\n\n/*\n\nhttp://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I&lang=ja\n\
    \nusing T = int;\nT op(T l, T r) { return l + r; }\nT id() { return 0; }\n\n*/\n\
    /*\n\n#include <iostream>\n\nint main() {\n  int n, q;\n  std::cin >> n >> q;\n\
    \  assign_segment_tree seg(n);\n  for (int i = 0; i < q; ++i) {\n    int c;\n\
    \    std::cin >> c;\n    if (c == 0) {\n      int s, t, x;\n      std::cin >>\
    \ s >> t >> x;\n      seg.assign(s, t + 1, x);\n    } else {\n      int s, t;\n\
    \      std::cin >> s >> t;\n      std::cout << seg.fold(s, t + 1) << std::endl;\n\
    \    }\n  }\n}\n\n//*/\n"
  code: "#include <vector>\n\nusing T = int;\nT op(T l, T r) { return l * r; }\nT\
    \ id() { return 1; }\n\nclass assign_segment_tree {\nprivate:\n  class node {\n\
    \  public:\n    T sum;\n    T *lazy;\n    node() : sum(id()), lazy(nullptr) {}\n\
    \    T get() {\n      if (lazy) {\n        return *lazy;\n      } else {\n   \
    \     return sum;\n      }\n    }\n  };\n\n  int height;\n  std::vector<node>\
    \ tree;\n  std::vector<T> table;\n\n  void push(int index) {\n    if (tree[index].lazy)\
    \ {\n      tree[index * 2].lazy = tree[index].lazy - 1;\n      tree[index * 2\
    \ + 1].lazy = tree[index].lazy - 1;\n      tree[index].sum = *tree[index].lazy;\n\
    \      tree[index].lazy = nullptr;\n    }\n  }\n\n  T fold(int index, int n_left,\
    \ int n_right, int q_left, int q_right) {\n    if (q_left <= n_left && n_right\
    \ <= q_right) {\n      return tree[index].get();\n    }\n    if (n_right <= q_left\
    \ || q_right <= n_left) {\n      return id();\n    }\n    push(index);\n    int\
    \ n_mid = (n_left + n_right) / 2;\n    return op(fold(index * 2, n_left, n_mid,\
    \ q_left, q_right),\n              fold(index * 2 + 1, n_mid, n_right, q_left,\
    \ q_right));\n  }\n\n  void assign(int index, int n_left, int n_right, int q_left,\
    \ int q_right,\n              T *lazy) {\n    if (q_left <= n_left && n_right\
    \ <= q_right) {\n      tree[index].lazy = lazy;\n      return;\n    }\n    if\
    \ (n_right <= q_left || q_right <= n_left) {\n      return;\n    }\n    push(index);\n\
    \    int n_mid = (n_left + n_right) / 2;\n    assign(index * 2, n_left, n_mid,\
    \ q_left, q_right, lazy - 1);\n    assign(index * 2 + 1, n_mid, n_right, q_left,\
    \ q_right, lazy - 1);\n    tree[index].sum = op(tree[index * 2].get(), tree[index\
    \ * 2 + 1].get());\n  }\n\npublic:\n  assign_segment_tree(int n) {\n    height\
    \ = 1;\n    int s = 1;\n    while (s < n) {\n      s *= 2;\n      ++height;\n\
    \    }\n    tree.assign(s * 2, node());\n    table.reserve(s * 2);\n  }\n\n  int\
    \ size() { return tree.size() / 2; }\n\n  T fold(int first, int last) { return\
    \ fold(1, 0, size(), first, last); }\n\n  void assign(int first, int last, T value)\
    \ {\n    for (int i = 0; i < height; ++i) {\n      table.push_back(value);\n \
    \     value = op(value, value);\n    }\n    assign(1, 0, size(), first, last,\
    \ &table.back());\n    if (table.capacity() - table.size() < height) {\n     \
    \ for (int i = 1; i < size(); ++i) {\n        push(i);\n      }\n      for (int\
    \ i = size(); i != tree.size(); ++i) {\n        if (tree[i].lazy) {\n        \
    \  tree[i].sum = *tree[i].lazy;\n          tree[i].lazy = nullptr;\n        }\n\
    \      }\n      table.clear();\n    }\n  }\n};\n\n/*\n\nhttp://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja\n\
    \n#include <algorithm>\nusing T = int;\nT op(T l, T r) { return std::min(l, r);\
    \ }\nT id() { return 2147483647; }\n\n*/\n/*\n\n#include <iostream>\n\nint main()\
    \ {\n  int n, q;\n  std::cin >> n >> q;\n  assign_segment_tree seg(n);\n  for\
    \ (int j = 0; j < q; ++j) {\n    int c;\n    std::cin >> c;\n    if (c == 0) {\n\
    \      int s, t, x;\n      std::cin >> s >> t >> x;\n      seg.assign(s, t + 1,\
    \ x);\n    } else {\n      int i;\n      std::cin >> i;\n      std::cout << seg.fold(i,\
    \ i + 1) << std::endl;\n    }\n  }\n}\n\n//*/\n\n/*\n\nhttp://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja\n\
    \n#include <algorithm>\nusing T = int;\nT op(T l, T r) { return std::min(l, r);\
    \ }\nT id() { return 2147483647; }\n\n*/\n/*\n\n#include <iostream>\n\nint main()\
    \ {\n  int n, q;\n  std::cin >> n >> q;\n  assign_segment_tree seg(n);\n  for\
    \ (int i = 0; i < q; ++i) {\n    int c;\n    std::cin >> c;\n    if (c == 0) {\n\
    \      int s, t, x;\n      std::cin >> s >> t >> x;\n      seg.assign(s, t + 1,\
    \ x);\n    } else {\n      int s, t;\n      std::cin >> s >> t;\n      std::cout\
    \ << seg.fold(s, t + 1) << std::endl;\n    }\n  }\n}\n\n//*/\n\n/*\n\nhttp://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I&lang=ja\n\
    \nusing T = int;\nT op(T l, T r) { return l + r; }\nT id() { return 0; }\n\n*/\n\
    /*\n\n#include <iostream>\n\nint main() {\n  int n, q;\n  std::cin >> n >> q;\n\
    \  assign_segment_tree seg(n);\n  for (int i = 0; i < q; ++i) {\n    int c;\n\
    \    std::cin >> c;\n    if (c == 0) {\n      int s, t, x;\n      std::cin >>\
    \ s >> t >> x;\n      seg.assign(s, t + 1, x);\n    } else {\n      int s, t;\n\
    \      std::cin >> s >> t;\n      std::cout << seg.fold(s, t + 1) << std::endl;\n\
    \    }\n  }\n}\n\n//*/\n"
  dependsOn: []
  isVerificationFile: false
  path: gomi/assign_segment_tree.cpp
  requiredBy: []
  timestamp: '2019-12-11 20:43:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: gomi/assign_segment_tree.cpp
layout: document
redirect_from:
- /library/gomi/assign_segment_tree.cpp
- /library/gomi/assign_segment_tree.cpp.html
title: gomi/assign_segment_tree.cpp
---
