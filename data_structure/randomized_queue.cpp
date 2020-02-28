#include "other/random_integer.cpp"

#include <cassert>
#include <cstddef>
#include <random>
#include <vector>

template <class T> class randomized_queue {
  using size_t = std::size_t;

public:
  using value_type = T;

private:
  std::vector<T> c;

  void select() {
    std::swap(c.back(), c[random_integer<size_t>(0, c.size() - 1)]);
  }

public:
  randomized_queue() = default;

  bool empty() const { return c.empty(); }

  T front() {
    assert(!empty());
    select();
    return c.back();
  }

  void push(const T x) { c.push_back(x); }
  T pop() {
    assert(!empty());
    select();
    const T ret = c.back();
    c.pop_back();
    return ret;
  }
};

/**
 * @brief Randomized Queue
 */
