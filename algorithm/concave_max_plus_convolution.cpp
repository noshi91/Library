#include "algorithm/smawk.cpp"

#include <cstddef>
#include <vector>

template <class T>
std::vector<T> concave_max_plus_convolution(const std::vector<T> &a,
                                            const std::vector<T> &b) {
  using size_t = std::size_t;

  const size_t n = a.size();
  const size_t m = b.size();
  const auto get = [&](const size_t i, const size_t j) {
    return a[j] + b[i - j];
  };
  const std::vector<size_t> amax =
      smawk(n + m - 1, n, [&](const size_t i, const size_t j, const size_t k) {
        if (i < k)
          return false;
        if (i - j >= m)
          return true;
        return get(i, j) <= get(i, k);
      });
  std::vector<T> c(n + m - 1);
  for (size_t i = 0; i != n + m - 1; i += 1)
    c[i] = get(i, amax[i]);
  return c;
}

/**
 * @brief Concave Max Plus Convlution
 * @see https://arxiv.org/abs/1802.06440
 */
