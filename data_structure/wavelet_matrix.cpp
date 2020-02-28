#include "data_structure/bit_vector.cpp"

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
  static bool test(const key_type x, const size_t k) {
    return (x & static_cast<key_type>(1) << k) != 0;
  }
  static void set(key_type &x, const size_t k) {
    x |= static_cast<key_type>(1) << k;
  }

  size_t size_;
  std::vector<bit_vector> mat;

  size_t less(size_t first, size_t last, const key_type key) const {
    size_t ret = 0;
    for (size_t p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p)) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        ret += v.rank0(last) - v.rank0(first);
        const size_t b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }

public:
  wavelet_matrix() = default;
  explicit wavelet_matrix(const size_t bit_length, std::vector<key_type> a)
      : size_(a.size()), mat(bit_length, bit_vector()) {
    const size_t s = size();
    for (size_t p = bit_length; p != 0;) {
      p -= 1;
      {
        std::vector<bool> t(s);
        for (size_t i = 0; i != s; i += 1)
          t[i] = test(a[i], p);
        mat[p] = bit_vector(t);
      }
      {
        std::vector<key_type> v0, v1;
        for (const size_t e : a)
          (test(e, p) ? v1 : v0).push_back(e);
        const auto itr = std::copy(v0.cbegin(), v0.cend(), a.begin());
        std::copy(v1.cbegin(), v1.cend(), itr);
      }
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
  key_type quantile(size_t first, size_t last, size_t k) const {
    assert(first <= last);
    assert(last <= size());
    assert(k < last - first);

    key_type ret = 0;
    for (size_t p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      const size_t z = v.rank0(last) - v.rank0(first);
      if (k < z) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        set(ret, p);
        k -= z;
        const size_t b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }
  size_t select(const key_type key, const size_t k) const {
    size_t index = 0;
    for (size_t p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.rank0(index);
      else
        index = v.rank0(size()) + v.rank1(index);
    }
    index += k;
    for (size_t p = 0; p != mat.size(); p += 1) {
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.select0(index);
      else
        index = v.select1(index - v.rank0(size()));
    }
    return index;
  }
};