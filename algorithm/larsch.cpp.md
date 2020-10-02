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
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/larsch.md
    document_title: LARSCH Algorithm
    links: []
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"algorithm/larsch.cpp\"\n\r\n#include <vector>\r\n\r\ntemplate <class\
    \ Select, class Update>\r\nvoid larsch(const std::size_t n, Select select, Update\
    \ update) {\r\n  using usize = std::size_t;\r\n\r\n  class header {\r\n  public:\r\
    \n    usize r;\r\n    usize c;\r\n  };\r\n\r\n  class node {\r\n  public:\r\n\
    \    std::vector<usize> cols;\r\n    usize prev;\r\n\r\n    std::vector<header>\
    \ tent;\r\n    usize pcnt;\r\n    usize curc;\r\n\r\n    node(const usize n) :\
    \ cols(), prev(0), tent(), pcnt(0), curc(0) {\r\n      cols.reserve(n);\r\n  \
    \    tent.reserve(n / 2);\r\n    }\r\n  };\r\n\r\n  std::vector<node> data;\r\n\
    \r\n  {\r\n    usize m = n;\r\n    while (m != 0) {\r\n      data.emplace_back(m);\r\
    \n      m /= 2;\r\n    }\r\n  }\r\n\r\n  const auto act = [&](const auto &act,\
    \ const usize layer,\r\n                       const usize row) -> usize {\r\n\
    \    node &t = data[layer];\r\n\r\n    if ((row >> layer) % 2 == 0) {\r\n    \
    \  usize res = t.prev;\r\n      usize idx = t.curc;\r\n      while (idx != t.cols.size())\
    \ {\r\n        if (select(row, t.cols[res], t.cols[idx])) {\r\n          res =\
    \ idx;\r\n        }\r\n        idx += 1;\r\n      }\r\n      t.prev = res;\r\n\
    \      return t.cols[res];\r\n    }\r\n\r\n    const usize a = [&]() {\r\n   \
    \   const usize step = static_cast<usize>(1) << layer;\r\n      if (row + step\
    \ > n) {\r\n        return t.cols.back();\r\n      }\r\n      while (t.curc !=\
    \ t.cols.size()) {\r\n        const usize c = t.cols[t.curc];\r\n        while\
    \ (t.tent.size() != t.pcnt &&\r\n               select(t.tent.back().r, t.tent.back().c,\
    \ c)) {\r\n          t.tent.pop_back();\r\n        }\r\n        if (t.tent.size()\
    \ == t.pcnt) {\r\n          t.tent.push_back({row + step, c});\r\n        } else\
    \ if (t.tent.back().r + step * 2 <= n) {\r\n          t.tent.push_back({t.tent.back().r\
    \ + step * 2, c});\r\n        }\r\n        t.curc += 1;\r\n      }\r\n      if\
    \ (t.pcnt != t.tent.size()) {\r\n        data[layer + 1].cols.push_back(t.tent[t.pcnt].c);\r\
    \n        t.pcnt += 1;\r\n      }\r\n      return act(act, layer + 1, row + step);\r\
    \n    }();\r\n\r\n    usize res = t.prev;\r\n    usize idx = t.prev;\r\n    while\
    \ (t.cols[idx] != a) {\r\n      idx += 1;\r\n      if (select(row, t.cols[res],\
    \ t.cols[idx])) {\r\n        res = idx;\r\n      }\r\n    }\r\n    t.prev = idx;\r\
    \n    return t.cols[res];\r\n  };\r\n\r\n  for (usize i = 0; i != n;) {\r\n  \
    \  data[0].cols.push_back(i);\r\n    i += 1;\r\n    update(i, act(act, 0, i));\r\
    \n  }\r\n}\r\n\r\n/**\r\n * @brief LARSCH Algorithm\r\n * @docs docs/larsch.md\r\
    \n */\r\n"
  code: "#include \"other/int_alias.cpp\"\r\n\r\n#include <vector>\r\n\r\ntemplate\
    \ <class Select, class Update>\r\nvoid larsch(const std::size_t n, Select select,\
    \ Update update) {\r\n  using usize = std::size_t;\r\n\r\n  class header {\r\n\
    \  public:\r\n    usize r;\r\n    usize c;\r\n  };\r\n\r\n  class node {\r\n \
    \ public:\r\n    std::vector<usize> cols;\r\n    usize prev;\r\n\r\n    std::vector<header>\
    \ tent;\r\n    usize pcnt;\r\n    usize curc;\r\n\r\n    node(const usize n) :\
    \ cols(), prev(0), tent(), pcnt(0), curc(0) {\r\n      cols.reserve(n);\r\n  \
    \    tent.reserve(n / 2);\r\n    }\r\n  };\r\n\r\n  std::vector<node> data;\r\n\
    \r\n  {\r\n    usize m = n;\r\n    while (m != 0) {\r\n      data.emplace_back(m);\r\
    \n      m /= 2;\r\n    }\r\n  }\r\n\r\n  const auto act = [&](const auto &act,\
    \ const usize layer,\r\n                       const usize row) -> usize {\r\n\
    \    node &t = data[layer];\r\n\r\n    if ((row >> layer) % 2 == 0) {\r\n    \
    \  usize res = t.prev;\r\n      usize idx = t.curc;\r\n      while (idx != t.cols.size())\
    \ {\r\n        if (select(row, t.cols[res], t.cols[idx])) {\r\n          res =\
    \ idx;\r\n        }\r\n        idx += 1;\r\n      }\r\n      t.prev = res;\r\n\
    \      return t.cols[res];\r\n    }\r\n\r\n    const usize a = [&]() {\r\n   \
    \   const usize step = static_cast<usize>(1) << layer;\r\n      if (row + step\
    \ > n) {\r\n        return t.cols.back();\r\n      }\r\n      while (t.curc !=\
    \ t.cols.size()) {\r\n        const usize c = t.cols[t.curc];\r\n        while\
    \ (t.tent.size() != t.pcnt &&\r\n               select(t.tent.back().r, t.tent.back().c,\
    \ c)) {\r\n          t.tent.pop_back();\r\n        }\r\n        if (t.tent.size()\
    \ == t.pcnt) {\r\n          t.tent.push_back({row + step, c});\r\n        } else\
    \ if (t.tent.back().r + step * 2 <= n) {\r\n          t.tent.push_back({t.tent.back().r\
    \ + step * 2, c});\r\n        }\r\n        t.curc += 1;\r\n      }\r\n      if\
    \ (t.pcnt != t.tent.size()) {\r\n        data[layer + 1].cols.push_back(t.tent[t.pcnt].c);\r\
    \n        t.pcnt += 1;\r\n      }\r\n      return act(act, layer + 1, row + step);\r\
    \n    }();\r\n\r\n    usize res = t.prev;\r\n    usize idx = t.prev;\r\n    while\
    \ (t.cols[idx] != a) {\r\n      idx += 1;\r\n      if (select(row, t.cols[res],\
    \ t.cols[idx])) {\r\n        res = idx;\r\n      }\r\n    }\r\n    t.prev = idx;\r\
    \n    return t.cols[res];\r\n  };\r\n\r\n  for (usize i = 0; i != n;) {\r\n  \
    \  data[0].cols.push_back(i);\r\n    i += 1;\r\n    update(i, act(act, 0, i));\r\
    \n  }\r\n}\r\n\r\n/**\r\n * @brief LARSCH Algorithm\r\n * @docs docs/larsch.md\r\
    \n */\r\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: algorithm/larsch.cpp
  requiredBy: []
  timestamp: '2020-10-03 01:04:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/larsch.test.cpp
documentation_of: algorithm/larsch.cpp
layout: document
redirect_from:
- /library/algorithm/larsch.cpp
- /library/algorithm/larsch.cpp.html
title: LARSCH Algorithm
---
## 入力
$N \times N$ 下三角行列 $A$
-   $A$ は totally monotone
-   出力の一部を使用しても良い（後述）

## 出力
各 $i$ について $\mathop {\rm arg \, min} \limits _ j A _ {i , j}$

## 計算量
-   時間計算量 $\Theta ( N )$
-   空間計算量 $\Theta ( N )$

## 説明
$A$ について、行の添え字は $1$ から、列の添え字は $0$ から始まるものとする。

大雑把に言えば、このアルゴリズムはある種の動的計画法を高速化するものである。
出力の値は $i$ の昇順に計算され、$A _ {i , j}$ の値は
$j$ についての $\mathop {\rm arg \, min} \limits _ k A _ {j , k}$
が計算された後にアクセス出来れば良い。
したがって $A _ {i , j}$ は ${\rm dp} \lbrack j \rbrack$ から
${\rm dp} \lbrack i \rbrack$ への遷移とみなすことが出来る。
[SMAWK Algorithm](https://noshi91.github.io/Library/library/algorithm/smawk.cpp.html)
を on-line な動的計画法に適用出来るよう工夫したものとも言える。
実際、アルゴリズムの内容も SMAWK Algorithm に類似している。

## 文献
-   Larmore, L. L., & Schieber, B. (1991). On-line dynamic programming with applications to the prediction of RNA secondary structure. Journal of Algorithms, 12(3), 490-515.

## 語

#### totally monotone
[SMAWK Algorithm](https://noshi91.github.io/Library/library/algorithm/smawk.cpp.html) を参照せよ。

## その他
-   実装例の引数 $\rm select$ について

    ${\rm select} ( i , j , k ) \mathrel := A _ {i , j}$ と $A _ {i , k} \  ( j \lt k )$ を比較して、前者を選ぶ場合 false、後者を選ぶ場合 true

-   実装例の引数 $\rm update$ について

    ${\rm update} ( i , k )$ が呼ばれたとき、$\mathop {\rm arg \, min} \limits _ j A _ {i , j} = k$ である。この関数は $i$ の昇順に呼ばれる。
