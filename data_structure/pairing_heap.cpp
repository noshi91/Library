#include <cassert>
#include <memory>
#include <utility>

template <class W> class pairing_heap {
public:
  using T = typename W::value_type;
  using value_type = T;

private:
  class node_type;
  using node_ptr = std::unique_ptr<node_type>;
  class node_type {
  public:
    T value;
    node_ptr head;
    node_ptr next;

    node_type(const T value) : value(value) {}
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

  T top() const {
    assert(!empty());
    return root->value;
  }

  void push(const T x) {
    root = merge(std::move(root), std::make_unique<node_type>(x));
  }
  void pop() {
    assert(!empty());
    root = merge_list(std::move(root->head));
  }

  static pairing_heap meld(pairing_heap x, pairing_heap y) {
    return pairing_heap(merge(std::move(x.root), std::move(y.root)));
  }
};