---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/randomized_queue.cpp
    title: Randomized Queue
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/random_integer.cpp
    title: other/random_integer.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/randomized_queue.test.cpp\"\n#define PROBLEM      \
    \                                                          \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
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
    \ */\n#line 6 \"test/randomized_queue.test.cpp\"\n\n#include <algorithm>\n#line\
    \ 9 \"test/randomized_queue.test.cpp\"\n#include <iostream>\n#line 11 \"test/randomized_queue.test.cpp\"\
    \n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 14 \"test/randomized_queue.test.cpp\"\n\n  const\
    \ int n = 1 << 20;\n\n  std::vector<int> a(n);\n  for (int &e : a)\n    e = random_integer(std::numeric_limits<int>::lowest(),\n\
    \                       std::numeric_limits<int>::max());\n\n  randomized_queue<int>\
    \ rq;\n  for (const int e : a)\n    rq.push(e);\n\n  assert(!rq.empty());\n\n\
    \  std::vector<int> b(n);\n  for (int &e : b)\n    e = rq.pop();\n\n  assert(rq.empty());\n\
    \  assert(a != b);\n  std::reverse(b.begin(), b.end());\n  assert(a != b);\n \
    \ std::sort(a.begin(), a.end());\n  std::sort(b.begin(), b.end());\n  assert(a\
    \ == b);\n\n  std::cout << \"Hello World\\n\";\n}\n"
  code: "#define PROBLEM                                                         \
    \       \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include \"data_structure/randomized_queue.cpp\"\n#include \"other/random_integer.cpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <vector>\n\
    \nint main() {\n#include \"other/fast_ios.cpp\"\n\n  const int n = 1 << 20;\n\n\
    \  std::vector<int> a(n);\n  for (int &e : a)\n    e = random_integer(std::numeric_limits<int>::lowest(),\n\
    \                       std::numeric_limits<int>::max());\n\n  randomized_queue<int>\
    \ rq;\n  for (const int e : a)\n    rq.push(e);\n\n  assert(!rq.empty());\n\n\
    \  std::vector<int> b(n);\n  for (int &e : b)\n    e = rq.pop();\n\n  assert(rq.empty());\n\
    \  assert(a != b);\n  std::reverse(b.begin(), b.end());\n  assert(a != b);\n \
    \ std::sort(a.begin(), a.end());\n  std::sort(b.begin(), b.end());\n  assert(a\
    \ == b);\n\n  std::cout << \"Hello World\\n\";\n}"
  dependsOn:
  - data_structure/randomized_queue.cpp
  - other/int_alias.cpp
  - other/random_integer.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/randomized_queue.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 00:35:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/randomized_queue.test.cpp
layout: document
redirect_from:
- /verify/test/randomized_queue.test.cpp
- /verify/test/randomized_queue.test.cpp.html
title: test/randomized_queue.test.cpp
---
