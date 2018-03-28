#include <cstdint>
#include <utility>
#include <vector>

template <typename Abelian> class PotentializedUnionFindTree {
  using int32 = std::int_fast32_t;
  using uint32 = std::uint_fast32_t;
  std::vector<std::pair<int32, Abelian>> tree;

public:
  PotentializedUnionFindTree(uint32 size, Abelian e = Abelian())
      : tree(size, {-1, e}) {}
  uint32 find(const uint32 x) {
    if (tree[x].first < 0)
      return x;
    uint32 t = (uint32)tree[x].first;
    tree[x].first = (int32)find(t);
    tree[x].second = tree[t].second + tree[x].second;
    return (uint32)tree[x].first;
  }
  Abelian potential(const uint32 x) {
    find(x);
    return tree[x].second;
  }
  Abelian diff(const uint32 x, const uint32 y) {
    return potential(y) + (-potential(x));
  }
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
  bool same(const uint32 x, const uint32 y) { return find(x) == find(y); }
  uint32 size(const uint32 x) { return (uint32)(-tree[find(x)].first); }
};

/*

template <typename Abelian>
class PotentializedUnionFindTree;

PotentializedUnionFindTreeはポテンシャルが付いた要素からなる素集合を管理するデータ構造です
空間計算量 O(N)


テンプレートパラメータ
-typename Abelian
 結合律 a + (b + c) = (a + b) + c
 交換律 a + b = b + a
 単位元 ∃e; e + a = a
 逆元　 ∀a, ∃-a; a + (-a) = e
 以上の条件を満たす代数的構造 (アーベル群)
 二項演算が operator+, 逆元が operator-(単項) で定義されている必要があります


メンバ関数
-(constructor) (uint32 size, Abelian e = Abelian())
 独立した要素を size 個持つ状態で構築します
 e には単位元を与えてください
 時間計算量 O(N)

-find (uint32 x)->uint32
 x の根を返します
 時間計算量 償却 O(α(N))

-potential (uint32 x)->Abelian
 x の持つポテンシャルを返します
 時間計算量 償却 O(α(N))

-diff (uint32 x, uint32 y)->Abelian
 x を基準とした y のポテンシャルを返します
 x と y が異なる集合に属していた場合の動作は保証されません
 時間計算量 償却 O(α(N))

-unite (uint32 x, uint32 y, Abelian d)->bool
 x と y がそれぞれ含まれる集合を x を基準とした y のポテンシャルが d
 となるように併合します
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