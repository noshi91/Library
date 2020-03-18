#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include "data_structure/physicists_queue.cpp"

#include <iostream>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  int q;
  std::cin >> q;

  std::vector<physicists_queue<int>> s_(q + 1);
  const auto s = s_.begin() + 1;

  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int t, x;
      std::cin >> t >> x;
      s[i] = s[t].push(x);
    } break;
    case 1: {
      int t;
      std::cin >> t;
      std::cout << s[t].front() << "\n";
      s[i] = s[t].pop();
    }
    }
  }
}
