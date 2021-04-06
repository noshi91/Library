---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/larsch.test.cpp
    title: test/larsch.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree.test.cpp
    title: test/segment_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/segment_tree.md
    document_title: Segment Tree
    links:
    - https://scrapbox.io/data-structures/Segment_Tree
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/segment_tree.cpp\"\n\n#include <cassert>\n#line 5 \"\
    data_structure/segment_tree.cpp\"\n#include <vector>\n\ntemplate <class M> class\
    \ segment_tree {\n  using T = typename M::value_type;\n\npublic:\n  using value_type\
    \ = T;\n\nprivate:\n  std::vector<T> tree;\n\n  template <class F>\n  usize search_subtree(usize\
    \ index, const F f, T fold_l) const {\n    while (index < size()) {\n      const\
    \ T temp = M::operation(fold_l, tree[index * 2]);\n      if (!f(temp)) {\n   \
    \     index = index * 2;\n      } else {\n        fold_l = temp;\n        index\
    \ = index * 2 + 1;\n      }\n    }\n    return index - size();\n  }\n\npublic:\n\
    \  segment_tree() = default;\n\n  explicit segment_tree(const usize n) : tree(n\
    \ * 2, M::identity) {}\n\n  usize size() const noexcept { return tree.size() /\
    \ 2; }\n\n  T fold(usize first, usize last) const {\n    assert(first <= last);\n\
    \    assert(last <= size());\n    first += size();\n    last += size();\n    T\
    \ fold_l = M::identity;\n    T fold_r = M::identity;\n    while (first != last)\
    \ {\n      if (first % 2 != 0) {\n        fold_l = M::operation(fold_l, tree[first]);\n\
    \        first += 1;\n      }\n      first /= 2;\n      if (last % 2 != 0) {\n\
    \        last -= 1;\n        fold_r = M::operation(tree[last], fold_r);\n    \
    \  }\n      last /= 2;\n    }\n    return M::operation(fold_l, fold_r);\n  }\n\
    \  \n  template <class F> usize search(usize first, usize last, const F f) const\
    \ {\n    assert(first <= last);\n    assert(last <= size());\n    first += size();\n\
    \    last += size();\n    const usize last_cp = last;\n    usize shift = 0;\n\
    \    T fold_l = M::identity;\n    while (first != last) {\n      if (first % 2\
    \ != 0) {\n        const T temp = M::operation(fold_l, tree[first]);\n       \
    \ if (!f(temp))\n          return search_subtree(first, f, fold_l);\n        fold_l\
    \ = temp;\n        first += 1;\n      }\n      first /= 2;\n      last /= 2;\n\
    \      shift += 1;\n    }\n    while (shift != 0) {\n      shift -= 1;\n     \
    \ last = last_cp >> shift;\n      if (last % 2 != 0) {\n        last -= 1;\n \
    \       const T temp = M::operation(fold_l, tree[last]);\n        if (!f(temp))\n\
    \          return search_subtree(last, f, fold_l);\n        fold_l = temp;\n \
    \     }\n    }\n    return last_cp - size();\n  }\n\n  void update(usize index,\
    \ const T x) {\n    assert(index < size());\n    index += size();\n    tree[index]\
    \ = x;\n    while (index != 1) {\n      index /= 2;\n      tree[index] = M::operation(tree[index\
    \ * 2], tree[index * 2 + 1]);\n    }\n  }\n};\n\n/**\n * @brief Segment Tree\n\
    \ * @docs docs/segment_tree.md\n * @see https://scrapbox.io/data-structures/Segment_Tree\n\
    \ */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <cassert>\n#include <cstddef>\n\
    #include <vector>\n\ntemplate <class M> class segment_tree {\n  using T = typename\
    \ M::value_type;\n\npublic:\n  using value_type = T;\n\nprivate:\n  std::vector<T>\
    \ tree;\n\n  template <class F>\n  usize search_subtree(usize index, const F f,\
    \ T fold_l) const {\n    while (index < size()) {\n      const T temp = M::operation(fold_l,\
    \ tree[index * 2]);\n      if (!f(temp)) {\n        index = index * 2;\n     \
    \ } else {\n        fold_l = temp;\n        index = index * 2 + 1;\n      }\n\
    \    }\n    return index - size();\n  }\n\npublic:\n  segment_tree() = default;\n\
    \n  explicit segment_tree(const usize n) : tree(n * 2, M::identity) {}\n\n  usize\
    \ size() const noexcept { return tree.size() / 2; }\n\n  T fold(usize first, usize\
    \ last) const {\n    assert(first <= last);\n    assert(last <= size());\n   \
    \ first += size();\n    last += size();\n    T fold_l = M::identity;\n    T fold_r\
    \ = M::identity;\n    while (first != last) {\n      if (first % 2 != 0) {\n \
    \       fold_l = M::operation(fold_l, tree[first]);\n        first += 1;\n   \
    \   }\n      first /= 2;\n      if (last % 2 != 0) {\n        last -= 1;\n   \
    \     fold_r = M::operation(tree[last], fold_r);\n      }\n      last /= 2;\n\
    \    }\n    return M::operation(fold_l, fold_r);\n  }\n  \n  template <class F>\
    \ usize search(usize first, usize last, const F f) const {\n    assert(first <=\
    \ last);\n    assert(last <= size());\n    first += size();\n    last += size();\n\
    \    const usize last_cp = last;\n    usize shift = 0;\n    T fold_l = M::identity;\n\
    \    while (first != last) {\n      if (first % 2 != 0) {\n        const T temp\
    \ = M::operation(fold_l, tree[first]);\n        if (!f(temp))\n          return\
    \ search_subtree(first, f, fold_l);\n        fold_l = temp;\n        first +=\
    \ 1;\n      }\n      first /= 2;\n      last /= 2;\n      shift += 1;\n    }\n\
    \    while (shift != 0) {\n      shift -= 1;\n      last = last_cp >> shift;\n\
    \      if (last % 2 != 0) {\n        last -= 1;\n        const T temp = M::operation(fold_l,\
    \ tree[last]);\n        if (!f(temp))\n          return search_subtree(last, f,\
    \ fold_l);\n        fold_l = temp;\n      }\n    }\n    return last_cp - size();\n\
    \  }\n\n  void update(usize index, const T x) {\n    assert(index < size());\n\
    \    index += size();\n    tree[index] = x;\n    while (index != 1) {\n      index\
    \ /= 2;\n      tree[index] = M::operation(tree[index * 2], tree[index * 2 + 1]);\n\
    \    }\n  }\n};\n\n/**\n * @brief Segment Tree\n * @docs docs/segment_tree.md\n\
    \ * @see https://scrapbox.io/data-structures/Segment_Tree\n */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/segment_tree.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/larsch.test.cpp
  - test/segment_tree.test.cpp
documentation_of: data_structure/segment_tree.cpp
layout: document
redirect_from:
- /library/data_structure/segment_tree.cpp
- /library/data_structure/segment_tree.cpp.html
title: Segment Tree
---
## Operations

モノイド$M$の列$(a_1, a_2, \dots, a_n)$を扱う.
空間計算量$\Theta(n)$

-   $\mathtt{new}()$
    -   列の項がすべて$M$の単位元であるSegment Treeを作成する.
    -   時間計算量[$ \Theta(n)$]
-   $\mathtt{build}(a_1, a_2, \dots, a_n)$
    -   与えられた列を表現するSegment Treeを作成する.
    -   時間計算量$\Theta(n)$
-   $\mathtt{set}(i, x)$
    -   $a_i$に$x$を代入する.
    -   時間計算量$O(\log n)$
-   $\mathtt{fold}(l, r)$
    -   $a_l \cdot a_{l+1} \cdot \dots \cdot a_r$を計算する.
    -   時間計算量$O(\log n)$
