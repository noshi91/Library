#include <cstdint>
#include <vector>

class UnionFindTree {
  using int32 = std::int_fast32_t;
  using uint32 = std::uint_fast32_t;
  std::vector<int32> tree;

public:
  UnionFindTree(uint32 size) : tree(size, -1) {}
  uint32 find(uint32 x) {
    if (tree[x] < 0)
      return x;
    return tree[x] = (int32)find((uint32)tree[x]);
  }
  bool unite(uint32 x, uint32 y) {
    x = find(x);
    y = find(y);
    if (x == y)
      return false;
    if (tree[x] > tree[y])
      std::swap(x, y);
    tree[x] += tree[y];
    tree[y] = (int32)x;
    return true;
  }
  uint32 size(uint32 x) { return (uint32)(-tree[find(x)]); }
  bool same(uint32 x, uint32 y) { return find(x) == find(y); }
};