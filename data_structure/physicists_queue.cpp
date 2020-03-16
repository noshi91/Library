#include "data_structure/persistent_stack.cpp"
#include "other/int_alias.cpp"
#include "other/suspension.cpp"

#include <cassert>
#include <utility>

template <class T> class physicists_queue {
  using Self = physicists_queue<T>;
  using stack_type = persistent_stack<T>;
  using susp_stack = suspension<stack_type>;

  stack_type working;
  susp_stack front_;
  usize f_size;
  stack_type back_;
  usize b_size;

  physicists_queue(stack_type working, susp_stack front_, usize f_size,
                   stack_type back_, usize b_size)
      : working(working), front_(front_), f_size(f_size), back_(back_),
        b_size(b_size) {}

  Self check_r() const {
    if (f_size >= b_size)
      return *this;
    stack_type temp = front_.force();
    auto f = [l = temp, r = back_]() mutable {
      r = r.reverse();
      l = l.reverse();
      while (not l.empty()) {
        r = r.push(l.top());
        l = l.pop();
      }
      return r;
    };
    return Self(temp, susp_stack(f), f_size + b_size, stack_type(), 0);
  }

  Self check_w() const {
    if (working.empty())
      return Self(front_.force(), front_, f_size, back_, b_size);
    else
      return *this;
  }

  Self check() const { return check_r().check_w(); }

public:
  physicists_queue()
      : working(), front_(std::in_place, stack_type()), f_size(0), back_(),
        b_size(0) {}

  bool empty() const { return f_size == 0; }

  T front() const {
    assert(not empty());

    return working.top();
  }

  Self push(T x) const {
    return Self(working, front_, f_size, back_.push(x), b_size + 1).check();
  }

  Self pop() const {
    assert(not empty());

    return Self(working.pop(),
                susp_stack([f = front_]() { return f.force().pop(); }),
                f_size - 1, back_, b_size)
        .check();
  }
};

/**
 * @brief Physicist's Queue
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */
