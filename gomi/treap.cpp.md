---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"gomi/treap.cpp\"\n#include <cstddef>\n#include <cstdint>\n\
    #include <memory>\n#include <utility>\n\ntemplate <class T> class treap {\npublic:\n\
    \  using size_type = std::size_t;\n\nprivate:\n  using u64 = std::uint64_t;\n\
    \  static u64 xorshift() {\n    static u64 seed = 91;\n    seed ^= seed << 7;\n\
    \    seed ^= seed >> 9;\n    return seed;\n  }\n\n  class node_type;\n  using\
    \ pointer = std::unique_ptr<node_type>;\n  class node_type {\n    friend treap;\n\
    \n    pointer left;\n    pointer right;\n    size_type size;\n    u64 priority;\n\
    \    T key;\n\n  public:\n    node_type(const T &key)\n        : left(), right(),\
    \ size(1), priority(xorshift()), key(key) {}\n  };\n\n  static size_type size(const\
    \ pointer &ptr) { return ptr ? ptr->size : 0; }\n\n  static u64 priority(const\
    \ pointer &ptr) { return ptr ? ptr->priority : 0; }\n\n  static void fix(const\
    \ pointer &ptr) {\n    ptr->size = size(ptr->left) + 1 + size(ptr->right);\n \
    \ }\n\n  static void rotate_left(pointer &ptr) {\n    pointer right = std::move(ptr->right);\n\
    \    ptr->right = std::move(right->left);\n    fix(ptr);\n    right->left = std::move(ptr);\n\
    \    fix(right);\n    ptr = std::move(right);\n  }\n\n  static void rotate_right(pointer\
    \ &ptr) {\n    pointer left = std::move(ptr->left);\n    ptr->left = std::move(left->right);\n\
    \    fix(ptr);\n    left->right = std::move(ptr);\n    fix(left);\n    ptr = std::move(left);\n\
    \  }\n\n  static const T &find_by_order(const pointer &ptr, const size_type index)\
    \ {\n    const size_type left_size = size(ptr->left);\n    if (index == left_size)\
    \ {\n      return ptr->key;\n    } else if (index < left_size) {\n      return\
    \ find_by_order(ptr->left, index);\n    } else {\n      return find_by_order(ptr->right,\
    \ index - left_size - 1);\n    }\n  }\n\n  static void insert(pointer &ptr, const\
    \ T &key) {\n    if (!ptr) {\n      ptr = std::make_unique<node_type>(key);\n\
    \      return;\n    }\n    if (key == ptr->key) {\n      return;\n    }\n    if\
    \ (key < ptr->key) {\n      insert(ptr->left, key);\n      fix(ptr);\n      if\
    \ (ptr->left->priority > ptr->priority) {\n        rotate_right(ptr);\n      }\n\
    \    } else {\n      insert(ptr->right, key);\n      fix(ptr);\n      if (ptr->right->priority\
    \ > ptr->priority) {\n        rotate_left(ptr);\n      }\n    }\n  }\n\n  static\
    \ void erase(pointer &ptr, const T &key) {\n    if (!ptr) {\n      return;\n \
    \   }\n    if (key == ptr->key) {\n      if (!ptr->left && !ptr->right) {\n  \
    \      ptr.reset();\n        return;\n      }\n      if (priority(ptr->left) >\
    \ priority(ptr->right)) {\n        rotate_right(ptr);\n      } else {\n      \
    \  rotate_left(ptr);\n      }\n    }\n    if (key < ptr->key) {\n      erase(ptr->left,\
    \ key);\n      fix(ptr);\n    } else {\n      erase(ptr->right, key);\n      fix(ptr);\n\
    \    }\n  }\n\n  pointer root;\n\npublic:\n  treap() : root() {}\n\n  const T\
    \ &find_by_order(const size_type index) const {\n    return find_by_order(root,\
    \ index);\n  }\n\n  void insert(const T &key) { insert(root, key); }\n\n  void\
    \ erase(const T &key) { erase(root, key); }\n};\n"
  code: "#include <cstddef>\n#include <cstdint>\n#include <memory>\n#include <utility>\n\
    \ntemplate <class T> class treap {\npublic:\n  using size_type = std::size_t;\n\
    \nprivate:\n  using u64 = std::uint64_t;\n  static u64 xorshift() {\n    static\
    \ u64 seed = 91;\n    seed ^= seed << 7;\n    seed ^= seed >> 9;\n    return seed;\n\
    \  }\n\n  class node_type;\n  using pointer = std::unique_ptr<node_type>;\n  class\
    \ node_type {\n    friend treap;\n\n    pointer left;\n    pointer right;\n  \
    \  size_type size;\n    u64 priority;\n    T key;\n\n  public:\n    node_type(const\
    \ T &key)\n        : left(), right(), size(1), priority(xorshift()), key(key)\
    \ {}\n  };\n\n  static size_type size(const pointer &ptr) { return ptr ? ptr->size\
    \ : 0; }\n\n  static u64 priority(const pointer &ptr) { return ptr ? ptr->priority\
    \ : 0; }\n\n  static void fix(const pointer &ptr) {\n    ptr->size = size(ptr->left)\
    \ + 1 + size(ptr->right);\n  }\n\n  static void rotate_left(pointer &ptr) {\n\
    \    pointer right = std::move(ptr->right);\n    ptr->right = std::move(right->left);\n\
    \    fix(ptr);\n    right->left = std::move(ptr);\n    fix(right);\n    ptr =\
    \ std::move(right);\n  }\n\n  static void rotate_right(pointer &ptr) {\n    pointer\
    \ left = std::move(ptr->left);\n    ptr->left = std::move(left->right);\n    fix(ptr);\n\
    \    left->right = std::move(ptr);\n    fix(left);\n    ptr = std::move(left);\n\
    \  }\n\n  static const T &find_by_order(const pointer &ptr, const size_type index)\
    \ {\n    const size_type left_size = size(ptr->left);\n    if (index == left_size)\
    \ {\n      return ptr->key;\n    } else if (index < left_size) {\n      return\
    \ find_by_order(ptr->left, index);\n    } else {\n      return find_by_order(ptr->right,\
    \ index - left_size - 1);\n    }\n  }\n\n  static void insert(pointer &ptr, const\
    \ T &key) {\n    if (!ptr) {\n      ptr = std::make_unique<node_type>(key);\n\
    \      return;\n    }\n    if (key == ptr->key) {\n      return;\n    }\n    if\
    \ (key < ptr->key) {\n      insert(ptr->left, key);\n      fix(ptr);\n      if\
    \ (ptr->left->priority > ptr->priority) {\n        rotate_right(ptr);\n      }\n\
    \    } else {\n      insert(ptr->right, key);\n      fix(ptr);\n      if (ptr->right->priority\
    \ > ptr->priority) {\n        rotate_left(ptr);\n      }\n    }\n  }\n\n  static\
    \ void erase(pointer &ptr, const T &key) {\n    if (!ptr) {\n      return;\n \
    \   }\n    if (key == ptr->key) {\n      if (!ptr->left && !ptr->right) {\n  \
    \      ptr.reset();\n        return;\n      }\n      if (priority(ptr->left) >\
    \ priority(ptr->right)) {\n        rotate_right(ptr);\n      } else {\n      \
    \  rotate_left(ptr);\n      }\n    }\n    if (key < ptr->key) {\n      erase(ptr->left,\
    \ key);\n      fix(ptr);\n    } else {\n      erase(ptr->right, key);\n      fix(ptr);\n\
    \    }\n  }\n\n  pointer root;\n\npublic:\n  treap() : root() {}\n\n  const T\
    \ &find_by_order(const size_type index) const {\n    return find_by_order(root,\
    \ index);\n  }\n\n  void insert(const T &key) { insert(root, key); }\n\n  void\
    \ erase(const T &key) { erase(root, key); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: gomi/treap.cpp
  requiredBy: []
  timestamp: '2019-12-11 20:43:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: gomi/treap.cpp
layout: document
redirect_from:
- /library/gomi/treap.cpp
- /library/gomi/treap.cpp.html
title: gomi/treap.cpp
---
