#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdint>
#include <utility>
#include <vector>
/*

verify:https://beta.atcoder.jp/contests/arc084/submissions/2200320

template<typename T>
class RadixHeap32;

RadixHeap32は32bit符号なし整数をキーとして、それと対応する値を管理する最小ヒープ(優先度付きキュー)です
追加される要素は直前に削除した値以上である必要があります
空間計算量 O(N)


テンプレートパラメータ
-typename T
 キーに対応する値


メンバ関数
-(constructor) ()
 空のヒープを構築します
 時間計算量 O(1)

-pop (void)->std::pair<uint32, T>
 先頭の要素を削除し、その値を返します
 時間計算量 償却 O(logD)

-push (std::pair<uint32, T> x)
 x を要素としてヒープに追加します
 時間計算量 O(1)

-empty ()->bool
 ヒープが空かどうかを返します
 時間計算量 O(1)


※D:キーの最大値

*/

template<typename T>
class RadixHeap32 {
  using uint32 = std::uint_fast32_t;
  using P = std::pair<uint32, T>;
  uint32 bsr(const uint32 x) {
    if (!x)
      return 0;
#ifdef __GNUC__
    return 32 - __builtin_clz(x);
#else
    uint32 t = 16;
    for (uint32 i = 3; ~i; --i) {
      if (x & ~(((uint32)1 << t) - 1)) {
        t += (uint32)1 << i;
      } else {
        t -= (uint32)1 << i;
      }
    }
    if (x & ~(((uint32)1 << t) - 1))
      ++t;
    return t;
#endif
  }
  std::vector<P> v[33];
  uint32 last, size;

public:
  RadixHeap32() : last(0), size(0) {}
  P pop() {
    assert(size);
    --size;
    if (v[0].empty()) {
      uint32 i = 1;
      while (v[i].empty())
        ++i;
      last = std::numeric_limits<uint32>::max();
      for (P &d : v[i])
        last = std::min(last, d.first);
      for (P &d : v[i])
        v[bsr(last ^ d.first)].push_back(d);
      v[i].clear();
    }
    P ret = v[0].back();
    v[0].pop_back();
    return ret;
  }
  void push(P x) {
    assert(last <= x.first);
    ++size;
    v[bsr(x.first ^ last)].push_back(x);
  }
  bool empty() { return !size; }
};