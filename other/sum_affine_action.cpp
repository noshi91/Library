#include "other/affine.cpp"
#include "other/cartesian_product_monoid.cpp"
#include "other/plus_monoid.cpp"

template <class T> class sum_affine_action {
public:
  using value_structure =
      cartesian_product_monoid<plus_monoid<T>, plus_monoid<T>>;
  using operator_structure = affine_composite_monoid<T>;

private:
  using U = typename value_structure::value_type;
  using E = typename operator_structure::value_type;

public:
  static constexpr U operation(const U &l, const E &r) {
    return U(l.first * r.a + l.second * r.b, l.second);
  }
};