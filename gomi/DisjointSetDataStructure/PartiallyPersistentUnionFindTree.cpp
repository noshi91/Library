#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

class PartiallyPersistentUnionFindTree {
public:
  using size_type = std::uint_fast32_t;

private:
  std::vector<std::pair<size_type, size_type>> tree;
  std::vector<std::vector<std::pair<size_type, size_type>>> siz;
  size_type global_count;

public:
  PartiallyPersistentUnionFindTree(const size_type size)
      : tree(size, std::make_pair(1, std::numeric_limits<size_type>::max())),
        siz(size, std::vector<std::pair<size_type, size_type>>(
                      1, std::make_pair(0, 1))),
        global_count(0) {}
  size_type find(const size_type ver, size_type x) const {
    assert(x < tree.size());
    while (tree[x].second <= ver)
      x = tree[x].first;
    return x;
  }
  bool unite(size_type x, size_type y) {
    assert(x < tree.size());
    assert(y < tree.size());
    ++global_count;
    x = find(global_count, x);
    y = find(global_count, y);
    if (x == y)
      return false;
    if (tree[x].first < tree[y].first)
      std::swap(x, y);
    tree[x].first += tree[y].first;
    siz[x].emplace_back(global_count, tree[x].first);
    tree[y] = std::make_pair(x, global_count);
    return true;
  }
  bool same(const size_type ver, const size_type x, const size_type y) const {
    assert(x < tree.size());
    assert(y < tree.size());
    return find(ver, x) == find(ver, y);
  }
  size_type size(const size_type ver, size_type x) const {
    assert(x < tree.size());
    x = find(ver, x);
    return (std::lower_bound(
                siz[x].begin(), siz[x].end(),
                std::make_pair(ver + 1, static_cast<size_type>(0))) -
            1)
        ->second;
  }
  size_type count() const { return global_count; }
};

/*

verify:https://beta.atcoder.jp/contests/code-thanks-festival-2017/submissions/2279624

class PartiallyPersistentUnionFindTree;

PartiallyPersistentUnionFindTreeは素集合を管理する部分永続的データ構造です
空間計算量 O(N)


メンバ型
-size_type
 符号なし整数型 (std::uint_fast32_t)

メンバ関数
-(constructor) (size_type size)
 独立した要素を size 個持つ状態で構築します
 時間計算量 O(N)

-find (size_type ver, size_type x)->size_type
 ver 回目の unite が終了した時点での x の根を返します
 時間計算量 O(logN)

-unite (size_type ver, size_type x, size_type y)->bool
 x と y がそれぞれ含まれる集合を併合します
 併合に成功したか、すなわち x と y が違う集合に属していたかを真偽値で返します
 時間計算量 O(logN)

-same (size_type ver, size_type x, size_type y)->bool
 ver 回目の併合操作が終了した時点で、
 x と y が同じ集合に属しているかを真偽値で返します
 時間計算量 O(logN)

-size (size_type ver, size_type x)->size_type
 ver 回目の併合操作が終了した時点で x の含まれる集合に含まれる要素数を返します
 時間計算量 O(logN)

-count ()->size_type
 現在の操作回数を返します
 時間計算量 O(1)


※N:全体の要素数

*/