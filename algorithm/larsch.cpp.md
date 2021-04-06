---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/larsch.test.cpp
    title: test/larsch.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/larsch.md
    document_title: LARSCH Algorithm
    links: []
  bundledCode: "#line 1 \"algorithm/larsch.cpp\"\n#include <functional>\r\n#include\
    \ <memory>\r\n#include <vector>\r\n\r\ntemplate <class T> class larsch {\r\n \
    \ struct reduce_row;\r\n  struct reduce_col;\r\n\r\n  struct reduce_row {\r\n\
    \    int n;\r\n    std::function<T(int, int)> f;\r\n    int cur_row;\r\n    int\
    \ state;\r\n    std::unique_ptr<reduce_col> rec;\r\n\r\n    reduce_row(int n_)\
    \ : n(n_), f(), cur_row(0), state(0), rec() {\r\n      const int m = n / 2;\r\n\
    \      if (m != 0) {\r\n        rec = std::make_unique<reduce_col>(m);\r\n   \
    \   }\r\n    }\r\n\r\n    void set_f(std::function<T(int, int)> f_) {\r\n    \
    \  f = f_;\r\n      if (rec) {\r\n        rec->set_f([&](int i, int j) -> T {\
    \ return f(2 * i + 1, j); });\r\n      }\r\n    }\r\n\r\n    int get_argmin()\
    \ {\r\n      const int cur_row_ = cur_row;\r\n      cur_row += 1;\r\n      if\
    \ (cur_row_ % 2 == 0) {\r\n        const int prev_argmin = state;\r\n        const\
    \ int next_argmin = [&]() {\r\n          if (cur_row_ + 1 == n) {\r\n        \
    \    return n - 1;\r\n          } else {\r\n            return rec->get_argmin();\r\
    \n          }\r\n        }();\r\n        state = next_argmin;\r\n        int ret\
    \ = prev_argmin;\r\n        for (int j = prev_argmin + 1; j <= next_argmin; j\
    \ += 1) {\r\n          if (f(cur_row_, ret) > f(cur_row_, j)) {\r\n          \
    \  ret = j;\r\n          }\r\n        }\r\n        return ret;\r\n      } else\
    \ {\r\n        if (f(cur_row_, state) <= f(cur_row_, cur_row_)) {\r\n        \
    \  return state;\r\n        } else {\r\n          return cur_row_;\r\n       \
    \ }\r\n      }\r\n    }\r\n  };\r\n\r\n  struct reduce_col {\r\n    int n;\r\n\
    \    std::function<T(int, int)> f;\r\n    int cur_row;\r\n    std::vector<int>\
    \ cols;\r\n    reduce_row rec;\r\n\r\n    reduce_col(int n_) : n(n_), f(), cur_row(0),\
    \ cols(), rec(n) {}\r\n\r\n    void set_f(std::function<T(int, int)> f_) {\r\n\
    \      f = f_;\r\n      rec.set_f([&](int i, int j) -> T { return f(i, cols[j]);\
    \ });\r\n    }\r\n\r\n    int get_argmin() {\r\n      const int cur_row_ = cur_row;\r\
    \n      cur_row += 1;\r\n      const auto cs = [&]() -> std::vector<int> {\r\n\
    \        if (cur_row_ == 0) {\r\n          return {{0}};\r\n        } else {\r\
    \n          return {{2 * cur_row_ - 1, 2 * cur_row_}};\r\n        }\r\n      }();\r\
    \n      for (const int j : cs) {\r\n        while ([&]() {\r\n          const\
    \ int size = cols.size();\r\n          return size != cur_row_ && f(size - 1,\
    \ cols.back()) > f(size - 1, j);\r\n        }()) {\r\n          cols.pop_back();\r\
    \n        }\r\n        if (cols.size() != n) {\r\n          cols.push_back(j);\r\
    \n        }\r\n      }\r\n      return cols[rec.get_argmin()];\r\n    }\r\n  };\r\
    \n\r\n  std::unique_ptr<reduce_row> base;\r\n\r\npublic:\r\n  larsch(int n, std::function<T(int,\
    \ int)> f)\r\n      : base(std::make_unique<reduce_row>(n)) {\r\n    base->set_f(f);\r\
    \n  }\r\n\r\n  int get_argmin() { return base->get_argmin(); }\r\n};\r\n\r\n/**\r\
    \n * @brief LARSCH Algorithm\r\n * @docs docs/larsch.md\r\n */\r\n"
  code: "#include <functional>\r\n#include <memory>\r\n#include <vector>\r\n\r\ntemplate\
    \ <class T> class larsch {\r\n  struct reduce_row;\r\n  struct reduce_col;\r\n\
    \r\n  struct reduce_row {\r\n    int n;\r\n    std::function<T(int, int)> f;\r\
    \n    int cur_row;\r\n    int state;\r\n    std::unique_ptr<reduce_col> rec;\r\
    \n\r\n    reduce_row(int n_) : n(n_), f(), cur_row(0), state(0), rec() {\r\n \
    \     const int m = n / 2;\r\n      if (m != 0) {\r\n        rec = std::make_unique<reduce_col>(m);\r\
    \n      }\r\n    }\r\n\r\n    void set_f(std::function<T(int, int)> f_) {\r\n\
    \      f = f_;\r\n      if (rec) {\r\n        rec->set_f([&](int i, int j) ->\
    \ T { return f(2 * i + 1, j); });\r\n      }\r\n    }\r\n\r\n    int get_argmin()\
    \ {\r\n      const int cur_row_ = cur_row;\r\n      cur_row += 1;\r\n      if\
    \ (cur_row_ % 2 == 0) {\r\n        const int prev_argmin = state;\r\n        const\
    \ int next_argmin = [&]() {\r\n          if (cur_row_ + 1 == n) {\r\n        \
    \    return n - 1;\r\n          } else {\r\n            return rec->get_argmin();\r\
    \n          }\r\n        }();\r\n        state = next_argmin;\r\n        int ret\
    \ = prev_argmin;\r\n        for (int j = prev_argmin + 1; j <= next_argmin; j\
    \ += 1) {\r\n          if (f(cur_row_, ret) > f(cur_row_, j)) {\r\n          \
    \  ret = j;\r\n          }\r\n        }\r\n        return ret;\r\n      } else\
    \ {\r\n        if (f(cur_row_, state) <= f(cur_row_, cur_row_)) {\r\n        \
    \  return state;\r\n        } else {\r\n          return cur_row_;\r\n       \
    \ }\r\n      }\r\n    }\r\n  };\r\n\r\n  struct reduce_col {\r\n    int n;\r\n\
    \    std::function<T(int, int)> f;\r\n    int cur_row;\r\n    std::vector<int>\
    \ cols;\r\n    reduce_row rec;\r\n\r\n    reduce_col(int n_) : n(n_), f(), cur_row(0),\
    \ cols(), rec(n) {}\r\n\r\n    void set_f(std::function<T(int, int)> f_) {\r\n\
    \      f = f_;\r\n      rec.set_f([&](int i, int j) -> T { return f(i, cols[j]);\
    \ });\r\n    }\r\n\r\n    int get_argmin() {\r\n      const int cur_row_ = cur_row;\r\
    \n      cur_row += 1;\r\n      const auto cs = [&]() -> std::vector<int> {\r\n\
    \        if (cur_row_ == 0) {\r\n          return {{0}};\r\n        } else {\r\
    \n          return {{2 * cur_row_ - 1, 2 * cur_row_}};\r\n        }\r\n      }();\r\
    \n      for (const int j : cs) {\r\n        while ([&]() {\r\n          const\
    \ int size = cols.size();\r\n          return size != cur_row_ && f(size - 1,\
    \ cols.back()) > f(size - 1, j);\r\n        }()) {\r\n          cols.pop_back();\r\
    \n        }\r\n        if (cols.size() != n) {\r\n          cols.push_back(j);\r\
    \n        }\r\n      }\r\n      return cols[rec.get_argmin()];\r\n    }\r\n  };\r\
    \n\r\n  std::unique_ptr<reduce_row> base;\r\n\r\npublic:\r\n  larsch(int n, std::function<T(int,\
    \ int)> f)\r\n      : base(std::make_unique<reduce_row>(n)) {\r\n    base->set_f(f);\r\
    \n  }\r\n\r\n  int get_argmin() { return base->get_argmin(); }\r\n};\r\n\r\n/**\r\
    \n * @brief LARSCH Algorithm\r\n * @docs docs/larsch.md\r\n */\r\n"
  dependsOn: []
  isVerificationFile: false
  path: algorithm/larsch.cpp
  requiredBy: []
  timestamp: '2021-04-07 08:01:56+09:00'
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
大雑把に言えば、このアルゴリズムはある種の動的計画法を高速化するものである。
出力の値は $i$ の昇順に計算され、$A _ {i , j + 1}$ の値は
$\mathop {\rm arg \, min} \limits _ k A _ {j, k}$
が計算された後にアクセス出来れば良い。
したがって $A _ {i , j}$ は ${\rm dp} \lbrack j \rbrack$ から
${\rm dp} \lbrack i + 1 \rbrack$ への遷移とみなすことが出来る。
[SMAWK Algorithm](https://noshi91.github.io/Library/library/algorithm/smawk.cpp.html)
を on-line な動的計画法に適用出来るよう工夫したものとも言える。
実際、アルゴリズムの内容も SMAWK Algorithm に類似している。

## 文献
-   Larmore, L. L., & Schieber, B. (1991). On-line dynamic programming with applications to the prediction of RNA secondary structure. Journal of Algorithms, 12(3), 490-515.

## 語

#### totally monotone
[SMAWK Algorithm](https://noshi91.github.io/Library/library/algorithm/smawk.cpp.html) を参照せよ。
ただしこのページでは文献に合わせて、$\min$ による定義を採用している。
