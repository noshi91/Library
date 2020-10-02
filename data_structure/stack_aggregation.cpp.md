---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/queue_aggregation.cpp
    title: Queue Aggregation
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/queue_aggregation.test.cpp
    title: test/queue_aggregation.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Stack Aggregation
    links:
    - https://scrapbox.io/data-structures/Sliding_Window_Aggregation
  bundledCode: "#line 1 \"data_structure/stack_aggregation.cpp\"\n#include <cassert>\n\
    #include <stack>\n\ntemplate <class M> class stack_aggregation {\n  using T =\
    \ typename M::value_type;\n\n  class node_type {\n  public:\n    T value;\n  \
    \  T fold;\n\n    node_type(const T value, const T fold) : value(value), fold(fold)\
    \ {}\n  };\n\n  std::stack<node_type> st;\n\npublic:\n  stack_aggregation() =\
    \ default;\n\n  bool empty() const { return st.empty(); }\n  T top() const {\n\
    \    assert(!empty());\n    return st.top().value;\n  }\n  T fold() const { return\
    \ st.empty() ? M::identity : st.top().fold; }\n\n  void push(const T x) { st.push(node_type(x,\
    \ M::operation(fold(), x))); }\n  void pop() {\n    assert(!empty());\n    st.pop();\n\
    \  }\n};\n\n/**\n * @brief Stack Aggregation\n * @see https://scrapbox.io/data-structures/Sliding_Window_Aggregation\n\
    \ */\n"
  code: "#include <cassert>\n#include <stack>\n\ntemplate <class M> class stack_aggregation\
    \ {\n  using T = typename M::value_type;\n\n  class node_type {\n  public:\n \
    \   T value;\n    T fold;\n\n    node_type(const T value, const T fold) : value(value),\
    \ fold(fold) {}\n  };\n\n  std::stack<node_type> st;\n\npublic:\n  stack_aggregation()\
    \ = default;\n\n  bool empty() const { return st.empty(); }\n  T top() const {\n\
    \    assert(!empty());\n    return st.top().value;\n  }\n  T fold() const { return\
    \ st.empty() ? M::identity : st.top().fold; }\n\n  void push(const T x) { st.push(node_type(x,\
    \ M::operation(fold(), x))); }\n  void pop() {\n    assert(!empty());\n    st.pop();\n\
    \  }\n};\n\n/**\n * @brief Stack Aggregation\n * @see https://scrapbox.io/data-structures/Sliding_Window_Aggregation\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/stack_aggregation.cpp
  requiredBy:
  - data_structure/queue_aggregation.cpp
  timestamp: '2020-02-28 14:18:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/queue_aggregation.test.cpp
documentation_of: data_structure/stack_aggregation.cpp
layout: document
redirect_from:
- /library/data_structure/stack_aggregation.cpp
- /library/data_structure/stack_aggregation.cpp.html
title: Stack Aggregation
---
