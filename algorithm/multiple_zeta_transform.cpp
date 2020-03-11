#include "other/ceildiv.cpp"
#include "other/int_alias.cpp"

#include <vector>

template <class S>
void multiple_zeta_transform(std::vector<typename S::value_type> &a) {
  const usize n = a.size();
  std::vector<bool> sieve(n, true);
  for (usize p = 2; p < n; p += 1) {
    if (!sieve[p])
      continue;
    for (usize k = ceildiv(n, p); k != 1) {
      k -= 1;
      sieve[k * p] = false;
      a[k] = S::operation(a[k], a[k * p]);
    }
  }
}

/**
 * @brief Multiple Zeta Transform
 */
