#include "other/int_alias.cpp"

#include <cassert>
#include <vector>
#include<utility>

template <class G> class potentialized_union_find {
  using T = typename G::value_type;
  class node_type {
  public:
    T value;
    usize parent;
    usize size;

    node_type(const T value, const usize parent, const usize size)
        : value(value), parent(parent), size(size) {}
  };

  std::vector<node_type> tree;

  void compress(const usize x) {
    const usize p = tree[x].parent;
    if (p == x)
      return;
    compress(p);
    tree[x].value = G::operation(tree[p].value, tree[x].value);
    tree[x].parent = tree[p].parent;
  }

public:
  potentialized_union_find() = default;

  explicit potentialized_union_find(const usize n)
      : tree(n, node_type(G::identity, 0, 1)) {
    for (usize i = 0; i != n; i += 1)
      tree[i].parent = i;
  }

  usize size() const { return tree.size(); }

  usize find(const usize x) {
    assert(x < size());

    compress(x);
    return tree[x].parent;
  }

  T potential(const usize x) {
    assert(x < size());

    compress(x);
    return tree[x].value;
  }

  bool same(const usize x, const usize y) {
    assert(x < size());

    compress(x);
    return find(x) == find(y);
  }

  T distance(const usize x, const usize y) {
    assert(x < size());
    assert(y < size());

    return G::operation(G::inverse(potential(x)), potential(y));
  }

  usize size(const usize x) {
    assert(x < size());

    return tree[find(x)].size;
  }

  void unite(usize x, usize y, T d) {
    assert(x < size());
    assert(y < size());
    assert(!same(x, y));

    if (size(x) < size(y)) {
      d = G::inverse(d);
      std::swap(x, y);
    }
    d = G::operation(G::operation(potential(x), d), G::inverse(potential(y)));
    x = find(x);
    y = find(y);
    tree[x].size += tree[y].size;
    tree[y].parent = x;
    tree[y].value = d;
  }
};

/**
 * @brief Potentialized Union Find
 */
