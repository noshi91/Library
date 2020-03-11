#include <cassert>
#include <memory>
#include <utility>

template <class W> class pairing_heap {
  using Self = pairing_heap;
  using T = typename W::value_type;

public:
  using value_compare = W;
  using value_type = T;

private:
  class node_type;
  using node_ptr = std::unique_ptr<node_type>;
  class node_type {
  public:
    T value;
    node_ptr head;
    node_ptr next;

    node_type(T value) : value(std::move(value)), head(), next() {}
  };

  static node_ptr merge(node_ptr x, node_ptr y) {
    if (!x)
      return y;
    if (!y)
      return x;
    if (!W::compare(x->value, y->value))
      std::swap(x, y);
    y->next = std::move(x->head);
    x->head = std::move(y);
    return x;
  }

  static node_ptr merge_list(node_ptr list) {
    if (!list || !list->next)
      return list;
    node_ptr next = std::move(list->next);
    node_ptr rem = std::move(next->next);
    return merge(merge(std::move(list), std::move(next)),
                 merge_list(std::move(rem)));
  }

  node_ptr root;

  pairing_heap(node_ptr root) : root(std::move(root)) {}

public:
  pairing_heap() = default;

  bool empty() const { return !root; }

  const T &top() const {
    assert(!empty());

    return root->value;
  }

  void push(T x) {
    root = merge(std::move(root), std::make_unique<node_type>(std::move(x)));
  }

  T pop() {
    assert(!empty());

    T ret = std::move(root->value);
    root = merge_list(std::move(root->head));
    return ret;
  }

  static Self meld(Self x, Self y) {
    return Self(merge(std::move(x.root), std::move(y.root)));
  }
};

/**
 * @brief Pairing Heap
 */
