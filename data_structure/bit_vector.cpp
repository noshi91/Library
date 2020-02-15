#include <cstddef>
#include <limits>
#include <vector>

class bit_vector {
  using size_t = std::size_t;

  static constexpr size_t wordsize = std::numeric_limits<size_t>::digits;

  static size_t popcount(size_t x) { return __builtin_popcountll(x); }

  class node_type {
  public:
    size_t bit;
    size_t sum;

    node_type() : bit(0), sum(0) {}
  };

  std::vector<node_type> v;

public:
  bit_vector() = default;
  explicit bit_vector(const std::vector<bool> a) : v(a.size() / wordsize + 1) {
    {
      const size_t s = a.size();
      for (size_t i = 0; i != s; i += 1)
        v[i / wordsize].bit |= static_cast<size_t>(a[i] ? 1 : 0)
                               << i % wordsize;
    }
    {
      const size_t s = v.size();
      for (size_t i = 1; i != s; i += 1)
        v[i].sum = v[i - 1].sum + popcount(v[i - 1].bit);
    }
  }

  size_t rank0(const size_t index) const { return index - rank1(index); }
  size_t rank1(const size_t index) const {
    return v[index / wordsize].sum +
           popcount(v[index / wordsize].bit &
                    ~(~static_cast<size_t>(0) << index % wordsize));
  }
};