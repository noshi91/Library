#include <cstddef>
#include <cstdint>

std::size_t popcount64(std::uint_fast64_t x) {
#ifdef __GNUC__
  return __builtin_popcountll(x);
#else
  x -= x >> 1 & 0x5555555555555555;
  x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
  x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;
  return x * 0x0101010101010101 >> 56 & 0x7f;
#endif
}