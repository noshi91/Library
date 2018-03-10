#include <cassert>
#include <cstdint>
#include <utility>

template <class T, bool P = false> class PairingHeap {
  static constexpr std::uint_fast64_t ALLOCSIZE = (std::uint_fast64_t)1 << 10;
  struct node_t {
    T data;
    node_t *left, *right;
  };
  node_t *root;
  static node_t *merge(node_t *x, node_t *y) {
    if (P ^ (x->data < y->data))
      std::swap(x, y);
    x->right = y->left;
    y->left = x;
    return y;
  }

public:
  PairingHeap() : root(nullptr) {}
  T min() const {
    assert(root);
    return root->data;
  }
  T pop() {
    assert(root);
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
  }
  bool empty() { return !root; }
  PairingHeap &operator+=(PairingHeap &other) {
    if (other.root) {
      root = root ? merge(root, other.root) : other.root;
      other.root = nullptr;
    }
    return *this;
  }
};