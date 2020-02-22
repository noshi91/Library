#include <array>
#include <cstddef>
#include <cstdint>

std::size_t countl_zero64(std::uint_fast64_t x) {
#ifdef __GNUC__
  return x == 0 ? 64 : __builtin_clzll(x);
#else
  if (x == 0)
    return 64;
  std::size_t ret = 0;
  if ((x & 0xFFFFFFFF00000000) != 0)
    x >>= 32;
  else
    ret += 32;
  if ((x & 0xFFFF0000) != 0)
    x >>= 16;
  else
    ret += 16;
  if ((x & 0xFF00) != 0)
    x >>= 8;
  else
    ret += 8;
  if ((x & 0xF0) != 0)
    x >>= 4;
  else
    ret += 4;
  if ((x & 0xC) != 0)
    x >>= 2;
  else
    ret += 2;
  if ((x & 0x2) != 0)
    x >>= 1;
  else
    ret += 1;
  return ret;
#endif
}