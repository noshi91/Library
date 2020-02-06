---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: gomi/Heap/RadixHeap64.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#129e783b40af8d9f118607f8172136f7">gomi/Heap</a>
* <a href="{{ site.github.repository_url }}/blob/master/gomi/Heap/RadixHeap64.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-11 20:43:35+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

template <typename T> class RadixHeap64 {
public:
  using key_type = std::uint_fast64_t;
  using value_type = std::pair<key_type, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::uint_fast32_t;

private:
  static size_type bsr(const key_type x) {
    if (!x)
      return 0;
#ifdef __GNUC__
    return 64 - __builtin_clzll(x);
#else
    size_type t = 32;
    for (size_type i = 4; ~i; --i) {
      if (x & ~(((key_type)1 << t) - 1))
        t += (size_type)1 << i;
      else
        t -= (size_type)1 << i;
    }
    if (x & ~(((key_type)1 << t) - 1))
      ++t;
    return t;
#endif
  }
  std::vector<value_type> v[65];
  key_type last;
  size_type size_;

public:
  RadixHeap64() : last(0), size_(0) {}
  value_type pop() {
    assert(size_);
    --size_;
    if (v[0].empty()) {
      size_type i = 1;
      while (v[i].empty())
        ++i;
      last = std::numeric_limits<key_type>::max();
      for (const auto &d : v[i])
        last = std::min(last, d.first);
      for (const auto &d : v[i])
        v[bsr(last ^ d.first)].push_back(d);
      v[i].clear();
    }
    value_type ret = v[0].back();
    v[0].pop_back();
    return ret;
  }
  void push(const_reference x) {
    assert(last <= x.first);
    ++size_;
    v[bsr(x.first ^ last)].push_back(x);
  }
  bool empty() const { return !size_; }
  size_type size() const { return size_; }
};

/*

verify:https://beta.atcoder.jp/contests/abc035/submissions/2280136

template<typename T>
class RadixHeap64;

RadixHeap64は64bit符号なし整数をキーとして、
それと対応する値を管理する最小ヒープ(優先度付きキュー)です
追加される要素は直前に削除した値以上である必要があります
空間計算量 O(N)


テンプレートパラメータ
-typename T
 キーに対応する値


メンバ型
-key_type
 キーになる64bit符号なし整数型 (std::uint_fast64_t)

-value_type
 要素の型 (std::pair<key_type, T>)

-reference
 要素(value_type)への参照型 (value_type &)

-const_reference
 要素(value_type)へのconst参照型 (const value_type &)

-size_type
 要素数を表す符号なし整数型 (std::uint_fast32_t)


メンバ関数
-(constructor) ()
 空のヒープを構築します
 時間計算量 O(1)

-pop (void)->value_type
 先頭の要素を削除し、その値を返します
 時間計算量 償却 O(logD)

-push (const_reference x)
 x を要素としてヒープに追加します
 時間計算量 O(1)

-empty ()->bool
 ヒープが空かどうかを返します
 時間計算量 O(1)

-size ()->size_type
 要素数を取得します
 時間計算量 O(1)


※D:キーの最大値

*/
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "gomi/Heap/RadixHeap64.cpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

template <typename T> class RadixHeap64 {
public:
  using key_type = std::uint_fast64_t;
  using value_type = std::pair<key_type, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::uint_fast32_t;

private:
  static size_type bsr(const key_type x) {
    if (!x)
      return 0;
#ifdef __GNUC__
    return 64 - __builtin_clzll(x);
#else
    size_type t = 32;
    for (size_type i = 4; ~i; --i) {
      if (x & ~(((key_type)1 << t) - 1))
        t += (size_type)1 << i;
      else
        t -= (size_type)1 << i;
    }
    if (x & ~(((key_type)1 << t) - 1))
      ++t;
    return t;
#endif
  }
  std::vector<value_type> v[65];
  key_type last;
  size_type size_;

public:
  RadixHeap64() : last(0), size_(0) {}
  value_type pop() {
    assert(size_);
    --size_;
    if (v[0].empty()) {
      size_type i = 1;
      while (v[i].empty())
        ++i;
      last = std::numeric_limits<key_type>::max();
      for (const auto &d : v[i])
        last = std::min(last, d.first);
      for (const auto &d : v[i])
        v[bsr(last ^ d.first)].push_back(d);
      v[i].clear();
    }
    value_type ret = v[0].back();
    v[0].pop_back();
    return ret;
  }
  void push(const_reference x) {
    assert(last <= x.first);
    ++size_;
    v[bsr(x.first ^ last)].push_back(x);
  }
  bool empty() const { return !size_; }
  size_type size() const { return size_; }
};

/*

verify:https://beta.atcoder.jp/contests/abc035/submissions/2280136

template<typename T>
class RadixHeap64;

RadixHeap64は64bit符号なし整数をキーとして、
それと対応する値を管理する最小ヒープ(優先度付きキュー)です
追加される要素は直前に削除した値以上である必要があります
空間計算量 O(N)


テンプレートパラメータ
-typename T
 キーに対応する値


メンバ型
-key_type
 キーになる64bit符号なし整数型 (std::uint_fast64_t)

-value_type
 要素の型 (std::pair<key_type, T>)

-reference
 要素(value_type)への参照型 (value_type &)

-const_reference
 要素(value_type)へのconst参照型 (const value_type &)

-size_type
 要素数を表す符号なし整数型 (std::uint_fast32_t)


メンバ関数
-(constructor) ()
 空のヒープを構築します
 時間計算量 O(1)

-pop (void)->value_type
 先頭の要素を削除し、その値を返します
 時間計算量 償却 O(logD)

-push (const_reference x)
 x を要素としてヒープに追加します
 時間計算量 O(1)

-empty ()->bool
 ヒープが空かどうかを返します
 時間計算量 O(1)

-size ()->size_type
 要素数を取得します
 時間計算量 O(1)


※D:キーの最大値

*/

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

