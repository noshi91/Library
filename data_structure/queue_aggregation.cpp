/*

アルゴリズムの一部は https://twitter.com/259_Momone/status/1199559095243530240
に影響を受けたものです

*/

#include <cassert>
#include <stack>

template <class Monoid> class queue_aggregation {
public:
  using T = typename Monoid::value_type;

private:
  std::stack<T> front_stack;
  std::stack<T> back_stack;
  T fold_back;

  T fold_front() const {
    if (!front_stack.empty()) {
      return front_stack.top();
    } else {
      return Monoid::identity;
    }
  }

public:
  queue_aggregation()
      : front_stack(), back_stack(), fold_back(Monoid::identity) {}

  bool empty() const { return front_stack.empty() && back_stack.empty(); }

  T fold_all() const { return Monoid::operation(fold_front(), fold_back); }

  void push(const T x) {
    fold_back = Monoid::operation(fold_back, x);
    back_stack.push(x);
  }
  void pop() {
    assert(!empty());
    if (front_stack.empty()) {
      while (!back_stack.empty()) {
        front_stack.push(Monoid::operation(back_stack.top(), fold_front()));
        back_stack.pop();
      }
      fold_back = Monoid::identity;
    }
    front_stack.pop();
  }
};