#include <optional>
#include <utility>

template <class S> class semigroup_to_monoid {
  using T = std::optional<typename S::value_type>;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    if (!l)
      return r;
    if (!r)
      return l;
    return T(std::in_place, S::operation(*l, *r));
  }
  static constexpr T identity{std::nullopt};
};