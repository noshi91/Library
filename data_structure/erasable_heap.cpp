#include <cassert>

template <class Heap> class erasable_heap {
  using W = typename Heap::value_compare;
  using T = typename W::value_type;

public:
  using value_compare = W;

private:
  static bool equivalent(const T x, const T y) {
    return W::compare(x, y) && W::compare(y, x);
  }

  Heap base;
  Heap erased;

  void normalize() {
    while (!base.empty() && !erased.empty() &&
           equivalent(base.top(), erased.top())) {
      base.pop();
      erased.pop();
    }
  }

public:
  erasable_heap() = default;

  bool empty() const { return base.empty(); }

  T top() const {
    assert(!empty());
    return base.top();
  }

  void push(const T x) {
    base.push(x);
    normalize();
  }
  void pop() {
    assert(!empty());
    base.pop();
    normalize();
  }
  void erase(const T x) {
    erased.push(x);
    normalize();
  }
};

/**
 * @brief Erasable Heap
 */
