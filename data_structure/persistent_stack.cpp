#include <cassert>
#include <memory>
#include <utility>

template <class T> class persistent_stack {
  using Self = persistent_stack<T>;

  class node_type;

  using node_ptr = std::shared_ptr<const node_type>;

  class node_type {
  public:
    T value;
    node_ptr next;

    node_type(T value, node_ptr next) : value(value), next(next) {}
  };

  node_ptr root;

  persistent_stack(node_ptr root) : root(root) {}

public:
  persistent_stack() = default;

  bool empty() const { return not root; }

  T top() const {
    assert(not empty());

    return root->value;
  }

  Self push(T x) const {
    return Self(std::make_shared<const node_type>(x, root));
  }

  Self pop() const {
    assert(not empty());

    return Self(root->next);
  }
};

/**
 * @brief Persistent Stack
 */
