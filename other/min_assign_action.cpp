#include "other/min_semigroup.cpp"
#include "other/right_zero_semigroup.cpp"
#include "other/semigroup_to_monoid.cpp"

#include <optional>

template <class W> class min_assign_action {
  using T = typename W::value_type;
  using U = std::optional<T>;

public:
  using value_structure = semigroup_to_monoid<min_semigroup<W>>;
  using operator_structure = semigroup_to_monoid<right_zero_semigroup<T>>;
  static constexpr U operation(const U &l, const U &r) noexcept {
    return r ? r : l;
  }
};