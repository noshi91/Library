#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <set>
#include <utility>

class parametric_heap {
  using i64 = std::int64_t;

  static constexpr i64 floor_div(const i64 n, const i64 d) {
    return n / d + ((n ^ d) < 0 && n % d);
  }

  class line {
  public:
    i64 a;
    i64 b;

    line(const i64 a_, const i64 b_) : a(a_), b(b_) {}
  };

  class node_type;

  using link_type = std::unique_ptr<node_type>;

  class leaf_type {
  public:
    i64 a;
    std::multiset<i64> b;

    leaf_type(const i64 a_, const i64 b_) : a(a_), b({b_}) {}

    i64 eval(const i64 x) const { return a * x + (*b.begin()); }
    line get() const { return line(a, *b.begin()); }
  };

  class internal_type {
  public:
    link_type left;
    link_type right;
    i64 x;
    i64 y;

    internal_type(link_type l, link_type r)
        : left(std::move(l)), right(std::move(r)), lc(&left->data.leaf),
          rc(&right->data.leaf) {}

    std::ptrdiff_t bias() const {
      return static_cast<std::ptrdiff_t>(left->rank) -
             static_cast<std::ptrdiff_t>(right->rank);
    }
  };

  class node_type {
  public:
    std::size_t rank;
    i64 la;
    union data_t {
      leaf_type leaf;
      internal_type internal;

      data_t() {}
      ~data_t() {}
    } data;

    node_type(node_type &&x) : rank(x.rank), la(x.la), data() {
      if (x.is_leaf()) {
        new (&data.leaf) leaf_type(std::move(x.data.leaf));
      } else {
        new (&data.internal) internal_type(std::move(x.data.internal));
      }
    }

    node_type(const i64 a, const i64 b) : rank(0), data() {
      new (&data.leaf) leaf_type(a, b);
    }

    node_type(link_type l, link_type r) : rank(1), data() {
      new (&data.internal) internal_type(std::move(l), std::move(r));
    }

    bool is_leaf() const { return rank == 0; }
    bool is_internal() const { return rank != 0; }

    ~node_type() {
      if (is_leaf()) {
        data.leaf.~leaf_type();
      } else {
        data.internal.~internal_type();
      }
    }
  };

  link_type root;

  void update_node(node_type &node) const {
    internal_type &internal = node.data.internal;
    node.rank = std::max(internal.left->rank, internal.right->rank) + 1;
    cont i64 m = internal.right.la;
    const node_type *l = internal.left.get();
    const node_type *r = internal.right.get();
    while (true) {
      if (l->is_leaf()) {
        if (r->is_leaf()) {
          break;
        } else {
          const internal_type &r_in = r->data.internal;
          if (l->data.leaf.eval(r_in.x) > r_in.y) {
            r = r_in.left.get();
          } else {
            r = r_in.right.get();
          }
        }
      } else {
        const internal_type &l_in = l->data.internal;
        if (r->is_leaf()) {
          if(r->data.leaf.eval(l_in.x)<l_in.y){
            
          }
          if (is_necessary(ll, lr, r->data.leaf.get())) {
            l = l_in.right.get();
          } else {
            l = l_in.left.get();
          }
        } else {
          const internal_type &r_in = r->data.internal;
          const line &rl = r_in.lc->get();
          const line &rr = r_in.rc->get();
          if (!is_necessary(ll, lr, rl)) {
            l = l_in.left.get();
          } else if (!is_necessary(lr, rl, rr)) {
            r = r_in.right.get();
          } else if (left_discard(ll, lr, rl, rr, m)) {
            l = l_in.right.get();
          } else {
            r = r_in.left.get();
          }
        }
      }
    }
    internal.lc = &l->data.leaf;
    internal.rc = &r->data.leaf;
  }

  void rotate_left(link_type &ptr) const {
    link_type right = std::move(ptr->data.internal.right);
    ptr->data.internal.right = std::move(right->data.internal.left);
    update_node(*ptr);
    right->data.internal.left = std::move(ptr);
    ptr = std::move(right);
  }

  void rotate_right(link_type &ptr) const {
    link_type left = std::move(ptr->data.internal.left);
    ptr->data.internal.left = std::move(left->data.internal.right);
    update_node(*ptr);
    left->data.internal.right = std::move(ptr);
    ptr = std::move(left);
  }

  void balance(link_type &ptr) const {
    internal_type &internal = ptr->data.internal;
    const std::size_t bias = internal.bias();
    if (bias == 2) {
      if (internal.left->data.internal.bias() == -2) {
        rotate_left(internal.left);
      }
      rotate_right(ptr);
    } else if (bias == -2) {
      if (internal.right->data.internal.bias() == 2) {
        rotate_right(internal.right);
      }
      rotate_left(ptr);
    }
    update_node(*ptr);
  }

public:
  explicit parametric_heap(const Compare comp_ = Compare())
      : comp(comp_), root() {}

  bool empty() const { return !static_cast<bool>(root); }

  void insert(const T &a, const T &b) {
    if (empty()) {
      root = std::make_unique<node_type>(node_type(a, b, comp));
      return;
    }
    const auto insert_rec = [&](const auto &self, link_type &ptr) -> void {
      if (ptr->is_leaf()) {
        leaf_type &leaf = ptr->data.leaf;
        if (comp_f(leaf.a, a)) {
          ptr = std::make_unique<node_type>(
              node_type(std::make_unique<node_type>(node_type(a, b, comp)),
                        std::move(ptr)));
        } else if (comp_f(a, leaf.a)) {
          ptr = std::make_unique<node_type>(
              node_type(std::move(ptr),
                        std::make_unique<node_type>(node_type(a, b, comp))));
        } else {
          leaf.b.insert(b);
        }
        return;
      }
      internal_type &internal = ptr->data.internal;
      if (comp_f(internal.get_mid(), a)) {
        self(self, internal.left);
      } else {
        self(self, internal.right);
      }
      balance(ptr);
    };
    insert_rec(insert_rec, root);
  }

  bool erase(const T &a, const T &b) {
    if (empty()) {
      return false;
    }
    bool res = false;
    const auto erase_rec = [&](const auto &self, link_type &ptr) -> void {
      if (ptr->is_leaf()) {
        leaf_type &leaf = ptr->data.leaf;
        if (!comp_f(leaf.a, a) && !comp_f(a, leaf.a)) {
          const auto itr = leaf.b.find(b);
          if (itr != leaf.b.end()) {
            res = true;
            leaf.b.erase(itr);
            if (leaf.b.empty()) {
              ptr.reset();
            }
          }
        }
        return;
      }
      internal_type &internal = ptr->data.internal;
      if (comp_f(internal.get_mid(), a)) {
        self(self, internal.left);
        if (!internal.left) {
          ptr = std::move(internal.right);
          return;
        }
      } else {
        self(self, internal.right);
        if (!internal.right) {
          ptr = std::move(internal.left);
          return;
        }
      }
      balance(ptr);
    };
    erase_rec(erase_rec, root);
    return res;
  }

  i64 min(const i64 x) const {
    assert(!empty());

    const node_type *ptr = root.get();
    while (ptr->is_internal()) {
      const internal_type &internal = ptr->data.internal;
      if (x <= internal.x) {
        ptr = internal.left.get();
      } else {
        ptr = internal.right.get();
      }
    }

    return ptr->data.leaf.eval(x);
  }
};

/**
 * @brief Parametric Heap i64
 * @docs docs/parametric_heap_i64.md
 */

/*

Reference

[1] Overmars, M. H., & Van Leeuwen, J. (1981).
    Maintenance of configurations in the plane.
    Journal of computer and System Sciences, 23(2), 166-204.

[2] Kaplan, H., Tarjan, R. E., & Tsioutsiouliklis, K. (2001, January).
    Faster kinetic heaps and their use in broadcast scheduling.
    In SODA (Vol. 1, pp. 836-844).

*/
