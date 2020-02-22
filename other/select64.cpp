#include <cstddef>
#include <cstdint>

std::size_t select64(const std::uint_fast64_t x0, size_t k) {
  using size_t = std::size_t;
  using u64 = std::uint_fast64_t;

  const u64 x1 = (x0 & 0x5555555555555555) + (x0 >> 1 & 0x5555555555555555);
  const u64 x2 = (x1 & 0x3333333333333333) + (x1 >> 2 & 0x3333333333333333);
  const u64 x3 = (x2 & 0x0F0F0F0F0F0F0F0F) + (x2 >> 4 & 0x0F0F0F0F0F0F0F0F);
  const u64 x4 = (x3 & 0x00FF00FF00FF00FF) + (x3 >> 8 & 0x00FF00FF00FF00FF);
  const u64 x5 = (x4 & 0x0000FFFF0000FFFF) + (x4 >> 16 & 0x0000FFFF0000FFFF);
  size_t ret = 0;
  size_t t;
  t = x5 >> ret & 0xFFFFFFFF;
  if (t <= k) {
    k -= t;
    ret += 32;
  }
  t = x4 >> ret & 0xFFFF;
  if (t <= k) {
    k -= t;
    ret += 16;
  }
  t = x3 >> ret & 0xFF;
  if (t <= k) {
    k -= t;
    ret += 8;
  }
  t = x2 >> ret & 0xF;
  if (t <= k) {
    k -= t;
    ret += 4;
  }
  t = x1 >> ret & 0x3;
  if (t <= k) {
    k -= t;
    ret += 2;
  }
  t = x0 >> ret & 0x1;
  if (t <= k) {
    k -= t;
    ret += 1;
  }
  return ret;
}