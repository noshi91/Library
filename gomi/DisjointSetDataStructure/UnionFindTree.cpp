#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

class UnionFindTree {

public:
  using size_type = std::uint_fast32_t;

private:
  std::vector<std::pair<bool, size_type>> tree;

public:
  UnionFindTree(const size_type size) : tree(size, std::make_pair(1, 1)) {}
  size_type find(const size_type x) {
    assert(x < tree.size());
    if (tree[x].first)
      return x;
    return tree[x].second = find(tree[x].second);
  }
  bool unite(size_type x, size_type y) {
    assert(x < tree.size());
    assert(y < tree.size());
    x = find(x);
    y = find(y);
    if (x == y)
      return false;
    if (tree[x].second < tree[y].second)
      std::swap(x, y);
    tree[x].second += tree[y].second;
    tree[y] = std::make_pair(0, x);
    return true;
  }
  bool same(const size_type x, const size_type y) {
    assert(x < tree.size());
    assert(y < tree.size());
    return find(x) == find(y);
  }
  size_type size(const size_type x) {
    assert(x < tree.size());
    return tree[find(x)].second;
  }
};

/*

verify:https://beta.atcoder.jp/contests/atc001/submissions/2279506

class UnionFindTree;

UnionFindTreeは素集合を管理するデータ構造です
空間計算量 O(N)


メンバ型
-size_type
 符号なし整数型 (std::uint_fast32_t)


メンバ関数
-(constructor) (size_type size)
 独立した要素を size 個持つ状態で構築します
 時間計算量 O(N)

-find (size_type x)->size_type
 x の根を返します
 時間計算量 償却 O(α(N))

-unite (size_type x, size_type y)->bool
 x と y がそれぞれ含まれる集合を併合します
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

*/