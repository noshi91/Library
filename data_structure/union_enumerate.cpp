#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

class union_enumerate {
  using size_t = std::size_t;

  std::vector<size_t> next;

public:
  union_enumerate() = default;
  union_enumerate(const size_t size) : next(size) {
    std::iota(next.begin(), next.end(), static_cast<size_t>(0));
  }

  std::vector<size_t> enumerate(const size_t x) const {
    std::vector<size_t> ret;
    size_t y = x;
    do {
      ret.push_back(y);
      y = next[y];
    } while (y != x);
    return ret;
  }

  void unite(const size_t x, const size_t y) { std::swap(next[x], next[y]); }
};

/**
 * @brief Union Enumerate
 * @see http://noshi91.hatenablog.com/entry/2019/07/19/180606
 */
