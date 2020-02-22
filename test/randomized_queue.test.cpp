#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include "data_structure/randomized_queue.cpp"
#include "other/random_integer.cpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int main() {
  const int n = 1 << 20;

  std::vector<int> a(n);
  for (int &e : a)
    e = random_integer(std::numeric_limits<int>::lowest(),
                       std::numeric_limits<int>::max());

  randomized_queue<int> rq;
  for (const int e : a)
    rq.push(e);

  assert(!rq.empty());

  std::vector<int> b(n);
  for (int &e : b)
    e = rq.pop();

  assert(rq.empty());
  assert(a != b);
  std::reverse(b.begin(), b.end());
  assert(a != b);
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  assert(a == b);

  std::cout << "Hello World" << std::endl;
}