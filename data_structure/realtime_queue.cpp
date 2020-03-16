#include "data_structure/persistent_stack.cpp"
#include "data_structure/stream.cpp"

#include <cassert>
#include <utility>

template <class T> class realtime_queue {
  using Self = realtime_queue<T>;
  using stream_type = stream<T>;
  using cell_type = typename stream_type::cell_type;
  using stack_type = persistent_stack<T>;

public:
  using value_type = T;

private:
  static stream_type rotate(stream_type f, stack_type b, stream_type t) {
    return stream_type([f, b, t]() {
      if (f.empty())
        return cell_type(std::in_place, b.top(), t);
      else
        return cell_type(std::in_place, f.top(),
                         rotate(f.pop(), b.pop(), t.push(b.top())));
    });
  }

  static Self make_queue(stream_type f, stack_type b, stream_type s) {
    if (not s.empty())
      return Self(f, b, s.pop());
    stream_type temp = rotate(f, b, stream_type());
    return Self(temp, stack_type(), temp);
  }

  stream_type front_;
  stack_type back_;
  stream_type schedule;

  realtime_queue(stream_type f, stack_type b, stream_type s)
      : front_(f), back_(b), schedule(s) {}

public:
  realtime_queue() = default;

  bool empty() const { return front_.empty(); }

  T front() const {
    assert(not empty());

    return front_.top();
  }

  Self push(T x) const { return make_queue(front_, back_.push(x), schedule); }

  Self pop() const {
    assert(not empty());

    return make_queue(front_.pop(), back_, schedule);
  }
};

/**
 * @brief Realtime Queue
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */
