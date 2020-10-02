#include "other/int_alias.cpp"

#include <vector>

template <class Select, class Update>
void larsch(const std::size_t n, Select select, Update update) {
  using usize = std::size_t;

  class header {
  public:
    usize r;
    usize c;
  };

  class node {
  public:
    std::vector<usize> cols;
    usize prev;

    std::vector<header> tent;
    usize pcnt;
    usize curc;

    node(const usize n) : cols(), prev(0), tent(), pcnt(0), curc(0) {
      cols.reserve(n);
      tent.reserve(n / 2);
    }
  };

  std::vector<node> data;

  {
    usize m = n;
    while (m != 0) {
      data.emplace_back(m);
      m /= 2;
    }
  }

  const auto act = [&](const auto &act, const usize layer,
                       const usize row) -> usize {
    node &t = data[layer];

    if ((row >> layer) % 2 == 0) {
      usize res = t.prev;
      usize idx = t.curc;
      while (idx != t.cols.size()) {
        if (select(row, t.cols[res], t.cols[idx])) {
          res = idx;
        }
        idx += 1;
      }
      t.prev = res;
      return t.cols[res];
    }

    const usize a = [&]() {
      const usize step = static_cast<usize>(1) << layer;
      if (row + step > n) {
        return t.cols.back();
      }
      while (t.curc != t.cols.size()) {
        const usize c = t.cols[t.curc];
        while (t.tent.size() != t.pcnt &&
               select(t.tent.back().r, t.tent.back().c, c)) {
          t.tent.pop_back();
        }
        if (t.tent.size() == t.pcnt) {
          t.tent.push_back({row + step, c});
        } else if (t.tent.back().r + step * 2 <= n) {
          t.tent.push_back({t.tent.back().r + step * 2, c});
        }
        t.curc += 1;
      }
      if (t.pcnt != t.tent.size()) {
        data[layer + 1].cols.push_back(t.tent[t.pcnt].c);
        t.pcnt += 1;
      }
      return act(act, layer + 1, row + step);
    }();

    usize res = t.prev;
    usize idx = t.prev;
    while (t.cols[idx] != a) {
      idx += 1;
      if (select(row, t.cols[res], t.cols[idx])) {
        res = idx;
      }
    }
    t.prev = idx;
    return t.cols[res];
  };

  for (usize i = 0; i != n;) {
    data[0].cols.push_back(i);
    i += 1;
    update(i, act(act, 0, i));
  }
}

/**
 * @brief LARSCH Algorithm
 * @docs docs/larsch.md
 */
