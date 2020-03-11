#include "other/bit_width.cpp"
#include "other/countr_zero.cpp"
#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <vector>

template <class M> class dual_segment_tree {
  using T = typename M::value_type;

public:
  using value_type = T;

private:
  static void add(T &x, const T y) { x = M::operation(x, y); }

  std::vector<T> tree;

  void push(const usize index) {
    add(tree[index * 2], tree[index]);
    add(tree[index * 2 + 1], tree[index]);
    tree[index] = M::identity;
  }
  void propagate(const usize index) {
    if (index == 0)
      return;
    const usize crz = countr_zero(index);
    for (usize h = bit_width(index) - 1; h != crz; h -= 1)
      push(index >> h);
  }

public:
  dual_segment_tree() = default;
  explicit dual_segment_tree(const usize n) : tree(n * 2, M::identity) {}

  usize size() const noexcept { return tree.size() / 2; }

  T fold(usize index) const {
    assert(index < size());
    index += size();
    T ret = tree[index];
    while (index != 1) {
      index /= 2;
      add(ret, tree[index]);
    }
    return ret;
  }

  void update(usize first, usize last, const T x) {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    propagate(first);
    propagate(last);
    while (first != last) {
      if (first % 2 != 0) {
        add(tree[first], x);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        add(tree[last], x);
      }
      last /= 2;
    }
  }
};

/**
 * @brief Dual Segment Tree
 * @see https://kimiyuki.net/blog/2019/02/21/dual-segment-tree/
 */
