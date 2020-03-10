#pragma once

#include "other/countl_zero.cpp"
#include "other/int_alias.cpp"

usize bit_width(const u64 x) { return 64 - countl_zero(x); }
