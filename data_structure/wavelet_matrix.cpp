#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

template <class Key> class wavelet_matrix {
  using size_t = std::size_t;

public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;

private:
  class bit_vector {
    static constexpr size_t wordsize = std::numeric_limits<size_t>::digits;

    static size_t popcount(size_t x) {
      //*
      static_assert(
          wordsize == 64,
          "this implementation is specialized for 64 bit unsigned integer");
      x -= x >> 1 & 0x5555555555555555;
      x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
      x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;
      return x * 0x0101010101010101 >> 56 & 0x7f;
      /*/
      static_assert(
          wordsize == 32,
          "this implementation is specialized for 32 bit unsigned integer");
      x -= x >> 1 & 0x55555555;
      x = (x & 0x33333333) + (x >> 2 & 0x33333333);
      x = x + (x >> 4) & 0x0F0F0F0F;
      return x * 0x01010101 >> 24 & 0x3F;
      //*/
    }

    class node_type {
      friend bit_vector;

      size_t sum;
      size_t bit;
      node_type() = default;
    };

    std::vector<node_type> v;

  public:
    bit_vector(const size_t size) : v(size / wordsize + 2) {}

    size_t rank(const size_t index) const {
      const node_type &t = v[index / wordsize];
      return t.sum +
             popcount(t.bit & ~(~static_cast<size_t>(0) << index % wordsize));
    }
    size_t all() const { return v.back().sum; }

    void set(const size_t index) {
      v[index / wordsize].bit |= static_cast<size_t>(1) << index % wordsize;
      v[index / wordsize + 1].sum += 1;
    }
    void build() {
      const size_t s = v.size();
      for (size_t i = 1; i != s; i += 1)
        v[i].sum += v[i - 1].sum;
    }
  };

  static bool test(const key_type x, const size_t k) {
    return (x & static_cast<key_type>(1) << k) != 0;
  }
  static void set(key_type &x, const size_t k) {
    x |= static_cast<key_type>(1) << k;
  }

  size_t size_;
  std::vector<bit_vector> vecs;

  size_t less(size_t first, size_t last, const key_type key) const {
    size_t ret = 0;
    size_t p = vecs.size();
    while (p != 0) {
      p -= 1;
      const bit_vector &v = vecs[p];
      const size_t rf = v.rank(first), rl = v.rank(last);
      if (!test(key, p)) {
        first -= rf;
        last -= rl;
      } else {
        ret += (last - first) - (rl - rf);
        const size_t b = size() - v.all();
        first = b + rf;
        last = b + rl;
      }
    }
    return ret;
  }

public:
  wavelet_matrix() = default;
  wavelet_matrix(const size_t bit_length, std::vector<key_type> a)
      : size_(a.size()), vecs(bit_length, bit_vector(size())) {
    const size_t s = size();
    std::vector<key_type> one;
    one.reserve(s);
    size_t p = vecs.size();
    while (p != 0) {
      p -= 1;
      bit_vector &v = vecs[p];
      size_t zi = 0;
      for (size_t i = 0; i < s; ++i) {
        if (!test(a[i], p)) {
          a[zi] = a[i];
          zi += 1;
        } else {
          v.set(i);
          one.push_back(a[i]);
        }
      }
      v.build();
      std::copy(one.cbegin(), one.cend(), a.begin() + zi);
      one.clear();
    }
  }

  size_t size() const { return size_; }

  size_t rangefreq(const size_t first, const size_t last, const key_type lower,
                   const key_type upper) const {
    assert(first <= last);
    assert(last <= size());
    assert(lower <= upper);

    return less(first, last, upper) - less(first, last, lower);
  }
  key_type quantile(size_t first, size_t last, size_t n) const {
    assert(first <= last);
    assert(last <= size());
    assert(n < last - first);

    key_type ret = 0;
    size_t p = vecs.size();
    while (p != 0) {
      p -= 1;
      const bit_vector &v = vecs[p];
      const size_t rf = v.rank(first), rl = v.rank(last);
      const size_t z = (last - first) - (rl - rf);
      if (n < z) {
        first -= rf;
        last -= rl;
      } else {
        set(ret, p);
        n -= z;
        const size_t b = size() - v.all();
        first = b + rf;
        last = b + rl;
      }
    }
    return ret;
  }
};
template <class Key>
constexpr typename wavelet_matrix<Key>::size_t
    wavelet_matrix<Key>::bit_vector::wordsize;

int main() { wavelet_matrix<int> wm; }