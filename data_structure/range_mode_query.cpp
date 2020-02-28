#include <cassert>
#include <cstddef>
#include <vector>

class range_mode_query {
  using size_t = std::size_t;

  class b_node {
  public:
    size_t value;
    size_t rank;

    b_node(const size_t value, const size_t rank) : value(value), rank(rank) {}
  };
  class s_node {
  public:
    size_t mode;
    size_t freq;

    s_node(const size_t mode, const size_t freq) : mode(mode), freq(freq) {}
  };

  std::vector<b_node> b;
  std::vector<std::vector<size_t>> q;
  std::vector<std::vector<s_node>> s;
  size_t t;

public:
  range_mode_query() = default;
  range_mode_query(const std::vector<size_t> a) : t(1) {
    const size_t n = a.size();
    b.assign(n, b_node(0, 0));
    q.assign(n, {});
    while (t * t < n)
      t += 1;
    for (size_t i = 0; i != n; i += 1) {
      const size_t e = a[i];
      assert(e < n);
      b[i] = b_node(e, q[e].size());
      q[e].push_back(i);
    }
    s.assign(n / t + 1, std::vector<s_node>(n / t + 1, s_node(0, 0)));
    for (size_t f = 0; f * t <= n; f += 1) {
      std::vector<size_t> freq(n, 0);
      s_node cur(0, 0);
      for (size_t l = f + 1; l * t <= n; l += 1) {
        for (size_t i = (l - 1) * t; i != l * t; i += 1) {
          const size_t e = a[i];
          freq[e] += 1;
          if (freq[e] > cur.freq)
            cur = s_node(e, freq[e]);
        }
        s[f][l] = cur;
      }
    }
  }

  size_t query(const size_t first, const size_t last) const {
    assert(first < last);
    assert(last <= b.size());
    size_t bf = first / t + 1;
    size_t bl = last / t;
    if (bf >= bl) {
      s_node cur(0, 0);
      for (size_t i = first; i != last; i += 1) {
        const b_node &e = b[i];
        const std::vector<size_t> &v = q[e.value];
        size_t idx;
        while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
          cur = s_node(e.value, cur.freq + 1);
      }
      return cur.mode;
    }
    s_node cur = s[bf][bl];
    for (size_t i = first; i != bf * t; i += 1) {
      const b_node &e = b[i];
      const std::vector<size_t> &v = q[e.value];
      size_t idx;
      while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)
        cur = s_node(e.value, cur.freq + 1);
    }
    for (size_t i = bl * t; i != last; i += 1) {
      const b_node &e = b[i];
      const std::vector<size_t> &v = q[e.value];
      size_t idx;
      while ((idx = e.rank - cur.freq) < v.size() && v[idx] >= first)
        cur = s_node(e.value, cur.freq + 1);
    }
    return cur.mode;
  }
};

/**
 * @brief Range Mode Query
 * @see https://scrapbox.io/data-structures/Range_Mode_Query
 */
