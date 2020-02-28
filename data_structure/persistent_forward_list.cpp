#include <cassert>
#include <memory>
#include <utility>

template <class T> class persistent_forward_list {
  using Self = persistent_forward_list;

  class node_type;
  using node_ptr = std::shared_ptr<const node_type>;
  class node_type {
  public:
    T value;
    node_ptr next;

    node_type(const T value, const node_ptr next) : value(value), next(next) {}
  };

  template <class... Args> static node_ptr make_node(Args &&... args) {
    return std::make_shared<const node_type>(std::forward<Args>(args)...);
  }

  node_ptr root;

  persistent_forward_list(const node_ptr root) : root(root) {}

public:
  persistent_forward_list() = default;

  bool empty() const { return !root; }

  T front() const {
    assert(!empty());
    return root->value;
  }

  Self push_front(const T x) const { return Self(make_node(x, root)); }
  Self pop_front() const {
    assert(!empty());
    return Self(root->next);
  }
};

/**
 * @brief Persistent Forward List
 */
