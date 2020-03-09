#pragma once

#include <random>
#include <type_traits>

template <class T, class... Args>
using any_of_is_same = std::disjunction<std::is_same<T, Args>...>;

template <class IntType = int>
IntType random_integer(const IntType a, const IntType b) {
  static_assert(
      any_of_is_same<IntType, short, int, long, long long, unsigned short,
                     unsigned int, unsigned long, unsigned long long>::value);
  static std::default_random_engine g(91);
  return std::uniform_int_distribution<IntType>(a, b)(g);
}
