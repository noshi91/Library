---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lazy_segment_tree.test.cpp
    title: test/lazy_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/queue_aggregation.test.cpp
    title: test/queue_aggregation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree.test.cpp
    title: test/segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/zeta_transform.test.cpp
    title: test/zeta_transform.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/modint.cpp\"\n#include <cstdint>\n\ntemplate <std::uint_fast64_t\
    \ Modulus> class modint {\n  using u64 = std::uint_fast64_t;\n\npublic:\n  using\
    \ value_type = u64;\n\n  static constexpr u64 mod = Modulus;\n\nprivate:\n  static_assert(mod\
    \ < static_cast<u64>(1) << 32,\n                \"Modulus must be less than 2**32\"\
    );\n\n  u64 v;\n\n  constexpr modint &negate() noexcept {\n    if (v != 0)\n \
    \     v = mod - v;\n    return *this;\n  }\n\npublic:\n  constexpr modint(const\
    \ u64 x = 0) noexcept : v(x % mod) {}\n  constexpr u64 &value() noexcept { return\
    \ v; }\n  constexpr const u64 &value() const noexcept { return v; }\n  constexpr\
    \ modint operator+() const noexcept { return modint(*this); }\n  constexpr modint\
    \ operator-() const noexcept { return modint(*this).negate(); }\n  constexpr modint\
    \ operator+(const modint rhs) const noexcept {\n    return modint(*this) += rhs;\n\
    \  }\n  constexpr modint operator-(const modint rhs) const noexcept {\n    return\
    \ modint(*this) -= rhs;\n  }\n  constexpr modint operator*(const modint rhs) const\
    \ noexcept {\n    return modint(*this) *= rhs;\n  }\n  constexpr modint operator/(const\
    \ modint rhs) const noexcept {\n    return modint(*this) /= rhs;\n  }\n  constexpr\
    \ modint &operator+=(const modint rhs) noexcept {\n    v += rhs.v;\n    if (v\
    \ >= mod)\n      v -= mod;\n    return *this;\n  }\n  constexpr modint &operator-=(const\
    \ modint rhs) noexcept {\n    if (v < rhs.v)\n      v += mod;\n    v -= rhs.v;\n\
    \    return *this;\n  }\n  constexpr modint &operator*=(const modint rhs) noexcept\
    \ {\n    v = v * rhs.v % mod;\n    return *this;\n  }\n  constexpr modint &operator/=(modint\
    \ rhs) noexcept {\n    u64 exp = mod - 2;\n    while (exp != 0) {\n      if (exp\
    \ % 2 != 0)\n        *this *= rhs;\n      rhs *= rhs;\n      exp /= 2;\n    }\n\
    \    return *this;\n  }\n};\ntemplate <std::uint_fast64_t Modulus>\nconstexpr\
    \ typename modint<Modulus>::u64 modint<Modulus>::mod;\n"
  code: "#include <cstdint>\n\ntemplate <std::uint_fast64_t Modulus> class modint\
    \ {\n  using u64 = std::uint_fast64_t;\n\npublic:\n  using value_type = u64;\n\
    \n  static constexpr u64 mod = Modulus;\n\nprivate:\n  static_assert(mod < static_cast<u64>(1)\
    \ << 32,\n                \"Modulus must be less than 2**32\");\n\n  u64 v;\n\n\
    \  constexpr modint &negate() noexcept {\n    if (v != 0)\n      v = mod - v;\n\
    \    return *this;\n  }\n\npublic:\n  constexpr modint(const u64 x = 0) noexcept\
    \ : v(x % mod) {}\n  constexpr u64 &value() noexcept { return v; }\n  constexpr\
    \ const u64 &value() const noexcept { return v; }\n  constexpr modint operator+()\
    \ const noexcept { return modint(*this); }\n  constexpr modint operator-() const\
    \ noexcept { return modint(*this).negate(); }\n  constexpr modint operator+(const\
    \ modint rhs) const noexcept {\n    return modint(*this) += rhs;\n  }\n  constexpr\
    \ modint operator-(const modint rhs) const noexcept {\n    return modint(*this)\
    \ -= rhs;\n  }\n  constexpr modint operator*(const modint rhs) const noexcept\
    \ {\n    return modint(*this) *= rhs;\n  }\n  constexpr modint operator/(const\
    \ modint rhs) const noexcept {\n    return modint(*this) /= rhs;\n  }\n  constexpr\
    \ modint &operator+=(const modint rhs) noexcept {\n    v += rhs.v;\n    if (v\
    \ >= mod)\n      v -= mod;\n    return *this;\n  }\n  constexpr modint &operator-=(const\
    \ modint rhs) noexcept {\n    if (v < rhs.v)\n      v += mod;\n    v -= rhs.v;\n\
    \    return *this;\n  }\n  constexpr modint &operator*=(const modint rhs) noexcept\
    \ {\n    v = v * rhs.v % mod;\n    return *this;\n  }\n  constexpr modint &operator/=(modint\
    \ rhs) noexcept {\n    u64 exp = mod - 2;\n    while (exp != 0) {\n      if (exp\
    \ % 2 != 0)\n        *this *= rhs;\n      rhs *= rhs;\n      exp /= 2;\n    }\n\
    \    return *this;\n  }\n};\ntemplate <std::uint_fast64_t Modulus>\nconstexpr\
    \ typename modint<Modulus>::u64 modint<Modulus>::mod;"
  dependsOn: []
  isVerificationFile: false
  path: other/modint.cpp
  requiredBy: []
  timestamp: '2020-01-04 13:23:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/segment_tree.test.cpp
  - test/zeta_transform.test.cpp
  - test/lazy_segment_tree.test.cpp
  - test/queue_aggregation.test.cpp
documentation_of: other/modint.cpp
layout: document
redirect_from:
- /library/other/modint.cpp
- /library/other/modint.cpp.html
title: other/modint.cpp
---
