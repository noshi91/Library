#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <limits>
#include <vector>

class partially_persistent_union_find {
  using size_t = std::size_t;

public:
  using time_type = size_t;

private:
  class node_type {
    friend partially_persistent_union_find;

    time_type time;
    size_t parent;
    size_t size;

    node_type(const time_type time, const size_t parent, const size_t size)
        : time(time), parent(parent), size(size) {}
  };
  class sh_node {
    friend partially_persistent_union_find;

    time_type time;
    size_t size;

    sh_node(const time_type time, const size_t size) : time(time), size(size) {}
  };

  std::vector<node_type> tree;
  std::vector<std::vector<sh_node>> size_history;
  time_type time_count;

  size_t size() const { return tree.size(); }

public:
  partially_persistent_union_find() = default;
  explicit partially_persistent_union_find(const size_t n)
      : tree(n, node_type(std::numeric_limits<time_type>::max(), 0, 1)),
        size_history(n, std::vector<sh_node>({sh_node(0, 1)})), time_count(0) {
    for (size_t i = 0; i != n; i += 1)
      tree[i].parent = i;
  }

  time_type now() const { return time_count; }

  size_t find(const time_type time, size_t x) const {
    assert(x < size());
    while (tree[x].time <= time)
      x = tree[x].parent;
    return x;
  }
  bool same(const time_type time, const size_t x, const size_t y) const {
    assert(x < size());
    assert(y < size());
    return find(time, x) == find(time, y);
  }
  size_t size(const time_type time, size_t x) const {
    assert(x < size());
    x = find(time, x);
    return std::prev(std::partition_point(
                         size_history[x].cbegin(), size_history[x].cend(),
                         [time](const sh_node &h) { return h.time <= time; }))
        ->size;
  }

  time_type unite(size_t x, size_t y) {
    assert(x < tree.size());
    assert(y < tree.size());
    x = find(now(), x);
    y = find(now(), y);
    time_count += 1;
    if (x != y) {
      if (tree[x].size < tree[y].size)
        std::swap(x, y);
      tree[x].size += tree[y].size;
      tree[y].parent = x;
      tree[y].time = time_count;
      size_history[x].push_back(sh_node(time_count, tree[x].size));
    }
    return time_count - 1;
  }
};

/**
 * @brief Partially Persistent Union Find
 */
