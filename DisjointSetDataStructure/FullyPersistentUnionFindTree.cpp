#include <cstdint>
#include <utility>
#include <cstdlib>
#include <tuple>

class FullyPersistentUnionFindTree
{
    static constexpr std::uint_fast64_t ALLOCSIZE = 1 << 10;
    using uint32 = std::uint_fast32_t;
    using int32 = std::int_fast32_t;
    struct node_t
    {
        union {
            node_t *child;
            int32 data;
        } edge[8];
        static node_t *alloc()
        {
            static node_t *pool = nullptr;
            static std::uint_fast64_t it = 0;
            if (!it)
            {
                pool = (node_t *)malloc(ALLOCSIZE * sizeof(node_t));
                it = ALLOCSIZE;
            }
            return &pool[--it];
        }
        static node_t *create(const uint32 L)
        {
            node_t *ret = alloc();
            if (L)
                for (uint32 i = 0; i < 8; ++i)
                    ret->edge[i].child = create(L - 3);
            else
                for (uint32 i = 0; i < 8; ++i)
                    ret->edge[i].data = -1;
            return ret;
        }
        node_t *build(const uint32 pos, const uint32 L, const int32 d) const
        {
            node_t *ret = alloc();
            if (!L)
            {
                for (uint32 i = 0; i < 8; ++i)
                    ret->edge[i].data = edge[i].data;
                ret->edge[pos].data = d;
                return ret;
            }
            for (uint32 i = 0; i < 8; ++i)
                ret->edge[i].child = edge[i].child;
            ret->edge[pos >> L].child = edge[pos >> L].child->build(pos & ((uint32)1 << L) - 1, L - 3, d);
            return ret;
        }
        int32 access(const uint32 pos, const uint32 L) const
        {
            if (L)
                return edge[pos >> L].child->access(pos & ((uint32)1 << L) - 1, L - 3);
            return edge[pos].data;
        }
    };
    node_t *root;
    uint32 L;
    explicit FullyPersistentUnionFindTree(node_t *r, uint32 L_) : root(r), L(L_) {}
    std::pair<uint32, int32> find_(uint32 x) const
    {
        int32 y = (int32)x;
        while (y >= 0)
        {
            x = (uint32)y;
            y = root->access(x, L);
        }
        return {x, y};
    }

  public:
    FullyPersistentUnionFindTree() : root(nullptr), L(0) {}
    uint32 find(const uint32 &x) const { return find_(x).first; }
    FullyPersistentUnionFindTree unite(uint32 x, uint32 y) const
    {
        int32 x_, y_;
        std::tie(x, x_) = find_(x);
        std::tie(y, y_) = find_(y);
        if (x == y)
            return *this;
        if (x_ > y_)
        {
            std::swap(x, y);
            std::swap(x_, y_);
        }
        return FullyPersistentUnionFindTree(root->build(x, L, x_ + y_)->build(y, L, (int32)x), L);
    }
    uint32 size(const uint32 &x) const { return (uint32)(-find_(x).second); }
    bool same(const uint32 &x, const uint32 &y) const { return find(x) == find(y); }
    static FullyPersistentUnionFindTree initialize(const uint32 size)
    {
        if (!size)
            return FullyPersistentUnionFindTree();
        uint32 L = 0;
        while ((uint32)1 << L < size)
            L += 3;
        L -= 3;
        return FullyPersistentUnionFindTree(node_t::create(L), L);
    }
};