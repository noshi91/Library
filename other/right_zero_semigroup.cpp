template <class T> class right_zero_semigroup {
public:
  using value_type = T;
  static constexpr T operation(const T &, const T &r) noexcept { return r; }
};