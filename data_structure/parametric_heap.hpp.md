---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/parametric_heap.test.cpp
    title: test/parametric_heap.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/parametric_heap.md
    document_title: Parametric Heap
    links: []
  bundledCode: "#line 1 \"data_structure/parametric_heap.hpp\"\n#include <algorithm>\r\
    \n#include <cstddef>\r\n#include <cstdlib>\r\n#include <functional>\r\n#include\
    \ <memory>\r\n#include <set>\r\n#include <utility>\r\n\r\ntemplate <class T, bool\
    \ Minimize = true, class Compare = std::less<T>>\r\nclass parametric_heap {\r\n\
    \  template <bool M, class V> class comp_helper {\r\n  public:\r\n    static bool\
    \ call(const Compare &comp, const T &l, const T &r) {\r\n      return comp(l,\
    \ r);\r\n    }\r\n  };\r\n\r\n  template <class V> class comp_helper<false, V>\
    \ {\r\n  public:\r\n    static bool call(const Compare &comp, const T &l, const\
    \ T &r) {\r\n      return comp(r, l);\r\n    }\r\n  };\r\n\r\n  class line_t {\r\
    \n  public:\r\n    T a;\r\n    T b;\r\n\r\n    line_t(T a_, T b_) : a(std::move(a_)),\
    \ b(std::move(b_)) {}\r\n  };\r\n\r\n  class node_t;\r\n\r\n  using link_t = std::unique_ptr<node_t>;\r\
    \n\r\n  class leaf_t {\r\n    class F {\r\n      Compare comp;\r\n\r\n    public:\r\
    \n      F(const Compare &comp) : comp(comp) {}\r\n\r\n      bool operator()(const\
    \ T &l, const T &r) const {\r\n        return comp_helper<Minimize, void>::call(comp,\
    \ l, r);\r\n      }\r\n    };\r\n\r\n  public:\r\n    T a;\r\n    std::multiset<T,\
    \ F> b;\r\n\r\n    leaf_t(T a_, T b_, const Compare &comp) : a(std::move(a_)),\
    \ b(F(comp)) {\r\n      b.insert(std::move(b_));\r\n    }\r\n\r\n    T eval(const\
    \ T &x) const { return a * x + (*b.begin()); }\r\n    line_t get() const { return\
    \ line_t(a, *b.begin()); }\r\n  };\r\n\r\n  class internal_t {\r\n  public:\r\n\
    \    link_t left;\r\n    link_t right;\r\n    const leaf_t *lc;\r\n    const leaf_t\
    \ *rc;\r\n\r\n    internal_t(link_t l, link_t r)\r\n        : left(std::move(l)),\
    \ right(std::move(r)), lc(&left->data.leaf),\r\n          rc(&right->data.leaf)\
    \ {}\r\n\r\n    std::ptrdiff_t bias() const {\r\n      return static_cast<std::ptrdiff_t>(left->rank)\
    \ -\r\n             static_cast<std::ptrdiff_t>(right->rank);\r\n    }\r\n\r\n\
    \    const T &get_mid() const {\r\n      const node_t *ptr = right.get();\r\n\
    \      while (ptr->is_internal()) {\r\n        ptr = ptr->data.internal.left.get();\r\
    \n      }\r\n      return ptr->data.leaf.a;\r\n    }\r\n  };\r\n\r\n  class node_t\
    \ {\r\n  public:\r\n    std::size_t rank;\r\n    union data_t {\r\n      leaf_t\
    \ leaf;\r\n      internal_t internal;\r\n\r\n      data_t() {}\r\n      ~data_t()\
    \ {}\r\n    } data;\r\n\r\n    node_t(node_t &&x) : rank(x.rank), data() {\r\n\
    \      if (x.is_leaf()) {\r\n        new (&data.leaf) leaf_t(std::move(x.data.leaf));\r\
    \n      } else {\r\n        new (&data.internal) internal_t(std::move(x.data.internal));\r\
    \n      }\r\n    }\r\n\r\n    node_t(T a, T b, const Compare &comp) : rank(0),\
    \ data() {\r\n      new (&data.leaf) leaf_t(std::move(a), std::move(b), comp);\r\
    \n    }\r\n\r\n    node_t(link_t l, link_t r) : rank(1), data() {\r\n      new\
    \ (&data.internal) internal_t(std::move(l), std::move(r));\r\n    }\r\n\r\n  \
    \  bool is_leaf() const { return rank == 0; }\r\n    bool is_internal() const\
    \ { return rank != 0; }\r\n\r\n    ~node_t() {\r\n      if (is_leaf()) {\r\n \
    \       data.leaf.~leaf_t();\r\n      } else {\r\n        data.internal.~internal_t();\r\
    \n      }\r\n    }\r\n  };\r\n\r\n  Compare comp;\r\n  link_t root;\r\n\r\n  bool\
    \ comp_f(const T &l, const T &r) const {\r\n    return comp_helper<Minimize, void>::call(comp,\
    \ l, r);\r\n  }\r\n\r\n  bool is_necessary(const line_t &x, const line_t &y, const\
    \ line_t &z) const {\r\n    return comp(y.a * z.b + z.a * x.b + x.a * y.b,\r\n\
    \                z.a * y.b + x.a * z.b + y.a * x.b);\r\n  }\r\n\r\n  bool left_discard(const\
    \ line_t &x, const line_t &y, const line_t &z,\r\n                    const line_t\
    \ &w, const T &m) const {\r\n    return comp_f(\r\n        x.a * y.b * z.a + x.b\
    \ * y.a * w.a + x.a * z.b * w.a + y.a * z.a * w.b +\r\n            m * (x.b *\
    \ z.a + x.a * w.b + y.a * z.b + y.b * w.a),\r\n        x.b * y.a * z.a + x.a *\
    \ y.b * w.a + x.a * z.a * w.b + y.a * z.b * w.a +\r\n            m * (x.a * z.b\
    \ + x.b * w.a + y.b * z.a + y.a * w.b));\r\n  }\r\n\r\n  void update_node(node_t\
    \ &node) const {\r\n    internal_t &internal = node.data.internal;\r\n    node.rank\
    \ = std::max(internal.left->rank, internal.right->rank) + 1;\r\n    const T &m\
    \ = internal.get_mid();\r\n    const node_t *l = internal.left.get();\r\n    const\
    \ node_t *r = internal.right.get();\r\n    while (true) {\r\n      if (l->is_leaf())\
    \ {\r\n        if (r->is_leaf()) {\r\n          break;\r\n        } else {\r\n\
    \          const internal_t &r_in = r->data.internal;\r\n          if (is_necessary(l->data.leaf.get(),\
    \ r_in.lc->get(),\r\n                           r_in.rc->get())) {\r\n       \
    \     r = r_in.left.get();\r\n          } else {\r\n            r = r_in.right.get();\r\
    \n          }\r\n        }\r\n      } else {\r\n        const internal_t &l_in\
    \ = l->data.internal;\r\n        const line_t &ll = l_in.lc->get();\r\n      \
    \  const line_t &lr = l_in.rc->get();\r\n        if (r->is_leaf()) {\r\n     \
    \     if (is_necessary(ll, lr, r->data.leaf.get())) {\r\n            l = l_in.right.get();\r\
    \n          } else {\r\n            l = l_in.left.get();\r\n          }\r\n  \
    \      } else {\r\n          const internal_t &r_in = r->data.internal;\r\n  \
    \        const line_t &rl = r_in.lc->get();\r\n          const line_t &rr = r_in.rc->get();\r\
    \n          if (!is_necessary(ll, lr, rl)) {\r\n            l = l_in.left.get();\r\
    \n          } else if (!is_necessary(lr, rl, rr)) {\r\n            r = r_in.right.get();\r\
    \n          } else if (left_discard(ll, lr, rl, rr, m)) {\r\n            l = l_in.right.get();\r\
    \n          } else {\r\n            r = r_in.left.get();\r\n          }\r\n  \
    \      }\r\n      }\r\n    }\r\n    internal.lc = &l->data.leaf;\r\n    internal.rc\
    \ = &r->data.leaf;\r\n  }\r\n\r\n  void rotate_left(link_t &ptr) const {\r\n \
    \   link_t right = std::move(ptr->data.internal.right);\r\n    ptr->data.internal.right\
    \ = std::move(right->data.internal.left);\r\n    update_node(*ptr);\r\n    right->data.internal.left\
    \ = std::move(ptr);\r\n    ptr = std::move(right);\r\n  }\r\n\r\n  void rotate_right(link_t\
    \ &ptr) const {\r\n    link_t left = std::move(ptr->data.internal.left);\r\n \
    \   ptr->data.internal.left = std::move(left->data.internal.right);\r\n    update_node(*ptr);\r\
    \n    left->data.internal.right = std::move(ptr);\r\n    ptr = std::move(left);\r\
    \n  }\r\n\r\n  void balance(link_t &ptr) const {\r\n    internal_t &internal =\
    \ ptr->data.internal;\r\n    const std::size_t bias = internal.bias();\r\n   \
    \ if (bias == 2) {\r\n      if (internal.left->data.internal.bias() == -2) {\r\
    \n        rotate_left(internal.left);\r\n      }\r\n      rotate_right(ptr);\r\
    \n    } else if (bias == -2) {\r\n      if (internal.right->data.internal.bias()\
    \ == 2) {\r\n        rotate_right(internal.right);\r\n      }\r\n      rotate_left(ptr);\r\
    \n    }\r\n    update_node(*ptr);\r\n  }\r\n\r\npublic:\r\n  explicit parametric_heap(const\
    \ Compare comp_ = Compare())\r\n      : comp(comp_), root() {}\r\n\r\n  bool empty()\
    \ const { return !static_cast<bool>(root); }\r\n\r\n  void insert(const T &a,\
    \ const T &b) {\r\n    if (empty()) {\r\n      root = std::make_unique<node_t>(node_t(a,\
    \ b, comp));\r\n      return;\r\n    }\r\n    const auto insert_rec = [&](const\
    \ auto &self, link_t &ptr) -> void {\r\n      if (ptr->is_leaf()) {\r\n      \
    \  leaf_t &leaf = ptr->data.leaf;\r\n        if (comp_f(leaf.a, a)) {\r\n    \
    \      ptr = std::make_unique<node_t>(node_t(\r\n              std::make_unique<node_t>(node_t(a,\
    \ b, comp)), std::move(ptr)));\r\n        } else if (comp_f(a, leaf.a)) {\r\n\
    \          ptr = std::make_unique<node_t>(node_t(\r\n              std::move(ptr),\
    \ std::make_unique<node_t>(node_t(a, b, comp))));\r\n        } else {\r\n    \
    \      leaf.b.insert(b);\r\n        }\r\n        return;\r\n      }\r\n      internal_t\
    \ &internal = ptr->data.internal;\r\n      if (comp_f(internal.get_mid(), a))\
    \ {\r\n        self(self, internal.left);\r\n      } else {\r\n        self(self,\
    \ internal.right);\r\n      }\r\n      balance(ptr);\r\n    };\r\n    insert_rec(insert_rec,\
    \ root);\r\n  }\r\n\r\n  bool erase(const T &a, const T &b) {\r\n    if (empty())\
    \ {\r\n      return false;\r\n    }\r\n    bool res = false;\r\n    const auto\
    \ erase_rec = [&](const auto &self, link_t &ptr) -> void {\r\n      if (ptr->is_leaf())\
    \ {\r\n        leaf_t &leaf = ptr->data.leaf;\r\n        if (!comp_f(leaf.a, a)\
    \ && !comp_f(a, leaf.a)) {\r\n          const auto itr = leaf.b.find(b);\r\n \
    \         if (itr != leaf.b.end()) {\r\n            res = true;\r\n          \
    \  leaf.b.erase(itr);\r\n            if (leaf.b.empty()) {\r\n              ptr.reset();\r\
    \n            }\r\n          }\r\n        }\r\n        return;\r\n      }\r\n\
    \      internal_t &internal = ptr->data.internal;\r\n      if (comp_f(internal.get_mid(),\
    \ a)) {\r\n        self(self, internal.left);\r\n        if (!internal.left) {\r\
    \n          ptr = std::move(internal.right);\r\n          return;\r\n        }\r\
    \n      } else {\r\n        self(self, internal.right);\r\n        if (!internal.right)\
    \ {\r\n          ptr = std::move(internal.left);\r\n          return;\r\n    \
    \    }\r\n      }\r\n      balance(ptr);\r\n    };\r\n    erase_rec(erase_rec,\
    \ root);\r\n    return res;\r\n  }\r\n\r\n  std::pair<T, T> top(const T &x) const\
    \ {\r\n    if (empty()) {\r\n      std::abort();\r\n    }\r\n\r\n    const node_t\
    \ *ptr = root.get();\r\n    while (ptr->is_internal()) {\r\n      const internal_t\
    \ &internal = ptr->data.internal;\r\n      if (comp_f(internal.lc->eval(x), internal.rc->eval(x)))\
    \ {\r\n        ptr = internal.left.get();\r\n      } else {\r\n        ptr = internal.right.get();\r\
    \n      }\r\n    }\r\n    const leaf_t &leaf = ptr->data.leaf;\r\n    return std::pair<T,\
    \ T>(leaf.a, *leaf.b.begin());\r\n  }\r\n};\r\n\r\n/**\r\n * @brief Parametric\
    \ Heap\r\n * @docs docs/parametric_heap.md\r\n */\r\n\r\n/*\r\n\r\nReference\r\
    \n\r\n[1] Overmars, M. H., & Van Leeuwen, J. (1981).\r\n    Maintenance of configurations\
    \ in the plane.\r\n    Journal of computer and System Sciences, 23(2), 166-204.\r\
    \n\r\n[2] Kaplan, H., Tarjan, R. E., & Tsioutsiouliklis, K. (2001, January).\r\
    \n    Faster kinetic heaps and their use in broadcast scheduling.\r\n    In SODA\
    \ (Vol. 1, pp. 836-844).\r\n\r\n*/\r\n"
  code: "#include <algorithm>\r\n#include <cstddef>\r\n#include <cstdlib>\r\n#include\
    \ <functional>\r\n#include <memory>\r\n#include <set>\r\n#include <utility>\r\n\
    \r\ntemplate <class T, bool Minimize = true, class Compare = std::less<T>>\r\n\
    class parametric_heap {\r\n  template <bool M, class V> class comp_helper {\r\n\
    \  public:\r\n    static bool call(const Compare &comp, const T &l, const T &r)\
    \ {\r\n      return comp(l, r);\r\n    }\r\n  };\r\n\r\n  template <class V> class\
    \ comp_helper<false, V> {\r\n  public:\r\n    static bool call(const Compare &comp,\
    \ const T &l, const T &r) {\r\n      return comp(r, l);\r\n    }\r\n  };\r\n\r\
    \n  class line_t {\r\n  public:\r\n    T a;\r\n    T b;\r\n\r\n    line_t(T a_,\
    \ T b_) : a(std::move(a_)), b(std::move(b_)) {}\r\n  };\r\n\r\n  class node_t;\r\
    \n\r\n  using link_t = std::unique_ptr<node_t>;\r\n\r\n  class leaf_t {\r\n  \
    \  class F {\r\n      Compare comp;\r\n\r\n    public:\r\n      F(const Compare\
    \ &comp) : comp(comp) {}\r\n\r\n      bool operator()(const T &l, const T &r)\
    \ const {\r\n        return comp_helper<Minimize, void>::call(comp, l, r);\r\n\
    \      }\r\n    };\r\n\r\n  public:\r\n    T a;\r\n    std::multiset<T, F> b;\r\
    \n\r\n    leaf_t(T a_, T b_, const Compare &comp) : a(std::move(a_)), b(F(comp))\
    \ {\r\n      b.insert(std::move(b_));\r\n    }\r\n\r\n    T eval(const T &x) const\
    \ { return a * x + (*b.begin()); }\r\n    line_t get() const { return line_t(a,\
    \ *b.begin()); }\r\n  };\r\n\r\n  class internal_t {\r\n  public:\r\n    link_t\
    \ left;\r\n    link_t right;\r\n    const leaf_t *lc;\r\n    const leaf_t *rc;\r\
    \n\r\n    internal_t(link_t l, link_t r)\r\n        : left(std::move(l)), right(std::move(r)),\
    \ lc(&left->data.leaf),\r\n          rc(&right->data.leaf) {}\r\n\r\n    std::ptrdiff_t\
    \ bias() const {\r\n      return static_cast<std::ptrdiff_t>(left->rank) -\r\n\
    \             static_cast<std::ptrdiff_t>(right->rank);\r\n    }\r\n\r\n    const\
    \ T &get_mid() const {\r\n      const node_t *ptr = right.get();\r\n      while\
    \ (ptr->is_internal()) {\r\n        ptr = ptr->data.internal.left.get();\r\n \
    \     }\r\n      return ptr->data.leaf.a;\r\n    }\r\n  };\r\n\r\n  class node_t\
    \ {\r\n  public:\r\n    std::size_t rank;\r\n    union data_t {\r\n      leaf_t\
    \ leaf;\r\n      internal_t internal;\r\n\r\n      data_t() {}\r\n      ~data_t()\
    \ {}\r\n    } data;\r\n\r\n    node_t(node_t &&x) : rank(x.rank), data() {\r\n\
    \      if (x.is_leaf()) {\r\n        new (&data.leaf) leaf_t(std::move(x.data.leaf));\r\
    \n      } else {\r\n        new (&data.internal) internal_t(std::move(x.data.internal));\r\
    \n      }\r\n    }\r\n\r\n    node_t(T a, T b, const Compare &comp) : rank(0),\
    \ data() {\r\n      new (&data.leaf) leaf_t(std::move(a), std::move(b), comp);\r\
    \n    }\r\n\r\n    node_t(link_t l, link_t r) : rank(1), data() {\r\n      new\
    \ (&data.internal) internal_t(std::move(l), std::move(r));\r\n    }\r\n\r\n  \
    \  bool is_leaf() const { return rank == 0; }\r\n    bool is_internal() const\
    \ { return rank != 0; }\r\n\r\n    ~node_t() {\r\n      if (is_leaf()) {\r\n \
    \       data.leaf.~leaf_t();\r\n      } else {\r\n        data.internal.~internal_t();\r\
    \n      }\r\n    }\r\n  };\r\n\r\n  Compare comp;\r\n  link_t root;\r\n\r\n  bool\
    \ comp_f(const T &l, const T &r) const {\r\n    return comp_helper<Minimize, void>::call(comp,\
    \ l, r);\r\n  }\r\n\r\n  bool is_necessary(const line_t &x, const line_t &y, const\
    \ line_t &z) const {\r\n    return comp(y.a * z.b + z.a * x.b + x.a * y.b,\r\n\
    \                z.a * y.b + x.a * z.b + y.a * x.b);\r\n  }\r\n\r\n  bool left_discard(const\
    \ line_t &x, const line_t &y, const line_t &z,\r\n                    const line_t\
    \ &w, const T &m) const {\r\n    return comp_f(\r\n        x.a * y.b * z.a + x.b\
    \ * y.a * w.a + x.a * z.b * w.a + y.a * z.a * w.b +\r\n            m * (x.b *\
    \ z.a + x.a * w.b + y.a * z.b + y.b * w.a),\r\n        x.b * y.a * z.a + x.a *\
    \ y.b * w.a + x.a * z.a * w.b + y.a * z.b * w.a +\r\n            m * (x.a * z.b\
    \ + x.b * w.a + y.b * z.a + y.a * w.b));\r\n  }\r\n\r\n  void update_node(node_t\
    \ &node) const {\r\n    internal_t &internal = node.data.internal;\r\n    node.rank\
    \ = std::max(internal.left->rank, internal.right->rank) + 1;\r\n    const T &m\
    \ = internal.get_mid();\r\n    const node_t *l = internal.left.get();\r\n    const\
    \ node_t *r = internal.right.get();\r\n    while (true) {\r\n      if (l->is_leaf())\
    \ {\r\n        if (r->is_leaf()) {\r\n          break;\r\n        } else {\r\n\
    \          const internal_t &r_in = r->data.internal;\r\n          if (is_necessary(l->data.leaf.get(),\
    \ r_in.lc->get(),\r\n                           r_in.rc->get())) {\r\n       \
    \     r = r_in.left.get();\r\n          } else {\r\n            r = r_in.right.get();\r\
    \n          }\r\n        }\r\n      } else {\r\n        const internal_t &l_in\
    \ = l->data.internal;\r\n        const line_t &ll = l_in.lc->get();\r\n      \
    \  const line_t &lr = l_in.rc->get();\r\n        if (r->is_leaf()) {\r\n     \
    \     if (is_necessary(ll, lr, r->data.leaf.get())) {\r\n            l = l_in.right.get();\r\
    \n          } else {\r\n            l = l_in.left.get();\r\n          }\r\n  \
    \      } else {\r\n          const internal_t &r_in = r->data.internal;\r\n  \
    \        const line_t &rl = r_in.lc->get();\r\n          const line_t &rr = r_in.rc->get();\r\
    \n          if (!is_necessary(ll, lr, rl)) {\r\n            l = l_in.left.get();\r\
    \n          } else if (!is_necessary(lr, rl, rr)) {\r\n            r = r_in.right.get();\r\
    \n          } else if (left_discard(ll, lr, rl, rr, m)) {\r\n            l = l_in.right.get();\r\
    \n          } else {\r\n            r = r_in.left.get();\r\n          }\r\n  \
    \      }\r\n      }\r\n    }\r\n    internal.lc = &l->data.leaf;\r\n    internal.rc\
    \ = &r->data.leaf;\r\n  }\r\n\r\n  void rotate_left(link_t &ptr) const {\r\n \
    \   link_t right = std::move(ptr->data.internal.right);\r\n    ptr->data.internal.right\
    \ = std::move(right->data.internal.left);\r\n    update_node(*ptr);\r\n    right->data.internal.left\
    \ = std::move(ptr);\r\n    ptr = std::move(right);\r\n  }\r\n\r\n  void rotate_right(link_t\
    \ &ptr) const {\r\n    link_t left = std::move(ptr->data.internal.left);\r\n \
    \   ptr->data.internal.left = std::move(left->data.internal.right);\r\n    update_node(*ptr);\r\
    \n    left->data.internal.right = std::move(ptr);\r\n    ptr = std::move(left);\r\
    \n  }\r\n\r\n  void balance(link_t &ptr) const {\r\n    internal_t &internal =\
    \ ptr->data.internal;\r\n    const std::size_t bias = internal.bias();\r\n   \
    \ if (bias == 2) {\r\n      if (internal.left->data.internal.bias() == -2) {\r\
    \n        rotate_left(internal.left);\r\n      }\r\n      rotate_right(ptr);\r\
    \n    } else if (bias == -2) {\r\n      if (internal.right->data.internal.bias()\
    \ == 2) {\r\n        rotate_right(internal.right);\r\n      }\r\n      rotate_left(ptr);\r\
    \n    }\r\n    update_node(*ptr);\r\n  }\r\n\r\npublic:\r\n  explicit parametric_heap(const\
    \ Compare comp_ = Compare())\r\n      : comp(comp_), root() {}\r\n\r\n  bool empty()\
    \ const { return !static_cast<bool>(root); }\r\n\r\n  void insert(const T &a,\
    \ const T &b) {\r\n    if (empty()) {\r\n      root = std::make_unique<node_t>(node_t(a,\
    \ b, comp));\r\n      return;\r\n    }\r\n    const auto insert_rec = [&](const\
    \ auto &self, link_t &ptr) -> void {\r\n      if (ptr->is_leaf()) {\r\n      \
    \  leaf_t &leaf = ptr->data.leaf;\r\n        if (comp_f(leaf.a, a)) {\r\n    \
    \      ptr = std::make_unique<node_t>(node_t(\r\n              std::make_unique<node_t>(node_t(a,\
    \ b, comp)), std::move(ptr)));\r\n        } else if (comp_f(a, leaf.a)) {\r\n\
    \          ptr = std::make_unique<node_t>(node_t(\r\n              std::move(ptr),\
    \ std::make_unique<node_t>(node_t(a, b, comp))));\r\n        } else {\r\n    \
    \      leaf.b.insert(b);\r\n        }\r\n        return;\r\n      }\r\n      internal_t\
    \ &internal = ptr->data.internal;\r\n      if (comp_f(internal.get_mid(), a))\
    \ {\r\n        self(self, internal.left);\r\n      } else {\r\n        self(self,\
    \ internal.right);\r\n      }\r\n      balance(ptr);\r\n    };\r\n    insert_rec(insert_rec,\
    \ root);\r\n  }\r\n\r\n  bool erase(const T &a, const T &b) {\r\n    if (empty())\
    \ {\r\n      return false;\r\n    }\r\n    bool res = false;\r\n    const auto\
    \ erase_rec = [&](const auto &self, link_t &ptr) -> void {\r\n      if (ptr->is_leaf())\
    \ {\r\n        leaf_t &leaf = ptr->data.leaf;\r\n        if (!comp_f(leaf.a, a)\
    \ && !comp_f(a, leaf.a)) {\r\n          const auto itr = leaf.b.find(b);\r\n \
    \         if (itr != leaf.b.end()) {\r\n            res = true;\r\n          \
    \  leaf.b.erase(itr);\r\n            if (leaf.b.empty()) {\r\n              ptr.reset();\r\
    \n            }\r\n          }\r\n        }\r\n        return;\r\n      }\r\n\
    \      internal_t &internal = ptr->data.internal;\r\n      if (comp_f(internal.get_mid(),\
    \ a)) {\r\n        self(self, internal.left);\r\n        if (!internal.left) {\r\
    \n          ptr = std::move(internal.right);\r\n          return;\r\n        }\r\
    \n      } else {\r\n        self(self, internal.right);\r\n        if (!internal.right)\
    \ {\r\n          ptr = std::move(internal.left);\r\n          return;\r\n    \
    \    }\r\n      }\r\n      balance(ptr);\r\n    };\r\n    erase_rec(erase_rec,\
    \ root);\r\n    return res;\r\n  }\r\n\r\n  std::pair<T, T> top(const T &x) const\
    \ {\r\n    if (empty()) {\r\n      std::abort();\r\n    }\r\n\r\n    const node_t\
    \ *ptr = root.get();\r\n    while (ptr->is_internal()) {\r\n      const internal_t\
    \ &internal = ptr->data.internal;\r\n      if (comp_f(internal.lc->eval(x), internal.rc->eval(x)))\
    \ {\r\n        ptr = internal.left.get();\r\n      } else {\r\n        ptr = internal.right.get();\r\
    \n      }\r\n    }\r\n    const leaf_t &leaf = ptr->data.leaf;\r\n    return std::pair<T,\
    \ T>(leaf.a, *leaf.b.begin());\r\n  }\r\n};\r\n\r\n/**\r\n * @brief Parametric\
    \ Heap\r\n * @docs docs/parametric_heap.md\r\n */\r\n\r\n/*\r\n\r\nReference\r\
    \n\r\n[1] Overmars, M. H., & Van Leeuwen, J. (1981).\r\n    Maintenance of configurations\
    \ in the plane.\r\n    Journal of computer and System Sciences, 23(2), 166-204.\r\
    \n\r\n[2] Kaplan, H., Tarjan, R. E., & Tsioutsiouliklis, K. (2001, January).\r\
    \n    Faster kinetic heaps and their use in broadcast scheduling.\r\n    In SODA\
    \ (Vol. 1, pp. 836-844).\r\n\r\n*/\r\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/parametric_heap.hpp
  requiredBy: []
  timestamp: '2020-12-26 18:20:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/parametric_heap.test.cpp
documentation_of: data_structure/parametric_heap.hpp
layout: document
redirect_from:
- /library/data_structure/parametric_heap.hpp
- /library/data_structure/parametric_heap.hpp.html
title: Parametric Heap
---
# parametric_heap
```
template <T, Minimize = true, Compare = std::less<T>>
class parametric_heap;
```

`parametric_heap` は数の組 $(a, b)$ の多重集合を管理するデータ構造です。
直線の削除が可能な Convex Hull Trick と理解することも出来ます。

## テンプレート引数

|引数名||
|:---|:---|
|`T`|数値の型|
|`Minimize`|`true` で最小化、`false` で最大化します。デフォルトは `true` です。|
|`Compare`|$\lt$ に相当する比較関数。デフォルトは `std::less<T>` です。|

## メンバ関数

$n$ を要素数とします。

|メンバ関数名|効果|時間計算量|
|:---|:---|:---|
|`explicit parametric_heap(Compare comp_ = Compare())`|`comp_` を比較関数として、空の状態で構築します。|$\Theta ( 1 )$|
|`bool empty() const`|空の場合 `true`、空でない場合 `false` を返します。|$\Theta ( 1 )$|
|`void insert(const T &a, const T &b)`|$(a, b)$ を追加します。|$\Theta ( \log ( n ) ^ 2 )$|
|`bool erase(const T &a, const T &b)`|$(a, b)$ を削除します。<br>削除に成功した場合 `true`、失敗した場合 `false` を返します。<br>複数存在する場合、そのうち $1$ つを削除します。|$\Theta ( \log ( n ) ^ 2 )$|
|`std::pair<T, T> top(const T &x) const`|$ax + b$ を最小化するような $(a, b)$ を返します。<br>`Minimize` が `false` の場合、最大化するものを返します。<br>複数存在する場合にどれを返すかは未規定です。<br>空の場合 abort します。|$\Theta ( \log ( n ) )$|

## 注意事項

多重集合を管理します。
すなわち、同じ $(a, b)$ を繰り返し `insert` するとそれだけ要素数が増えます。
また、(`std::multiset` と異なり) `erase` によっても $1$ つずつ消えます。

`T`, `Compare` が満たすべき条件は、大雑把には

-   `T` が実数の部分集合である。
-   `T` 同士の加算と乗算は `T` を実数として見たときと同じ挙動をする。
-   `Compare` による比較は、`T` を実数として見たときの $\lt$ と同じ挙動をする。

と表現されます。したがって、オーバーフローを無視すれば `int` や有理数型を `T`
に用いることが出来ます。 また、誤差を度外視すれば `double`
も用いることが出来ます。

特に、`Compare` は $\lt$ (`less`) であることに注意してください。$\gt$ (`greater`) や $\leq$
(`less_equal`) にすると壊れます。最大化したい場合、`Compare` ではなく `Minimize`
の方で調整してください。


計算の過程で最大 `8 * a * a * b` 程度の大きさの値が現れます。
したがって、これにより `T` がオーバーフローしないようにしてください。
`__int128_t` が必要になることも多いと思われます。

## 参考文献

-   Overmars, M. H., & Van Leeuwen, J. (1981).
    Maintenance of configurations in the plane.
    Journal of computer and System Sciences, 23(2), 166-204.

-   Kaplan, H., Tarjan, R. E., & Tsioutsiouliklis, K. (2001, January).
    Faster kinetic heaps and their use in broadcast scheduling.
    In SODA (Vol. 1, pp. 836-844).
