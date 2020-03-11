#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <vector>

template <class M> class fenwick_tree {
  using T = typename M::value_type;

public:
  using value_type = T;

private:
  std::vector<T> tree;

public:
  fenwick_tree() = default;

  explicit fenwick_tree(const usize size) : tree(size + 1, M::identity) {}

  bool empty() const { return size() == 0; }
  
  usize size() const { return tree.size() - 1; }

  T fold_prefix(usize last) const {
    assert(last <= size());
    T ret = M::identity;
    while (last != 0) {
      ret = M::operation(tree[last], ret);
      last &= last - 1;
    }
    return ret;
  }

  void add(usize index, const T value) {
    assert(index < size());
    index += 1;
    while (index < tree.size()) {
      tree[index] = M::operation(tree[index], value);
      index += index & ~index + 1;
    }
  }
};

/**
 * @brief Fenwick Tree
 * @see https://scrapbox.io/data-structures/Fenwick_Tree
 */
