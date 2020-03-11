#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <vector>

template <class M> class segment_tree {
  using T = typename M::value_type;

public:
  using value_type = T;

private:
  std::vector<T> tree;

  template <class F>
  usize search_subtree(usize index, const F f, T fold_l) const {
    while (index < size()) {
      const T temp = M::operation(fold_l, tree[index * 2]);
      if (!f(temp)) {
        index = index * 2;
      } else {
        fold_l = temp;
        index = index * 2 + 1;
      }
    }
    return index - size();
  }

public:
  segment_tree() = default;

  explicit segment_tree(const usize n) : tree(n * 2, M::identity) {}

  usize size() const noexcept { return tree.size() / 2; }

  T fold(usize first, usize last) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    T fold_l = M::identity;
    T fold_r = M::identity;
    while (first != last) {
      if (first % 2 != 0) {
        fold_l = M::operation(fold_l, tree[first]);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        fold_r = M::operation(tree[last], fold_r);
      }
      last /= 2;
    }
    return M::operation(fold_l, fold_r);
  }
  
  template <class F> usize search(usize first, usize last, const F f) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    const usize last_cp = last;
    usize shift = 0;
    T fold_l = M::identity;
    while (first != last) {
      if (first % 2 != 0) {
        const T temp = M::operation(fold_l, tree[first]);
        if (!f(temp))
          return search_subtree(first, f, fold_l);
        fold_l = temp;
        first += 1;
      }
      first /= 2;
      last /= 2;
      shift += 1;
    }
    while (shift != 0) {
      shift -= 1;
      last = last_cp >> shift;
      if (last % 2 != 0) {
        last -= 1;
        const T temp = M::operation(fold_l, tree[last]);
        if (!f(temp))
          return search_subtree(last, f, fold_l);
        fold_l = temp;
      }
    }
    return last_cp - size();
  }

  void update(usize index, const T x) {
    assert(index < size());
    index += size();
    tree[index] = x;
    while (index != 1) {
      index /= 2;
      tree[index] = M::operation(tree[index * 2], tree[index * 2 + 1]);
    }
  }
};

/**
 * @brief Segment Tree
 * @docs docs/segment_tree.md
 * @see https://scrapbox.io/data-structures/Segment_Tree
 */
