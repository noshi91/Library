#include "data_structure/stream.cpp"
#include "other/int_alias.cpp"

#include <cassert>

template <class T> class bankers_queue {
  using Self = bankers_queue<T>;
  using stream_type = stream<T>;

  stream_type front_;
  usize f_size;
  stream_type back_;
  usize b_size;

  bankers_queue(stream_type front_, usize f_size, stream_type back_,
                usize b_size)
      : front_(front_), f_size(f_size), back_(back_), b_size(b_size) {}

  Self normalize() const {
    if (f_size >= b_size)
      return *this;
    else
      return Self(front_ + back_.reverse(), f_size + b_size, stream_type(), 0);
  }

public:
  bankers_queue() : front_(), f_size(0), back_(), b_size(0) {}

  bool empty() const { return f_size == 0; }

  T front() const {
    assert(not empty());

    return front_.top();
  }

  Self push(T x) const {
    return Self(front_, f_size, back_.push(x), b_size + 1).normalize();
  }

  Self pop() const {
    assert(not empty());

    return Self(front_.pop(), f_size - 1, back_, b_size).normalize();
  }
};

/**
 * @brief Banker's Queue
 * @see https://www.cs.cmu.edu/~rwh/theses/okasaki.pdf
 */
