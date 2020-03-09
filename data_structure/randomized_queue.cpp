#include "other/int_alias.cpp"
#include "other/random_integer.cpp"

#include <cassert>
#include <cstddef>
#include <random>
#include <vector>

template <class T> class randomized_queue {
public:
  using value_type = T;

private:
  std::vector<T> c;

  void select() {
    std::swap(c.back(), c[random_integer<usize>(0, c.size() - 1)]);
  }

public:
  randomized_queue() = default;

  bool empty() const { return c.empty(); }
  usize size() const { return c.size(); }
  T &front() {
    assert(!empty());
    select();
    return c.back();
  }

  void push(T x) { c.push_back(std::move(x)); }
  T pop() {
    assert(!empty());
    select();
    const T ret = std::move(c.back());
    c.pop_back();
    return ret;
  }
};

/**
 * @brief Randomized Queue
 */
