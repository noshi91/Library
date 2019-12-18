#include <cassert>

template <class W, template <class> class Heap> class eraseable_heap {
  using T = typename W::value_type;

public:
  using value_type = T;

private:
  static bool equivalent(const T x, const T y) {
    return W::compare(x, y) && W::compare(y, x);
  }

  Heap<W> base;
  Heap<W> erased;

  void normalize() {
    while (!erased.empty() && equivalent(base.top(), erased.top())) {
      base.pop();
      erased.pop();
    }
  }

public:
  eraseable_heap() = default;

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