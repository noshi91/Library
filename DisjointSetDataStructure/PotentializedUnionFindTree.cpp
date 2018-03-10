#include <cstdint>
#include <utility>
#include <vector>

template <typename Abelian> class PotentializedUnionFindTree {
  using int32 = std::int_fast32_t;
  using uint32 = std::uint_fast32_t;
  std::vector<std::pair<int32, Abelian>> tree;

public:
  PotentializedUnionFindTree(uint32 size) : tree(size, {-1, Abelian()}) {}
  uint32 find(uint32 x) {
    if (tree[x].first < 0)
      return x;
    uint32 t = (uint32)tree[x].first;
    tree[x].first = (int32)find(t);
    tree[x].second = tree[t].second + tree[x].second;
    return (uint32)tree[x].first;
  }
  Abelian potential(uint32 x) {
    find(x);
    return tree[x].second;
  }
  Abelian diff(uint32 x, uint32 y) { return potential(y) - potential(x); }
  bool unite(uint32 x, uint32 y, Abelian d) {
    d = d + diff(y, x);
    x = find(x);
    y = find(y);
    if (x == y)
      return false;
    if (tree[x].first > tree[y].first) {
      std::swap(x, y);
      d = -d;
    }
    tree[x].first += tree[y].first;
    tree[y] = std::pair<int32, Abelian>(x, d);
    return true;
  }
  bool same(uint32 x, uint32 y) { return find(x) == find(y); }
  uint32 size(uint32 x) {
    x = find(x);
    return (uint32)(-tree[x].first);
  }
};