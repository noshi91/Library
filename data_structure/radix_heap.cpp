#include "other/log2p164.cpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

template <class T> class radix_heap {
  using size_t = std::size_t;
  using u64 = std::uint_fast64_t;
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

  void push(const V x) {
    assert(last <= x.first);

    const size_t i = log2p164(x.first ^ last);
    if (u.size() <= i)
      u.resize(i + 1);
    u[i].push_back(x);
  }
  V pop() {
    if (u[0].empty()) {
      size_t i = 1;
      while (u[i].empty())
        i += 1;
      last = std::numeric_limits<u64>::max();
      for (const V &e : u[i])
        last = std::min(last, e.first);
      for (const V &e : u[i])
        u[log2p164(e.first ^ last)].push_back(e);
      u[i].clear();
    }
    V ret = u[0].back();
    u[0].pop_back();
    return ret;
  }
};

/**
 * @brief Radix Heap
 * @see https://yosupo.hatenablog.com/entry/2015/04/03/224649
 */
