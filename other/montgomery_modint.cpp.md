---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://min-25.hatenablog.com/entry/2017/08/20/171214
  bundledCode: "#line 1 \"other/montgomery_modint.cpp\"\n/*\nreference: https://min-25.hatenablog.com/entry/2017/08/20/171214\n\
    */\n\n#include <cassert>\n#include <cstdint>\n#include <limits>\n#include <utility>\n\
    \nclass montgomery_modint {\n  using Self = montgomery_modint;\n\n  using u64\
    \ = std::uint64_t;\n  using u32 = std::uint32_t;\n  using i32 = std::int32_t;\n\
    \n  static u32 mod;\n  static u32 inv;\n  static u32 r2;\n\n  static u32 reduce(const\
    \ u64 x) noexcept {\n    const u32 y = u32(x >> 32) - u32(u64(u32(x) * inv) *\
    \ mod >> 32);\n    return i32(y) < 0 ? y + mod : y;\n  }\n\n  u32 v;\n\npublic:\n\
    \  montgomery_modint(const u32 x = 0) noexcept : v(reduce(u64(x) * r2)) {}\n\n\
    \  u32 value() const noexcept { return reduce(v); }\n\n  Self operator+(const\
    \ Self r) const noexcept { return Self(*this) += r; }\n  Self operator-(const\
    \ Self r) const noexcept { return Self(*this) -= r; }\n  Self operator*(const\
    \ Self r) const noexcept { return Self(*this) *= r; }\n  Self operator/(const\
    \ Self r) const noexcept { return Self(*this) /= r; }\n\n  Self &operator+=(const\
    \ Self r) noexcept {\n    v += r.v;\n    if (v >= mod)\n      v -= mod;\n    return\
    \ *this;\n  }\n  Self &operator-=(const Self r) noexcept {\n    if (v < r.v)\n\
    \      v += mod;\n    v -= r.v;\n    return *this;\n  }\n  Self &operator*=(const\
    \ Self r) noexcept {\n    v = reduce(u64(v) * r.v);\n    return *this;\n  }\n\
    \  Self &operator/=(const Self r) noexcept {\n    u32 a = mod;\n    u32 b = reduce(reduce(r.v));\n\
    \    u32 s = 0;\n    u32 t = 1;\n    while (b != 1) {\n      const u32 q = a /\
    \ b;\n      std::swap(a -= q * b, b);\n      std::swap(s -= q * t, t);\n    }\n\
    \    if (i32(t) < 0)\n      t += mod;\n    v = reduce(u64(v) * t);\n    return\
    \ *this;\n  }\n\n  static void set_mod(const u32 m) noexcept {\n    assert(m <\
    \ u32(1) << 31);\n    assert(m % 2 == 1);\n    mod = m;\n    inv = m;\n    for\
    \ (u32 i = 0; i != 4; i += 1)\n      inv *= u32(2) - inv * m;\n    r2 = -u64(m)\
    \ % m;\n  }\n  static u32 get_mod() noexcept { return mod; }\n};\ntypename montgomery_modint::u32\
    \ montgomery_modint::mod;\ntypename montgomery_modint::u32 montgomery_modint::inv;\n\
    typename montgomery_modint::u32 montgomery_modint::r2;\n"
  code: "/*\nreference: https://min-25.hatenablog.com/entry/2017/08/20/171214\n*/\n\
    \n#include <cassert>\n#include <cstdint>\n#include <limits>\n#include <utility>\n\
    \nclass montgomery_modint {\n  using Self = montgomery_modint;\n\n  using u64\
    \ = std::uint64_t;\n  using u32 = std::uint32_t;\n  using i32 = std::int32_t;\n\
    \n  static u32 mod;\n  static u32 inv;\n  static u32 r2;\n\n  static u32 reduce(const\
    \ u64 x) noexcept {\n    const u32 y = u32(x >> 32) - u32(u64(u32(x) * inv) *\
    \ mod >> 32);\n    return i32(y) < 0 ? y + mod : y;\n  }\n\n  u32 v;\n\npublic:\n\
    \  montgomery_modint(const u32 x = 0) noexcept : v(reduce(u64(x) * r2)) {}\n\n\
    \  u32 value() const noexcept { return reduce(v); }\n\n  Self operator+(const\
    \ Self r) const noexcept { return Self(*this) += r; }\n  Self operator-(const\
    \ Self r) const noexcept { return Self(*this) -= r; }\n  Self operator*(const\
    \ Self r) const noexcept { return Self(*this) *= r; }\n  Self operator/(const\
    \ Self r) const noexcept { return Self(*this) /= r; }\n\n  Self &operator+=(const\
    \ Self r) noexcept {\n    v += r.v;\n    if (v >= mod)\n      v -= mod;\n    return\
    \ *this;\n  }\n  Self &operator-=(const Self r) noexcept {\n    if (v < r.v)\n\
    \      v += mod;\n    v -= r.v;\n    return *this;\n  }\n  Self &operator*=(const\
    \ Self r) noexcept {\n    v = reduce(u64(v) * r.v);\n    return *this;\n  }\n\
    \  Self &operator/=(const Self r) noexcept {\n    u32 a = mod;\n    u32 b = reduce(reduce(r.v));\n\
    \    u32 s = 0;\n    u32 t = 1;\n    while (b != 1) {\n      const u32 q = a /\
    \ b;\n      std::swap(a -= q * b, b);\n      std::swap(s -= q * t, t);\n    }\n\
    \    if (i32(t) < 0)\n      t += mod;\n    v = reduce(u64(v) * t);\n    return\
    \ *this;\n  }\n\n  static void set_mod(const u32 m) noexcept {\n    assert(m <\
    \ u32(1) << 31);\n    assert(m % 2 == 1);\n    mod = m;\n    inv = m;\n    for\
    \ (u32 i = 0; i != 4; i += 1)\n      inv *= u32(2) - inv * m;\n    r2 = -u64(m)\
    \ % m;\n  }\n  static u32 get_mod() noexcept { return mod; }\n};\ntypename montgomery_modint::u32\
    \ montgomery_modint::mod;\ntypename montgomery_modint::u32 montgomery_modint::inv;\n\
    typename montgomery_modint::u32 montgomery_modint::r2;"
  dependsOn: []
  isVerificationFile: false
  path: other/montgomery_modint.cpp
  requiredBy: []
  timestamp: '2020-01-06 19:32:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/montgomery_modint.cpp
layout: document
redirect_from:
- /library/other/montgomery_modint.cpp
- /library/other/montgomery_modint.cpp.html
title: other/montgomery_modint.cpp
---
