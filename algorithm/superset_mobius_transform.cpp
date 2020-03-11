#include "other/int_alias.cpp"

#include <vector>

template <class G>
void superset_mobius_transform(std::vector<typename G::value_type> &a) {
  const usize n = a.size();
  usize i = 1;
  while (i < n)
    i *= 2;
  while (i != 1) {
    i /= 2;
    for (usize j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j & ~i] = G::operation(a[j & ~i], G::inverse(a[j]));
    }
  }
}

/**
 * @brief Superset Möbius Transform
 */
