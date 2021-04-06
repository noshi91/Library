---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Xor Linked List
    links:
    - https://en.wikipedia.org/wiki/XOR_linked_list
  bundledCode: "#line 1 \"data_structure/xor_linked_list.cpp\"\n#include <cassert>\n\
    #include <cstdint>\n#include <utility>\n\ntemplate <class T> class xor_linked_list\
    \ {\npublic:\n  using value_type = T;\n\nprivate:\n  class node_type {\n  public:\n\
    \    T value;\n    std::uintptr_t link;\n\n    node_type(T value, const std::uintptr_t\
    \ link)\n        : value(std::move(value)), link(link) {}\n  };\n\n  static std::uintptr_t\
    \ ptoi(node_type *const ptr) {\n    return reinterpret_cast<std::uintptr_t>(ptr);\n\
    \  }\n\n  static node_type *itop(const std::uintptr_t id) {\n    return reinterpret_cast<node_type\
    \ *>(id);\n  }\n\n  node_type *front_;\n  node_type *back_;\n\n  void release()\
    \ {\n    front_ = nullptr;\n    back_ = nullptr;\n  }\n\npublic:\n  xor_linked_list()\
    \ : front_(nullptr), back_(nullptr) {}\n\n  xor_linked_list(const xor_linked_list\
    \ &) = delete;\n\n  xor_linked_list(xor_linked_list &&r) noexcept\n      : front_(r.front_),\
    \ back_(r.back_) {\n    r.release();\n  }\n\n  ~xor_linked_list() { clear(); }\n\
    \n  xor_linked_list &operator=(const xor_linked_list &) = delete;\n\n  xor_linked_list\
    \ &operator=(xor_linked_list &&r) noexcept {\n    front_ = r.front_;\n    back_\
    \ = r.back_;\n    r.release();\n    return *this;\n  }\n\n  bool empty() const\
    \ { return front_ == nullptr; }\n\n  T &front() {\n    assert(!empty());\n\n \
    \   return front_->value;\n  }\n\n  T &back() {\n    assert(!empty());\n\n   \
    \ return back_->value;\n  }\n\n  void push_back(T x) {\n    if (empty()) {\n \
    \     node_type *const next = new node_type(std::move(x), 0);\n      front_ =\
    \ next;\n      back_ = next;\n    } else {\n      node_type *const next = new\
    \ node_type(std::move(x), ptoi(back_));\n      back_->link ^= ptoi(next);\n  \
    \    back_ = next;\n    }\n  }\n\n  void pop_back() {\n    assert(!empty());\n\
    \n    if (front_ == back_) {\n      delete front_;\n      front_ = nullptr;\n\
    \      back_ = nullptr;\n    } else {\n      node_type *const next = itop(back_->link);\n\
    \      next->link ^= ptoi(back_);\n      delete back_;\n      back_ = next;\n\
    \    }\n  }\n\n  void push_front(T x) {\n    reverse();\n    push_back(std::move(x));\n\
    \    reverse();\n  }\n\n  void pop_front() {\n    assert(!empty());\n\n    reverse();\n\
    \    pop_back();\n    reverse();\n  }\n\n  void clear() {\n    if (empty())\n\
    \      return;\n    node_type *itr = front_;\n    std::uintptr_t prev = 0;\n \
    \   while (itr != back_) {\n      node_type *const next = itop(itr->link ^ prev);\n\
    \      prev = ptoi(itr);\n      delete itr;\n      itr = next;\n    }\n    delete\
    \ itr;\n    release();\n  }\n\n  void reverse() { std::swap(front_, back_); }\n\
    \n  static xor_linked_list catenate(xor_linked_list left, xor_linked_list right)\
    \ {\n    if (left.empty())\n      return right;\n    if (right.empty())\n    \
    \  return left;\n    left.back_->link ^= ptoi(right.front_);\n    right.front_->link\
    \ ^= ptoi(left.back_);\n    xor_linked_list ret;\n    ret.front_ = left.front_;\n\
    \    ret.back_ = right.back_;\n    left.release();\n    right.release();\n   \
    \ return ret;\n  }\n};\n\n/**\n * @brief Xor Linked List\n * @see https://en.wikipedia.org/wiki/XOR_linked_list\n\
    \ */\n"
  code: "#include <cassert>\n#include <cstdint>\n#include <utility>\n\ntemplate <class\
    \ T> class xor_linked_list {\npublic:\n  using value_type = T;\n\nprivate:\n \
    \ class node_type {\n  public:\n    T value;\n    std::uintptr_t link;\n\n   \
    \ node_type(T value, const std::uintptr_t link)\n        : value(std::move(value)),\
    \ link(link) {}\n  };\n\n  static std::uintptr_t ptoi(node_type *const ptr) {\n\
    \    return reinterpret_cast<std::uintptr_t>(ptr);\n  }\n\n  static node_type\
    \ *itop(const std::uintptr_t id) {\n    return reinterpret_cast<node_type *>(id);\n\
    \  }\n\n  node_type *front_;\n  node_type *back_;\n\n  void release() {\n    front_\
    \ = nullptr;\n    back_ = nullptr;\n  }\n\npublic:\n  xor_linked_list() : front_(nullptr),\
    \ back_(nullptr) {}\n\n  xor_linked_list(const xor_linked_list &) = delete;\n\n\
    \  xor_linked_list(xor_linked_list &&r) noexcept\n      : front_(r.front_), back_(r.back_)\
    \ {\n    r.release();\n  }\n\n  ~xor_linked_list() { clear(); }\n\n  xor_linked_list\
    \ &operator=(const xor_linked_list &) = delete;\n\n  xor_linked_list &operator=(xor_linked_list\
    \ &&r) noexcept {\n    front_ = r.front_;\n    back_ = r.back_;\n    r.release();\n\
    \    return *this;\n  }\n\n  bool empty() const { return front_ == nullptr; }\n\
    \n  T &front() {\n    assert(!empty());\n\n    return front_->value;\n  }\n\n\
    \  T &back() {\n    assert(!empty());\n\n    return back_->value;\n  }\n\n  void\
    \ push_back(T x) {\n    if (empty()) {\n      node_type *const next = new node_type(std::move(x),\
    \ 0);\n      front_ = next;\n      back_ = next;\n    } else {\n      node_type\
    \ *const next = new node_type(std::move(x), ptoi(back_));\n      back_->link ^=\
    \ ptoi(next);\n      back_ = next;\n    }\n  }\n\n  void pop_back() {\n    assert(!empty());\n\
    \n    if (front_ == back_) {\n      delete front_;\n      front_ = nullptr;\n\
    \      back_ = nullptr;\n    } else {\n      node_type *const next = itop(back_->link);\n\
    \      next->link ^= ptoi(back_);\n      delete back_;\n      back_ = next;\n\
    \    }\n  }\n\n  void push_front(T x) {\n    reverse();\n    push_back(std::move(x));\n\
    \    reverse();\n  }\n\n  void pop_front() {\n    assert(!empty());\n\n    reverse();\n\
    \    pop_back();\n    reverse();\n  }\n\n  void clear() {\n    if (empty())\n\
    \      return;\n    node_type *itr = front_;\n    std::uintptr_t prev = 0;\n \
    \   while (itr != back_) {\n      node_type *const next = itop(itr->link ^ prev);\n\
    \      prev = ptoi(itr);\n      delete itr;\n      itr = next;\n    }\n    delete\
    \ itr;\n    release();\n  }\n\n  void reverse() { std::swap(front_, back_); }\n\
    \n  static xor_linked_list catenate(xor_linked_list left, xor_linked_list right)\
    \ {\n    if (left.empty())\n      return right;\n    if (right.empty())\n    \
    \  return left;\n    left.back_->link ^= ptoi(right.front_);\n    right.front_->link\
    \ ^= ptoi(left.back_);\n    xor_linked_list ret;\n    ret.front_ = left.front_;\n\
    \    ret.back_ = right.back_;\n    left.release();\n    right.release();\n   \
    \ return ret;\n  }\n};\n\n/**\n * @brief Xor Linked List\n * @see https://en.wikipedia.org/wiki/XOR_linked_list\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/xor_linked_list.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/xor_linked_list.cpp
layout: document
redirect_from:
- /library/data_structure/xor_linked_list.cpp
- /library/data_structure/xor_linked_list.cpp.html
title: Xor Linked List
---
