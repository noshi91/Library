---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/physicists_queue.cpp
    title: Physicist's Queue
  - icon: ':heavy_check_mark:'
    path: data_structure/realtime_queue.cpp
    title: Realtime Queue
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/physicists_queue.test.cpp
    title: test/physicists_queue.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/realtime_queue.test.cpp
    title: test/realtime_queue.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Persistent Stack
    links: []
  bundledCode: "#line 1 \"data_structure/persistent_stack.cpp\"\n#include <cassert>\n\
    #include <memory>\n#include <utility>\n\ntemplate <class T> class persistent_stack\
    \ {\n  using Self = persistent_stack<T>;\n  class node_type;\n  using node_ptr\
    \ = std::shared_ptr<const node_type>;\n\n  class node_type {\n  public:\n    T\
    \ value;\n    node_ptr next;\n\n    node_type(T value, node_ptr next) : value(value),\
    \ next(next) {}\n  };\n\n  node_ptr root;\n\n  persistent_stack(node_ptr root)\
    \ : root(root) {}\n\npublic:\n  persistent_stack() = default;\n\n  bool empty()\
    \ const { return not root; }\n\n  T top() const {\n    assert(not empty());\n\n\
    \    return root->value;\n  }\n\n  Self push(T x) const {\n    return Self(std::make_shared<const\
    \ node_type>(x, root));\n  }\n\n  Self pop() const {\n    assert(not empty());\n\
    \n    return Self(root->next);\n  }\n\n  Self reverse() const {\n    Self ret;\n\
    \    Self x = *this;\n    while (not x.empty()) {\n      ret = ret.push(x.top());\n\
    \      x = x.pop();\n    }\n    return ret;\n  }\n};\n\n/**\n * @brief Persistent\
    \ Stack\n */\n"
  code: "#include <cassert>\n#include <memory>\n#include <utility>\n\ntemplate <class\
    \ T> class persistent_stack {\n  using Self = persistent_stack<T>;\n  class node_type;\n\
    \  using node_ptr = std::shared_ptr<const node_type>;\n\n  class node_type {\n\
    \  public:\n    T value;\n    node_ptr next;\n\n    node_type(T value, node_ptr\
    \ next) : value(value), next(next) {}\n  };\n\n  node_ptr root;\n\n  persistent_stack(node_ptr\
    \ root) : root(root) {}\n\npublic:\n  persistent_stack() = default;\n\n  bool\
    \ empty() const { return not root; }\n\n  T top() const {\n    assert(not empty());\n\
    \n    return root->value;\n  }\n\n  Self push(T x) const {\n    return Self(std::make_shared<const\
    \ node_type>(x, root));\n  }\n\n  Self pop() const {\n    assert(not empty());\n\
    \n    return Self(root->next);\n  }\n\n  Self reverse() const {\n    Self ret;\n\
    \    Self x = *this;\n    while (not x.empty()) {\n      ret = ret.push(x.top());\n\
    \      x = x.pop();\n    }\n    return ret;\n  }\n};\n\n/**\n * @brief Persistent\
    \ Stack\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/persistent_stack.cpp
  requiredBy:
  - data_structure/realtime_queue.cpp
  - data_structure/physicists_queue.cpp
  timestamp: '2020-03-16 22:45:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/realtime_queue.test.cpp
  - test/physicists_queue.test.cpp
documentation_of: data_structure/persistent_stack.cpp
layout: document
redirect_from:
- /library/data_structure/persistent_stack.cpp
- /library/data_structure/persistent_stack.cpp.html
title: Persistent Stack
---
