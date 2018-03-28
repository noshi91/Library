#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <utility>

template <typename T, bool P = false> class PairingHeap {
  static constexpr std::uint_fast64_t ALLOCSIZE = (std::uint_fast64_t)1 << 10;
  struct node_t {
    T data;
    node_t *left, *right;
  };
  node_t *root;
  std::uint_fast32_t size_;
  static node_t *merge(node_t *x, node_t *y) {
    if (P ^ (x->data < y->data))
      std::swap(x, y);
    x->right = y->left;
    y->left = x;
    return y;
  }

public:
  PairingHeap() : root(nullptr), size_(0) {}
  const T &top() const {
    assert(root);
    return root->data;
  }
  const T &pop() {
    assert(root);
    --size_;
    const T &ret = root->data;
    node_t *n = nullptr, *x = root->left, *y;
    while (x) {
      y = x;
      if (x->right) {
        x = x->right->right;
        y = merge(y, y->right);
      } else {
        x = nullptr;
      }
      y->right = n;
      n = y;
    }
    if (!n) {
      root = nullptr;
      return ret;
    }
    root = n;
    n = n->right;
    while (n) {
      x = n;
      n = n->right;
      root = merge(root, x);
    }
    return ret;
  }
  void push(const T &data) {
    static node_t *pool = nullptr;
    static std::uint_fast64_t it = ALLOCSIZE;
    if (it == ALLOCSIZE) {
      pool = (node_t *)malloc(ALLOCSIZE * sizeof(node_t));
      it = 0;
    }
    node_t *top = &pool[it++];
    top->data = data;
    top->left = nullptr;
    root = root ? merge(root, top) : top;
    ++size_;
  }
  bool empty() const { return !root; }
  std::uint_fast32_t size() const { return size_; }
  void meld(PairingHeap<T, P> &other) {
    size_ += other.size_;
    other.size_ = 0;
    if (other.root) {
      root = root ? merge(root, other.root) : other.root;
      other.root = nullptr;
    }
  }
};

/*

verify:https://beta.atcoder.jp/contests/apc001/submissions/2199437

template<typename T, bool P = false>
class PairingHeap;

PairingHeapは融合可能なヒープ(優先度付きキュー)です
空間計算量 O(N)


テンプレートパラメータ
-typename T
 operator< によって大小が定義された構造体
 要素の型になります

-bool P
 true を与えると最大ヒープになります
 デフォルトでは false で最小ヒープです


メンバ関数
-(constructor) ()
 空のヒープを構築します
 時間計算量 O(1)

-top (void)->const T &
 先頭の要素のconst参照を返します
 時間計算量 O(1)

-pop (void)->const T &
 先頭の要素を削除し、そのconst参照を返します
 時間計算量 償却 O(logN)

-push (T data)
 data を要素としてヒープに追加します
 時間計算量 O(1)

-empty ()->bool
 ヒープが空かどうかを返します
 時間計算量 O(1)

-size ()->uint32
 要素数を返します
 時間計算量 O(1)

-meld (ParingHeap<T, P> &other)
 other の持つ要素全てをヒープに追加します
 other は空になります
 時間計算量 O(1)


※N:要素数
※T の比較に掛かる時間計算量を O(1) と仮定

*/