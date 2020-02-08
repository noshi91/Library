template <class T> class plus_group {
public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return l + r;
  }
  static constexpr T identity = 0;
  static constexpr T inverse(const T &x) noexcept { return -x; }
};