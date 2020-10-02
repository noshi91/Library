---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/persistent_stack.cpp
    title: Persistent Stack
  - icon: ':heavy_check_mark:'
    path: data_structure/realtime_queue.cpp
    title: Realtime Queue
  - icon: ':heavy_check_mark:'
    path: data_structure/stream.cpp
    title: Stream
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
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
  bundledCode: "#line 1 \"test/realtime_queue.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\
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
    \ Stack\n */\n#line 1 \"other/suspension.cpp\"\n#include <functional>\n#line 4\
    \ \"other/suspension.cpp\"\n#include <variant>\n\ntemplate <class T>\nclass suspension\n\
    \    : private std::shared_ptr<std::variant<T, std::function<T()>>> {\npublic:\n\
    \  using value_type = T;\n  using func_type = std::function<T()>;\n  using node_type\
    \ = std::variant<T, func_type>;\n\nprivate:\n  using base_type = std::shared_ptr<node_type>;\n\
    \n  static T get(node_type &x) {\n    if (x.index() != 0)\n      x = std::get<1>(x)();\n\
    \    return std::get<0>(x);\n  }\n\n  template <class... Args> static base_type\
    \ make_node(Args &&... args) {\n    return std::make_shared<node_type>(std::forward<Args>(args)...);\n\
    \  }\n\npublic:\n  suspension(std::in_place_t, T x)\n      : base_type(make_node(std::in_place_index<0>,\
    \ x)) {}\n\n  suspension(func_type f) : base_type(make_node(std::in_place_index<1>,\
    \ f)) {}\n\n  T force() const { return get(**this); }\n};\n\n/**\n * @brief Suspension\n\
    \ * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf\n */\n#line 2 \"data_structure/stream.cpp\"\
    \n\n#line 4 \"data_structure/stream.cpp\"\n#include <optional>\n#line 6 \"data_structure/stream.cpp\"\
    \n\ntemplate <class T>\nclass stream : private suspension<std::optional<std::pair<T,\
    \ stream<T>>>> {\n  using Self = stream<T>;\n\npublic:\n  using value_type = T;\n\
    \  using cell_type = std::optional<std::pair<T, Self>>;\n\nprivate:\n  using base_type\
    \ = suspension<cell_type>;\n\n  stream(T x, Self s)\n      : base_type(std::in_place,\
    \ cell_type(std::in_place, x, s)) {}\n\npublic:\n  stream() : base_type(std::in_place,\
    \ cell_type(std::nullopt)) {}\n\n  stream(std::function<cell_type()> f) : base_type(f)\
    \ {}\n\n  using base_type::force;\n\n  bool empty() const { return not force().has_value();\
    \ }\n\n  T top() const {\n    assert(not empty());\n\n    return (*force()).first;\n\
    \  }\n\n  Self push(T x) const { return Self(x, *this); }\n\n  Self pop() const\
    \ {\n    assert(not empty());\n\n    return (*force()).second;\n  }\n\n  Self\
    \ reverse() const {\n    return Self([x = *this]() mutable {\n      Self ret;\n\
    \      while (not x.empty()) {\n        ret = ret.push(x.top());\n        x =\
    \ x.pop();\n      }\n      return ret.force();\n    });\n  }\n\n  friend Self\
    \ operator+(Self l, Self r) {\n    return Self([l, r]() {\n      if (l.empty())\n\
    \        return r.force();\n      else\n        return cell_type(std::in_place,\
    \ l.top(), l.pop() + r);\n    });\n  }\n};\n\n/**\n * @brief Stream\n * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf\n\
    \ */\n#line 3 \"data_structure/realtime_queue.cpp\"\n\n#line 6 \"data_structure/realtime_queue.cpp\"\
    \n\ntemplate <class T> class realtime_queue {\n  using Self = realtime_queue<T>;\n\
    \  using stream_type = stream<T>;\n  using cell_type = typename stream_type::cell_type;\n\
    \  using stack_type = persistent_stack<T>;\n\npublic:\n  using value_type = T;\n\
    \nprivate:\n  static stream_type rotate(stream_type f, stack_type b, stream_type\
    \ t) {\n    return stream_type([f, b, t]() {\n      if (f.empty())\n        return\
    \ cell_type(std::in_place, b.top(), t);\n      else\n        return cell_type(std::in_place,\
    \ f.top(),\n                         rotate(f.pop(), b.pop(), t.push(b.top())));\n\
    \    });\n  }\n\n  static Self make_queue(stream_type f, stack_type b, stream_type\
    \ s) {\n    if (not s.empty())\n      return Self(f, b, s.pop());\n    stream_type\
    \ temp = rotate(f, b, stream_type());\n    return Self(temp, stack_type(), temp);\n\
    \  }\n\n  stream_type front_;\n  stack_type back_;\n  stream_type schedule;\n\n\
    \  realtime_queue(stream_type f, stack_type b, stream_type s)\n      : front_(f),\
    \ back_(b), schedule(s) {}\n\npublic:\n  realtime_queue() = default;\n\n  bool\
    \ empty() const { return front_.empty(); }\n\n  T front() const {\n    assert(not\
    \ empty());\n\n    return front_.top();\n  }\n\n  Self push(T x) const { return\
    \ make_queue(front_, back_.push(x), schedule); }\n\n  Self pop() const {\n   \
    \ assert(not empty());\n\n    return make_queue(front_.pop(), back_, schedule);\n\
    \  }\n};\n\n/**\n * @brief Realtime Queue\n * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf\n\
    \ */\n#line 4 \"test/realtime_queue.test.cpp\"\n\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 10 \"test/realtime_queue.test.cpp\"\n\n  int q;\n\
    \  std::cin >> q;\n\n  std::vector<realtime_queue<int>> s_(q + 1);\n  const auto\
    \ s = s_.begin() + 1;\n\n  for (int i = 0; i != q; i += 1) {\n    int c;\n   \
    \ std::cin >> c;\n    switch (c) {\n    case 0: {\n      int t, x;\n      std::cin\
    \ >> t >> x;\n      s[i] = s[t].push(x);\n    } break;\n    case 1: {\n      int\
    \ t;\n      std::cin >> t;\n      std::cout << s[t].front() << \"\\n\";\n    \
    \  s[i] = s[t].pop();\n    }\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\n\n\
    #include \"data_structure/realtime_queue.cpp\"\n\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n#include \"other/fast_ios.cpp\"\n\n  int q;\n  std::cin\
    \ >> q;\n\n  std::vector<realtime_queue<int>> s_(q + 1);\n  const auto s = s_.begin()\
    \ + 1;\n\n  for (int i = 0; i != q; i += 1) {\n    int c;\n    std::cin >> c;\n\
    \    switch (c) {\n    case 0: {\n      int t, x;\n      std::cin >> t >> x;\n\
    \      s[i] = s[t].push(x);\n    } break;\n    case 1: {\n      int t;\n     \
    \ std::cin >> t;\n      std::cout << s[t].front() << \"\\n\";\n      s[i] = s[t].pop();\n\
    \    }\n    }\n  }\n}\n"
  dependsOn:
  - data_structure/realtime_queue.cpp
  - data_structure/persistent_stack.cpp
  - data_structure/stream.cpp
  - other/suspension.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/realtime_queue.test.cpp
  requiredBy: []
  timestamp: '2020-03-18 22:48:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/realtime_queue.test.cpp
layout: document
redirect_from:
- /verify/test/realtime_queue.test.cpp
- /verify/test/realtime_queue.test.cpp.html
title: test/realtime_queue.test.cpp
---
