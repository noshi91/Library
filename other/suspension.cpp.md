---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/bankers_queue.cpp
    title: Banker's Queue
  - icon: ':heavy_check_mark:'
    path: data_structure/physicists_queue.cpp
    title: Physicist's Queue
  - icon: ':heavy_check_mark:'
    path: data_structure/realtime_queue.cpp
    title: Realtime Queue
  - icon: ':heavy_check_mark:'
    path: data_structure/stream.cpp
    title: Stream
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/bankers_queue.test.cpp
    title: test/bankers_queue.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/physicists_queue.test.cpp
    title: test/physicists_queue.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/realtime_queue.test.cpp
    title: test/realtime_queue.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Suspension
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
    \ * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf\n */\n"
  code: "#include <functional>\n#include <memory>\n#include <utility>\n#include <variant>\n\
    \ntemplate <class T>\nclass suspension\n    : private std::shared_ptr<std::variant<T,\
    \ std::function<T()>>> {\npublic:\n  using value_type = T;\n  using func_type\
    \ = std::function<T()>;\n  using node_type = std::variant<T, func_type>;\n\nprivate:\n\
    \  using base_type = std::shared_ptr<node_type>;\n\n  static T get(node_type &x)\
    \ {\n    if (x.index() != 0)\n      x = std::get<1>(x)();\n    return std::get<0>(x);\n\
    \  }\n\n  template <class... Args> static base_type make_node(Args &&... args)\
    \ {\n    return std::make_shared<node_type>(std::forward<Args>(args)...);\n  }\n\
    \npublic:\n  suspension(std::in_place_t, T x)\n      : base_type(make_node(std::in_place_index<0>,\
    \ x)) {}\n\n  suspension(func_type f) : base_type(make_node(std::in_place_index<1>,\
    \ f)) {}\n\n  T force() const { return get(**this); }\n};\n\n/**\n * @brief Suspension\n\
    \ * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: other/suspension.cpp
  requiredBy:
  - data_structure/realtime_queue.cpp
  - data_structure/bankers_queue.cpp
  - data_structure/stream.cpp
  - data_structure/physicists_queue.cpp
  timestamp: '2020-03-15 18:29:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/realtime_queue.test.cpp
  - test/physicists_queue.test.cpp
  - test/bankers_queue.test.cpp
documentation_of: other/suspension.cpp
layout: document
redirect_from:
- /library/other/suspension.cpp
- /library/other/suspension.cpp.html
title: Suspension
---
