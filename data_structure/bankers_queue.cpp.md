---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/stream.cpp
    title: Stream
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/suspension.cpp
    title: Suspension
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/bankers_queue.test.cpp
    title: test/bankers_queue.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Banker's Queue
    links:
    - https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
  bundledCode: "#line 1 \"other/suspension.cpp\"\n#include <functional>\n#include\
    \ <memory>\n#include <utility>\n#include <variant>\n\ntemplate <class T>\nclass\
    \ suspension\n    : private std::shared_ptr<std::variant<T, std::function<T()>>>\
    \ {\npublic:\n  using value_type = T;\n  using func_type = std::function<T()>;\n\
    \  using node_type = std::variant<T, func_type>;\n\nprivate:\n  using base_type\
    \ = std::shared_ptr<node_type>;\n\n  static T get(node_type &x) {\n    if (x.index()\
    \ != 0)\n      x = std::get<1>(x)();\n    return std::get<0>(x);\n  }\n\n  template\
    \ <class... Args> static base_type make_node(Args &&... args) {\n    return std::make_shared<node_type>(std::forward<Args>(args)...);\n\
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
    \ */\n"
  code: "#include \"data_structure/stream.cpp\"\n#include \"other/int_alias.cpp\"\n\
    \n#include <cassert>\n\ntemplate <class T> class bankers_queue {\n  using Self\
    \ = bankers_queue<T>;\n  using stream_type = stream<T>;\n\n  stream_type front_;\n\
    \  usize f_size;\n  stream_type back_;\n  usize b_size;\n\n  bankers_queue(stream_type\
    \ front_, usize f_size, stream_type back_,\n                usize b_size)\n  \
    \    : front_(front_), f_size(f_size), back_(back_), b_size(b_size) {}\n\n  Self\
    \ normalize() const {\n    if (f_size >= b_size)\n      return *this;\n    else\n\
    \      return Self(front_ + back_.reverse(), f_size + b_size, stream_type(), 0);\n\
    \  }\n\npublic:\n  bankers_queue() : front_(), f_size(0), back_(), b_size(0) {}\n\
    \n  bool empty() const { return f_size == 0; }\n\n  T front() const {\n    assert(not\
    \ empty());\n\n    return front_.top();\n  }\n\n  Self push(T x) const {\n   \
    \ return Self(front_, f_size, back_.push(x), b_size + 1).normalize();\n  }\n\n\
    \  Self pop() const {\n    assert(not empty());\n\n    return Self(front_.pop(),\
    \ f_size - 1, back_, b_size).normalize();\n  }\n};\n\n/**\n * @brief Banker's\
    \ Queue\n * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf\n */\n"
  dependsOn:
  - data_structure/stream.cpp
  - other/suspension.cpp
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/bankers_queue.cpp
  requiredBy: []
  timestamp: '2020-03-16 22:45:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/bankers_queue.test.cpp
documentation_of: data_structure/bankers_queue.cpp
layout: document
redirect_from:
- /library/data_structure/bankers_queue.cpp
- /library/data_structure/bankers_queue.cpp.html
title: Banker's Queue
---
