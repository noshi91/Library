#include <cassert>
#include <iostream>
#include <limits>

class ll_ext {
public:
  using ll = long long int;

  enum tag_t {
    finite_tag,
    p_inf_tag,
    n_inf_tag,
  };

  // static constexpr bool infinity_same = true;

  ll v;
  tag_t t;

private:
  static constexpr ll ll_min = std::numeric_limits<ll>::min();
  static constexpr ll ll_max = std::numeric_limits<ll>::max();

  static constexpr bool add_overflow_base(const ll a, const ll b, ll *res) {
    if (a >= 0) {
      if (b >= 0) {
        if (a > ll_max - b) {
          return true;
        }
      }
    } else {
      if (b < 0) {
        if (a < ll_min - b) {
          return true;
        }
      }
    }
    *res = a + b;
    return false;
  }

  static constexpr bool add_overflow(const ll a, const ll b, ll *res) {
#ifdef __GNUC__
    return __builtin_saddll_overflow(a, b, res);
#else
    return add_overflow_base(a, b, res);
#endif
  }

  static constexpr bool sub_overflow_base(const ll a, const ll b, ll *res) {
    if (a >= 0) {
      if (b < 0) {
        if (a > ll_max + b) {
          return true;
        }
      }
    } else {
      if (b >= 0) {
        if (a < ll_min + b) {
          return true;
        }
      }
    }
    *res = a - b;
    return false;
  }

  static constexpr bool sub_overflow(const ll a, const ll b, ll *res) {
#ifdef __GNUC__
    return __builtin_ssubll_overflow(a, b, res);
#else
    return sub_overflow_base(a, b, res);
#endif
  }

  static constexpr bool mul_overflow_base(const ll a, const ll b, ll *res) {
    if (a > 0) {
      if (b > 0) {
        if (a > ll_max / b) {
          return true;
        }
      } else if (b < 0) {
        if (b < ll_min / a) {
          return true;
        }
      }
    } else if (a < 0) {
      if (b > 0) {
        if (a < ll_min / b) {
          return true;
        }
      } else if (b < 0) {
        if (a < ll_max / b) {
          return true;
        }
      }
    }
    *res = a * b;
    return false;
  }

  static constexpr bool mul_overflow(const ll a, const ll b, ll *res) {
#ifdef __GNUC__
    return __builtin_smulll_overflow(a, b, res);
#else
    return mul_overflow_base(a, b, res);
#endif
  }

public:
  static constexpr ll_ext p_infinity() {
    ll_ext ret;
    ret.t = p_inf_tag;
    return ret;
  }
  static constexpr ll_ext n_infinity() {
    ll_ext ret;
    ret.t = n_inf_tag;
    return ret;
  }

  constexpr ll_ext() noexcept : v(0), t(finite_tag) {}
  constexpr ll_ext(const ll x) noexcept : v(x), t(finite_tag) {}

  friend constexpr ll_ext operator+(const ll_ext &l, const ll_ext &r) noexcept {
    switch (l.t) {
    case finite_tag: {
      switch (r.t) {
      case finite_tag: {
        ll x = 0;
        assert(!add_overflow(l.v, r.v, &x) && "overflow: +");
        return x;
      } break;
      case p_inf_tag: {
        return p_infinity();
      } break;
      case n_inf_tag: {
        return n_infinity();
      } break;
      }
    } break;
    case p_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        return p_infinity();
      } break;
      case p_inf_tag: {
        return p_infinity();
      } break;
      case n_inf_tag: {
        assert(false && "p_inf + n_inf");
        return 0;
      } break;
      }
    } break;
    case n_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        return n_infinity();
      } break;
      case p_inf_tag: {
        assert(false && "n_inf + p_inf");
        return 0;
      } break;
      case n_inf_tag: {
        return n_infinity();
      } break;
      }
    }
    }
  }

  friend constexpr ll_ext operator-(const ll_ext &l, const ll_ext &r) noexcept {
    switch (l.t) {
    case finite_tag: {
      switch (r.t) {
      case finite_tag: {
        ll x = 0;
        assert(!sub_overflow(l.v, r.v, &x) && "overflow: -");
        return x;
      } break;
      case p_inf_tag: {
        return n_infinity();
      } break;
      case n_inf_tag: {
        return p_infinity();
      } break;
      }
    } break;
    case p_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        return p_infinity();
      } break;
      case p_inf_tag: {
        assert(false && "p_inf - p_inf");
        return 0;
      } break;
      case n_inf_tag: {
        return p_infinity();
      } break;
      }
    } break;
    case n_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        return n_infinity();
      } break;
      case p_inf_tag: {
        return n_infinity();
      } break;
      case n_inf_tag: {
        assert(false && "n_inf - n_inf");
        return 0;
      } break;
      }
    }
    }
  }

  friend constexpr ll_ext operator*(const ll_ext &l, const ll_ext &r) noexcept {
    switch (l.t) {
    case finite_tag: {
      switch (r.t) {
      case finite_tag: {
        ll x = 0;
        assert(!mul_overflow(l.v, r.v, &x) && "overflow: *");
        return x;
      } break;
      case p_inf_tag: {
        if (l.v > 0) {
          return p_infinity();
        } else if (l.v == 0) {
          return 0;
        } else {
          return n_infinity();
        }
      } break;
      case n_inf_tag: {
        if (l.v > 0) {
          return n_infinity();
        } else if (l.v == 0) {
          return 0;
        } else {
          return p_infinity();
        }
      } break;
      }
    } break;
    case p_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        if (r.v > 0) {
          return p_infinity();
        } else if (r.v == 0) {
          return 0;
        } else {
          return n_infinity();
        }
      } break;
      case p_inf_tag: {
        return p_infinity();
      } break;
      case n_inf_tag: {
        return n_infinity();
      } break;
      }
    } break;
    case n_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        if (r.v > 0) {
          return n_infinity();
        } else if (r.v == 0) {
          return 0;
        } else {
          return p_infinity();
        }
      } break;
      case p_inf_tag: {
        return n_infinity();
      } break;
      case n_inf_tag: {
        return p_infinity();
      } break;
      }
    }
    }
  }

  friend constexpr ll_ext operator/(const ll_ext &l, const ll_ext &r) noexcept {
    switch (l.t) {
    case finite_tag: {
      switch (r.t) {
      case finite_tag: {
        assert(r.v != 0 && "division by zero: /");
        assert(!(l.v == ll_min && r.v == -1) && "overflow: /");
        return l.v / r.v;
      } break;
      case p_inf_tag: {
        return 0;
      } break;
      case n_inf_tag: {
        return 0;
      } break;
      }
    } break;
    case p_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        if (r.v > 0) {
          return p_infinity();
        } else if (r.v == 0) {
          assert(false && "division by zero: /");
        } else {
          return n_infinity();
        }
      } break;
      case p_inf_tag: {
        assert(false && "p_inf / p_inf");
        return 0;
      } break;
      case n_inf_tag: {
        assert(false && "p_inf / n_inf");
        return 0;
      } break;
      }
    } break;
    case n_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        if (r.v > 0) {
          return n_infinity();
        } else if (r.v == 0) {
          assert(false && "division by zero: /");
        } else {
          return p_infinity();
        }
      } break;
      case p_inf_tag: {
        assert(false && "n_inf / p_inf");
        return 0;
      } break;
      case n_inf_tag: {
        assert(false && "n_inf / n_inf");
        return 0;
      } break;
      }
    }
    }
  }

  friend constexpr ll_ext operator%(const ll_ext &l, const ll_ext &r) noexcept {
    switch (l.t) {
    case finite_tag: {
      switch (r.t) {
      case finite_tag: {
        assert(r.v != 0 && "division by zero: %");
        assert(!(l.v == ll_min && r.v == -1) && "overflow: %");
        return l.v % r.v;
      } break;
      case p_inf_tag: {
        return l.v;
      } break;
      case n_inf_tag: {
        return l.v;
      } break;
      }
    } break;
    case p_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        assert(false && "p_inf % finite");
        return 0;
      } break;
      case p_inf_tag: {
        assert(false && "p_inf % p_inf");
        return 0;
      } break;
      case n_inf_tag: {
        assert(false && "p_inf % n_inf");
        return 0;
      } break;
      }
    } break;
    case n_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        assert(false && "n_inf % finite");
        return 0;
      } break;
      case p_inf_tag: {
        assert(false && "n_inf % p_inf");
        return 0;
      } break;
      case n_inf_tag: {
        assert(false && "n_inf % n_inf");
        return 0;
      } break;
      }
    }
    }
  }

  constexpr ll_ext operator+() const noexcept { return *this; }

  constexpr ll_ext operator-() const noexcept {
    switch (t) {
    case finite_tag: {
      assert(v != ll_min && "overflow: unary -");
      return -v;
    } break;
    case p_inf_tag: {
      return n_infinity();
    } break;
    case n_inf_tag: {
      return p_infinity();
    } break;
    }
  }

  constexpr ll_ext &operator+=(const ll_ext &r) noexcept {
    return *this = *this + r;
  }

  constexpr ll_ext &operator-=(const ll_ext &r) noexcept {
    return *this = *this - r;
  }

  constexpr ll_ext &operator*=(const ll_ext &r) noexcept {
    return *this = *this * r;
  }

  constexpr ll_ext &operator/=(const ll_ext &r) noexcept {
    return *this = *this / r;
  }

  constexpr ll_ext &operator%=(const ll_ext &r) noexcept {
    return *this = *this % r;
  }

  friend constexpr bool operator==(const ll_ext &l, const ll_ext &r) noexcept {
    return l.v == r.v && l.t == r.t;
  }

  friend constexpr bool operator!=(const ll_ext &l, const ll_ext &r) noexcept {
    return !(l == r);
  }

  friend constexpr bool operator<(const ll_ext &l, const ll_ext &r) noexcept {
    switch (l.t) {
    case finite_tag: {
      switch (r.t) {
      case finite_tag: {
        return l.v < r.v;
      } break;
      case p_inf_tag: {
        return true;
      } break;
      case n_inf_tag: {
        return false;
      } break;
      }
    } break;
    case p_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        return false;
      } break;
      case p_inf_tag: {
        // assert(false && "p_inf < p_inf");
        return false;
      } break;
      case n_inf_tag: {
        return false;
      } break;
      }
    } break;
    case n_inf_tag: {
      switch (r.t) {
      case finite_tag: {
        return true;
      } break;
      case p_inf_tag: {
        return true;
      } break;
      case n_inf_tag: {
        // assert(false && "n_inf < n_inf");
        return false;
      } break;
      }
    }
    }
  }

  friend constexpr bool operator<=(const ll_ext &l, const ll_ext &r) noexcept {
    return !(r < l);
  }

  friend constexpr bool operator>(const ll_ext &l, const ll_ext &r) noexcept {
    return r < l;
  }

  friend constexpr bool operator>=(const ll_ext &l, const ll_ext &r) noexcept {
    return !(l < r);
  }

  friend std::istream &operator>>(std::istream &is, ll_ext &x) {
    x.t = finite_tag;
    is >> x.v;
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const ll_ext &x) {
    switch (x.t) {
    case finite_tag: {
      os << x.v;
      return os;
    } break;
    case p_inf_tag: {
      assert(false && "ostream << p_inf");
      return os;
    } break;
    case n_inf_tag: {
      assert(false && "ostream << n_inf");
      return os;
    } break;
    }
  }
};
