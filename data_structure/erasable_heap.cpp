#include <cassert>
#include <utility>

template <class Heap> class erasable_heap {
  using W = typename Heap::value_compare;
  using T = typename Heap::value_type;

public:
  using value_compare = W;
  using value_type = T;

private:
  static bool equivalent(const T &x, const T &y) {
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

  const T &top() const {
    assert(!empty());

    return base.top();
  }

  void push(T x) {
    base.push(std::move(x));
    normalize();
  }

  T pop() {
    assert(!empty());

    T ret = base.pop();
    normalize();
    return ret;
  }

  void erase(T x) {
    erased.push(std::move(x));
    normalize();
  }
};

/**
 * @brief Erasable Heap
 */
