template <class W> class opposite_ordered_set {
  using T = typename W::value_type;

public:
  using value_type = T;
  static constexpr bool compare(const T &l, const T &r) noexcept {
    return W::compare(r, l);
  }
};