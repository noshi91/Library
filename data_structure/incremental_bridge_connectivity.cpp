#include "data_structure/union_find.cpp"
#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <unordered_set>
#include <utility>
#include <vector>

class incremental_bridge_connectivity {
  union_find cc;
  union_find bcc;
  std::vector<usize> bbf;

  usize size() const { return bbf.size(); }

  usize nil() const { return size(); }

  usize parent(const usize v) {
    if (bbf[v] == nil())
      return nil();
    else
      return bcc.find(bbf[v]);
  }

  usize lca(usize u, usize v) {
    std::unordered_set<usize> reached;
    while (true) {
      if (u != nil()) {
        if (!reached.insert(u).second)
          return u;
        u = parent(u);
      }
      std::swap(u, v);
    }
  }

  void condense_path(usize u, const usize v) {
    while (!bcc.same(u, v)) {
      const usize next = parent(u);
      bbf[u] = bbf[v];
      bcc.unite(u, v);
      u = next;
    }
  }

  void link(const usize x, const usize y) {
    usize v = x, prev = y;
    while (v != nil()) {
      const usize next = parent(v);
      bbf[v] = prev;
      prev = v;
      v = next;
    }
  }

public:
  incremental_bridge_connectivity() = default;

  explicit incremental_bridge_connectivity(const usize n)
      : cc(n), bcc(n), bbf(n, n) {}

  usize find_block(const usize v) {
    assert(v < size());

    return bcc.find(v);
  }

  bool bridge_connected(const usize u, const usize v) {
    assert(u < size());
    assert(v < size());

    return bcc.same(u, v);
  }

  void insert_edge(usize u, usize v) {
    assert(u < size());
    assert(v < size());

    u = bcc.find(u);
    v = bcc.find(v);
    if (cc.same(u, v)) {
      const usize w = lca(u, v);
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
