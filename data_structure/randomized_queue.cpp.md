---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/random_integer.cpp
    title: other/random_integer.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/randomized_queue.test.cpp
    title: test/randomized_queue.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Randomized Queue
    links: []
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"other/random_integer.cpp\"\n\n#include <random>\n#include <type_traits>\n\
    \ntemplate <class T, class... Args>\nusing any_of_is_same = std::disjunction<std::is_same<T,\
    \ Args>...>;\n\ntemplate <class IntType = int>\nIntType random_integer(const IntType\
    \ a, const IntType b) {\n  static_assert(\n      any_of_is_same<IntType, short,\
    \ int, long, long long, unsigned short,\n                     unsigned int, unsigned\
    \ long, unsigned long long>::value);\n  static std::default_random_engine g(91);\n\
    \  return std::uniform_int_distribution<IntType>(a, b)(g);\n}\n#line 3 \"data_structure/randomized_queue.cpp\"\
    \n\n#include <cassert>\n#line 7 \"data_structure/randomized_queue.cpp\"\n#include\
    \ <utility>\n#include <vector>\n\ntemplate <class T> class randomized_queue {\n\
    public:\n  using value_type = T;\n\nprivate:\n  std::vector<T> c;\n\n  void select()\
    \ {\n    std::swap(c.back(), c[random_integer<usize>(0, c.size() - 1)]);\n  }\n\
    \npublic:\n  randomized_queue() = default;\n\n  bool empty() const { return c.empty();\
    \ }\n  usize size() const { return c.size(); }\n  T &front() {\n    assert(!empty());\n\
    \    select();\n    return c.back();\n  }\n\n  void push(T x) { c.push_back(std::move(x));\
    \ }\n  T pop() {\n    assert(!empty());\n    select();\n    T ret = std::move(c.back());\n\
    \    c.pop_back();\n    return ret;\n  }\n};\n\n/**\n * @brief Randomized Queue\n\
    \ */\n"
  code: "#include \"other/int_alias.cpp\"\n#include \"other/random_integer.cpp\"\n\
    \n#include <cassert>\n#include <cstddef>\n#include <random>\n#include <utility>\n\
    #include <vector>\n\ntemplate <class T> class randomized_queue {\npublic:\n  using\
    \ value_type = T;\n\nprivate:\n  std::vector<T> c;\n\n  void select() {\n    std::swap(c.back(),\
    \ c[random_integer<usize>(0, c.size() - 1)]);\n  }\n\npublic:\n  randomized_queue()\
    \ = default;\n\n  bool empty() const { return c.empty(); }\n  usize size() const\
    \ { return c.size(); }\n  T &front() {\n    assert(!empty());\n    select();\n\
    \    return c.back();\n  }\n\n  void push(T x) { c.push_back(std::move(x)); }\n\
    \  T pop() {\n    assert(!empty());\n    select();\n    T ret = std::move(c.back());\n\
    \    c.pop_back();\n    return ret;\n  }\n};\n\n/**\n * @brief Randomized Queue\n\
    \ */\n"
  dependsOn:
  - other/int_alias.cpp
  - other/random_integer.cpp
  isVerificationFile: false
  path: data_structure/randomized_queue.cpp
  requiredBy: []
  timestamp: '2020-03-11 00:35:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/randomized_queue.test.cpp
documentation_of: data_structure/randomized_queue.cpp
layout: document
redirect_from:
- /library/data_structure/randomized_queue.cpp
- /library/data_structure/randomized_queue.cpp.html
title: Randomized Queue
---
