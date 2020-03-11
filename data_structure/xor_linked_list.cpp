#include <cassert>
#include <cstdint>
#include <utility>

template <class T> class xor_linked_list {
public:
  using value_type = T;

private:
  class node_type {
  public:
    T value;
    std::uintptr_t link;

    node_type(T value, const std::uintptr_t link)
        : value(std::move(value)), link(link) {}
  };

  static std::uintptr_t ptoi(node_type *const ptr) {
    return reinterpret_cast<std::uintptr_t>(ptr);
  }

  static node_type *itop(const std::uintptr_t id) {
    return reinterpret_cast<node_type *>(id);
  }

  node_type *front_;
  node_type *back_;

  void release() {
    front_ = nullptr;
    back_ = nullptr;
  }

public:
  xor_linked_list() : front_(nullptr), back_(nullptr) {}

  xor_linked_list(const xor_linked_list &) = delete;

  xor_linked_list(xor_linked_list &&r) noexcept
      : front_(r.front_), back_(r.back_) {
    r.release();
  }

  ~xor_linked_list() { clear(); }

  xor_linked_list &operator=(const xor_linked_list &) = delete;

  xor_linked_list &operator=(xor_linked_list &&r) noexcept {
    front_ = r.front_;
    back_ = r.back_;
    r.release();
    return *this;
  }

  bool empty() const { return front_ == nullptr; }

  T &front() {
    assert(!empty());

    return front_->value;
  }

  T &back() {
    assert(!empty());

    return back_->value;
  }

  void push_back(T x) {
    if (empty()) {
      node_type *const next = new node_type(std::move(x), 0);
      front_ = next;
      back_ = next;
    } else {
      node_type *const next = new node_type(std::move(x), ptoi(back_));
      back_->link ^= ptoi(next);
      back_ = next;
    }
  }

  void pop_back() {
    assert(!empty());

    if (front_ == back_) {
      delete front_;
      front_ = nullptr;
      back_ = nullptr;
    } else {
      node_type *const next = itop(back_->link);
      next->link ^= ptoi(back_);
      delete back_;
      back_ = next;
    }
  }

  void push_front(T x) {
    reverse();
    push_back(std::move(x));
    reverse();
  }

  void pop_front() {
    assert(!empty());

    reverse();
    pop_back();
    reverse();
  }

  void clear() {
    if (empty())
      return;
    node_type *itr = front_;
    std::uintptr_t prev = 0;
    while (itr != back_) {
      node_type *const next = itop(itr->link ^ prev);
      prev = ptoi(itr);
      delete itr;
      itr = next;
    }
    delete itr;
    release();
  }

  void reverse() { std::swap(front_, back_); }

  static xor_linked_list catenate(xor_linked_list left, xor_linked_list right) {
    if (left.empty())
      return right;
    if (right.empty())
      return left;
    left.back_->link ^= ptoi(right.front_);
    right.front_->link ^= ptoi(left.back_);
    xor_linked_list ret;
    ret.front_ = left.front_;
    ret.back_ = right.back_;
    left.release();
    right.release();
    return ret;
  }
};

/**
 * @brief Xor Linked List
 * @see https://en.wikipedia.org/wiki/XOR_linked_list
 */
