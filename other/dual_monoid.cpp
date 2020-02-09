template <class M> class dual_monoid {
  using T = typename M::value_type;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return M::operation(r, l);
  }
  static constexpr T identity = M::identity;
};