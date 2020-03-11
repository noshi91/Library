#include "other/int_alias.cpp"

#include <vector>

template <class S>
void divisor_zeta_transform(std::vector<typename S::value_type> &a) {
  const usize n = a.size();
  std::vector<bool> sieve(n, true);
  for (usize p = 2; p < n; p += 1) {
    if (!sieve[p])
      continue;
    for (usize k = 1; k * p < n; k += 1) {
      sieve[k * p] = false;
      a[k * p] = S::operation(a[k], a[k * p]);
    }
  }
}

/**
 * @brief Divisor Zeta Transform
 */
