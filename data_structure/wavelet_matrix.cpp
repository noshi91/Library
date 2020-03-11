#include "data_structure/bit_vector.cpp"
#include "other/int_alias.cpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

template <class Key> class wavelet_matrix {
public:
  using key_type = Key;
  using value_type = Key;

private:
  static bool test(const key_type x, const usize k) {
    return (x & static_cast<key_type>(1) << k) != 0;
  }
  static void set(key_type &x, const usize k) {
    x |= static_cast<key_type>(1) << k;
  }

  usize size_;
  std::vector<bit_vector> mat;

  usize less(usize first, usize last, const key_type key) const {
    usize ret = 0;
    for (usize p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p)) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        ret += v.rank0(last) - v.rank0(first);
        const usize b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }

public:
  wavelet_matrix() = default;
  explicit wavelet_matrix(const usize bit_length, std::vector<key_type> a)
      : size_(a.size()), mat(bit_length, bit_vector()) {
    const usize s = size();
    for (usize p = bit_length; p != 0;) {
      p -= 1;
      {
        std::vector<bool> t(s);
        for (usize i = 0; i != s; i += 1)
          t[i] = test(a[i], p);
        mat[p] = bit_vector(t);
      }
      {
        std::vector<key_type> v0, v1;
        for (const usize e : a)
          (test(e, p) ? v1 : v0).push_back(e);
        const auto itr = std::copy(v0.cbegin(), v0.cend(), a.begin());
        std::copy(v1.cbegin(), v1.cend(), itr);
      }
    }
  }

  usize size() const { return size_; }

  usize rangefreq(const usize first, const usize last, const key_type lower,
                  const key_type upper) const {
    assert(first <= last);
    assert(last <= size());
    assert(lower <= upper);

    return less(first, last, upper) - less(first, last, lower);
  }
  key_type quantile(usize first, usize last, usize k) const {
    assert(first <= last);
    assert(last <= size());
    assert(k < last - first);

    key_type ret = 0;
    for (usize p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      const usize z = v.rank0(last) - v.rank0(first);
      if (k < z) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        set(ret, p);
        k -= z;
        const usize b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }
  usize select(const key_type key, const usize k) const {
    usize index = 0;
    for (usize p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.rank0(index);
      else
        index = v.rank0(size()) + v.rank1(index);
    }
    index += k;
    for (usize p = 0; p != mat.size(); p += 1) {
      const bit_vector &v = mat[p];
      if (!test(key, p))
        index = v.select0(index);
      else
        index = v.select1(index - v.rank0(size()));
    }
    return index;
  }
};

/**
 * @brief Wavelet Matrix
 */
