#include "other/int_alias.cpp"

#include <vector>

template <class S>
void subset_zeta_transform(std::vector<typename S::value_type> &a) {
  const usize n = a.size();
  for (usize i = 1; i < n; i *= 2) {
    for (usize j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j] = S::operation(a[j & ~i], a[j]);
    }
  }
}

/**
 * @brief Subset Zeta Transform
 */
