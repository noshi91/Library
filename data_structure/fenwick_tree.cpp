#include <cassert>
#include <cstddef>
#include <vector>

template <class M> class fenwick_tree {
  using size_t = std::size_t;

public:
  using T = typename M::value_type;

private:
  std::vector<T> tree;

public:
  fenwick_tree() = default;
  explicit fenwick_tree(const size_t size) : tree(size + 1, M::identity) {}

  bool empty() const { return size() == 0; }
  size_t size() const { return tree.size() - 1; }

  T fold_prefix(size_t last) const {
    assert(last <= size());
    T ret = M::identity;
    while (last != 0) {
      ret = M::operation(tree[last], ret);
      last &= last - 1;
    }
    return ret;
  }

  void add(size_t index, const T value) {
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
