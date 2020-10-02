---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/persistent_stack.cpp
    title: Persistent Stack
  - icon: ':heavy_check_mark:'
    path: data_structure/physicists_queue.cpp
    title: Physicist's Queue
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/suspension.cpp
    title: Suspension
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_queue
    links:
    - https://judge.yosupo.jp/problem/persistent_queue
  bundledCode: "#line 1 \"test/physicists_queue.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\
    \n\n#line 1 \"data_structure/persistent_stack.cpp\"\n#include <cassert>\n#include\
    \ <memory>\n#include <utility>\n\ntemplate <class T> class persistent_stack {\n\
    \  using Self = persistent_stack<T>;\n  class node_type;\n  using node_ptr = std::shared_ptr<const\
    \ node_type>;\n\n  class node_type {\n  public:\n    T value;\n    node_ptr next;\n\
    \n    node_type(T value, node_ptr next) : value(value), next(next) {}\n  };\n\n\
    \  node_ptr root;\n\n  persistent_stack(node_ptr root) : root(root) {}\n\npublic:\n\
    \  persistent_stack() = default;\n\n  bool empty() const { return not root; }\n\
    \n  T top() const {\n    assert(not empty());\n\n    return root->value;\n  }\n\
    \n  Self push(T x) const {\n    return Self(std::make_shared<const node_type>(x,\
    \ root));\n  }\n\n  Self pop() const {\n    assert(not empty());\n\n    return\
    \ Self(root->next);\n  }\n\n  Self reverse() const {\n    Self ret;\n    Self\
    \ x = *this;\n    while (not x.empty()) {\n      ret = ret.push(x.top());\n  \
    \    x = x.pop();\n    }\n    return ret;\n  }\n};\n\n/**\n * @brief Persistent\
    \ Stack\n */\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include\
    \ <cstdint>\n\nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32\
    \ = std::uint32_t;\nusing u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\n\
    using usize = std::size_t;\n#line 1 \"other/suspension.cpp\"\n#include <functional>\n\
    #line 4 \"other/suspension.cpp\"\n#include <variant>\n\ntemplate <class T>\nclass\
    \ suspension\n    : private std::shared_ptr<std::variant<T, std::function<T()>>>\
    \ {\npublic:\n  using value_type = T;\n  using func_type = std::function<T()>;\n\
    \  using node_type = std::variant<T, func_type>;\n\nprivate:\n  using base_type\
    \ = std::shared_ptr<node_type>;\n\n  static T get(node_type &x) {\n    if (x.index()\
    \ != 0)\n      x = std::get<1>(x)();\n    return std::get<0>(x);\n  }\n\n  template\
    \ <class... Args> static base_type make_node(Args &&... args) {\n    return std::make_shared<node_type>(std::forward<Args>(args)...);\n\
    \  }\n\npublic:\n  suspension(std::in_place_t, T x)\n      : base_type(make_node(std::in_place_index<0>,\
    \ x)) {}\n\n  suspension(func_type f) : base_type(make_node(std::in_place_index<1>,\
    \ f)) {}\n\n  T force() const { return get(**this); }\n};\n\n/**\n * @brief Suspension\n\
    \ * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf\n */\n#line 4 \"data_structure/physicists_queue.cpp\"\
    \n\n#line 7 \"data_structure/physicists_queue.cpp\"\n\ntemplate <class T> class\
    \ physicists_queue {\n  using Self = physicists_queue<T>;\n  using stack_type\
    \ = persistent_stack<T>;\n  using susp_stack = suspension<stack_type>;\n\n  stack_type\
    \ working;\n  susp_stack front_;\n  usize f_size;\n  stack_type back_;\n  usize\
    \ b_size;\n\n  physicists_queue(stack_type working, susp_stack front_, usize f_size,\n\
    \                   stack_type back_, usize b_size)\n      : working(working),\
    \ front_(front_), f_size(f_size), back_(back_),\n        b_size(b_size) {}\n\n\
    \  Self check_r() const {\n    if (f_size >= b_size)\n      return *this;\n  \
    \  stack_type temp = front_.force();\n    auto f = [l = temp, r = back_]() mutable\
    \ {\n      r = r.reverse();\n      l = l.reverse();\n      while (not l.empty())\
    \ {\n        r = r.push(l.top());\n        l = l.pop();\n      }\n      return\
    \ r;\n    };\n    return Self(temp, susp_stack(f), f_size + b_size, stack_type(),\
    \ 0);\n  }\n\n  Self check_w() const {\n    if (working.empty())\n      return\
    \ Self(front_.force(), front_, f_size, back_, b_size);\n    else\n      return\
    \ *this;\n  }\n\n  Self check() const { return check_r().check_w(); }\n\npublic:\n\
    \  physicists_queue()\n      : working(), front_(std::in_place, stack_type()),\
    \ f_size(0), back_(),\n        b_size(0) {}\n\n  bool empty() const { return f_size\
    \ == 0; }\n\n  T front() const {\n    assert(not empty());\n\n    return working.top();\n\
    \  }\n\n  Self push(T x) const {\n    return Self(working, front_, f_size, back_.push(x),\
    \ b_size + 1).check();\n  }\n\n  Self pop() const {\n    assert(not empty());\n\
    \n    return Self(working.pop(),\n                susp_stack([f = front_]() {\
    \ return f.force().pop(); }),\n                f_size - 1, back_, b_size)\n  \
    \      .check();\n  }\n};\n\n/**\n * @brief Physicist's Queue\n * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf\n\
    \ */\n#line 4 \"test/physicists_queue.test.cpp\"\n\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 10 \"test/physicists_queue.test.cpp\"\n\n  int q;\n\
    \  std::cin >> q;\n\n  std::vector<physicists_queue<int>> s_(q + 1);\n  const\
    \ auto s = s_.begin() + 1;\n\n  for (int i = 0; i != q; i += 1) {\n    int c;\n\
    \    std::cin >> c;\n    switch (c) {\n    case 0: {\n      int t, x;\n      std::cin\
    \ >> t >> x;\n      s[i] = s[t].push(x);\n    } break;\n    case 1: {\n      int\
    \ t;\n      std::cin >> t;\n      std::cout << s[t].front() << \"\\n\";\n    \
    \  s[i] = s[t].pop();\n    }\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\n\n\
    #include \"data_structure/physicists_queue.cpp\"\n\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n#include \"other/fast_ios.cpp\"\n\n  int q;\n  std::cin\
    \ >> q;\n\n  std::vector<physicists_queue<int>> s_(q + 1);\n  const auto s = s_.begin()\
    \ + 1;\n\n  for (int i = 0; i != q; i += 1) {\n    int c;\n    std::cin >> c;\n\
    \    switch (c) {\n    case 0: {\n      int t, x;\n      std::cin >> t >> x;\n\
    \      s[i] = s[t].push(x);\n    } break;\n    case 1: {\n      int t;\n     \
    \ std::cin >> t;\n      std::cout << s[t].front() << \"\\n\";\n      s[i] = s[t].pop();\n\
    \    }\n    }\n  }\n}\n"
  dependsOn:
  - data_structure/physicists_queue.cpp
  - data_structure/persistent_stack.cpp
  - other/int_alias.cpp
  - other/suspension.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/physicists_queue.test.cpp
  requiredBy: []
  timestamp: '2020-03-18 22:48:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/physicists_queue.test.cpp
layout: document
redirect_from:
- /verify/test/physicists_queue.test.cpp
- /verify/test/physicists_queue.test.cpp.html
title: test/physicists_queue.test.cpp
---
