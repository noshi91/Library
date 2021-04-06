---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algorithm/superset_mobius_transform.cpp
    title: "Superset M\xF6bius Transform"
  - icon: ':heavy_check_mark:'
    path: algorithm/superset_zeta_transform.cpp
    title: Superset Zeta Transform
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/modint.cpp
    title: other/modint.cpp
  - icon: ':heavy_check_mark:'
    path: other/multiplies_monoid.cpp
    title: other/multiplies_monoid.cpp
  - icon: ':heavy_check_mark:'
    path: other/plus_group.cpp
    title: other/plus_group.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3119
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3119
  bundledCode: "#line 1 \"test/zeta_transform.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3119\"\
    \n\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"algorithm/superset_mobius_transform.cpp\"\n\n#include <vector>\n\ntemplate\
    \ <class G>\nvoid superset_mobius_transform(std::vector<typename G::value_type>\
    \ &a) {\n  const usize n = a.size();\n  usize i = 1;\n  while (i < n)\n    i *=\
    \ 2;\n  while (i != 1) {\n    i /= 2;\n    for (usize j = 0; j != n; j += 1) {\n\
    \      if ((j & i) != 0)\n        a[j & ~i] = G::operation(a[j & ~i], G::inverse(a[j]));\n\
    \    }\n  }\n}\n\n/**\n * @brief Superset M\xF6bius Transform\n */\n#line 2 \"\
    algorithm/superset_zeta_transform.cpp\"\n\n#line 4 \"algorithm/superset_zeta_transform.cpp\"\
    \n\ntemplate <class S>\nvoid superset_zeta_transform(std::vector<typename S::value_type>\
    \ &a) {\n  const usize n = a.size();\n  for (usize i = 1; i < n; i *= 2) {\n \
    \   for (usize j = 0; j != n; j += 1) {\n      if ((j & i) != 0)\n        a[j\
    \ & ~i] = S::operation(a[j & ~i], a[j]);\n    }\n  }\n}\n\n/**\n * @brief Superset\
    \ Zeta Transform\n */\n#line 2 \"other/modint.cpp\"\n\ntemplate <std::uint_fast64_t\
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
    \ typename modint<Modulus>::u64 modint<Modulus>::mod;\n#line 1 \"other/multiplies_monoid.cpp\"\
    \ntemplate <class T> class multiplies_monoid {\npublic:\n  using value_type =\
    \ T;\n  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ l * r;\n  }\n  static constexpr T identity = 1;\n};\n#line 1 \"other/plus_group.cpp\"\
    \ntemplate <class T> class plus_group {\npublic:\n  using value_type = T;\n  static\
    \ constexpr T operation(const T &l, const T &r) noexcept {\n    return l + r;\n\
    \  }\n  static constexpr T identity = 0;\n  static constexpr T inverse(const T\
    \ &x) noexcept { return -x; }\n};\n#line 8 \"test/zeta_transform.test.cpp\"\n\n\
    #include <iostream>\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 13 \"test/zeta_transform.test.cpp\"\n\n  using mint\
    \ = modint<1000000007>;\n  constexpr int b = 20;\n\n  int n;\n  std::cin >> n;\n\
    \  std::vector<mint> v(1 << b, 1);\n  for (int i = 0; i != n; i += 1) {\n    int\
    \ a;\n    std::cin >> a;\n    v[a] *= 2;\n  }\n  superset_zeta_transform<multiplies_monoid<mint>>(v);\n\
    \  for (mint &e : v)\n    e -= 1;\n  superset_mobius_transform<plus_group<mint>>(v);\n\
    \  std::cout << v[0].value() << \"\\n\";\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3119\"\
    \n\n#include \"algorithm/superset_mobius_transform.cpp\"\n#include \"algorithm/superset_zeta_transform.cpp\"\
    \n#include \"other/modint.cpp\"\n#include \"other/multiplies_monoid.cpp\"\n#include\
    \ \"other/plus_group.cpp\"\n\n#include <iostream>\n\nint main() {\n#include \"\
    other/fast_ios.cpp\"\n\n  using mint = modint<1000000007>;\n  constexpr int b\
    \ = 20;\n\n  int n;\n  std::cin >> n;\n  std::vector<mint> v(1 << b, 1);\n  for\
    \ (int i = 0; i != n; i += 1) {\n    int a;\n    std::cin >> a;\n    v[a] *= 2;\n\
    \  }\n  superset_zeta_transform<multiplies_monoid<mint>>(v);\n  for (mint &e :\
    \ v)\n    e -= 1;\n  superset_mobius_transform<plus_group<mint>>(v);\n  std::cout\
    \ << v[0].value() << \"\\n\";\n}"
  dependsOn:
  - algorithm/superset_mobius_transform.cpp
  - other/int_alias.cpp
  - algorithm/superset_zeta_transform.cpp
  - other/modint.cpp
  - other/multiplies_monoid.cpp
  - other/plus_group.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/zeta_transform.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 23:32:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/zeta_transform.test.cpp
layout: document
redirect_from:
- /verify/test/zeta_transform.test.cpp
- /verify/test/zeta_transform.test.cpp.html
title: test/zeta_transform.test.cpp
---
