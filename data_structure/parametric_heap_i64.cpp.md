---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    _deprecated_at_docs: docs/parametric_heap_i64.md
    document_title: Parametric Heap i64
    links: []
  bundledCode: "#line 1 \"data_structure/parametric_heap_i64.cpp\"\n#include <algorithm>\r\
    \n#include <cassert>\r\n#include <cstddef>\r\n#include <cstdint>\r\n#include <memory>\r\
    \n#include <set>\r\n#include <utility>\r\n\r\nclass parametric_heap {\r\n  using\
    \ i64 = std::int64_t;\r\n\r\n  static constexpr i64 floor_div(const i64 n, const\
    \ i64 d) {\r\n    return n / d + ((n ^ d) < 0 && n % d);\r\n  }\r\n\r\n  class\
    \ line {\r\n  public:\r\n    i64 a;\r\n    i64 b;\r\n\r\n    line(const i64 a_,\
    \ const i64 b_) : a(a_), b(b_) {}\r\n  };\r\n\r\n  class node_type;\r\n\r\n  using\
    \ link_type = std::unique_ptr<node_type>;\r\n\r\n  class leaf_type {\r\n  public:\r\
    \n    i64 a;\r\n    std::multiset<i64> b;\r\n\r\n    leaf_type(const i64 a_, const\
    \ i64 b_) : a(a_), b({b_}) {}\r\n\r\n    i64 eval(const i64 x) const { return\
    \ a * x + (*b.begin()); }\r\n    line get() const { return line(a, *b.begin());\
    \ }\r\n  };\r\n\r\n  class internal_type {\r\n  public:\r\n    link_type left;\r\
    \n    link_type right;\r\n    i64 x;\r\n    i64 y;\r\n\r\n    internal_type(link_type\
    \ l, link_type r)\r\n        : left(std::move(l)), right(std::move(r)), lc(&left->data.leaf),\r\
    \n          rc(&right->data.leaf) {}\r\n\r\n    std::ptrdiff_t bias() const {\r\
    \n      return static_cast<std::ptrdiff_t>(left->rank) -\r\n             static_cast<std::ptrdiff_t>(right->rank);\r\
    \n    }\r\n  };\r\n\r\n  class node_type {\r\n  public:\r\n    std::size_t rank;\r\
    \n    i64 la;\r\n    union data_t {\r\n      leaf_type leaf;\r\n      internal_type\
    \ internal;\r\n\r\n      data_t() {}\r\n      ~data_t() {}\r\n    } data;\r\n\r\
    \n    node_type(node_type &&x) : rank(x.rank), la(x.la), data() {\r\n      if\
    \ (x.is_leaf()) {\r\n        new (&data.leaf) leaf_type(std::move(x.data.leaf));\r\
    \n      } else {\r\n        new (&data.internal) internal_type(std::move(x.data.internal));\r\
    \n      }\r\n    }\r\n\r\n    node_type(const i64 a, const i64 b) : rank(0), data()\
    \ {\r\n      new (&data.leaf) leaf_type(a, b);\r\n    }\r\n\r\n    node_type(link_type\
    \ l, link_type r) : rank(1), data() {\r\n      new (&data.internal) internal_type(std::move(l),\
    \ std::move(r));\r\n    }\r\n\r\n    bool is_leaf() const { return rank == 0;\
    \ }\r\n    bool is_internal() const { return rank != 0; }\r\n\r\n    ~node_type()\
    \ {\r\n      if (is_leaf()) {\r\n        data.leaf.~leaf_type();\r\n      } else\
    \ {\r\n        data.internal.~internal_type();\r\n      }\r\n    }\r\n  };\r\n\
    \r\n  link_type root;\r\n\r\n  void update_node(node_type &node) const {\r\n \
    \   internal_type &internal = node.data.internal;\r\n    node.rank = std::max(internal.left->rank,\
    \ internal.right->rank) + 1;\r\n    cont i64 m = internal.right.la;\r\n    const\
    \ node_type *l = internal.left.get();\r\n    const node_type *r = internal.right.get();\r\
    \n    while (true) {\r\n      if (l->is_leaf()) {\r\n        if (r->is_leaf())\
    \ {\r\n          break;\r\n        } else {\r\n          const internal_type &r_in\
    \ = r->data.internal;\r\n          if (l->data.leaf.eval(r_in.x) > r_in.y) {\r\
    \n            r = r_in.left.get();\r\n          } else {\r\n            r = r_in.right.get();\r\
    \n          }\r\n        }\r\n      } else {\r\n        const internal_type &l_in\
    \ = l->data.internal;\r\n        if (r->is_leaf()) {\r\n          if(r->data.leaf.eval(l_in.x)<l_in.y){\r\
    \n            \r\n          }\r\n          if (is_necessary(ll, lr, r->data.leaf.get()))\
    \ {\r\n            l = l_in.right.get();\r\n          } else {\r\n           \
    \ l = l_in.left.get();\r\n          }\r\n        } else {\r\n          const internal_type\
    \ &r_in = r->data.internal;\r\n          const line &rl = r_in.lc->get();\r\n\
    \          const line &rr = r_in.rc->get();\r\n          if (!is_necessary(ll,\
    \ lr, rl)) {\r\n            l = l_in.left.get();\r\n          } else if (!is_necessary(lr,\
    \ rl, rr)) {\r\n            r = r_in.right.get();\r\n          } else if (left_discard(ll,\
    \ lr, rl, rr, m)) {\r\n            l = l_in.right.get();\r\n          } else {\r\
    \n            r = r_in.left.get();\r\n          }\r\n        }\r\n      }\r\n\
    \    }\r\n    internal.lc = &l->data.leaf;\r\n    internal.rc = &r->data.leaf;\r\
    \n  }\r\n\r\n  void rotate_left(link_type &ptr) const {\r\n    link_type right\
    \ = std::move(ptr->data.internal.right);\r\n    ptr->data.internal.right = std::move(right->data.internal.left);\r\
    \n    update_node(*ptr);\r\n    right->data.internal.left = std::move(ptr);\r\n\
    \    ptr = std::move(right);\r\n  }\r\n\r\n  void rotate_right(link_type &ptr)\
    \ const {\r\n    link_type left = std::move(ptr->data.internal.left);\r\n    ptr->data.internal.left\
    \ = std::move(left->data.internal.right);\r\n    update_node(*ptr);\r\n    left->data.internal.right\
    \ = std::move(ptr);\r\n    ptr = std::move(left);\r\n  }\r\n\r\n  void balance(link_type\
    \ &ptr) const {\r\n    internal_type &internal = ptr->data.internal;\r\n    const\
    \ std::size_t bias = internal.bias();\r\n    if (bias == 2) {\r\n      if (internal.left->data.internal.bias()\
    \ == -2) {\r\n        rotate_left(internal.left);\r\n      }\r\n      rotate_right(ptr);\r\
    \n    } else if (bias == -2) {\r\n      if (internal.right->data.internal.bias()\
    \ == 2) {\r\n        rotate_right(internal.right);\r\n      }\r\n      rotate_left(ptr);\r\
    \n    }\r\n    update_node(*ptr);\r\n  }\r\n\r\npublic:\r\n  explicit parametric_heap(const\
    \ Compare comp_ = Compare())\r\n      : comp(comp_), root() {}\r\n\r\n  bool empty()\
    \ const { return !static_cast<bool>(root); }\r\n\r\n  void insert(const T &a,\
    \ const T &b) {\r\n    if (empty()) {\r\n      root = std::make_unique<node_type>(node_type(a,\
    \ b, comp));\r\n      return;\r\n    }\r\n    const auto insert_rec = [&](const\
    \ auto &self, link_type &ptr) -> void {\r\n      if (ptr->is_leaf()) {\r\n   \
    \     leaf_type &leaf = ptr->data.leaf;\r\n        if (comp_f(leaf.a, a)) {\r\n\
    \          ptr = std::make_unique<node_type>(\r\n              node_type(std::make_unique<node_type>(node_type(a,\
    \ b, comp)),\r\n                        std::move(ptr)));\r\n        } else if\
    \ (comp_f(a, leaf.a)) {\r\n          ptr = std::make_unique<node_type>(\r\n  \
    \            node_type(std::move(ptr),\r\n                        std::make_unique<node_type>(node_type(a,\
    \ b, comp))));\r\n        } else {\r\n          leaf.b.insert(b);\r\n        }\r\
    \n        return;\r\n      }\r\n      internal_type &internal = ptr->data.internal;\r\
    \n      if (comp_f(internal.get_mid(), a)) {\r\n        self(self, internal.left);\r\
    \n      } else {\r\n        self(self, internal.right);\r\n      }\r\n      balance(ptr);\r\
    \n    };\r\n    insert_rec(insert_rec, root);\r\n  }\r\n\r\n  bool erase(const\
    \ T &a, const T &b) {\r\n    if (empty()) {\r\n      return false;\r\n    }\r\n\
    \    bool res = false;\r\n    const auto erase_rec = [&](const auto &self, link_type\
    \ &ptr) -> void {\r\n      if (ptr->is_leaf()) {\r\n        leaf_type &leaf =\
    \ ptr->data.leaf;\r\n        if (!comp_f(leaf.a, a) && !comp_f(a, leaf.a)) {\r\
    \n          const auto itr = leaf.b.find(b);\r\n          if (itr != leaf.b.end())\
    \ {\r\n            res = true;\r\n            leaf.b.erase(itr);\r\n         \
    \   if (leaf.b.empty()) {\r\n              ptr.reset();\r\n            }\r\n \
    \         }\r\n        }\r\n        return;\r\n      }\r\n      internal_type\
    \ &internal = ptr->data.internal;\r\n      if (comp_f(internal.get_mid(), a))\
    \ {\r\n        self(self, internal.left);\r\n        if (!internal.left) {\r\n\
    \          ptr = std::move(internal.right);\r\n          return;\r\n        }\r\
    \n      } else {\r\n        self(self, internal.right);\r\n        if (!internal.right)\
    \ {\r\n          ptr = std::move(internal.left);\r\n          return;\r\n    \
    \    }\r\n      }\r\n      balance(ptr);\r\n    };\r\n    erase_rec(erase_rec,\
    \ root);\r\n    return res;\r\n  }\r\n\r\n  i64 min(const i64 x) const {\r\n \
    \   assert(!empty());\r\n\r\n    const node_type *ptr = root.get();\r\n    while\
    \ (ptr->is_internal()) {\r\n      const internal_type &internal = ptr->data.internal;\r\
    \n      if (x <= internal.x) {\r\n        ptr = internal.left.get();\r\n     \
    \ } else {\r\n        ptr = internal.right.get();\r\n      }\r\n    }\r\n\r\n\
    \    return ptr->data.leaf.eval(x);\r\n  }\r\n};\r\n\r\n/**\r\n * @brief Parametric\
    \ Heap i64\r\n * @docs docs/parametric_heap_i64.md\r\n */\r\n\r\n/*\r\n\r\nReference\r\
    \n\r\n[1] Overmars, M. H., & Van Leeuwen, J. (1981).\r\n    Maintenance of configurations\
    \ in the plane.\r\n    Journal of computer and System Sciences, 23(2), 166-204.\r\
    \n\r\n[2] Kaplan, H., Tarjan, R. E., & Tsioutsiouliklis, K. (2001, January).\r\
    \n    Faster kinetic heaps and their use in broadcast scheduling.\r\n    In SODA\
    \ (Vol. 1, pp. 836-844).\r\n\r\n*/\r\n"
  code: "#include <algorithm>\r\n#include <cassert>\r\n#include <cstddef>\r\n#include\
    \ <cstdint>\r\n#include <memory>\r\n#include <set>\r\n#include <utility>\r\n\r\
    \nclass parametric_heap {\r\n  using i64 = std::int64_t;\r\n\r\n  static constexpr\
    \ i64 floor_div(const i64 n, const i64 d) {\r\n    return n / d + ((n ^ d) < 0\
    \ && n % d);\r\n  }\r\n\r\n  class line {\r\n  public:\r\n    i64 a;\r\n    i64\
    \ b;\r\n\r\n    line(const i64 a_, const i64 b_) : a(a_), b(b_) {}\r\n  };\r\n\
    \r\n  class node_type;\r\n\r\n  using link_type = std::unique_ptr<node_type>;\r\
    \n\r\n  class leaf_type {\r\n  public:\r\n    i64 a;\r\n    std::multiset<i64>\
    \ b;\r\n\r\n    leaf_type(const i64 a_, const i64 b_) : a(a_), b({b_}) {}\r\n\r\
    \n    i64 eval(const i64 x) const { return a * x + (*b.begin()); }\r\n    line\
    \ get() const { return line(a, *b.begin()); }\r\n  };\r\n\r\n  class internal_type\
    \ {\r\n  public:\r\n    link_type left;\r\n    link_type right;\r\n    i64 x;\r\
    \n    i64 y;\r\n\r\n    internal_type(link_type l, link_type r)\r\n        : left(std::move(l)),\
    \ right(std::move(r)), lc(&left->data.leaf),\r\n          rc(&right->data.leaf)\
    \ {}\r\n\r\n    std::ptrdiff_t bias() const {\r\n      return static_cast<std::ptrdiff_t>(left->rank)\
    \ -\r\n             static_cast<std::ptrdiff_t>(right->rank);\r\n    }\r\n  };\r\
    \n\r\n  class node_type {\r\n  public:\r\n    std::size_t rank;\r\n    i64 la;\r\
    \n    union data_t {\r\n      leaf_type leaf;\r\n      internal_type internal;\r\
    \n\r\n      data_t() {}\r\n      ~data_t() {}\r\n    } data;\r\n\r\n    node_type(node_type\
    \ &&x) : rank(x.rank), la(x.la), data() {\r\n      if (x.is_leaf()) {\r\n    \
    \    new (&data.leaf) leaf_type(std::move(x.data.leaf));\r\n      } else {\r\n\
    \        new (&data.internal) internal_type(std::move(x.data.internal));\r\n \
    \     }\r\n    }\r\n\r\n    node_type(const i64 a, const i64 b) : rank(0), data()\
    \ {\r\n      new (&data.leaf) leaf_type(a, b);\r\n    }\r\n\r\n    node_type(link_type\
    \ l, link_type r) : rank(1), data() {\r\n      new (&data.internal) internal_type(std::move(l),\
    \ std::move(r));\r\n    }\r\n\r\n    bool is_leaf() const { return rank == 0;\
    \ }\r\n    bool is_internal() const { return rank != 0; }\r\n\r\n    ~node_type()\
    \ {\r\n      if (is_leaf()) {\r\n        data.leaf.~leaf_type();\r\n      } else\
    \ {\r\n        data.internal.~internal_type();\r\n      }\r\n    }\r\n  };\r\n\
    \r\n  link_type root;\r\n\r\n  void update_node(node_type &node) const {\r\n \
    \   internal_type &internal = node.data.internal;\r\n    node.rank = std::max(internal.left->rank,\
    \ internal.right->rank) + 1;\r\n    cont i64 m = internal.right.la;\r\n    const\
    \ node_type *l = internal.left.get();\r\n    const node_type *r = internal.right.get();\r\
    \n    while (true) {\r\n      if (l->is_leaf()) {\r\n        if (r->is_leaf())\
    \ {\r\n          break;\r\n        } else {\r\n          const internal_type &r_in\
    \ = r->data.internal;\r\n          if (l->data.leaf.eval(r_in.x) > r_in.y) {\r\
    \n            r = r_in.left.get();\r\n          } else {\r\n            r = r_in.right.get();\r\
    \n          }\r\n        }\r\n      } else {\r\n        const internal_type &l_in\
    \ = l->data.internal;\r\n        if (r->is_leaf()) {\r\n          if(r->data.leaf.eval(l_in.x)<l_in.y){\r\
    \n            \r\n          }\r\n          if (is_necessary(ll, lr, r->data.leaf.get()))\
    \ {\r\n            l = l_in.right.get();\r\n          } else {\r\n           \
    \ l = l_in.left.get();\r\n          }\r\n        } else {\r\n          const internal_type\
    \ &r_in = r->data.internal;\r\n          const line &rl = r_in.lc->get();\r\n\
    \          const line &rr = r_in.rc->get();\r\n          if (!is_necessary(ll,\
    \ lr, rl)) {\r\n            l = l_in.left.get();\r\n          } else if (!is_necessary(lr,\
    \ rl, rr)) {\r\n            r = r_in.right.get();\r\n          } else if (left_discard(ll,\
    \ lr, rl, rr, m)) {\r\n            l = l_in.right.get();\r\n          } else {\r\
    \n            r = r_in.left.get();\r\n          }\r\n        }\r\n      }\r\n\
    \    }\r\n    internal.lc = &l->data.leaf;\r\n    internal.rc = &r->data.leaf;\r\
    \n  }\r\n\r\n  void rotate_left(link_type &ptr) const {\r\n    link_type right\
    \ = std::move(ptr->data.internal.right);\r\n    ptr->data.internal.right = std::move(right->data.internal.left);\r\
    \n    update_node(*ptr);\r\n    right->data.internal.left = std::move(ptr);\r\n\
    \    ptr = std::move(right);\r\n  }\r\n\r\n  void rotate_right(link_type &ptr)\
    \ const {\r\n    link_type left = std::move(ptr->data.internal.left);\r\n    ptr->data.internal.left\
    \ = std::move(left->data.internal.right);\r\n    update_node(*ptr);\r\n    left->data.internal.right\
    \ = std::move(ptr);\r\n    ptr = std::move(left);\r\n  }\r\n\r\n  void balance(link_type\
    \ &ptr) const {\r\n    internal_type &internal = ptr->data.internal;\r\n    const\
    \ std::size_t bias = internal.bias();\r\n    if (bias == 2) {\r\n      if (internal.left->data.internal.bias()\
    \ == -2) {\r\n        rotate_left(internal.left);\r\n      }\r\n      rotate_right(ptr);\r\
    \n    } else if (bias == -2) {\r\n      if (internal.right->data.internal.bias()\
    \ == 2) {\r\n        rotate_right(internal.right);\r\n      }\r\n      rotate_left(ptr);\r\
    \n    }\r\n    update_node(*ptr);\r\n  }\r\n\r\npublic:\r\n  explicit parametric_heap(const\
    \ Compare comp_ = Compare())\r\n      : comp(comp_), root() {}\r\n\r\n  bool empty()\
    \ const { return !static_cast<bool>(root); }\r\n\r\n  void insert(const T &a,\
    \ const T &b) {\r\n    if (empty()) {\r\n      root = std::make_unique<node_type>(node_type(a,\
    \ b, comp));\r\n      return;\r\n    }\r\n    const auto insert_rec = [&](const\
    \ auto &self, link_type &ptr) -> void {\r\n      if (ptr->is_leaf()) {\r\n   \
    \     leaf_type &leaf = ptr->data.leaf;\r\n        if (comp_f(leaf.a, a)) {\r\n\
    \          ptr = std::make_unique<node_type>(\r\n              node_type(std::make_unique<node_type>(node_type(a,\
    \ b, comp)),\r\n                        std::move(ptr)));\r\n        } else if\
    \ (comp_f(a, leaf.a)) {\r\n          ptr = std::make_unique<node_type>(\r\n  \
    \            node_type(std::move(ptr),\r\n                        std::make_unique<node_type>(node_type(a,\
    \ b, comp))));\r\n        } else {\r\n          leaf.b.insert(b);\r\n        }\r\
    \n        return;\r\n      }\r\n      internal_type &internal = ptr->data.internal;\r\
    \n      if (comp_f(internal.get_mid(), a)) {\r\n        self(self, internal.left);\r\
    \n      } else {\r\n        self(self, internal.right);\r\n      }\r\n      balance(ptr);\r\
    \n    };\r\n    insert_rec(insert_rec, root);\r\n  }\r\n\r\n  bool erase(const\
    \ T &a, const T &b) {\r\n    if (empty()) {\r\n      return false;\r\n    }\r\n\
    \    bool res = false;\r\n    const auto erase_rec = [&](const auto &self, link_type\
    \ &ptr) -> void {\r\n      if (ptr->is_leaf()) {\r\n        leaf_type &leaf =\
    \ ptr->data.leaf;\r\n        if (!comp_f(leaf.a, a) && !comp_f(a, leaf.a)) {\r\
    \n          const auto itr = leaf.b.find(b);\r\n          if (itr != leaf.b.end())\
    \ {\r\n            res = true;\r\n            leaf.b.erase(itr);\r\n         \
    \   if (leaf.b.empty()) {\r\n              ptr.reset();\r\n            }\r\n \
    \         }\r\n        }\r\n        return;\r\n      }\r\n      internal_type\
    \ &internal = ptr->data.internal;\r\n      if (comp_f(internal.get_mid(), a))\
    \ {\r\n        self(self, internal.left);\r\n        if (!internal.left) {\r\n\
    \          ptr = std::move(internal.right);\r\n          return;\r\n        }\r\
    \n      } else {\r\n        self(self, internal.right);\r\n        if (!internal.right)\
    \ {\r\n          ptr = std::move(internal.left);\r\n          return;\r\n    \
    \    }\r\n      }\r\n      balance(ptr);\r\n    };\r\n    erase_rec(erase_rec,\
    \ root);\r\n    return res;\r\n  }\r\n\r\n  i64 min(const i64 x) const {\r\n \
    \   assert(!empty());\r\n\r\n    const node_type *ptr = root.get();\r\n    while\
    \ (ptr->is_internal()) {\r\n      const internal_type &internal = ptr->data.internal;\r\
    \n      if (x <= internal.x) {\r\n        ptr = internal.left.get();\r\n     \
    \ } else {\r\n        ptr = internal.right.get();\r\n      }\r\n    }\r\n\r\n\
    \    return ptr->data.leaf.eval(x);\r\n  }\r\n};\r\n\r\n/**\r\n * @brief Parametric\
    \ Heap i64\r\n * @docs docs/parametric_heap_i64.md\r\n */\r\n\r\n/*\r\n\r\nReference\r\
    \n\r\n[1] Overmars, M. H., & Van Leeuwen, J. (1981).\r\n    Maintenance of configurations\
    \ in the plane.\r\n    Journal of computer and System Sciences, 23(2), 166-204.\r\
    \n\r\n[2] Kaplan, H., Tarjan, R. E., & Tsioutsiouliklis, K. (2001, January).\r\
    \n    Faster kinetic heaps and their use in broadcast scheduling.\r\n    In SODA\
    \ (Vol. 1, pp. 836-844).\r\n\r\n*/\r\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/parametric_heap_i64.cpp
  requiredBy: []
  timestamp: '2023-02-25 07:41:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/parametric_heap_i64.cpp
layout: document
redirect_from:
- /library/data_structure/parametric_heap_i64.cpp
- /library/data_structure/parametric_heap_i64.cpp.html
title: Parametric Heap i64
---
