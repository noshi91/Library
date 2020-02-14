template <class W> class min_semigroup {
  using T = typename W::value_type;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return W::compare(l, r) ? l : r;
  }
};