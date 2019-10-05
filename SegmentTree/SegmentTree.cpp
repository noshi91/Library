#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

template <typename Monoid, class Container = std::vector<Monoid>>
class SegmentTree {
public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;
  using container_type = Container;

private:
  using F = std::function<value_type(const_reference, const_reference)>;
  const F f;
  const value_type neutral_;
  const size_type size_;
  container_type tree;
  static size_type getsize(const size_type size) {
    size_type ret = 1;
    while (ret < size)
      ret <<= 1;
    return ret;
  }
  void recalc(const size_type index) {
    tree[index] = f(tree[index << 1], tree[index << 1 | 1]);
  }

public:
  SegmentTree(const size_type size, const_reference neutral = value_type(),
              const F &addition = std::plus<value_type>())
      : f(addition), neutral_(neutral), size_(getsize(size)),
        tree(size_ << 1, neutral_) {}
  void update(size_type index,
              const std::function<value_type(const_reference)> &g) {
    assert(index < size_);
    index += size_;
    tree[index] = g(tree[index]);
    while (index >>= 1)
      recalc(index);
  }
  void update(const size_type index, const_reference data) {
    update(index, [&data](const_reference e) { return data; });
  }
  value_type range(size_type begin, size_type end) const {
    assert(begin <= end);
    assert(begin <= size_);
    assert(end <= size_);
    value_type retL = neutral_, retR = neutral_;
    for (begin += size_, end += size_; begin < end; begin >>= 1, end >>= 1) {
      if (begin & 1)
        retL = f(retL, tree[begin++]);
      if (end & 1)
        retR = f(tree[end - 1], retR);
    }
    return f(retL, retR);
  }
  size_type search(const std::function<bool(const_reference)> &b) const {
    if (!b(tree[1]))
      return size_;
    value_type acc = neutral_;
    size_type i = 1;
    while (i < size_)
      if (!b(f(acc, tree[i <<= 1])))
        acc = f(acc, tree[i++]);
    return i - size_;
  }
  const_reference operator[](const size_type index) const {
    assert(index < size_);
    return tree[index + size_];
  }
  size_type size() const { return size_; }
};

/*

verify:https://beta.atcoder.jp/contests/arc033/submissions/2291069

template<typename Monoid, class Container = std::vector<Monoid>>
class SegmentTree;

SegmentTreeはモノイドの区間和を高速に計算するデータ構造です
空間計算量 O(N)


テンプレートパラメータ
-typename Monoid
 結合律 a + (b + c) = (a + b) + c
 単位元 ∃e [∀a [e + a = a + e = a]]
 以上の条件を満たす代数的構造 (モノイド)

-class Container
 内部実装のコンテナクラス
 デフォルトでは std::vector<Monoid>


メンバ型
-container_type
 コンテナの型 (Container)

-value_type
 要素の型 (Container::value_type)

-reference
 要素(value_type)への参照型 (Container::reference)

-const_reference
 要素(value_type)へのconst参照型 (Container::const_reference)

-size_type
 符号なし整数型 (Container::size_type)


メンバ関数
-(constructor) (size_type size, const_reference neutral = value_type(),
                std::function<value_type(const_reference,
                const_reference)> addition = std::plus<value_type>())
 要素数 size、単位元を neutral、演算を addition として SegmentTree を構築します
 各要素は単位元で初期化されます
 時間計算量 O(N)

-update (size_type index, const_reference data)
 index で指定した要素を data に変更します
 時間計算量 O(logN)

-update (size_type index, std::function<value_type(const_reference)> g)
 index で指定した要素を g を適用した値で更新します
 時間計算量 O(logN)

-range (size_type begin, size_type end)->value_type
 [begin, end)の和を返します
 begin == end のとき 単位元を返します
 時間計算量 O(logN)

-search (std::function<bool(const_reference)> b)->size_type
 b(range(0, i + 1)) が true を返すような i のうち最小の値を返します
 そのような i が存在しない場合 N 以上の値を返します
 b(range(0, 1     ~ i)) が false かつ
 b(range(0, i + 1 ~ N)) が true  である必要があります
 時間計算量 O(logN)

-operator[] (size_type index)->const_reference
 index で指定した要素にアクセスします
 時間計算量 O(1)

-size ()->size_type
 要素数を返します　(コンストラクタで与えた size より大きい可能性があります)
 時間計算量 O(1)

※N:全体の要素数
※f() の時間計算量を O(1) と仮定

*/