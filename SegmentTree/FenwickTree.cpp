#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

template <typename CommutativeMonoid> class FenwickTree {

public:
  using value_type = CommutativeMonoid;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::uint_fast32_t;

private:
  using F = std::function<value_type(const_reference, const_reference)>;
  const value_type neutral_;
  const F f;
  const size_type size_;
  std::vector<value_type> tree;
  static size_type getsize(const size_type size) {
    size_type ret = 1;
    while (ret < size)
      ret <<= 1;
    return ret;
  }

public:
  FenwickTree(const size_type size, const_reference neutral = value_type(),
              const F &f = std::plus<value_type>())
      : neutral_(neutral), f(f), size_(getsize(size)),
        tree(size_ + 1, neutral_) {}
  void update(size_type index, const_reference diff) {
    assert(index < size_);
    for (++index; index <= size_; index += index & ~index + 1)
      tree[index] = f(tree[index], diff);
  }
  value_type range(size_type end) const {
    assert(end <= size_);
    value_type ret = neutral_;
    do
      ret = f(tree[end], ret);
    while (end &= end - 1);
    return ret;
  }
  size_type search(const std::function<bool(const_reference)> &b) const {
    if (!b(tree[size_]))
      return size_;
    size_type i = 0, k = size_;
    value_type acc = neutral_;
    while (k >>= 1)
      if (!b(f(acc, tree[i + k])))
        acc = f(acc, tree[i += k]);
    return i;
  }
};

/*

verify:https://beta.atcoder.jp/contests/arc033/submissions/2279714

template<typename CommutativeMonoid>
class FenwickTree;

FenwickTreeは可換モノイドの区間和を高速に計算するデータ構造です
空間計算量 O(N)


テンプレートパラメータ
-typename CommutativeMonoid
 結合律 a + (b + c) = (a + b) + c
 交換律 a + b = b + a
 単位元 ∃e [∀a [e + a = a]]
 以上の条件を満たす代数的構造 (可換モノイド)


メンバ型
-value_type
 要素の型 (CommutativeMonoid)

-reference
 要素(value_type)への参照型 (value_type &)

-const_reference
 要素(value_type)へのconst参照型 (const value_type &)

-size_type
 符号なし整数型 (std::uint_fast32_t)


メンバ関数
-(constructor) (size_type size, const_reference neutral = value_type(),
                std::function<value_type(const_reference, const_reference)>
                f =std::plus<value_type>())
 大きさを size、単位元を neutral、演算を f として FenwickTree を構築します
 各要素は単位元で初期化されます
 時間計算量 O(N)

-update (size_type index, const_reference diff)
 index で指定した要素に diff を加算します
 時間計算量 O(logN)

-range (size_type end)-value_type
 [0, end)の和を返します
 end == 0 のとき 単位元を返します
 時間計算量 O(logN)

-search (std::function<bool(const_reference)> b)->size_type
 b(range(i + 1)) が true を返すような i のうち最小の値を返します
 そのような i が存在しない場合 N 以上の値を返します
 b(range(1   ~ i)) が false かつ
 b(range(i+1 ~ N)) が true  である必要があります
 時間計算量 O(logN)


※N:全体の要素数
※f()の時間計算量をO(1)と仮定

*/