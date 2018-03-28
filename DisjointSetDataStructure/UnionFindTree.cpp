#include <cstdint>
#include <vector>

class UnionFindTree {
  using int32 = std::int_fast32_t;
  using uint32 = std::uint_fast32_t;
  std::vector<int32> tree;

public:
  UnionFindTree(uint32 size) : tree(size, -1) {}
  uint32 find(const uint32 x) {
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
  uint32 size(const uint32 x) { return (uint32)(-tree[find(x)]); }
  bool same(const uint32 x, const uint32 y) { return find(x) == find(y); }
};

/*

class UnionFindTree;

UnionFindTreeは素集合を管理するデータ構造です
空間計算量 O(N)


メンバ関数
-(constructor) (uint32 size)
 独立した要素を size 個持つ状態で構築します
 時間計算量 O(N)

-find (uint32 x)->uint32
 x の根を返します
 時間計算量 償却 O(α(N))

-unite (uint32 x, uint32 y)->bool
 x と y がそれぞれ含まれる集合を併合します
 併合に成功したか、すなわち x と y が違う集合に属していたかを返します
 時間計算量 償却 O(α(N))

-same (uint32 x, uint32 y)->bool
 x と y が同じ集合に属しているかを返します
 時間計算量 償却 O(α(N))

-size (uint32 x)->uint32
 x の含まれる集合に含まれる要素数を返します
 時間計算量 償却 O(α(N))


※N:全体の要素数
※α():アッカーマン関数の逆関数

*/