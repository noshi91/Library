#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <memory>
#include <set>
#include <utility>

template <class T, bool Minimize = true, class Compare = std::less<T>>
class parametric_heap {
  template <bool M, class V> class comp_helper {
  public:
    static bool call(const Compare &comp, const T &l, const T &r) {
      return comp(l, r);
    }
  };

  template <class V> class comp_helper<false, V> {
  public:
    static bool call(const Compare &comp, const T &l, const T &r) {
      return comp(r, l);
    }
  };

  class line_t {
  public:
    T a;
    T b;

    line_t(T a_, T b_) : a(std::move(a_)), b(std::move(b_)) {}
  };

  class node_t;

  using link_t = std::unique_ptr<node_t>;

  class leaf_t {
    class F {
      Compare comp;

    public:
      F(const Compare &comp) : comp(comp) {}

      bool operator()(const T &l, const T &r) const {
        return comp_helper<Minimize, void>::call(comp, l, r);
      }
    };

  public:
    T a;
    std::multiset<T, F> b;

    leaf_t(T a_, T b_, const Compare &comp) : a(std::move(a_)), b(F(comp)) {
      b.insert(std::move(b_));
    }

    T eval(const T &x) const { return a * x + (*b.begin()); }
    line_t get() const { return line_t(a, *b.begin()); }
  };

  class internal_t {
  public:
    link_t left;
    link_t right;
    const leaf_t *lc;
    const leaf_t *rc;

    internal_t(link_t l, link_t r)
        : left(std::move(l)), right(std::move(r)), lc(&left->data.leaf),
          rc(&right->data.leaf) {}

    std::ptrdiff_t bias() const {
      return static_cast<std::ptrdiff_t>(left->rank) -
             static_cast<std::ptrdiff_t>(right->rank);
    }

    const T &get_mid() const {
      const node_t *ptr = right.get();
      while (ptr->is_internal()) {
        ptr = ptr->data.internal.left.get();
      }
      return ptr->data.leaf.a;
    }
  };

  class node_t {
  public:
    std::size_t rank;
    union data_t {
      leaf_t leaf;
      internal_t internal;

      data_t() {}
      ~data_t() {}
    } data;

    node_t(node_t &&x) : rank(x.rank), data() {
      if (x.is_leaf()) {
        new (&data.leaf) leaf_t(std::move(x.data.leaf));
      } else {
        new (&data.internal) internal_t(std::move(x.data.internal));
      }
    }

    node_t(T a, T b, const Compare &comp) : rank(0), data() {
      new (&data.leaf) leaf_t(std::move(a), std::move(b), comp);
    }

    node_t(link_t l, link_t r) : rank(1), data() {
      new (&data.internal) internal_t(std::move(l), std::move(r));
    }

    bool is_leaf() const { return rank == 0; }
    bool is_internal() const { return rank != 0; }

    ~node_t() {
      if (is_leaf()) {
        data.leaf.~leaf_t();
      } else {
        data.internal.~internal_t();
      }
    }
  };

  Compare comp;
  link_t root;

  bool comp_f(const T &l, const T &r) const {
    return comp_helper<Minimize, void>::call(comp, l, r);
  }

  bool is_necessary(const line_t &x, const line_t &y, const line_t &z) const {
    return comp(y.a * z.b + z.a * x.b + x.a * y.b,
                z.a * y.b + x.a * z.b + y.a * x.b);
  }

  bool left_discard(const line_t &x, const line_t &y, const line_t &z,
                    const line_t &w, const T &m) const {
    return comp_f(
        x.a * y.b * z.a + x.b * y.a * w.a + x.a * z.b * w.a + y.a * z.a * w.b +
            m * (x.b * z.a + x.a * w.b + y.a * z.b + y.b * w.a),
        x.b * y.a * z.a + x.a * y.b * w.a + x.a * z.a * w.b + y.a * z.b * w.a +
            m * (x.a * z.b + x.b * w.a + y.b * z.a + y.a * w.b));
  }

  void update_node(node_t &node) const {
    internal_t &internal = node.data.internal;
    node.rank = std::max(internal.left->rank, internal.right->rank) + 1;
    const T &m = internal.get_mid();
    const node_t *l = internal.left.get();
    const node_t *r = internal.right.get();
    while (true) {
      if (l->is_leaf()) {
        if (r->is_leaf()) {
          break;
        } else {
          const internal_t &r_in = r->data.internal;
          if (is_necessary(l->data.leaf.get(), r_in.lc->get(),
                           r_in.rc->get())) {
            r = r_in.left.get();
          } else {
            r = r_in.right.get();
          }
        }
      } else {
        const internal_t &l_in = l->data.internal;
        const line_t &ll = l_in.lc->get();
        const line_t &lr = l_in.rc->get();
        if (r->is_leaf()) {
          if (is_necessary(ll, lr, r->data.leaf.get())) {
            l = l_in.right.get();
          } else {
            l = l_in.left.get();
          }
        } else {
          const internal_t &r_in = r->data.internal;
          const line_t &rl = r_in.lc->get();
          const line_t &rr = r_in.rc->get();
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

  void rotate_left(link_t &ptr) const {
    link_t right = std::move(ptr->data.internal.right);
    ptr->data.internal.right = std::move(right->data.internal.left);
    update_node(*ptr);
    right->data.internal.left = std::move(ptr);
    ptr = std::move(right);
  }

  void rotate_right(link_t &ptr) const {
    link_t left = std::move(ptr->data.internal.left);
    ptr->data.internal.left = std::move(left->data.internal.right);
    update_node(*ptr);
    left->data.internal.right = std::move(ptr);
    ptr = std::move(left);
  }

  void balance(link_t &ptr) const {
    internal_t &internal = ptr->data.internal;
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
      root = std::make_unique<node_t>(node_t(a, b, comp));
      return;
    }
    const auto insert_rec = [&](const auto &self, link_t &ptr) -> void {
      if (ptr->is_leaf()) {
        leaf_t &leaf = ptr->data.leaf;
        if (comp_f(leaf.a, a)) {
          ptr = std::make_unique<node_t>(node_t(
              std::make_unique<node_t>(node_t(a, b, comp)), std::move(ptr)));
        } else if (comp_f(a, leaf.a)) {
          ptr = std::make_unique<node_t>(node_t(
              std::move(ptr), std::make_unique<node_t>(node_t(a, b, comp))));
        } else {
          leaf.b.insert(b);
        }
        return;
      }
      internal_t &internal = ptr->data.internal;
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
    const auto erase_rec = [&](const auto &self, link_t &ptr) -> void {
      if (ptr->is_leaf()) {
        leaf_t &leaf = ptr->data.leaf;
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
      internal_t &internal = ptr->data.internal;
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

  std::pair<T, T> top(const T &x) const {
    if (empty()) {
      std::abort();
    }

    const node_t *ptr = root.get();
    while (ptr->is_internal()) {
      const internal_t &internal = ptr->data.internal;
      if (comp_f(internal.lc->eval(x), internal.rc->eval(x))) {
        ptr = internal.left.get();
      } else {
        ptr = internal.right.get();
      }
    }
    const leaf_t &leaf = ptr->data.leaf;
    return std::pair<T, T>(leaf.a, *leaf.b.begin());
  }
};

/**
 * @brief Parametric Heap
 * @docs docs/parametric_heap.md
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
