#include <cassert>
#include <cstdint>
#include <functional>
#include <tuple>
#include <vector>

template <typename Abelian> class PotentializedUnionFindTree {

public:
  using value_type = Abelian;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::uint_fast32_t;

private:
  using F = std::function<value_type(const_reference, const_reference)>;
  using G = std::function<value_type(const_reference)>;
  const F f;
  const G g;
  const value_type neutral_;
  std::vector<std::tuple<bool, size_type, value_type>> tree;

public:
  PotentializedUnionFindTree(const size_type size,
                             const_reference neutral = value_type(),
                             const F &f = std::plus<value_type>(),
                             const G &g = std::negate<value_type>())
      : f(f), g(g), neutral_(neutral),
        tree(size, std::forward_as_tuple(1, 1, neutral_)) {}
  size_type find(const size_type x) {
    assert(x < tree.size());
    if (std::get<0>(tree[x]))
      return x;
    const size_type t = std::get<1>(tree[x]);
    std::get<1>(tree[x]) = find(t);
    std::get<2>(tree[x]) = f(std::get<2>(tree[t]), std::get<2>(tree[x]));
    return std::get<1>(tree[x]);
  }
  value_type potential(const size_type x) {
    assert(x < tree.size());
    find(x);
    return std::get<2>(tree[x]);
  }
  value_type diff(const size_type x, const size_type y) {
    assert(x < tree.size());
    assert(y < tree.size());
    return f(potential(y), g(potential(x)));
  }
  bool unite(size_type x, size_type y, value_type d) {
    assert(x < tree.size());
    assert(y < tree.size());
    d = f(d, diff(y, x));
    x = find(x);
    y = find(y);
    if (x == y)
      return false;
    if (std::get<1>(tree[x]) < std::get<1>(tree[y]))
      std::swap(x, y), d = g(d);
    std::get<1>(tree[x]) += std::get<1>(tree[y]);
    tree[y] = std::forward_as_tuple(0, x, d);
    return true;
  }
  bool same(const size_type x, const size_type y) {
    assert(x < tree.size());
    assert(y < tree.size());
    return find(x) == find(y);
  }
  size_type size(const size_type x) {
    assert(x < tree.size());
    return std::get<1>(tree[find(x)]);
  }
};

/*

verify:https://beta.atcoder.jp/contests/abc087/submissions/2279390

template <typename Abelian, typename Size = std::uint_fast32_t>
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


メンバ型
-value_type
 要素の型 (Abelian)

-reference
 要素(value_type)への参照型 (value_type &)

-const_reference
 要素(value_type)へのconst参照型 (const value_type &)

-size_type
 符号なし整数型 (std::uint_fast32_t)


メンバ関数
-(constructor) (size_type size, const_reference neutral = value_type(),
                std::function<value_type(const_reference, const_reference)>
                f = std::plus<value_type>(),
                std::function<value_type(const_reference)>
                g = std::negate<value_type>())
 独立した要素を size 個持つ状態で、neutral を単位元
 f を演算、g を逆元を得る関数として構築します
 各要素のポテンシャルは単位元で初期化されます
 時間計算量 O(N)

-find (size_type x)->size_type
 x の根を返します
 時間計算量 償却 O(α(N))

-potential (size_type x)->value_type
 x の持つポテンシャルを返します
 時間計算量 償却 O(α(N))

-diff (size_type x, size_type y)->value_type
 x を基準とした y のポテンシャルを返します
 x と y が異なる集合に属していた場合の動作は保証されません
 時間計算量 償却 O(α(N))

-unite (size_type x, size_type y, value_type d)->bool
 x と y がそれぞれ含まれる集合を x を基準とした y のポテンシャルが
 d となるように併合します
 併合に成功したか、すなわち x と y が違う集合に属していたかを真偽値で返します
 時間計算量 償却 O(α(N))

-same (size_type x, size_type y)->bool
 x と y が同じ集合に属しているかを真偽値で返します
 時間計算量 償却 O(α(N))

-size (size_type x)->size_type
 x の含まれる集合に含まれる要素数を返します
 時間計算量 償却 O(α(N))


※N:全体の要素数
※α():アッカーマン関数の逆関数
※f(), g() の時間計算量を O(1) と仮定

*/