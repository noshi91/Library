#include <cassert>
#include <functional>
#include <utility>
#include <vector>

template <typename ValueMonoid, typename OperatorMonoid> class LazySegmentTree {
public:
  using value_type = ValueMonoid;
  using reference = value_type &;
  using const_reference = const value_type &;
  using operator_type = OperatorMonoid;

private:
  using operator_constref = const operator_type &;
  using container_type = std::vector<std::pair<value_type, operator_type>>;

public:
  using size_type = typename container_type::size_type;

private:
  using F = std::function<value_type(const_reference, const_reference)>;
  using G = std::function<operator_type(operator_constref, operator_constref)>;
  using H = std::function<value_type(const_reference, operator_constref)>;
  const F f;
  const G g;
  const H h;
  const value_type v_neutral;
  const operator_type o_neutral;
  size_type height, size_;
  container_type tree;
  static size_type getheight(const size_type size) {
    size_type ret = 0;
    while ((size_type)1 << ret < size)
      ++ret;
    return ret;
  }
  value_type reflect(const size_type index) {
    return h(tree[index].first, tree[index].second);
  }
  void recalc(const size_type index) {
    tree[index].first = f(reflect(index << 1), reflect(index << 1 | 1));
  }
  void assign(const size_type index, operator_constref data) {
    tree[index].second = g(tree[index].second, data);
  }
  void push(const size_type index) {
    assign(index << 1, tree[index].second);
    assign(index << 1 | 1, tree[index].second);
    tree[index].second = o_neutral;
  }
  void propagate(const size_type index) {
    for (size_type i = height; i; --i)
      push(index >> i);
  }
  void thrust(const size_type index) {
    tree[index].first = reflect(index);
    push(index);
  }
  void evaluate(const size_type index) {
    for (size_type i = height; i; --i)
      thrust(index >> i);
  }
  void build(size_type index) {
    while (index >>= 1)
      recalc(index);
  }

public:
  LazySegmentTree(
      const size_type size, const F &value_addition = std::plus<value_type>(),
      const_reference value_neutral = value_type(),
      const G &operator_multiplication = std::multiplies<operator_type>(),
      operator_constref operator_neutral = operator_type(),
      const H &mutual_multiplication =
          [](const_reference l, operator_constref r) { return l * r; })
      : f(value_addition), v_neutral(value_neutral), g(operator_multiplication),
        o_neutral(operator_neutral), h(mutual_multiplication),
        height(getheight(size)), size_((size_type)1 << height),
        tree(size_ << 1, std::make_pair(v_neutral, o_neutral)) {}
  void update(size_type begin, size_type end, operator_constref data) {
    assert(begin <= end);
    assert(begin <= size_);
    assert(end <= size_);
    begin += size_;
    end += size_;
    propagate(begin);
    propagate(end - 1);
    for (size_type left = begin, right = end; left < right;
         left >>= 1, right >>= 1) {
      if (left & 1)
        assign(left++, data);
      if (right & 1)
        assign(right - 1, data);
    }
    build(begin);
    build(end - 1);
  }
  void update(size_type index,
              const std::function<value_type(const_reference)> &e) {
    assert(index < size_);
    index += size_;
    propagate(index);
    tree[index].first = e(reflect(index));
    tree[index].second = o_neutral;
    build(index);
  }
  void update(const size_type index, const_reference data) {
    assert(index < size_);
    update(index, [&data](const_reference d) { return data; });
  }
  value_type range(size_type begin, size_type end) {
    assert(begin <= end);
    assert(begin <= size_);
    assert(end <= size_);
    begin += size_;
    end += size_;
    evaluate(begin);
    evaluate(end - 1);
    value_type retL = v_neutral, retR = v_neutral;
    for (; begin < end; begin >>= 1, end >>= 1) {
      if (begin & 1)
        retL = f(retL, reflect(begin++));
      if (end & 1)
        retR = f(reflect(end - 1), retR);
    }
    return f(retL, retR);
  }
  size_type search(const std::function<bool(const_reference)> &b) {
    if (!b(reflect(1)))
      return size_;
    value_type acc = v_neutral;
    size_type i = 1;
    while (i < size_) {
      thrust(i);
      if (!b(f(acc, reflect(i <<= 1))))
        acc = f(acc, reflect(i++));
    }
    return i - size_;
  }
  const_reference operator[](const size_type index) {
    assert(index < size_);
    index += size_;
    evaluate(index);
    tree[index].first = reflect(index);
    tree[index].second = o_neutral;
    return tree[index].first;
  }
  size_type size() const { return size_; }
};

/*

verify:http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=2758255#1

template<typename ValueMonoid, typename OperatorMonoid>
class LazySegmentTree;

LazySegmentTreeはモノイドの区間和と区間更新を高速に計算するデータ構造です
空間計算量 O(N)


テンプレートパラメータ
-typename ValueMonoid
 結合律 a + (b + c) = (a + b) + c
 単位元 ∃e [∀a [e + a = a + e = a]]
 以上の条件を満たす代数的構造 (モノイド)

-typename OperatorMonoid
 結合律 a * (b * c) = (a * b) * c
 単位元 ∃e [∀a [e * a = a * e = a]]
 以上の条件を満たす代数的構造 (モノイド)

 また、以下の条件が成立する必要がある
 (ValueMonoid を V、OperatorMonoid を O と表記)
 閉性 V * O -> V
 単位元 ∃e∈O [∀a∈V [a * e = a]]
 結合律 a * (b * c) = (a * b) * c (a∈V, b,c∈O)
 分配法則 (a * c) + (b * c) = (a + b) * c (a,b∈V, c∈O)


メンバ型

-value_type
 要素の型 (ValueMonoid)

-reference
 要素(value_type)への参照型 (value_type &)

-const_reference
 要素(value_type)へのconst参照型 (const value_type &)

-operator_type
 演算要素の型 (OperatorMonoid)

-size_type
 符号なし整数型 (std::vector<std::pair<value_type, operator_type>>::size_type)


メンバ関数
-(constructor) (size_type size,
                std::function<value_type(const_reference, const_reference)>
                value_addition=std::plus<value_type>(),
                const_reference value_neutral = value_type(),
                std::function<operator_type
                (const operator_type &,const operator_type &)>
                &operator_multiplication = std::multiplies<operator_type>(),
                const operator_type &operator_neutral = operator_type(),
                std::function<value_type
                (const_reference, const operator_type &)>
                mutual_multiplication
                = [](const_reference l,const operator_type &r){ return l * r; })
 要素数 :size
 value_type :演算 :value_addition
            :単位元 :value_neutral
 operator_type :演算 :operator_multiplication
               :単位元 :operator_neutral
 value_type, operator_type間の演算 :mutual_multiplication
 上記の状態で LazySegmentTree を構築します
 各要素は単位元で初期化されます
 時間計算量 O(N)

-update (size_type begin, size_type end const operator_type &data)
 [begin, end) に data を乗じます
 時間計算量 O(logN)

-update (size_type index, std::function<value_type(const_reference)> g)
 index で指定した要素を g を適用した値で更新します
 時間計算量 O(logN)

-update (size_type index, const_reference data)
 index で指定した要素を data に変更します
 時間計算量 O(logN)

-range (size_type begin, size_type end)->value_type
 [begin, end) の和を返します
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
 時間計算量 O(logN)

-size ()->size_type
 要素数を返します　(コンストラクタで与えた size より大きい可能性があります)
 時間計算量 O(1)

※N:全体の要素数
※f() の時間計算量を O(1) と仮定

*/