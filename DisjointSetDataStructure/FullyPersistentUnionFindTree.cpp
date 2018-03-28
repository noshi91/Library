#include <cstdint>
#include <cstdlib>
#include <tuple>
#include <utility>

class FullyPersistentUnionFindTree {
  static constexpr std::uint_fast64_t ALLOCSIZE = 1 << 10;
  static constexpr std::uint_fast32_t shiftsize = 3;
  using uint32 = std::uint_fast32_t;
  using int32 = std::int_fast32_t;
  struct node_t {
    union {
      node_t *child;
      int32 data;
    } edge[(uint32)1 << shiftsize];
    static node_t *alloc() {
      static node_t *pool = nullptr;
      static std::uint_fast64_t it = ALLOCSIZE;
      if (it == ALLOCSIZE) {
        pool = (node_t *)malloc(ALLOCSIZE * sizeof(node_t));
        it = 0;
      }
      return &pool[it++];
    }
    static node_t *create(const uint32 L) {
      node_t *ret = alloc();
      if (L) {
        node_t *x = create(L - shiftsize);
        for (uint32 i = 0; i < (uint32)1 << shiftsize; ++i)
          ret->edge[i].child = x;
      } else
        for (uint32 i = 0; i < (uint32)1 << shiftsize; ++i)
          ret->edge[i].data = -1;
      return ret;
    }
    node_t *build(const uint32 pos, const int32 d, const uint32 L) const {
      node_t *ret = alloc();
      if (!L) {
        for (uint32 i = 0; i < (uint32)1 << shiftsize; ++i)
          ret->edge[i].data = edge[i].data;
        ret->edge[pos].data = d;
        return ret;
      }
      for (uint32 i = 0; i < (uint32)1 << shiftsize; ++i)
        ret->edge[i].child = edge[i].child;
      ret->edge[pos >> L].child = edge[pos >> L].child->build(
          pos & ((uint32)1 << L) - 1, d, L - shiftsize);
      return ret;
    }
    int32 access(const uint32 pos, const uint32 L) const {
      if (L)
        return edge[pos >> L].child->access(pos & ((uint32)1 << L) - 1,
                                            L - shiftsize);
      return edge[pos].data;
    }
  };
  node_t *root;
  uint32 L;
  explicit FullyPersistentUnionFindTree(node_t *r, uint32 L_)
      : root(r), L(L_) {}
  std::pair<uint32, int32> find_(uint32 x) const {
    int32 y = (int32)x;
    while (y >= 0) {
      x = (uint32)y;
      y = root->access(x, L);
    }
    return {x, y};
  }

public:
  FullyPersistentUnionFindTree(const uint32 size = 0) : root(nullptr), L(0) {
    if (!size)
      return;
    while ((uint32)1 << L < size)
      L += shiftsize;
    L -= shiftsize;
    root = node_t::create(L);
  }
  uint32 find(const uint32 x) const { return find_(x).first; }
  FullyPersistentUnionFindTree unite(uint32 x, uint32 y) const {
    int32 x_, y_;
    std::tie(x, x_) = find_(x);
    std::tie(y, y_) = find_(y);
    if (x == y)
      return *this;
    if (x_ > y_) {
      std::swap(x, y);
      std::swap(x_, y_);
    }
    return FullyPersistentUnionFindTree(
        root->build(x, x_ + y_, L)->build(y, (int32)x, L), L);
  }
  uint32 size(const uint32 x) const { return (uint32)(-find_(x).second); }
  bool same(const uint32 x, const uint32 y) const { return find(x) == find(y); }
};

/*

class FullyPersistentUnionFindTree;

FullyPersistentUnionFindTreeは素集合を管理する全永続的データ構造です


メンバ関数
-(constructor) (uint32 size = 0)
 独立した要素を size 個持つ状態で構築します
 時間計算量 O(log^2N/loglogN)
 空間計算量 O(logN/loglogN)

-find (uint32 x)->uint32
 x の根を返します
 時間計算量 O(log^2N/loglogN)
 
-unite (uint32 x, uint32 y)->FullyPersistentUnionFindTree
 x と y がそれぞれ含まれる集合を併合します
 時間/空間計算量 O(log^2N/loglogN)

-size (uint32 x)->uint32
 x の含まれる集合に含まれる要素数を返します
 時間計算量 O(log^2N/loglogN)

-same(uint32 x, uint32 y)->bool
 x と y が同じ集合に含まれているかを返します
 時間計算量 O(log^2N/loglogN)


※N:全体の要素数
※効率を最大化する場合 shiftsize を loglogN 程度に設定してください
　初期状態は 3 です( N=10^5 程度を想定しています)

*/