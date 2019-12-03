#include <cassert>
#include <cstddef>
#include <vector>

template <class Monoid> class segment_tree {
public:
  using T = typename Monoid::value_type;
  using size_t = std::size_t;

private:
  std::vector<T> tree;

  template <class F>
  size_t search_subtree(size_t index, const F f, T fold_l) const {
    while (index < size()) {
      const T temp = Monoid::operate(fold_l, tree[index * 2]);
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
  explicit segment_tree(const size_t n) : tree(n * 2, Monoid::identity) {}

  size_t size() const noexcept { return tree.size() / 2; }

  T fold(size_t first, size_t last) const {
    assert(first <= last);
    assert(first <= size());
    assert(last <= size());
    first += size();
    last += size();
    T fold_l = Monoid::identity;
    T fold_r = Monoid::identity;
    while (first != last) {
      if (first % 2 != 0) {
        fold_l = Monoid::operate(fold_l, tree[first]);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        fold_r = Monoid::operate(tree[last], fold_r);
      }
      last /= 2;
    }
    return Monoid::operate(fold_l, fold_r);
  }
  template <class F>
  size_t search(size_t first, size_t last, const F f) const {
    assert(first <= last);
    assert(first <= size());
    assert(last <= size());
    first += size();
    last += size();
    const size_t last_cp = last;
    size_t shift = 0;
    T fold_l = Monoid::identity;
    while (first != last) {
      if (first % 2 != 0) {
        const T temp = Monoid::operate(fold_l, tree[first]);
        if (!f(temp)) {
          return search_subtree(first, f, fold_l);
        }
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
        const T temp = Monoid::operate(fold_l, tree[last]);
        if (!f(temp)) {
          return search_subtree(last, f, fold_l);
        }
        fold_l = temp;
      }
    }
    return last_cp - size();
  }

  template <class F> void update(size_t index, const F f) {
    assert(index < size());
    index += size();
    tree[index] = f(tree[index]);
    while (index != 1) {
      index /= 2;
      tree[index] = Monoid::operate(tree[index * 2], tree[index * 2 + 1]);
    }
  }
};