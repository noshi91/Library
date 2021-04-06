---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/erasable_heap.test.cpp
    title: test/erasable_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Erasable Heap
    links: []
  bundledCode: "#line 1 \"data_structure/erasable_heap.cpp\"\n#include <cassert>\n\
    #include <utility>\n\ntemplate <class Heap> class erasable_heap {\n  using W =\
    \ typename Heap::value_compare;\n  using T = typename Heap::value_type;\n\npublic:\n\
    \  using value_compare = W;\n  using value_type = T;\n\nprivate:\n  static bool\
    \ equivalent(const T &x, const T &y) {\n    return W::compare(x, y) && W::compare(y,\
    \ x);\n  }\n\n  Heap base;\n  Heap erased;\n\n  void normalize() {\n    while\
    \ (!base.empty() && !erased.empty() &&\n           equivalent(base.top(), erased.top()))\
    \ {\n      base.pop();\n      erased.pop();\n    }\n  }\n\npublic:\n  erasable_heap()\
    \ = default;\n\n  bool empty() const { return base.empty(); }\n\n  const T &top()\
    \ const {\n    assert(!empty());\n\n    return base.top();\n  }\n\n  void push(T\
    \ x) {\n    base.push(std::move(x));\n    normalize();\n  }\n\n  T pop() {\n \
    \   assert(!empty());\n\n    T ret = base.pop();\n    normalize();\n    return\
    \ ret;\n  }\n\n  void erase(T x) {\n    erased.push(std::move(x));\n    normalize();\n\
    \  }\n};\n\n/**\n * @brief Erasable Heap\n */\n"
  code: "#include <cassert>\n#include <utility>\n\ntemplate <class Heap> class erasable_heap\
    \ {\n  using W = typename Heap::value_compare;\n  using T = typename Heap::value_type;\n\
    \npublic:\n  using value_compare = W;\n  using value_type = T;\n\nprivate:\n \
    \ static bool equivalent(const T &x, const T &y) {\n    return W::compare(x, y)\
    \ && W::compare(y, x);\n  }\n\n  Heap base;\n  Heap erased;\n\n  void normalize()\
    \ {\n    while (!base.empty() && !erased.empty() &&\n           equivalent(base.top(),\
    \ erased.top())) {\n      base.pop();\n      erased.pop();\n    }\n  }\n\npublic:\n\
    \  erasable_heap() = default;\n\n  bool empty() const { return base.empty(); }\n\
    \n  const T &top() const {\n    assert(!empty());\n\n    return base.top();\n\
    \  }\n\n  void push(T x) {\n    base.push(std::move(x));\n    normalize();\n \
    \ }\n\n  T pop() {\n    assert(!empty());\n\n    T ret = base.pop();\n    normalize();\n\
    \    return ret;\n  }\n\n  void erase(T x) {\n    erased.push(std::move(x));\n\
    \    normalize();\n  }\n};\n\n/**\n * @brief Erasable Heap\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/erasable_heap.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/erasable_heap.test.cpp
documentation_of: data_structure/erasable_heap.cpp
layout: document
redirect_from:
- /library/data_structure/erasable_heap.cpp
- /library/data_structure/erasable_heap.cpp.html
title: Erasable Heap
---
