#include <cassert>
#include <iterator>
#include <list>

template <class T> class partially_retroactive_queue {
  class node_type;

public:
  using time_type = typename std::list<node_type>::const_iterator;

private:
  class node_type {
    friend partially_retroactive_queue;

    T value;
    bool in_queue;
    node_type(const T value) : value(value), in_queue() {}
  };

  std::list<node_type> list;
  typename std::list<node_type>::iterator front_itr;

public:
  partially_retroactive_queue() : list(), front_itr(list.end()) {}

  time_type now() const { return list.cend(); }

  bool empty() const { return front_itr == list.end(); }

  T front() const {
    assert(!empty());
    return front_itr->value;
  }

  time_type insert_push(const time_type time, const T x) {
    const auto itr = list.insert(time, node_type(x));
    if (itr == list.begin() || !std::prev(itr)->in_queue) {
      itr->in_queue = false;
      --front_itr;
      front_itr->in_queue = true;
    } else {
      itr->in_queue = true;
    }
    return time_type(itr);
  }
  void erase_push(const time_type time) {
    assert(time != now());
    if (time == list.cbegin() || !std::prev(time)->in_queue) {
      front_itr->in_queue = false;
      ++front_itr;
    }
    list.erase(time);
  }
  void insert_pop() {
    assert(!empty());
    front_itr->in_queue = false;
    ++front_itr;
  }
  void erase_pop() {
    assert(front_itr != list.begin());
    --front_itr;
    front_itr->in_queue = true;
  }
};