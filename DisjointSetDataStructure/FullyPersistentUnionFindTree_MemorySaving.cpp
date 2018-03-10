#include <cstdint>
#include <cstdlib>
#include <tuple>
#include <utility>


class FullyPersistentUnionFindTree {
  static constexpr std::uint_fast64_t ALLOCSIZE = 1 << 10;
  using int32 = std::int_fast32_t;
  using uint32 = std::uint_fast32_t;
  struct node_t {
    union e {
      node_t *child;
      int32 data;
    } edge[8];
    std::uint_least32_t ref, L;
    static node_t *pool;
    void reset(const uint32 L) {
      if (--ref)
        return;
      if (L)
        for (uint32 i = 0; i < 8; ++i)
          edge[i].child->reset(L - 3);
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
      ret->L = L;
      if (L)
        for (uint32 i = 0; i < 8; ++i)
          ret->edge[i].child = create(L - 3);
      else
        for (uint32 i = 0; i < 8; ++i)
          ret->edge[i].data = -1;
      return ret;
    }
    node_t *build(const uint32 pos, const int32 data, const uint32 L) {
      node_t *ret = alloc();
      ret->L = L;
      if (!L) {
        for (uint32 i = 0; i < 8; ++i)
          ret->edge[i].data = edge[i].data;
        ret->edge[pos].data = data;
        return ret;
      }
      for (uint32 i = 0; i < 8; ++i) {
        ret->edge[i].child = edge[i].child;
        ++edge[i].child->ref;
      }
      --ret->edge[pos >> L].child->ref;
      ret->edge[pos >> L].child = edge[pos >> L].child->build(
          pos & (((uint32)1 << L) - 1), data, L - 3);
      return ret;
    }
    int32 access(const uint32 pos, const uint32 L) {
      if (L)
        return edge[pos >> L].child->access(pos & (((uint32)1 << L) - 1),
                                            L - 3);
      return edge[pos].data;
    }
  };
  node_t *root;
  uint32 L;
  explicit FullyPersistentUnionFindTree(node_t *r) : root(r), L(0) {}
  std::pair<uint32, int32> find_(uint32 x) const {
    int32 y = (int32)x;
    while (y >= 0) {
      x = (uint32)y;
      y = root->access(x, L);
    }
    return {x, y};
  }

public:
  FullyPersistentUnionFindTree() : root(nullptr) {}
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
    node_t *t = root->build(x, L, x_ + y_);
    node_t *ret = t->build(y, L, (int32)x);
    t->reset(L);
    return FullyPersistentUnionFindTree(ret);
  }
  uint32 size(const uint32 &x) const { return (uint32)(-find_(x).second); }
  bool same(const uint32 &x, const uint32 &y) const {
    return find(x) == find(y);
  }
  static FullyPersistentUnionFindTree initialize(const uint32 size) {
    if (!size)
      return FullyPersistentUnionFindTree();
    uint32 L = 0;
    while ((uint32)1 << L < size)
      L += 3;
    L -= 3;
    return FullyPersistentUnionFindTree(node_t::create(L));
  }
};
typename FullyPersistentUnionFindTree::node_t
    *FullyPersistentUnionFindTree::node_t::pool = nullptr;