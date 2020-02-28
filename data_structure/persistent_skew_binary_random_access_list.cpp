#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

template <class T, class Size = std::size_t>
class persistent_skew_binary_random_access_list {
  using Self = persistent_skew_binary_random_access_list;

  class tree_type;
  using tree_ptr = std::shared_ptr<const tree_type>;
  class tree_type {
  public:
    T value;
    tree_ptr left;
    tree_ptr right;

    tree_type(const T value, const tree_ptr left, const tree_ptr right)
        : value(value), left(left), right(right) {}

    T lookup(const Size size, const Size index) const {
      if (index == 0) {
        return value;
      } else {
        assert(size != 1);
        const Size rem_index = index - 1;
        const Size ch_size = size / 2;
        if (rem_index < ch_size) {
          return left->lookup(ch_size, rem_index);
        } else {
          return right->lookup(ch_size, rem_index - ch_size);
        }
      }
    }
    tree_ptr update(const Size size, const Size index, const T x) const {
      if (index == 0) {
        return make_tree(x, left, right);
      } else {
        assert(size != 1);
        const Size rem_index = index - 1;
        const Size ch_size = size / 2;
        if (rem_index < ch_size) {
          return make_tree(value, left->update(ch_size, rem_index, x), right);
        } else {
          return make_tree(value, left,
                           right->update(ch_size, rem_index - ch_size, x));
        }
      }
    }
  };

  class digit_type;
  using digit_ptr = std::shared_ptr<const digit_type>;
  class digit_type {
  public:
    Size size;
    tree_ptr tree;
    digit_ptr next;

    digit_type(const Size size, const tree_ptr tree, const digit_ptr next)
        : size(size), tree(tree), next(next) {}

    T lookup(const Size index) const {
      if (index < size) {
        return tree->lookup(size, index);
      } else {
        return next->lookup(index - size);
      }
    }
    digit_ptr update(const Size index, const T x) const {
      if (index < size) {
        return make_digit(size, tree->update(size, index, x), next);
      } else {
        return make_digit(size, tree, next->update(index - size, x));
      }
    }
  };

  template <class... Args> static tree_ptr make_tree(Args &&... args) {
    return std::make_shared<tree_type>(std::forward<Args>(args)...);
  }
  template <class... Args> static digit_ptr make_digit(Args &&... args) {
    return std::make_shared<digit_type>(std::forward<Args>(args)...);
  }

  digit_ptr root;

  persistent_skew_binary_random_access_list(const digit_ptr root)
      : root(root) {}

public:
  persistent_skew_binary_random_access_list() = default;

  bool empty() const { return !root; }

  T operator[](const Size index) const { return root->lookup(index); }
  T front() const { return root->tree->value; }

  Self update(const Size index, const T x) const {
    return Self(root->update(index, x));
  }
  Self push_front(const T x) const {
    if (root && root->next && root->size == root->next->size) {
      return Self(make_digit(1 + root->size + root->next->size,
                             make_tree(x, root->tree, root->next->tree),
                             root->next->next));
    } else {
      return Self(make_digit(1, make_tree(x, nullptr, nullptr), root));
    }
  }
  Self pop_front() const {
    if (root->size == 1) {
      return Self(root->next);
    } else {
      const Size ch_size = root->size / 2;
      return Self(
          make_digit(ch_size, root->tree->left,
                     make_digit(ch_size, root->tree->right, root->next)));
    }
  }
};

/**
 * @brief Persistent Skew Binary Random Access List
 * @see https://scrapbox.io/data-structures/Skew_Binary_List
 */
