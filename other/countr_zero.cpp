#pragma once

#include "other/int_alias.cpp"

#include <array>

usize countr_zero(u64 x) {
  if (x == 0)
    return 64;
#ifdef __GNUC__
  return __builtin_ctzll(x);
#else
  constexpr std::array<usize, 64> table = {
      0,  1,  2,  7,  3,  13, 8,  27, 4,  33, 14, 36, 9,  49, 28, 19,
      5,  25, 34, 17, 15, 53, 37, 55, 10, 46, 50, 39, 29, 42, 20, 57,
      63, 6,  12, 26, 32, 35, 48, 18, 24, 16, 52, 54, 45, 38, 41, 56,
      62, 11, 31, 47, 23, 51, 44, 40, 61, 30, 22, 43, 60, 21, 59, 58};
  return table[(x & ~x + 1) * 0x218A7A392DD9ABF >> 58 & 0x3F];
#endif
}
