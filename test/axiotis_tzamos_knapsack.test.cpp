#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja"

#include "algorithm/axiotis_tzamos_knapsack.cpp"

#include <iostream>
#include <vector>

int main() {
  usize n, w;
  std::cin >> n >> w;
  struct item_t {
    i64 v, w;
  };
  std::vector<item_t> is(n);
  for (auto &e : is) {
    std::cin >> e.v >> e.w;
  }
  std::cout << axiotis_tzamos_knapsack(w + 1, is) << std::endl;
}
