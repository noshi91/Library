#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C&lang=ja"

#include "data_structure/w_ary_tree_set.cpp"

#include "other/int_alias.cpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  static constexpr usize max_q = 2000000;

  struct query_t {
    bool t;
    u32 key;
  };
  std::vector<query_t> q;
  q.reserve(max_q);
  std::vector<u32> v;
  v.reserve(max_q);
  std::string s;

  while (true) {
    std::cin >> s;
    if (s[2] == 's') {
      u32 x;
      std::cin >> x;
      q.push_back({true, x});
      v.push_back(x);
    } else if (s[2] == 't') {
      q.push_back({false, 0});
    } else {
      break;
    }
  }

  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
  std::vector<usize> count(v.size(), 0);

  w_ary_tree_set<max_q> wats;
  for (const auto &e : q) {
    if (e.t) {
      const usize i = std::lower_bound(v.begin(), v.end(), e.key) - v.begin();
      if (count[i] == 0) {
        wats.insert(i);
      }
      ++count[i];
    } else {
      const usize i = wats.max();
      std::cout << v[i] << "\n";
      --count[i];
      if (count[i] == 0) {
        wats.erase(i);
      }
    }
  }

  return 0;
}
