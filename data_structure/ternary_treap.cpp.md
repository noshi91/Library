---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Ternary Treap
    links:
    - https://scrapbox.io/data-structures/Ternary_Search_Tree
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/ternary_treap.cpp\"\n\n#include <algorithm>\n#line 5\
    \ \"data_structure/ternary_treap.cpp\"\n#include <iterator>\n#include <limits>\n\
    #include <memory>\n#include <random>\n#include <utility>\n#include <vector>\n\n\
    template <class W> class ternary_treap {\n  using T = typename W::value_type;\n\
    \npublic:\n  using key_type = std::vector<T>;\n\nprivate:\n  using key_itr = typename\
    \ key_type::const_iterator;\n  class node_type;\n  using node_ptr = std::unique_ptr<node_type>;\n\
    \  class mid_type {\n    friend ternary_treap;\n\n    usize prio_;\n    usize\
    \ key_prio;\n    node_ptr ptr;\n\n    void fix() { prio_ = std::max(key_prio,\
    \ prio(ptr)); }\n\n  public:\n    mid_type() : prio_(0), key_prio(0), ptr() {}\n\
    \  };\n  class node_type {\n    friend ternary_treap;\n\n    T key;\n    node_ptr\
    \ left;\n    mid_type mid;\n    node_ptr right;\n\n    usize prio() const { return\
    \ mid.prio_; }\n\n  public:\n    node_type(const T key) : key(key), left(), mid(),\
    \ right() {}\n  };\n\n  static usize rand() {\n    static std::default_random_engine\
    \ rng(91);\n    static std::uniform_int_distribution<usize> uid(\n        1, std::numeric_limits<usize>::max());\n\
    \    return uid(rng);\n  }\n  static usize prio(const node_ptr &ptr) { return\
    \ ptr ? ptr->prio() : 0; }\n  static void rot_left(node_ptr &ptr) {\n    node_ptr\
    \ right = std::move(ptr->right);\n    ptr->right = std::move(right->left);\n \
    \   right->left = std::move(ptr);\n    ptr = std::move(right);\n  }\n  static\
    \ void rot_right(node_ptr &ptr) {\n    node_ptr left = std::move(ptr->left);\n\
    \    ptr->left = std::move(left->right);\n    left->right = std::move(ptr);\n\
    \    ptr = std::move(left);\n  }\n\n  static bool contains(const mid_type &mid,\
    \ const key_itr f, const key_itr l) {\n    if (f == l)\n      return mid.key_prio\
    \ != 0;\n    return contains(mid.ptr, f, l);\n  }\n  static bool contains(const\
    \ node_ptr &ptr, const key_itr f, const key_itr l) {\n    if (!ptr)\n      return\
    \ false;\n    if (!W::compare(ptr->key, *f))\n      return contains(ptr->left,\
    \ f, l);\n    else if (!W::compare(*f, ptr->key))\n      return contains(ptr->right,\
    \ f, l);\n    else\n      return contains(ptr->mid, std::next(f), l);\n  }\n \
    \ static void insert(mid_type &mid, const key_itr f, const key_itr l) {\n    if\
    \ (f == l) {\n      if (mid.key_prio == 0)\n        mid.key_prio = rand();\n \
    \   } else {\n      insert(mid.ptr, f, l);\n    }\n    mid.fix();\n  }\n  static\
    \ void insert(node_ptr &ptr, const key_itr f, const key_itr l) {\n    if (!ptr)\n\
    \      ptr = std::make_unique<node_type>(*f);\n    if (!W::compare(ptr->key, *f))\
    \ {\n      insert(ptr->left, f, l);\n      if (ptr->left->prio() > ptr->prio())\n\
    \        rot_right(ptr);\n    } else if (!W::compare(*f, ptr->key)) {\n      insert(ptr->right,\
    \ f, l);\n      if (ptr->right->prio() > ptr->prio())\n        rot_left(ptr);\n\
    \    } else {\n      insert(ptr->mid, std::next(f), l);\n    }\n  }\n  static\
    \ void erase(mid_type &mid, const key_itr f, const key_itr l) {\n    if (f ==\
    \ l) {\n      if (mid.key_prio != 0)\n        mid.key_prio = 0;\n    } else {\n\
    \      erase(mid.ptr, f, l);\n    }\n    mid.fix();\n  }\n  static void erase(node_ptr\
    \ &ptr, const key_itr f, const key_itr l) {\n    if (!ptr)\n      return;\n  \
    \  if (!W::compare(ptr->key, *f)) {\n      erase(ptr->left, f, l);\n    } else\
    \ if (!W::compare(*f, ptr->key)) {\n      erase(ptr->right, f, l);\n    } else\
    \ {\n      erase(ptr->mid, std::next(f), l);\n      heapify(ptr);\n    }\n  }\n\
    \  static void heapify(node_ptr &ptr) {\n    if (prio(ptr->left) > ptr->prio()\
    \ || prio(ptr->right) > ptr->prio()) {\n      if (prio(ptr->left) >= prio(ptr->right))\
    \ {\n        rot_right(ptr);\n        heapify(ptr->right);\n      } else {\n \
    \       rot_left(ptr);\n        heapify(ptr->left);\n      }\n    } else {\n \
    \     if (ptr->prio() == 0)\n        ptr.reset();\n    }\n  }\n\n  mid_type root;\n\
    \npublic:\n  ternary_treap() = default;\n\n  bool empty() const { return root.prio\
    \ == 0; }\n\n  bool contains(const key_type x) const {\n    return contains(root,\
    \ x.cbegin(), x.cend());\n  }\n\n  void insert(const std::vector<T> x) { insert(root,\
    \ x.cbegin(), x.cend()); }\n  void erase(const std::vector<T> x) { erase(root,\
    \ x.cbegin(), x.cend()); }\n};\n\n/**\n * @brief Ternary Treap\n * @see https://scrapbox.io/data-structures/Ternary_Search_Tree\n\
    \ */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <algorithm>\n#include <cstddef>\n\
    #include <iterator>\n#include <limits>\n#include <memory>\n#include <random>\n\
    #include <utility>\n#include <vector>\n\ntemplate <class W> class ternary_treap\
    \ {\n  using T = typename W::value_type;\n\npublic:\n  using key_type = std::vector<T>;\n\
    \nprivate:\n  using key_itr = typename key_type::const_iterator;\n  class node_type;\n\
    \  using node_ptr = std::unique_ptr<node_type>;\n  class mid_type {\n    friend\
    \ ternary_treap;\n\n    usize prio_;\n    usize key_prio;\n    node_ptr ptr;\n\
    \n    void fix() { prio_ = std::max(key_prio, prio(ptr)); }\n\n  public:\n   \
    \ mid_type() : prio_(0), key_prio(0), ptr() {}\n  };\n  class node_type {\n  \
    \  friend ternary_treap;\n\n    T key;\n    node_ptr left;\n    mid_type mid;\n\
    \    node_ptr right;\n\n    usize prio() const { return mid.prio_; }\n\n  public:\n\
    \    node_type(const T key) : key(key), left(), mid(), right() {}\n  };\n\n  static\
    \ usize rand() {\n    static std::default_random_engine rng(91);\n    static std::uniform_int_distribution<usize>\
    \ uid(\n        1, std::numeric_limits<usize>::max());\n    return uid(rng);\n\
    \  }\n  static usize prio(const node_ptr &ptr) { return ptr ? ptr->prio() : 0;\
    \ }\n  static void rot_left(node_ptr &ptr) {\n    node_ptr right = std::move(ptr->right);\n\
    \    ptr->right = std::move(right->left);\n    right->left = std::move(ptr);\n\
    \    ptr = std::move(right);\n  }\n  static void rot_right(node_ptr &ptr) {\n\
    \    node_ptr left = std::move(ptr->left);\n    ptr->left = std::move(left->right);\n\
    \    left->right = std::move(ptr);\n    ptr = std::move(left);\n  }\n\n  static\
    \ bool contains(const mid_type &mid, const key_itr f, const key_itr l) {\n   \
    \ if (f == l)\n      return mid.key_prio != 0;\n    return contains(mid.ptr, f,\
    \ l);\n  }\n  static bool contains(const node_ptr &ptr, const key_itr f, const\
    \ key_itr l) {\n    if (!ptr)\n      return false;\n    if (!W::compare(ptr->key,\
    \ *f))\n      return contains(ptr->left, f, l);\n    else if (!W::compare(*f,\
    \ ptr->key))\n      return contains(ptr->right, f, l);\n    else\n      return\
    \ contains(ptr->mid, std::next(f), l);\n  }\n  static void insert(mid_type &mid,\
    \ const key_itr f, const key_itr l) {\n    if (f == l) {\n      if (mid.key_prio\
    \ == 0)\n        mid.key_prio = rand();\n    } else {\n      insert(mid.ptr, f,\
    \ l);\n    }\n    mid.fix();\n  }\n  static void insert(node_ptr &ptr, const key_itr\
    \ f, const key_itr l) {\n    if (!ptr)\n      ptr = std::make_unique<node_type>(*f);\n\
    \    if (!W::compare(ptr->key, *f)) {\n      insert(ptr->left, f, l);\n      if\
    \ (ptr->left->prio() > ptr->prio())\n        rot_right(ptr);\n    } else if (!W::compare(*f,\
    \ ptr->key)) {\n      insert(ptr->right, f, l);\n      if (ptr->right->prio()\
    \ > ptr->prio())\n        rot_left(ptr);\n    } else {\n      insert(ptr->mid,\
    \ std::next(f), l);\n    }\n  }\n  static void erase(mid_type &mid, const key_itr\
    \ f, const key_itr l) {\n    if (f == l) {\n      if (mid.key_prio != 0)\n   \
    \     mid.key_prio = 0;\n    } else {\n      erase(mid.ptr, f, l);\n    }\n  \
    \  mid.fix();\n  }\n  static void erase(node_ptr &ptr, const key_itr f, const\
    \ key_itr l) {\n    if (!ptr)\n      return;\n    if (!W::compare(ptr->key, *f))\
    \ {\n      erase(ptr->left, f, l);\n    } else if (!W::compare(*f, ptr->key))\
    \ {\n      erase(ptr->right, f, l);\n    } else {\n      erase(ptr->mid, std::next(f),\
    \ l);\n      heapify(ptr);\n    }\n  }\n  static void heapify(node_ptr &ptr) {\n\
    \    if (prio(ptr->left) > ptr->prio() || prio(ptr->right) > ptr->prio()) {\n\
    \      if (prio(ptr->left) >= prio(ptr->right)) {\n        rot_right(ptr);\n \
    \       heapify(ptr->right);\n      } else {\n        rot_left(ptr);\n       \
    \ heapify(ptr->left);\n      }\n    } else {\n      if (ptr->prio() == 0)\n  \
    \      ptr.reset();\n    }\n  }\n\n  mid_type root;\n\npublic:\n  ternary_treap()\
    \ = default;\n\n  bool empty() const { return root.prio == 0; }\n\n  bool contains(const\
    \ key_type x) const {\n    return contains(root, x.cbegin(), x.cend());\n  }\n\
    \n  void insert(const std::vector<T> x) { insert(root, x.cbegin(), x.cend());\
    \ }\n  void erase(const std::vector<T> x) { erase(root, x.cbegin(), x.cend());\
    \ }\n};\n\n/**\n * @brief Ternary Treap\n * @see https://scrapbox.io/data-structures/Ternary_Search_Tree\n\
    \ */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/ternary_treap.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/ternary_treap.cpp
layout: document
redirect_from:
- /library/data_structure/ternary_treap.cpp
- /library/data_structure/ternary_treap.cpp.html
title: Ternary Treap
---
