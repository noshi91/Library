#include "other/int_alias.cpp"

#include <cassert>
#include <utility>
#include <vector>

class union_find {
private:
  class node_type {
    friend union_find;

    usize parent;
    usize size;

    node_type(const usize parent, const usize size)
        : parent(parent), size(size) {}
  };

  std::vector<node_type> tree;

public:
  union_find() = default;

  explicit union_find(const usize n) : tree(n, node_type(n, 1)) {}

  usize size() const { return tree.size(); }

  usize find(const usize x) {
    assert(x < size());
    if (tree[x].parent == size())
      return x;
    else
      return tree[x].parent = find(tree[x].parent);
  }

  bool same(const usize x, const usize y) {
    assert(x < size());
    assert(y < size());
    return find(x) == find(y);
  }

  usize size(const usize x) {
    assert(x < size());
    return tree[find(x)].size;
  }

  void unite(usize x, usize y) {
    assert(x < size());
    assert(y < size());
    x = find(x);
    y = find(y);
    if (x != y) {
      if (tree[x].size < tree[y].size)
        std::swap(x, y);
      tree[x].size += tree[y].size;
      tree[y].parent = x;
    }
  }
};

/**
 * @brief Union Find
 * @see https://scrapbox.io/data-structures/Union_Find
 */
