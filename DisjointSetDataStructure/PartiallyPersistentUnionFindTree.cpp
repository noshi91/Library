#include <algorithm>
#include <cstdint>
#include <vector>

class PartiallyPersistentUnionFindTree {
  using uint32 = std::uint_fast32_t;
  std::vector<std::pair<uint32, uint32>> tree;
  std::vector<std::vector<std::pair<uint32, uint32>>> siz;
  uint32 global_count;

public:
  PartiallyPersistentUnionFindTree(const uint32 size)
      : tree(size, {1, std::numeric_limits<uint32>::max()}),
        siz(size, std::vector<std::pair<uint32, uint32>>(1, {0, 1})),
        global_count(0) {}
  uint32 find(const uint32 ver, uint32 x) const {
    while (tree[x].second <= ver)
      x = tree[x].first;
    return x;
  }
  bool unite(uint32 x, uint32 y) {
    ++global_count;
    x = find(global_count, x);
    y = find(global_count, y);
    if (x == y)
      return false;
    if (tree[x].first < tree[y].first)
      std::swap(x, y);
    tree[x].first += tree[y].first;
    siz[x].emplace_back(global_count, tree[x].first);
    tree[y] = {x, global_count};
    return true;
  }
  bool same(const uint32 ver, const uint32 x, const uint32 y) const {
    return find(ver, x) == find(ver, y);
  }
  uint32 size(const uint32 ver, uint32 x) const {
    x = find(ver, x);
    return (std::lower_bound(siz[x].begin(), siz[x].end(),
                             std::pair<uint32, uint32>(ver + 1, 0)) -
            1)
        ->second;
  }
  uint32 count(void) { return global_count; }
};

/*

class PartiallyPersistentUnionFindTree;

PartiallyPersistentUnionFindTreeは素集合を管理する部分永続的データ構造です
空間計算量 O(N)


メンバ関数
-(constructor) (uint32 size)
 独立した要素を size 個持つ状態で構築します
 時間計算量 O(N)

-find (uint32 ver, uint32 x)->uint32
 ver 回目の unite が終了した時点での x の根を返します
 時間計算量 O(logN)

-unite (uint32 ver, uint32 x, uint32 y)->bool
 x と y がそれぞれ含まれる集合を併合します
 併合に成功したか、すなわち x と y が違う集合に属していたかを返します
 時間計算量 O(logN)

-same (uint32 ver, uint32 x, uint32 y)->bool
 ver 回目の併合操作が終了した時点で x と y が同じ集合に属しているかを返します
 時間計算量 O(logN)

-size (uint32 ver, uint32 x)->uint32
 ver 回目の併合操作が終了した時点で x の含まれる集合に含まれる要素数を返します
 時間計算量 O(logN)

-count (void)->uint32
 現在の操作回数を返します
 時間計算量 O(1)


※N:全体の要素数

*/