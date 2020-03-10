#include "other/bit_width.cpp"
#include "other/int_alias.cpp"

#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

template <class T> class radix_heap {
  using V = std::pair<u64, T>;

public:
  using key_type = u64;
  using mapped_type = T;
  using value_type = V;

private:
  std::vector<std::vector<V>> u;
  u64 last;

public:
  radix_heap() : u(), last(0) {}

  void push(V x) {
    assert(last <= x.first);

    const usize i = bit_width(x.first ^ last);
    if (u.size() <= i)
      u.resize(i + 1);
    u[i].push_back(std::move(x));
  }

  V pop() {
    if (u[0].empty()) {
      usize i = 1;
      while (u[i].empty())
        i += 1;
      last = std::numeric_limits<u64>::max();
      for (const V &e : u[i])
        last = std::min(last, e.first);
      for (V &e : u[i]) {
        const usize j = bit_width(e.first ^ last);
        u[j].push_back(std::move(e));
      }
      u[i].clear();
    }
    V ret = std::move(u[0].back());
    u[0].pop_back();
    return ret;
  }
};

/**
 * @brief Radix Heap
 * @see https://yosupo.hatenablog.com/entry/2015/04/03/224649
 */
