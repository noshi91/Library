#include <utility>

template <class M, class N> class cartesian_product_monoid {
  using T = std::pair<typename M::value_type, typename N::value_type>;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return T(M::operation(l.first, r.first), N::operation(l.second, r.second));
  }
  static constexpr T identity{M::identity, N::identity};
};