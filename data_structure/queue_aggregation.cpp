#include "data_structure/stack_aggregation.cpp"
#include "other/opposite_monoid.cpp"

template <class M> class queue_aggregation {
  using T = typename M::value_type;

  stack_aggregation<opposite_monoid<M>> front_st;
  stack_aggregation<M> back_st;

public:
  queue_aggregation() = default;

  bool empty() const { return front_st.empty(); }
  T fold() const { return M::operation(front_st.fold(), back_st.fold()); }

  void push(const T x) {
    if (empty())
      front_st.push(x);
    else
      back_st.push(x);
  }
  void pop() {
    assert(!empty());
    front_st.pop();
    if (front_st.empty()) {
      while (!back_st.empty()) {
        front_st.push(back_st.top());
        back_st.pop();
      }
    }
  }
};