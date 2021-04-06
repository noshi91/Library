---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/bankers_queue.cpp
    title: Banker's Queue
  - icon: ':heavy_check_mark:'
    path: data_structure/stream.cpp
    title: Stream
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
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_queue
    links:
    - https://judge.yosupo.jp/problem/persistent_queue
  bundledCode: "#line 1 \"test/bankers_queue.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\
    \n\n#line 1 \"other/suspension.cpp\"\n#include <functional>\n#include <memory>\n\
    #include <utility>\n#include <variant>\n\ntemplate <class T>\nclass suspension\n\
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
    \n\n#include <cassert>\n#include <optional>\n#line 6 \"data_structure/stream.cpp\"\
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
    \ */\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 3 \"data_structure/bankers_queue.cpp\"\n\n#line 5 \"data_structure/bankers_queue.cpp\"\
    \n\ntemplate <class T> class bankers_queue {\n  using Self = bankers_queue<T>;\n\
    \  using stream_type = stream<T>;\n\n  stream_type front_;\n  usize f_size;\n\
    \  stream_type back_;\n  usize b_size;\n\n  bankers_queue(stream_type front_,\
    \ usize f_size, stream_type back_,\n                usize b_size)\n      : front_(front_),\
    \ f_size(f_size), back_(back_), b_size(b_size) {}\n\n  Self normalize() const\
    \ {\n    if (f_size >= b_size)\n      return *this;\n    else\n      return Self(front_\
    \ + back_.reverse(), f_size + b_size, stream_type(), 0);\n  }\n\npublic:\n  bankers_queue()\
    \ : front_(), f_size(0), back_(), b_size(0) {}\n\n  bool empty() const { return\
    \ f_size == 0; }\n\n  T front() const {\n    assert(not empty());\n\n    return\
    \ front_.top();\n  }\n\n  Self push(T x) const {\n    return Self(front_, f_size,\
    \ back_.push(x), b_size + 1).normalize();\n  }\n\n  Self pop() const {\n    assert(not\
    \ empty());\n\n    return Self(front_.pop(), f_size - 1, back_, b_size).normalize();\n\
    \  }\n};\n\n/**\n * @brief Banker's Queue\n * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf\n\
    \ */\n#line 4 \"test/bankers_queue.test.cpp\"\n\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 10 \"test/bankers_queue.test.cpp\"\n\n  int q;\n\
    \  std::cin >> q;\n\n  std::vector<bankers_queue<int>> s_(q + 1);\n  const auto\
    \ s = s_.begin() + 1;\n\n  for (int i = 0; i != q; i += 1) {\n    int c;\n   \
    \ std::cin >> c;\n    switch (c) {\n    case 0: {\n      int t, x;\n      std::cin\
    \ >> t >> x;\n      s[i] = s[t].push(x);\n    } break;\n    case 1: {\n      int\
    \ t;\n      std::cin >> t;\n      std::cout << s[t].front() << \"\\n\";\n    \
    \  s[i] = s[t].pop();\n    }\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\n\n\
    #include \"data_structure/bankers_queue.cpp\"\n\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n#include \"other/fast_ios.cpp\"\n\n  int q;\n  std::cin\
    \ >> q;\n\n  std::vector<bankers_queue<int>> s_(q + 1);\n  const auto s = s_.begin()\
    \ + 1;\n\n  for (int i = 0; i != q; i += 1) {\n    int c;\n    std::cin >> c;\n\
    \    switch (c) {\n    case 0: {\n      int t, x;\n      std::cin >> t >> x;\n\
    \      s[i] = s[t].push(x);\n    } break;\n    case 1: {\n      int t;\n     \
    \ std::cin >> t;\n      std::cout << s[t].front() << \"\\n\";\n      s[i] = s[t].pop();\n\
    \    }\n    }\n  }\n}\n"
  dependsOn:
  - data_structure/bankers_queue.cpp
  - data_structure/stream.cpp
  - other/suspension.cpp
  - other/int_alias.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/bankers_queue.test.cpp
  requiredBy: []
  timestamp: '2020-03-18 22:48:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/bankers_queue.test.cpp
layout: document
redirect_from:
- /verify/test/bankers_queue.test.cpp
- /verify/test/bankers_queue.test.cpp.html
title: test/bankers_queue.test.cpp
---
