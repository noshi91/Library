#include "other/int_alias.cpp"

#include <vector>

template <class G>
void multiple_mobius_transform(std::vector<typename G::value_type> &a) {
  const usize n = a.size();
  std::vector<bool> sieve(n, true);
  for (usize p = 2; p < n; p += 1) {
    if (!sieve[p])
      continue;
    for (usize k = 1; k * p < n; k += 1) {
      sieve[k * p] = false;
      a[k] = G::operation(a[k], G::inverse(a[k * p]));
    }
  }
}

/**
 * @brief Multiple Möbius Transform
 */
