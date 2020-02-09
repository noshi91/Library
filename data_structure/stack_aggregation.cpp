#include <cassert>
#include <stack>

template <class M> class stack_aggregation {
  using T = typename M::value_type;

  class node_type {
  public:
    T value;
    T fold;

    node_type(const T value, const T fold) : value(value), fold(fold) {}
  };

  std::stack<node_type> st;

public:
  stack_aggregation() = default;

  bool empty() const { return st.empty(); }
  T top() const {
    assert(!empty());
    return st.top().value;
  }
  T fold() const { return st.empty() ? M::identity : st.top().fold; }

  void push(const T x) { st.push(node_type(x, M::operation(fold(), x))); }
  void pop() {
    assert(!empty());
    st.pop();
  }
};