#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

class union_enumerate {
  std::vector<usize> next;

public:
  union_enumerate() = default;
  union_enumerate(const usize size) : next(size) {
    std::iota(next.begin(), next.end(), static_cast<usize>(0));
  }

  usize size() const { return next.size(); }

  std::vector<usize> enumerate(const usize x) const {
    assert(x < size());

    std::vector<usize> ret;
    usize y = x;
    do {
      ret.push_back(y);
      y = next[y];
    } while (y != x);
    return ret;
  }

  std::vector<std::vector<usize>> get_all() const {
    const usize n = size();
    std::vector<std::vector<usize>> res;
    std::vector<bool> visited(n, false);
    for (usize i = 0; i != n; i += 1) {
      if (!visited[i]) {
        const std::vector<usize> list = enumerate(i);
        for (const usize j : list)
          visited[j] = true;
        res.push_back(list);
      }
    }
    return res;
  }

  void unite(const usize x, const usize y) {
    assert(x < size());
    assert(y < size());

    std::swap(next[x], next[y]);
  }
};

/**
 * @brief Union Enumerate
 * @see http://noshi91.hatenablog.com/entry/2019/07/19/180606
 */
