#include "other/countl_zero64.cpp"

#include <cstddef>
#include <cstdint>

std::size_t log2p164(const std::uint_fast64_t x) {
  return 64 - countl_zero64(x);
}