#include "other/ceildiv.cpp"
#include "other/int_alias.cpp"

#include <vector>

template <class G>
void divisor_mobius_transform(std::vector<typename G::value_type> &a) {
  const usize n = a.size();
  std::vector<bool> sieve(n, true);
  for (usize p = 2; p < n; p += 1) {
    if (!sieve[p])
      continue;
    for (usize k = ceildiv(n, p); k != 1;) {
      k -= 1;
      sieve[k * p] = false;
      a[k * p] = G::operation(G::inverse(a[k]), a[k * p]);
    }
  }
}

/**
 * @brief Divisor Möbius Transform
 */
