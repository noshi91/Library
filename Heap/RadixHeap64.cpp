#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdint>
#include <utility>
#include <vector>
/*

class RadixHeap64;

RadixHeap64は64bit符号なし整数をキーとして、それに紐づけられた32bit符号なし整数を管理する最小ヒープ(優先度付きキュー)です
追加される要素は直前に削除した値以上である必要があります
空間計算量 O(N)


メンバ関数
-(constructor) ()
 空のヒープを構築します
 時間計算量 O(1)

-pop (void)->std::pair<uint64, uint32>
 先頭の要素を削除し、その値を返します
 時間計算量 償却 O(logD)

-push (std::pair<uint64, uint32> x)
 x を要素としてヒープに追加します
 時間計算量 O(1)

-empty ()->bool
 ヒープが空かどうかを返します
 時間計算量 O(1)


※D:キーの最大値

*/

class RadixHeap64 {
  using uint32 = std::uint_fast32_t;
  using uint64 = std::uint_fast64_t;
  using P = std::pair<uint64, uint32>;
  uint32 bsr(const uint64 x) {
    if (!x)
      return 0;
#ifdef __GNUC__
    return 64 - __builtin_clzll(x);
#else
    uint32 t = 32;
    for (uint32 i = 4; ~i; --i) {
      if (x & ~(((uint64)1 << t) - 1)) {
        t += (uint64)1 << i;
      } else {
        t -= (uint64)1 << i;
      }
    }
    if (x & ~(((uint64)1 << t) - 1))
      ++t;
    return t;
#endif
  }
  std::vector<P> v[65];
  uint64 last;
  uint32 size;

public:
  RadixHeap64() : last(0), size(0) {}
  P pop() {
    assert(size);
    --size;
    if (v[0].empty()) {
      uint32 i = 1;
      while (v[i].empty())
        ++i;
      last = std::numeric_limits<uint64>::max();
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
  void push(const P &x) {
    assert(last <= x.first);
    ++size;
    v[bsr(x.first ^ last)].push_back(x);
  }
  bool empty() { return !size; }
};