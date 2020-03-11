#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170&lang=en"

#include "data_structure/pairing_heap.cpp"
#include "other/less_equal_ordered_set.cpp"
#include "other/opposite_ordered_set.cpp"

#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

void solve(const int n, const int q) {
  using heap_type =
      pairing_heap<opposite_ordered_set<less_equal_ordered_set<int>>>;

  std::vector<int> p(n), deg(n, 0);
  for (int i = 1; i != n; i += 1) {
    std::cin >> p[i];
    p[i] -= 1;
    deg[p[i]] += 1;
  }
  std::vector<heap_type> ph(n);
  std::vector<int> time(n, q);
  time[0] = -1;
  for (int i = 0; i != q; i += 1) {
    char c;
    std::cin >> c;
    switch (c) {
    case 'M': {
      int v;
      std::cin >> v;
      v -= 1;
      time[v] = std::min(time[v], i);
    } break;
    case 'Q': {
      int v;
      std::cin >> v;
      v -= 1;
      ph[v].push(i);
    } break;
    }
  }
  std::stack<int> st;
  for (int i = 0; i != n; i += 1) {
    if (deg[i] == 0)
      st.push(i);
  }
  long long ans = 0;
  while (!st.empty()) {
    const int v = st.top();
    st.pop();
    auto &pv = ph[v];
    while (!pv.empty() && time[v] < pv.top()) {
      pv.pop();
      ans += v + 1;
    }
    if (v == 0)
      continue;
    ph[p[v]] = heap_type::meld(std::move(ph[p[v]]), std::move(pv));
    deg[p[v]] -= 1;
    if (deg[p[v]] == 0)
      st.push(p[v]);
  }
  std::cout << ans << "\n";
}

int main() {
#include "other/fast_ios.cpp"

  while (true) {
    int n, q;
    std::cin >> n >> q;
    if (n == 0 && q == 0)
      break;
    solve(n, q);
  }
}
