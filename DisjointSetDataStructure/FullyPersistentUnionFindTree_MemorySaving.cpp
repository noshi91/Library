#include <cstdint>
#include <cstdlib>
#include <tuple>
#include <utility>
/*

説明は FullyPersistentUnionFindTree を参照してください
GarbageCollectionを実装し、メモリ効率が良いですが定数倍が悪化しています
クエリの数に対して実際に保持するデータの量が少ない場合に有効です

*/

class FullyPersistentUnionFindTree {
  static constexpr std::uint_fast64_t ALLOCSIZE = 1 << 10;
  static constexpr std::uint_fast32_t shiftsize = 3;
  using int32 = std::int_fast32_t;
  using uint32 = std::uint_fast32_t;
  struct node_t {
    union {
      node_t *child;
      int32 data;
    } edge[(uint32)1 << shiftsize];
    std::uint_least32_t ref;
    static node_t *pool;
    void reset(const uint32 L) {
      if (--ref)
        return;
      if (L)
        for (uint32 i = 0; i < (uint32)1 << shiftsize; ++i)
          edge[i].child->reset(L - shiftsize);
      edge[0].child = pool;
      pool = this;
    }
    static node_t *alloc() {
      if (!pool) {
        pool = (node_t *)malloc(ALLOCSIZE * sizeof(node_t));
        uint32 i = ALLOCSIZE;
        pool[i - 1].edge[0].child = nullptr;
        while (--i)
          pool[i - 1].edge[0].child = pool + i;
      }
      node_t *ret = pool;
      pool = pool->edge[0].child;
      ret->ref = 1;
      return ret;
    }
    static node_t *create(const uint32 L) {
      node_t *ret = alloc();
      if (L) {
        node_t *x = create(L - shiftsize);
        x->ref = (uint32)1 << shiftsize;
        for (uint32 i = 0; i < (uint32)1 << shiftsize; ++i)
          ret->edge[i].child = x;
      } else
        for (uint32 i = 0; i < (uint32)1 << shiftsize; ++i)
          ret->edge[i].data = -1;
      return ret;
    }
    node_t *build(const uint32 pos, const int32 data, const uint32 L) {
      node_t *ret = alloc();
      if (!L) {
        for (uint32 i = 0; i < (uint32)1 << shiftsize; ++i)
          ret->edge[i].data = edge[i].data;
        ret->edge[pos].data = data;
        return ret;
      }
      for (uint32 i = 0; i < (uint32)1 << shiftsize; ++i) {
        ret->edge[i].child = edge[i].child;
        ++edge[i].child->ref;
      }
      --ret->edge[pos >> L].child->ref;
      ret->edge[pos >> L].child = edge[pos >> L].child->build(
          pos & (((uint32)1 << L) - 1), data, L - shiftsize);
      return ret;
    }
    int32 access(const uint32 pos, const uint32 L) {
      if (L)
        return edge[pos >> L].child->access(pos & (((uint32)1 << L) - 1),
                                            L - shiftsize);
      return edge[pos].data;
    }
  };
  node_t *root;
  uint32 L;
  explicit FullyPersistentUnionFindTree(node_t *const r, const uint32 L)
      : root(r), L(L) {}
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
  FullyPersistentUnionFindTree &
  operator=(const FullyPersistentUnionFindTree &o) {
    if (root)
      root->reset(L);
    root = o.root;
    L = o.L;
    if (root)
      ++root->ref;
    return *this;
  }
  ~FullyPersistentUnionFindTree() {
    if (root)
      root->reset(L);
  }
  uint32 find(const uint32 x) const { return find_(x).first; }
  FullyPersistentUnionFindTree unite(uint32 x, uint32 y) {
    int32 x_, y_;
    std::tie(x, x_) = find_(x);
    std::tie(y, y_) = find_(y);
    if (x == y)
      return *this;
    if (x_ > y_) {
      std::swap(x, y);
      std::swap(x_, y_);
    }
    node_t *t = root->build(x, x_ + y_, L);
    node_t *ret = t->build(y, (int32)x, L);
    t->reset(L);
    return FullyPersistentUnionFindTree(ret, L);
  }
  uint32 size(const uint32 x) const { return (uint32)(-find_(x).second); }
  bool same(const uint32 x, const uint32 y) const { return find(x) == find(y); }
};
typename FullyPersistentUnionFindTree::node_t
    *FullyPersistentUnionFindTree::node_t::pool = nullptr;