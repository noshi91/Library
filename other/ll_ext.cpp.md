---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/ll_ext.cpp\"\n#include <cassert>\r\n#include <iostream>\r\
    \n#include <limits>\r\n\r\nclass ll_ext {\r\npublic:\r\n  using ll = long long\
    \ int;\r\n\r\n  enum tag_t {\r\n    finite_tag,\r\n    p_inf_tag,\r\n    n_inf_tag,\r\
    \n  };\r\n\r\n  // static constexpr bool infinity_same = true;\r\n\r\n  ll v;\r\
    \n  tag_t t;\r\n\r\nprivate:\r\n  static constexpr ll ll_min = std::numeric_limits<ll>::min();\r\
    \n  static constexpr ll ll_max = std::numeric_limits<ll>::max();\r\n\r\n  static\
    \ constexpr bool add_overflow_base(const ll a, const ll b, ll *res) {\r\n    if\
    \ (a >= 0) {\r\n      if (b >= 0) {\r\n        if (a > ll_max - b) {\r\n     \
    \     return true;\r\n        }\r\n      }\r\n    } else {\r\n      if (b < 0)\
    \ {\r\n        if (a < ll_min - b) {\r\n          return true;\r\n        }\r\n\
    \      }\r\n    }\r\n    *res = a + b;\r\n    return false;\r\n  }\r\n\r\n  static\
    \ constexpr bool add_overflow(const ll a, const ll b, ll *res) {\r\n#ifdef __GNUC__\r\
    \n    return __builtin_saddll_overflow(a, b, res);\r\n#else\r\n    return add_overflow_base(a,\
    \ b, res);\r\n#endif\r\n  }\r\n\r\n  static constexpr bool sub_overflow_base(const\
    \ ll a, const ll b, ll *res) {\r\n    if (a >= 0) {\r\n      if (b < 0) {\r\n\
    \        if (a > ll_max + b) {\r\n          return true;\r\n        }\r\n    \
    \  }\r\n    } else {\r\n      if (b >= 0) {\r\n        if (a < ll_min + b) {\r\
    \n          return true;\r\n        }\r\n      }\r\n    }\r\n    *res = a - b;\r\
    \n    return false;\r\n  }\r\n\r\n  static constexpr bool sub_overflow(const ll\
    \ a, const ll b, ll *res) {\r\n#ifdef __GNUC__\r\n    return __builtin_ssubll_overflow(a,\
    \ b, res);\r\n#else\r\n    return sub_overflow_base(a, b, res);\r\n#endif\r\n\
    \  }\r\n\r\n  static constexpr bool mul_overflow_base(const ll a, const ll b,\
    \ ll *res) {\r\n    if (a > 0) {\r\n      if (b > 0) {\r\n        if (a > ll_max\
    \ / b) {\r\n          return true;\r\n        }\r\n      } else if (b < 0) {\r\
    \n        if (b < ll_min / a) {\r\n          return true;\r\n        }\r\n   \
    \   }\r\n    } else if (a < 0) {\r\n      if (b > 0) {\r\n        if (a < ll_min\
    \ / b) {\r\n          return true;\r\n        }\r\n      } else if (b < 0) {\r\
    \n        if (a < ll_max / b) {\r\n          return true;\r\n        }\r\n   \
    \   }\r\n    }\r\n    *res = a * b;\r\n    return false;\r\n  }\r\n\r\n  static\
    \ constexpr bool mul_overflow(const ll a, const ll b, ll *res) {\r\n#ifdef __GNUC__\r\
    \n    return __builtin_smulll_overflow(a, b, res);\r\n#else\r\n    return mul_overflow_base(a,\
    \ b, res);\r\n#endif\r\n  }\r\n\r\npublic:\r\n  static constexpr ll_ext p_infinity()\
    \ {\r\n    ll_ext ret;\r\n    ret.t = p_inf_tag;\r\n    return ret;\r\n  }\r\n\
    \  static constexpr ll_ext n_infinity() {\r\n    ll_ext ret;\r\n    ret.t = n_inf_tag;\r\
    \n    return ret;\r\n  }\r\n\r\n  constexpr ll_ext() noexcept : v(0), t(finite_tag)\
    \ {}\r\n  constexpr ll_ext(const ll x) noexcept : v(x), t(finite_tag) {}\r\n\r\
    \n  friend constexpr ll_ext operator+(const ll_ext &l, const ll_ext &r) noexcept\
    \ {\r\n    switch (l.t) {\r\n    case finite_tag: {\r\n      switch (r.t) {\r\n\
    \      case finite_tag: {\r\n        ll x = 0;\r\n        assert(!add_overflow(l.v,\
    \ r.v, &x) && \"overflow: +\");\r\n        return x;\r\n      } break;\r\n   \
    \   case p_inf_tag: {\r\n        return p_infinity();\r\n      } break;\r\n  \
    \    case n_inf_tag: {\r\n        return n_infinity();\r\n      } break;\r\n \
    \     }\r\n    } break;\r\n    case p_inf_tag: {\r\n      switch (r.t) {\r\n \
    \     case finite_tag: {\r\n        return p_infinity();\r\n      } break;\r\n\
    \      case p_inf_tag: {\r\n        return p_infinity();\r\n      } break;\r\n\
    \      case n_inf_tag: {\r\n        assert(false && \"p_inf + n_inf\");\r\n  \
    \      return 0;\r\n      } break;\r\n      }\r\n    } break;\r\n    case n_inf_tag:\
    \ {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n        return n_infinity();\r\
    \n      } break;\r\n      case p_inf_tag: {\r\n        assert(false && \"n_inf\
    \ + p_inf\");\r\n        return 0;\r\n      } break;\r\n      case n_inf_tag:\
    \ {\r\n        return n_infinity();\r\n      } break;\r\n      }\r\n    }\r\n\
    \    }\r\n  }\r\n\r\n  friend constexpr ll_ext operator-(const ll_ext &l, const\
    \ ll_ext &r) noexcept {\r\n    switch (l.t) {\r\n    case finite_tag: {\r\n  \
    \    switch (r.t) {\r\n      case finite_tag: {\r\n        ll x = 0;\r\n     \
    \   assert(!sub_overflow(l.v, r.v, &x) && \"overflow: -\");\r\n        return\
    \ x;\r\n      } break;\r\n      case p_inf_tag: {\r\n        return n_infinity();\r\
    \n      } break;\r\n      case n_inf_tag: {\r\n        return p_infinity();\r\n\
    \      } break;\r\n      }\r\n    } break;\r\n    case p_inf_tag: {\r\n      switch\
    \ (r.t) {\r\n      case finite_tag: {\r\n        return p_infinity();\r\n    \
    \  } break;\r\n      case p_inf_tag: {\r\n        assert(false && \"p_inf - p_inf\"\
    );\r\n        return 0;\r\n      } break;\r\n      case n_inf_tag: {\r\n     \
    \   return p_infinity();\r\n      } break;\r\n      }\r\n    } break;\r\n    case\
    \ n_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n       \
    \ return n_infinity();\r\n      } break;\r\n      case p_inf_tag: {\r\n      \
    \  return n_infinity();\r\n      } break;\r\n      case n_inf_tag: {\r\n     \
    \   assert(false && \"n_inf - n_inf\");\r\n        return 0;\r\n      } break;\r\
    \n      }\r\n    }\r\n    }\r\n  }\r\n\r\n  friend constexpr ll_ext operator*(const\
    \ ll_ext &l, const ll_ext &r) noexcept {\r\n    switch (l.t) {\r\n    case finite_tag:\
    \ {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n        ll x = 0;\r\
    \n        assert(!mul_overflow(l.v, r.v, &x) && \"overflow: *\");\r\n        return\
    \ x;\r\n      } break;\r\n      case p_inf_tag: {\r\n        if (l.v > 0) {\r\n\
    \          return p_infinity();\r\n        } else if (l.v == 0) {\r\n        \
    \  return 0;\r\n        } else {\r\n          return n_infinity();\r\n       \
    \ }\r\n      } break;\r\n      case n_inf_tag: {\r\n        if (l.v > 0) {\r\n\
    \          return n_infinity();\r\n        } else if (l.v == 0) {\r\n        \
    \  return 0;\r\n        } else {\r\n          return p_infinity();\r\n       \
    \ }\r\n      } break;\r\n      }\r\n    } break;\r\n    case p_inf_tag: {\r\n\
    \      switch (r.t) {\r\n      case finite_tag: {\r\n        if (r.v > 0) {\r\n\
    \          return p_infinity();\r\n        } else if (r.v == 0) {\r\n        \
    \  return 0;\r\n        } else {\r\n          return n_infinity();\r\n       \
    \ }\r\n      } break;\r\n      case p_inf_tag: {\r\n        return p_infinity();\r\
    \n      } break;\r\n      case n_inf_tag: {\r\n        return n_infinity();\r\n\
    \      } break;\r\n      }\r\n    } break;\r\n    case n_inf_tag: {\r\n      switch\
    \ (r.t) {\r\n      case finite_tag: {\r\n        if (r.v > 0) {\r\n          return\
    \ n_infinity();\r\n        } else if (r.v == 0) {\r\n          return 0;\r\n \
    \       } else {\r\n          return p_infinity();\r\n        }\r\n      } break;\r\
    \n      case p_inf_tag: {\r\n        return n_infinity();\r\n      } break;\r\n\
    \      case n_inf_tag: {\r\n        return p_infinity();\r\n      } break;\r\n\
    \      }\r\n    }\r\n    }\r\n  }\r\n\r\n  friend constexpr ll_ext operator/(const\
    \ ll_ext &l, const ll_ext &r) noexcept {\r\n    switch (l.t) {\r\n    case finite_tag:\
    \ {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n        assert(r.v\
    \ != 0 && \"division by zero: /\");\r\n        assert(!(l.v == ll_min && r.v ==\
    \ -1) && \"overflow: /\");\r\n        return l.v / r.v;\r\n      } break;\r\n\
    \      case p_inf_tag: {\r\n        return 0;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        return 0;\r\n      } break;\r\n      }\r\n    } break;\r\
    \n    case p_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n\
    \        if (r.v > 0) {\r\n          return p_infinity();\r\n        } else if\
    \ (r.v == 0) {\r\n          assert(false && \"division by zero: /\");\r\n    \
    \    } else {\r\n          return n_infinity();\r\n        }\r\n      } break;\r\
    \n      case p_inf_tag: {\r\n        assert(false && \"p_inf / p_inf\");\r\n \
    \       return 0;\r\n      } break;\r\n      case n_inf_tag: {\r\n        assert(false\
    \ && \"p_inf / n_inf\");\r\n        return 0;\r\n      } break;\r\n      }\r\n\
    \    } break;\r\n    case n_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag:\
    \ {\r\n        if (r.v > 0) {\r\n          return n_infinity();\r\n        } else\
    \ if (r.v == 0) {\r\n          assert(false && \"division by zero: /\");\r\n \
    \       } else {\r\n          return p_infinity();\r\n        }\r\n      } break;\r\
    \n      case p_inf_tag: {\r\n        assert(false && \"n_inf / p_inf\");\r\n \
    \       return 0;\r\n      } break;\r\n      case n_inf_tag: {\r\n        assert(false\
    \ && \"n_inf / n_inf\");\r\n        return 0;\r\n      } break;\r\n      }\r\n\
    \    }\r\n    }\r\n  }\r\n\r\n  friend constexpr ll_ext operator%(const ll_ext\
    \ &l, const ll_ext &r) noexcept {\r\n    switch (l.t) {\r\n    case finite_tag:\
    \ {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n        assert(r.v\
    \ != 0 && \"division by zero: %\");\r\n        assert(!(l.v == ll_min && r.v ==\
    \ -1) && \"overflow: %\");\r\n        return l.v % r.v;\r\n      } break;\r\n\
    \      case p_inf_tag: {\r\n        return l.v;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        return l.v;\r\n      } break;\r\n      }\r\n    } break;\r\
    \n    case p_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n\
    \        assert(false && \"p_inf % finite\");\r\n        return 0;\r\n      }\
    \ break;\r\n      case p_inf_tag: {\r\n        assert(false && \"p_inf % p_inf\"\
    );\r\n        return 0;\r\n      } break;\r\n      case n_inf_tag: {\r\n     \
    \   assert(false && \"p_inf % n_inf\");\r\n        return 0;\r\n      } break;\r\
    \n      }\r\n    } break;\r\n    case n_inf_tag: {\r\n      switch (r.t) {\r\n\
    \      case finite_tag: {\r\n        assert(false && \"n_inf % finite\");\r\n\
    \        return 0;\r\n      } break;\r\n      case p_inf_tag: {\r\n        assert(false\
    \ && \"n_inf % p_inf\");\r\n        return 0;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        assert(false && \"n_inf % n_inf\");\r\n        return\
    \ 0;\r\n      } break;\r\n      }\r\n    }\r\n    }\r\n  }\r\n\r\n  constexpr\
    \ ll_ext operator+() const noexcept { return *this; }\r\n\r\n  constexpr ll_ext\
    \ operator-() const noexcept {\r\n    switch (t) {\r\n    case finite_tag: {\r\
    \n      assert(v != ll_min && \"overflow: unary -\");\r\n      return -v;\r\n\
    \    } break;\r\n    case p_inf_tag: {\r\n      return n_infinity();\r\n    }\
    \ break;\r\n    case n_inf_tag: {\r\n      return p_infinity();\r\n    } break;\r\
    \n    }\r\n  }\r\n\r\n  constexpr ll_ext &operator+=(const ll_ext &r) noexcept\
    \ {\r\n    return *this = *this + r;\r\n  }\r\n\r\n  constexpr ll_ext &operator-=(const\
    \ ll_ext &r) noexcept {\r\n    return *this = *this - r;\r\n  }\r\n\r\n  constexpr\
    \ ll_ext &operator*=(const ll_ext &r) noexcept {\r\n    return *this = *this *\
    \ r;\r\n  }\r\n\r\n  constexpr ll_ext &operator/=(const ll_ext &r) noexcept {\r\
    \n    return *this = *this / r;\r\n  }\r\n\r\n  constexpr ll_ext &operator%=(const\
    \ ll_ext &r) noexcept {\r\n    return *this = *this % r;\r\n  }\r\n\r\n  friend\
    \ constexpr bool operator==(const ll_ext &l, const ll_ext &r) noexcept {\r\n \
    \   return l.v == r.v && l.t == r.t;\r\n  }\r\n\r\n  friend constexpr bool operator!=(const\
    \ ll_ext &l, const ll_ext &r) noexcept {\r\n    return !(l == r);\r\n  }\r\n\r\
    \n  friend constexpr bool operator<(const ll_ext &l, const ll_ext &r) noexcept\
    \ {\r\n    switch (l.t) {\r\n    case finite_tag: {\r\n      switch (r.t) {\r\n\
    \      case finite_tag: {\r\n        return l.v < r.v;\r\n      } break;\r\n \
    \     case p_inf_tag: {\r\n        return true;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        return false;\r\n      } break;\r\n      }\r\n    }\
    \ break;\r\n    case p_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag:\
    \ {\r\n        return false;\r\n      } break;\r\n      case p_inf_tag: {\r\n\
    \        // assert(false && \"p_inf < p_inf\");\r\n        return false;\r\n \
    \     } break;\r\n      case n_inf_tag: {\r\n        return false;\r\n      }\
    \ break;\r\n      }\r\n    } break;\r\n    case n_inf_tag: {\r\n      switch (r.t)\
    \ {\r\n      case finite_tag: {\r\n        return true;\r\n      } break;\r\n\
    \      case p_inf_tag: {\r\n        return true;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        // assert(false && \"n_inf < n_inf\");\r\n        return\
    \ false;\r\n      } break;\r\n      }\r\n    }\r\n    }\r\n  }\r\n\r\n  friend\
    \ constexpr bool operator<=(const ll_ext &l, const ll_ext &r) noexcept {\r\n \
    \   return !(r < l);\r\n  }\r\n\r\n  friend constexpr bool operator>(const ll_ext\
    \ &l, const ll_ext &r) noexcept {\r\n    return r < l;\r\n  }\r\n\r\n  friend\
    \ constexpr bool operator>=(const ll_ext &l, const ll_ext &r) noexcept {\r\n \
    \   return !(l < r);\r\n  }\r\n\r\n  friend std::istream &operator>>(std::istream\
    \ &is, ll_ext &x) {\r\n    x.t = finite_tag;\r\n    is >> x.v;\r\n    return is;\r\
    \n  }\r\n\r\n  friend std::ostream &operator<<(std::ostream &os, const ll_ext\
    \ &x) {\r\n    switch (x.t) {\r\n    case finite_tag: {\r\n      os << x.v;\r\n\
    \      return os;\r\n    } break;\r\n    case p_inf_tag: {\r\n      assert(false\
    \ && \"ostream << p_inf\");\r\n      return os;\r\n    } break;\r\n    case n_inf_tag:\
    \ {\r\n      assert(false && \"ostream << n_inf\");\r\n      return os;\r\n  \
    \  } break;\r\n    }\r\n  }\r\n};\r\n"
  code: "#include <cassert>\r\n#include <iostream>\r\n#include <limits>\r\n\r\nclass\
    \ ll_ext {\r\npublic:\r\n  using ll = long long int;\r\n\r\n  enum tag_t {\r\n\
    \    finite_tag,\r\n    p_inf_tag,\r\n    n_inf_tag,\r\n  };\r\n\r\n  // static\
    \ constexpr bool infinity_same = true;\r\n\r\n  ll v;\r\n  tag_t t;\r\n\r\nprivate:\r\
    \n  static constexpr ll ll_min = std::numeric_limits<ll>::min();\r\n  static constexpr\
    \ ll ll_max = std::numeric_limits<ll>::max();\r\n\r\n  static constexpr bool add_overflow_base(const\
    \ ll a, const ll b, ll *res) {\r\n    if (a >= 0) {\r\n      if (b >= 0) {\r\n\
    \        if (a > ll_max - b) {\r\n          return true;\r\n        }\r\n    \
    \  }\r\n    } else {\r\n      if (b < 0) {\r\n        if (a < ll_min - b) {\r\n\
    \          return true;\r\n        }\r\n      }\r\n    }\r\n    *res = a + b;\r\
    \n    return false;\r\n  }\r\n\r\n  static constexpr bool add_overflow(const ll\
    \ a, const ll b, ll *res) {\r\n#ifdef __GNUC__\r\n    return __builtin_saddll_overflow(a,\
    \ b, res);\r\n#else\r\n    return add_overflow_base(a, b, res);\r\n#endif\r\n\
    \  }\r\n\r\n  static constexpr bool sub_overflow_base(const ll a, const ll b,\
    \ ll *res) {\r\n    if (a >= 0) {\r\n      if (b < 0) {\r\n        if (a > ll_max\
    \ + b) {\r\n          return true;\r\n        }\r\n      }\r\n    } else {\r\n\
    \      if (b >= 0) {\r\n        if (a < ll_min + b) {\r\n          return true;\r\
    \n        }\r\n      }\r\n    }\r\n    *res = a - b;\r\n    return false;\r\n\
    \  }\r\n\r\n  static constexpr bool sub_overflow(const ll a, const ll b, ll *res)\
    \ {\r\n#ifdef __GNUC__\r\n    return __builtin_ssubll_overflow(a, b, res);\r\n\
    #else\r\n    return sub_overflow_base(a, b, res);\r\n#endif\r\n  }\r\n\r\n  static\
    \ constexpr bool mul_overflow_base(const ll a, const ll b, ll *res) {\r\n    if\
    \ (a > 0) {\r\n      if (b > 0) {\r\n        if (a > ll_max / b) {\r\n       \
    \   return true;\r\n        }\r\n      } else if (b < 0) {\r\n        if (b <\
    \ ll_min / a) {\r\n          return true;\r\n        }\r\n      }\r\n    } else\
    \ if (a < 0) {\r\n      if (b > 0) {\r\n        if (a < ll_min / b) {\r\n    \
    \      return true;\r\n        }\r\n      } else if (b < 0) {\r\n        if (a\
    \ < ll_max / b) {\r\n          return true;\r\n        }\r\n      }\r\n    }\r\
    \n    *res = a * b;\r\n    return false;\r\n  }\r\n\r\n  static constexpr bool\
    \ mul_overflow(const ll a, const ll b, ll *res) {\r\n#ifdef __GNUC__\r\n    return\
    \ __builtin_smulll_overflow(a, b, res);\r\n#else\r\n    return mul_overflow_base(a,\
    \ b, res);\r\n#endif\r\n  }\r\n\r\npublic:\r\n  static constexpr ll_ext p_infinity()\
    \ {\r\n    ll_ext ret;\r\n    ret.t = p_inf_tag;\r\n    return ret;\r\n  }\r\n\
    \  static constexpr ll_ext n_infinity() {\r\n    ll_ext ret;\r\n    ret.t = n_inf_tag;\r\
    \n    return ret;\r\n  }\r\n\r\n  constexpr ll_ext() noexcept : v(0), t(finite_tag)\
    \ {}\r\n  constexpr ll_ext(const ll x) noexcept : v(x), t(finite_tag) {}\r\n\r\
    \n  friend constexpr ll_ext operator+(const ll_ext &l, const ll_ext &r) noexcept\
    \ {\r\n    switch (l.t) {\r\n    case finite_tag: {\r\n      switch (r.t) {\r\n\
    \      case finite_tag: {\r\n        ll x = 0;\r\n        assert(!add_overflow(l.v,\
    \ r.v, &x) && \"overflow: +\");\r\n        return x;\r\n      } break;\r\n   \
    \   case p_inf_tag: {\r\n        return p_infinity();\r\n      } break;\r\n  \
    \    case n_inf_tag: {\r\n        return n_infinity();\r\n      } break;\r\n \
    \     }\r\n    } break;\r\n    case p_inf_tag: {\r\n      switch (r.t) {\r\n \
    \     case finite_tag: {\r\n        return p_infinity();\r\n      } break;\r\n\
    \      case p_inf_tag: {\r\n        return p_infinity();\r\n      } break;\r\n\
    \      case n_inf_tag: {\r\n        assert(false && \"p_inf + n_inf\");\r\n  \
    \      return 0;\r\n      } break;\r\n      }\r\n    } break;\r\n    case n_inf_tag:\
    \ {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n        return n_infinity();\r\
    \n      } break;\r\n      case p_inf_tag: {\r\n        assert(false && \"n_inf\
    \ + p_inf\");\r\n        return 0;\r\n      } break;\r\n      case n_inf_tag:\
    \ {\r\n        return n_infinity();\r\n      } break;\r\n      }\r\n    }\r\n\
    \    }\r\n  }\r\n\r\n  friend constexpr ll_ext operator-(const ll_ext &l, const\
    \ ll_ext &r) noexcept {\r\n    switch (l.t) {\r\n    case finite_tag: {\r\n  \
    \    switch (r.t) {\r\n      case finite_tag: {\r\n        ll x = 0;\r\n     \
    \   assert(!sub_overflow(l.v, r.v, &x) && \"overflow: -\");\r\n        return\
    \ x;\r\n      } break;\r\n      case p_inf_tag: {\r\n        return n_infinity();\r\
    \n      } break;\r\n      case n_inf_tag: {\r\n        return p_infinity();\r\n\
    \      } break;\r\n      }\r\n    } break;\r\n    case p_inf_tag: {\r\n      switch\
    \ (r.t) {\r\n      case finite_tag: {\r\n        return p_infinity();\r\n    \
    \  } break;\r\n      case p_inf_tag: {\r\n        assert(false && \"p_inf - p_inf\"\
    );\r\n        return 0;\r\n      } break;\r\n      case n_inf_tag: {\r\n     \
    \   return p_infinity();\r\n      } break;\r\n      }\r\n    } break;\r\n    case\
    \ n_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n       \
    \ return n_infinity();\r\n      } break;\r\n      case p_inf_tag: {\r\n      \
    \  return n_infinity();\r\n      } break;\r\n      case n_inf_tag: {\r\n     \
    \   assert(false && \"n_inf - n_inf\");\r\n        return 0;\r\n      } break;\r\
    \n      }\r\n    }\r\n    }\r\n  }\r\n\r\n  friend constexpr ll_ext operator*(const\
    \ ll_ext &l, const ll_ext &r) noexcept {\r\n    switch (l.t) {\r\n    case finite_tag:\
    \ {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n        ll x = 0;\r\
    \n        assert(!mul_overflow(l.v, r.v, &x) && \"overflow: *\");\r\n        return\
    \ x;\r\n      } break;\r\n      case p_inf_tag: {\r\n        if (l.v > 0) {\r\n\
    \          return p_infinity();\r\n        } else if (l.v == 0) {\r\n        \
    \  return 0;\r\n        } else {\r\n          return n_infinity();\r\n       \
    \ }\r\n      } break;\r\n      case n_inf_tag: {\r\n        if (l.v > 0) {\r\n\
    \          return n_infinity();\r\n        } else if (l.v == 0) {\r\n        \
    \  return 0;\r\n        } else {\r\n          return p_infinity();\r\n       \
    \ }\r\n      } break;\r\n      }\r\n    } break;\r\n    case p_inf_tag: {\r\n\
    \      switch (r.t) {\r\n      case finite_tag: {\r\n        if (r.v > 0) {\r\n\
    \          return p_infinity();\r\n        } else if (r.v == 0) {\r\n        \
    \  return 0;\r\n        } else {\r\n          return n_infinity();\r\n       \
    \ }\r\n      } break;\r\n      case p_inf_tag: {\r\n        return p_infinity();\r\
    \n      } break;\r\n      case n_inf_tag: {\r\n        return n_infinity();\r\n\
    \      } break;\r\n      }\r\n    } break;\r\n    case n_inf_tag: {\r\n      switch\
    \ (r.t) {\r\n      case finite_tag: {\r\n        if (r.v > 0) {\r\n          return\
    \ n_infinity();\r\n        } else if (r.v == 0) {\r\n          return 0;\r\n \
    \       } else {\r\n          return p_infinity();\r\n        }\r\n      } break;\r\
    \n      case p_inf_tag: {\r\n        return n_infinity();\r\n      } break;\r\n\
    \      case n_inf_tag: {\r\n        return p_infinity();\r\n      } break;\r\n\
    \      }\r\n    }\r\n    }\r\n  }\r\n\r\n  friend constexpr ll_ext operator/(const\
    \ ll_ext &l, const ll_ext &r) noexcept {\r\n    switch (l.t) {\r\n    case finite_tag:\
    \ {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n        assert(r.v\
    \ != 0 && \"division by zero: /\");\r\n        assert(!(l.v == ll_min && r.v ==\
    \ -1) && \"overflow: /\");\r\n        return l.v / r.v;\r\n      } break;\r\n\
    \      case p_inf_tag: {\r\n        return 0;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        return 0;\r\n      } break;\r\n      }\r\n    } break;\r\
    \n    case p_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n\
    \        if (r.v > 0) {\r\n          return p_infinity();\r\n        } else if\
    \ (r.v == 0) {\r\n          assert(false && \"division by zero: /\");\r\n    \
    \    } else {\r\n          return n_infinity();\r\n        }\r\n      } break;\r\
    \n      case p_inf_tag: {\r\n        assert(false && \"p_inf / p_inf\");\r\n \
    \       return 0;\r\n      } break;\r\n      case n_inf_tag: {\r\n        assert(false\
    \ && \"p_inf / n_inf\");\r\n        return 0;\r\n      } break;\r\n      }\r\n\
    \    } break;\r\n    case n_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag:\
    \ {\r\n        if (r.v > 0) {\r\n          return n_infinity();\r\n        } else\
    \ if (r.v == 0) {\r\n          assert(false && \"division by zero: /\");\r\n \
    \       } else {\r\n          return p_infinity();\r\n        }\r\n      } break;\r\
    \n      case p_inf_tag: {\r\n        assert(false && \"n_inf / p_inf\");\r\n \
    \       return 0;\r\n      } break;\r\n      case n_inf_tag: {\r\n        assert(false\
    \ && \"n_inf / n_inf\");\r\n        return 0;\r\n      } break;\r\n      }\r\n\
    \    }\r\n    }\r\n  }\r\n\r\n  friend constexpr ll_ext operator%(const ll_ext\
    \ &l, const ll_ext &r) noexcept {\r\n    switch (l.t) {\r\n    case finite_tag:\
    \ {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n        assert(r.v\
    \ != 0 && \"division by zero: %\");\r\n        assert(!(l.v == ll_min && r.v ==\
    \ -1) && \"overflow: %\");\r\n        return l.v % r.v;\r\n      } break;\r\n\
    \      case p_inf_tag: {\r\n        return l.v;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        return l.v;\r\n      } break;\r\n      }\r\n    } break;\r\
    \n    case p_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag: {\r\n\
    \        assert(false && \"p_inf % finite\");\r\n        return 0;\r\n      }\
    \ break;\r\n      case p_inf_tag: {\r\n        assert(false && \"p_inf % p_inf\"\
    );\r\n        return 0;\r\n      } break;\r\n      case n_inf_tag: {\r\n     \
    \   assert(false && \"p_inf % n_inf\");\r\n        return 0;\r\n      } break;\r\
    \n      }\r\n    } break;\r\n    case n_inf_tag: {\r\n      switch (r.t) {\r\n\
    \      case finite_tag: {\r\n        assert(false && \"n_inf % finite\");\r\n\
    \        return 0;\r\n      } break;\r\n      case p_inf_tag: {\r\n        assert(false\
    \ && \"n_inf % p_inf\");\r\n        return 0;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        assert(false && \"n_inf % n_inf\");\r\n        return\
    \ 0;\r\n      } break;\r\n      }\r\n    }\r\n    }\r\n  }\r\n\r\n  constexpr\
    \ ll_ext operator+() const noexcept { return *this; }\r\n\r\n  constexpr ll_ext\
    \ operator-() const noexcept {\r\n    switch (t) {\r\n    case finite_tag: {\r\
    \n      assert(v != ll_min && \"overflow: unary -\");\r\n      return -v;\r\n\
    \    } break;\r\n    case p_inf_tag: {\r\n      return n_infinity();\r\n    }\
    \ break;\r\n    case n_inf_tag: {\r\n      return p_infinity();\r\n    } break;\r\
    \n    }\r\n  }\r\n\r\n  constexpr ll_ext &operator+=(const ll_ext &r) noexcept\
    \ {\r\n    return *this = *this + r;\r\n  }\r\n\r\n  constexpr ll_ext &operator-=(const\
    \ ll_ext &r) noexcept {\r\n    return *this = *this - r;\r\n  }\r\n\r\n  constexpr\
    \ ll_ext &operator*=(const ll_ext &r) noexcept {\r\n    return *this = *this *\
    \ r;\r\n  }\r\n\r\n  constexpr ll_ext &operator/=(const ll_ext &r) noexcept {\r\
    \n    return *this = *this / r;\r\n  }\r\n\r\n  constexpr ll_ext &operator%=(const\
    \ ll_ext &r) noexcept {\r\n    return *this = *this % r;\r\n  }\r\n\r\n  friend\
    \ constexpr bool operator==(const ll_ext &l, const ll_ext &r) noexcept {\r\n \
    \   return l.v == r.v && l.t == r.t;\r\n  }\r\n\r\n  friend constexpr bool operator!=(const\
    \ ll_ext &l, const ll_ext &r) noexcept {\r\n    return !(l == r);\r\n  }\r\n\r\
    \n  friend constexpr bool operator<(const ll_ext &l, const ll_ext &r) noexcept\
    \ {\r\n    switch (l.t) {\r\n    case finite_tag: {\r\n      switch (r.t) {\r\n\
    \      case finite_tag: {\r\n        return l.v < r.v;\r\n      } break;\r\n \
    \     case p_inf_tag: {\r\n        return true;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        return false;\r\n      } break;\r\n      }\r\n    }\
    \ break;\r\n    case p_inf_tag: {\r\n      switch (r.t) {\r\n      case finite_tag:\
    \ {\r\n        return false;\r\n      } break;\r\n      case p_inf_tag: {\r\n\
    \        // assert(false && \"p_inf < p_inf\");\r\n        return false;\r\n \
    \     } break;\r\n      case n_inf_tag: {\r\n        return false;\r\n      }\
    \ break;\r\n      }\r\n    } break;\r\n    case n_inf_tag: {\r\n      switch (r.t)\
    \ {\r\n      case finite_tag: {\r\n        return true;\r\n      } break;\r\n\
    \      case p_inf_tag: {\r\n        return true;\r\n      } break;\r\n      case\
    \ n_inf_tag: {\r\n        // assert(false && \"n_inf < n_inf\");\r\n        return\
    \ false;\r\n      } break;\r\n      }\r\n    }\r\n    }\r\n  }\r\n\r\n  friend\
    \ constexpr bool operator<=(const ll_ext &l, const ll_ext &r) noexcept {\r\n \
    \   return !(r < l);\r\n  }\r\n\r\n  friend constexpr bool operator>(const ll_ext\
    \ &l, const ll_ext &r) noexcept {\r\n    return r < l;\r\n  }\r\n\r\n  friend\
    \ constexpr bool operator>=(const ll_ext &l, const ll_ext &r) noexcept {\r\n \
    \   return !(l < r);\r\n  }\r\n\r\n  friend std::istream &operator>>(std::istream\
    \ &is, ll_ext &x) {\r\n    x.t = finite_tag;\r\n    is >> x.v;\r\n    return is;\r\
    \n  }\r\n\r\n  friend std::ostream &operator<<(std::ostream &os, const ll_ext\
    \ &x) {\r\n    switch (x.t) {\r\n    case finite_tag: {\r\n      os << x.v;\r\n\
    \      return os;\r\n    } break;\r\n    case p_inf_tag: {\r\n      assert(false\
    \ && \"ostream << p_inf\");\r\n      return os;\r\n    } break;\r\n    case n_inf_tag:\
    \ {\r\n      assert(false && \"ostream << n_inf\");\r\n      return os;\r\n  \
    \  } break;\r\n    }\r\n  }\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: other/ll_ext.cpp
  requiredBy: []
  timestamp: '2020-10-03 20:39:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/ll_ext.cpp
layout: document
redirect_from:
- /library/other/ll_ext.cpp
- /library/other/ll_ext.cpp.html
title: other/ll_ext.cpp
---
