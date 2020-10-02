---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fenwick_tree.test.cpp
    title: test/fenwick_tree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Fenwick Tree
    links:
    - https://scrapbox.io/data-structures/Fenwick_Tree
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/fenwick_tree.cpp\"\n\n#include <cassert>\n#line 5 \"\
    data_structure/fenwick_tree.cpp\"\n#include <vector>\n\ntemplate <class M> class\
    \ fenwick_tree {\n  using T = typename M::value_type;\n\npublic:\n  using value_type\
    \ = T;\n\nprivate:\n  std::vector<T> tree;\n\npublic:\n  fenwick_tree() = default;\n\
    \n  explicit fenwick_tree(const usize size) : tree(size + 1, M::identity) {}\n\
    \n  bool empty() const { return size() == 0; }\n  \n  usize size() const { return\
    \ tree.size() - 1; }\n\n  T fold_prefix(usize last) const {\n    assert(last <=\
    \ size());\n    T ret = M::identity;\n    while (last != 0) {\n      ret = M::operation(tree[last],\
    \ ret);\n      last &= last - 1;\n    }\n    return ret;\n  }\n\n  void add(usize\
    \ index, const T value) {\n    assert(index < size());\n    index += 1;\n    while\
    \ (index < tree.size()) {\n      tree[index] = M::operation(tree[index], value);\n\
    \      index += index & ~index + 1;\n    }\n  }\n};\n\n/**\n * @brief Fenwick\
    \ Tree\n * @see https://scrapbox.io/data-structures/Fenwick_Tree\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <cassert>\n#include <cstddef>\n\
    #include <vector>\n\ntemplate <class M> class fenwick_tree {\n  using T = typename\
    \ M::value_type;\n\npublic:\n  using value_type = T;\n\nprivate:\n  std::vector<T>\
    \ tree;\n\npublic:\n  fenwick_tree() = default;\n\n  explicit fenwick_tree(const\
    \ usize size) : tree(size + 1, M::identity) {}\n\n  bool empty() const { return\
    \ size() == 0; }\n  \n  usize size() const { return tree.size() - 1; }\n\n  T\
    \ fold_prefix(usize last) const {\n    assert(last <= size());\n    T ret = M::identity;\n\
    \    while (last != 0) {\n      ret = M::operation(tree[last], ret);\n      last\
    \ &= last - 1;\n    }\n    return ret;\n  }\n\n  void add(usize index, const T\
    \ value) {\n    assert(index < size());\n    index += 1;\n    while (index < tree.size())\
    \ {\n      tree[index] = M::operation(tree[index], value);\n      index += index\
    \ & ~index + 1;\n    }\n  }\n};\n\n/**\n * @brief Fenwick Tree\n * @see https://scrapbox.io/data-structures/Fenwick_Tree\n\
    \ */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/fenwick_tree.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fenwick_tree.test.cpp
documentation_of: data_structure/fenwick_tree.cpp
layout: document
redirect_from:
- /library/data_structure/fenwick_tree.cpp
- /library/data_structure/fenwick_tree.cpp.html
title: Fenwick Tree
---
