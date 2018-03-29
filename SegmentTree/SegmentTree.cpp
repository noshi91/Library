#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

template <typename Monoid> class SegmentTree {
  using uint32 = std::uint_fast32_t;

public:
  using value_type = Monoid;
  using reference = value_type &;
  using const_reference = const value_type &;

private:
  using F = std::function<value_type(const_reference, const_reference)>;
  const F f;
  const value_type neutral_;
  const uint32 size_;
  std::vector<value_type> tree;
  static uint32 getsize(const uint32 size) {
    uint32 ret = 1;
    while (ret < size)
      ret <<= 1;
    return ret;
  }
  void recalc(const uint32 index) {
    tree[index] = f(tree[index << 1], tree[index << 1 | 1]);
  }

public:
  SegmentTree(const uint32 size, const_reference neutral = value_type(),
              const F &f = std::plus<value_type>())
      : f(f), neutral_(neutral), size_(getsize(size)),
        tree(size_ << 1, neutral_) {}
  SegmentTree(const std::vector<value_type> &arr,
              const_reference neutral = value_type(),
              const F &f = std::plus<value_type>())
      : f(f), neutral_(neutral), size_(getsize(arr.size())),
        tree(size_ << 1, neutral_) {
    for (uint32 i = 0; i < arr.size(); ++i)
      tree[size_ + i] = arr[i];
    for (uint32 i = size_; --i;)
      recalc(i);
  }
  void update(uint32 index, const std::function<void(reference)> &g) {
    assert(index < size_);
    g(tree[index += size_]);
    while (index >>= 1)
      recalc(index);
  }
  void update(uint32 index, const_reference data) {
    update(index, [&data](reference e) { e = data; });
  }
  value_type range(uint32 begin, uint32 end) const {
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
  uint32 search(const std::function<bool(const_reference)> &b) const {
    if (!b(tree[1]))
      return size_;
    value_type acc = neutral_;
    uint32 i = 1;
    while (i < size_)
      if (!b(f(acc, tree[i <<= 1])))
        acc = f(acc, tree[i++]);
    return i - size_;
  }
  const_reference operator[](const uint32 index) const {
    assert(index < size_);
    return tree[index + size_];
  }
};

/*

verify:https://beta.atcoder.jp/contests/arc033/submissions/2275600

template<typename Monoid>
class SegmentTree;

SegmentTreeはモノイドの区間和を高速に計算するデータ構造です
空間計算量 O(N)


テンプレートパラメータ
-typename Monoid
 結合律 a + (b + c) = (a + b) + c
 単位元 ∃e; e + a = a
 以上の条件を満たす代数的構造 (モノイド)


メンバ型
-value_type
 要素の型 (Monoid)

-reference
 要素(value_type)への参照型 (value_type &)

-const_refernce
 要素(value_type)へのconst参照型 (const value_type &)


メンバ関数
-(constructor) (uint32 size, const_reference neutral = value_type(),
                std::function<value_type(const_reference,
                const_reference)> f = std::plus<value_type>())
 大きさを size、単位元を neutral、演算を f として SegmentTree を構築します
 各要素は単位元で初期化されます
 時間計算量 O(N)

-(constructor) (std::vector<value_type> arr,
                const_reference neutral = value_type(),
                std::function<value_type(const_reference,const_reference)>
                f = std::plus<value_type>())
 arr を要素とし、単位元を neutral、演算を f として SegmentTree を構築します
 時間計算量 O(N)

-update (uint32 index, const_reference data)
 index で指定した要素を data に変更します
 時間計算量 O(logN)

-update (uint32 index, std::function<void(reference)> g)
 index で指定した要素に g を適用します
 時間計算量 O(logN)

-range (uint32 begin, uint32 end)->value_type
 [begin, end)の和を返します
 begin == end のとき 単位元を返します
 時間計算量 O(logN)

-search (std::function<bool(const_reference)> b)->uint32
 b(range(0, i + 1)) が true を返すような i のうち最小の値を返します
 そのような i が存在しない場合 N 以上の値を返します
 b(range(0, 1     ~ i)) が false かつ
 b(range(0, i + 1 ~ N)) が true  である必要があります
 時間計算量 O(logN)

-operator[] (uint32 index)->const_reference
 index で指定した要素にアクセスします
 時間計算量 O(1)


※N:全体の要素数
※f()の時間計算量をO(1)と仮定

*/