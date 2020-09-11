#include "other/ceildiv.cpp"
#include "other/int_alias.cpp"

#include <array>
#include <type_traits>

namespace w_ary_tree_set_impl {
constexpr usize calc_c(usize n) {
  usize ret = 1;
  while (n > 64) {
    ret *= 64;
    n /= 64;
  }
  return ret;
}
usize bsf(const u64 x) {
#ifdef __GNUC__
  return __builtin_ctzll(x);
#else
  unsigned long ret;
  if (_BitScanForward(&ret, x & ~(~static_cast<u64>(0) << 32))) {
    return ret;
  } else {
    _BitScanForward(&ret, x >> 32);
    return ret + 32;
  }
#endif
}
usize bsr(const u64 x) {
#ifdef __GNUC__
  return 63 - __builtin_clzll(x);
#else
  unsigned long ret;
  if (_BitScanReverse(&ret, x >> 32)) {
    return ret + 32;
  } else {
    _BitScanReverse(&ret, x & ~(~static_cast<u64>(0) << 32));
    return ret;
  }
#endif
}

template <usize N, class D = void> class w_ary_tree_set {
  static constexpr usize C = calc_c(N);

  u64 map;
  std::array<w_ary_tree_set<C>, ceildiv(N, C)> child;

public:
  w_ary_tree_set() : map(0), child() {}

  bool insert(const usize key) {
    const usize pos = key / C;
    map |= static_cast<u64>(1) << pos;
    return child[pos].insert(key % C);
  }

  bool erase(const usize key) {
    const usize pos = key / C;
    const bool ret = child[pos].erase(key % C);
    if (child[pos]._get_map() == 0) {
      map &= ~(static_cast<u64>(1) << pos);
    }
    return ret;
  }

  bool contains(const usize key) const {
    return child[key / C].contains(key % C);
  }

  usize min() const {
    const usize pos = bsf(map);
    return pos * C + child[pos].min();
  }

  usize max() const {
    const usize pos = bsr(map);
    return pos * C + child[pos].max();
  }

  u64 _get_map() const { return map; }
};

template <usize N>
class w_ary_tree_set<N, typename std::enable_if<(N <= 64)>::type> {
  u64 map;

public:
  w_ary_tree_set() : map(0) {}

  bool insert(const usize key) {
    const u64 pop = static_cast<u64>(1) << key;
    if ((map & pop) != 0) {
      return false;
    } else {
      map |= pop;
      return true;
    }
  }

  bool erase(const usize key) {
    const u64 pop = static_cast<u64>(1) << key;
    if ((map & pop) != 0) {
      map &= ~pop;
      return true;
    } else {
      return false;
    }
  }

  bool contains(const usize key) const {
    return (map & static_cast<u64>(1) << key) != 0;
  }

  usize min() const { return bsf(map); }

  usize max() const { return bsr(map); }

  u64 _get_map() const { return map; }
};

} // namespace w_ary_tree_set_impl

template <usize N>
using w_ary_tree_set = w_ary_tree_set_impl::w_ary_tree_set<N>;

/**
 * @brief w-ary Tree Set
 */
