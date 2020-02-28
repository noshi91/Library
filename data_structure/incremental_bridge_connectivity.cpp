#include "data_structure/union_find.cpp"

#include <cassert>
#include <cstddef>
#include <unordered_set>
#include <utility>
#include <vector>

class incremental_bridge_connectivity {
  using size_t = std::size_t;

  union_find cc;
  union_find bcc;
  std::vector<size_t> bbf;

  size_t size() const { return bbf.size(); }
  size_t nil() const { return size(); }

  size_t parent(const size_t v) {
    if (bbf[v] == nil())
      return nil();
    else
      return bcc.find(bbf[v]);
  }
  size_t lca(size_t u, size_t v) {
    std::unordered_set<size_t> reached;
    while (true) {
      if (u != nil()) {
        if (!reached.insert(u).second)
          return u;
        u = parent(u);
      }
      std::swap(u, v);
    }
  }
  void condense_path(size_t u, const size_t v) {
    while (!bcc.same(u, v)) {
      const size_t next = parent(u);
      bbf[u] = bbf[v];
      bcc.unite(u, v);
      u = next;
    }
  }
  void link(const size_t x, const size_t y) {
    size_t v = x, prev = y;
    while (v != nil()) {
      const size_t next = bbf[v];
      bbf[v] = prev;
      prev = v;
      v = next;
    }
  }

public:
  incremental_bridge_connectivity() = default;
  explicit incremental_bridge_connectivity(const size_t n)
      : cc(n), bcc(n), bbf(n, n) {}

  bool bridge_connected(const size_t u, const size_t v) {
    assert(u < size());
    assert(v < size());
    return bcc.same(u, v);
  }

  void insert_edge(size_t u, size_t v) {
    assert(u < size());
    assert(v < size());
    u = bcc.find(u);
    v = bcc.find(v);
    if (cc.same(u, v)) {
      const size_t w = lca(u, v);
      condense_path(u, w);
      condense_path(v, w);
    } else {
      if (cc.size(u) > cc.size(v))
        std::swap(u, v);
      link(u, v);
      cc.unite(u, v);
    }
  }
};

/**
 * @brief Incremental Bridge-Connectivity
 * @see https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity
 */
