---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/stack_aggregation.cpp
    title: Stack Aggregation
  - icon: ':heavy_check_mark:'
    path: other/opposite_monoid.cpp
    title: other/opposite_monoid.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/queue_aggregation.test.cpp
    title: test/queue_aggregation.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Queue Aggregation
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
    \ */\n#line 1 \"other/opposite_monoid.cpp\"\ntemplate <class M> class opposite_monoid\
    \ {\n  using T = typename M::value_type;\n\npublic:\n  using value_type = T;\n\
    \  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ M::operation(r, l);\n  }\n  static constexpr T identity = M::identity;\n};\n\
    #line 3 \"data_structure/queue_aggregation.cpp\"\n\ntemplate <class M> class queue_aggregation\
    \ {\n  using T = typename M::value_type;\n\n  stack_aggregation<opposite_monoid<M>>\
    \ front_st;\n  stack_aggregation<M> back_st;\n\npublic:\n  queue_aggregation()\
    \ = default;\n\n  bool empty() const { return front_st.empty(); }\n  T fold()\
    \ const { return M::operation(front_st.fold(), back_st.fold()); }\n\n  void push(const\
    \ T x) {\n    if (empty())\n      front_st.push(x);\n    else\n      back_st.push(x);\n\
    \  }\n  void pop() {\n    assert(!empty());\n    front_st.pop();\n    if (front_st.empty())\
    \ {\n      while (!back_st.empty()) {\n        front_st.push(back_st.top());\n\
    \        back_st.pop();\n      }\n    }\n  }\n};\n\n/**\n * @brief Queue Aggregation\n\
    \ * @see https://scrapbox.io/data-structures/Sliding_Window_Aggregation\n */\n"
  code: "#include \"data_structure/stack_aggregation.cpp\"\n#include \"other/opposite_monoid.cpp\"\
    \n\ntemplate <class M> class queue_aggregation {\n  using T = typename M::value_type;\n\
    \n  stack_aggregation<opposite_monoid<M>> front_st;\n  stack_aggregation<M> back_st;\n\
    \npublic:\n  queue_aggregation() = default;\n\n  bool empty() const { return front_st.empty();\
    \ }\n  T fold() const { return M::operation(front_st.fold(), back_st.fold());\
    \ }\n\n  void push(const T x) {\n    if (empty())\n      front_st.push(x);\n \
    \   else\n      back_st.push(x);\n  }\n  void pop() {\n    assert(!empty());\n\
    \    front_st.pop();\n    if (front_st.empty()) {\n      while (!back_st.empty())\
    \ {\n        front_st.push(back_st.top());\n        back_st.pop();\n      }\n\
    \    }\n  }\n};\n\n/**\n * @brief Queue Aggregation\n * @see https://scrapbox.io/data-structures/Sliding_Window_Aggregation\n\
    \ */\n"
  dependsOn:
  - data_structure/stack_aggregation.cpp
  - other/opposite_monoid.cpp
  isVerificationFile: false
  path: data_structure/queue_aggregation.cpp
  requiredBy: []
  timestamp: '2020-02-28 14:18:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/queue_aggregation.test.cpp
documentation_of: data_structure/queue_aggregation.cpp
layout: document
redirect_from:
- /library/data_structure/queue_aggregation.cpp
- /library/data_structure/queue_aggregation.cpp.html
title: Queue Aggregation
---
