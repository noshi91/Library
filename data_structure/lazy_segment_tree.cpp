#include "other/bit_width.cpp"
#include "other/countr_zero.cpp"
#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <vector>

template <class A> class lazy_segment_tree {
  using V = typename A::value_structure;
  using T = typename V::value_type;
  using O = typename A::operator_structure;
  using E = typename O::value_type;

  class node_type {
  public:
    T value;
    E lazy;

    node_type(const T value, const E lazy) : value(value), lazy(lazy) {}
  };

  static T get(const node_type &x) { return A::operation(x.value, x.lazy); }
  static void add(E &x, const E y) { x = O::operation(x, y); }

  std::vector<node_type> tree;

  void propagate(const usize index) {
    add(tree[index * 2].lazy, tree[index].lazy);
    add(tree[index * 2 + 1].lazy, tree[index].lazy);
    tree[index].lazy = O::identity;
  }

  void propagate_bound(const usize index) {
    if (index == 0)
      return;
    const usize crz = countr_zero(index);
    for (usize h = bit_width(index) - 1; h != crz; h -= 1)
      propagate(index >> h);
  }

  void recalc(const usize index) {
    tree[index].value =
        V::operation(get(tree[index * 2]), get(tree[index * 2 + 1]));
  }

  void recalc_bound(usize index) {
    if (index == 0)
      return;
    index >>= countr_zero(index);
    while (index != 1) {
      index /= 2;
      recalc(index);
    }
  }

public:
  lazy_segment_tree() = default;

  explicit lazy_segment_tree(const usize n)
      : tree(n * 2, node_type(V::identity, O::identity)) {}

  usize size() const { return tree.size() / 2; }

  T fold(usize first, usize last) {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    propagate_bound(first);
    recalc_bound(first);
    propagate_bound(last);
    recalc_bound(last);
    T fold_l = V::identity;
    T fold_r = V::identity;
    while (first != last) {
      if (first % 2 != 0) {
        fold_l = V::operation(fold_l, get(tree[first]));
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        fold_r = V::operation(get(tree[last]), fold_r);
      }
      last /= 2;
    }
    return V::operation(fold_l, fold_r);
  }

  void update_range(usize first, usize last, const E x) {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    propagate_bound(first);
    propagate_bound(last);
    const usize first_c = first;
    const usize last_c = last;
    while (first != last) {
      if (first % 2 != 0) {
        add(tree[first].lazy, x);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        add(tree[last].lazy, x);
      }
      last /= 2;
    }
    recalc_bound(first_c);
    recalc_bound(last_c);
  }

  void update_point(usize index, const T x) {
    assert(index < size());
    index += size();
    for (usize h = bit_width(index) - 1; h != 0; h -= 1)
      propagate(index >> h);
    tree[index] = node_type(x, O::identity);
    while (index != 1) {
      index /= 2;
      recalc(index);
    }
  }
};

/**
 * @brief Lazy Segment Tree
 * @see https://scrapbox.io/data-structures/Lazy_Segment_Tree
 */
