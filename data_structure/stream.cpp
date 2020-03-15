#include "other/suspension.cpp"

#include <cassert>
#include <optional>
#include <utility>

template <class T>
class stream : private suspension<std::optional<std::pair<T, stream<T>>>> {
  using Self = stream<T>;

public:
  using value_type = T;

  using cell_type = std::optional<std::pair<T, Self>>;

private:
  using base_type = suspension<cell_type>;

  stream(T x, Self s)
      : base_type(std::in_place, cell_type(std::in_place, x, s)) {}

public:
  stream() : base_type(std::in_place, cell_type(std::nullopt)) {}

  stream(std::function<cell_type()> f) : base_type(f) {}

  using base_type::force;

  bool empty() const { return not force().has_value(); }

  T top() const {
    assert(not empty());

    return (*force()).first;
  }

  stream push(T x) const { return stream(x, *this); }

  stream pop() const {
    assert(not empty());

    return (*force()).second;
  }

  stream reverse() const {
    if (empty())
      return Self();
    else
      return pop().reverse().push(top());
  }

  friend Self operator+(Self l, Self r) {
    return Self([l, r] {
      if (l.empty())
        return r.force();
      else
        return cell_type(std::in_place, l.top(), l.pop() + r);
    });
  }
};

/**
 * @brief Stream
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */
