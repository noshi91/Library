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
    static std::default_random_engine drg(91);

    const size_t index =
        std::uniform_int_distribution<size_t>(0, c.size() - 1)(drg);
    std::swap(c.back(), c[index]);
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