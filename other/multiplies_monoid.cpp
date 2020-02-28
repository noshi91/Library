template <class T> class multiplies_monoid {
public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return l * r;
  }
  static constexpr T identity = 1;
};