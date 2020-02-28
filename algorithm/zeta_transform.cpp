#include <cstddef>
#include <vector>

template <class S>
void subset_zeta_transform(std::vector<typename S::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  for (size_t i = 1; i < n; i *= 2) {
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j] = S::operation(a[j & ~i], a[j]);
    }
  }
}

template <class S>
void superset_zeta_transform(std::vector<typename S::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  for (size_t i = 1; i < n; i *= 2) {
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j & ~i] = S::operation(a[j & ~i], a[j]);
    }
  }
}

template <class G>
void subset_mobius_transform(std::vector<typename G::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  size_t i = 1;
  while (i < n)
    i *= 2;
  while (i != 1) {
    i /= 2;
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j] = G::operation(G::inverse(a[j & ~i]), a[j]);
    }
  }
}

template <class G>
void superset_mobius_transform(std::vector<typename G::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  size_t i = 1;
  while (i < n)
    i *= 2;
  while (i != 1) {
    i /= 2;
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j & ~i] = G::operation(a[j & ~i], G::inverse(a[j]));
    }
  }
}

/**
 * @brief Zeta Transform
 */
