#include "other/int_alias.cpp"
#include "other/popcount.cpp"
#include "other/select64.cpp"

#include <cstddef>
#include <limits>
#include <vector>

class bit_vector {
  static constexpr usize wordsize = std::numeric_limits<usize>::digits;

  class node_type {
  public:
    usize bit;
    usize sum;

    node_type() : bit(0), sum(0) {}
  };

  std::vector<node_type> v;

public:
  bit_vector() = default;
  explicit bit_vector(const std::vector<bool> a) : v(a.size() / wordsize + 1) {
    {
      const usize s = a.size();
      for (usize i = 0; i != s; i += 1)
        v[i / wordsize].bit |= static_cast<usize>(a[i] ? 1 : 0) << i % wordsize;
    }
    {
      const usize s = v.size();
      for (usize i = 1; i != s; i += 1)
        v[i].sum = v[i - 1].sum + popcount(v[i - 1].bit);
    }
  }

  usize rank0(const usize index) const { return index - rank1(index); }
  usize rank1(const usize index) const {
    return v[index / wordsize].sum +
           popcount(v[index / wordsize].bit &
                    ~(~static_cast<usize>(0) << index % wordsize));
  }
  usize select0(const usize k) const {
    usize l = 0;
    usize r = v.size();
    while (l != r) {
      const usize m = (l + r) / 2;
      if (m * wordsize - v[m].sum <= k)
        l = m + 1;
      else
        r = m;
    }
    const usize i = l - 1;
    return i * wordsize + select64(~v[i].bit, k - (i * wordsize - v[i].sum));
  }
  usize select1(const usize k) const {
    usize l = 0;
    usize r = v.size();
    while (l != r) {
      const usize m = (l + r) / 2;
      if (v[m].sum <= k)
        l = m + 1;
      else
        r = m;
    }
    const usize i = l - 1;
    return i * wordsize + select64(v[i].bit, k - v[i].sum);
  }
};

/**
 * @brief Bit Vector
 */
