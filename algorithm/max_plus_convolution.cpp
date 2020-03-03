#include "other/int_alias.cpp"

#include <algorithm>
#include <vector>

template <class T>
std::vector<T> max_plus_convolution(const std::vector<T> &a,
                                    const std::vector<T> &b) {
  const usize n = a.size();
  const usize m = b.size();
  std::vector<T> c(n + m - 1, std::numeric_limits<T>::lowest());
  for (usize i = 0; i != n; i += 1) {
    for (usize j = 0; j != m; j += 1)
      c[i + j] = std::max(c[i + j], a[i] + b[j]);
  }
  return c;
}

/**
 * @brief Max Plus Convolution
 */
