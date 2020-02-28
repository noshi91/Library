#include <cstddef>
#include <functional>
#include <numeric>
#include <vector>

template <class Select>
std::vector<std::size_t> smawk(const std::size_t row_size,
                               const std::size_t col_size,
                               const Select &select) {
  using size_t = std::size_t;
  using vec_zu = std::vector<size_t>;

  const std::function<vec_zu(const vec_zu &, const vec_zu &)> solve =
      [&](const vec_zu &row, const vec_zu &col) -> vec_zu {
    const size_t n = row.size();
    if (n == 0)
      return {};
    vec_zu c2;
    for (const size_t i : col) {
      while (!c2.empty() && select(row[c2.size() - 1], c2.back(), i))
        c2.pop_back();
      if (c2.size() < n)
        c2.push_back(i);
    }
    vec_zu r2;
    for (size_t i = 1; i < n; i += 2)
      r2.push_back(row[i]);
    const vec_zu a2 = solve(r2, c2);
    vec_zu ans(n);
    for (size_t i = 0; i != a2.size(); i += 1)
      ans[i * 2 + 1] = a2[i];
    size_t j = 0;
    for (size_t i = 0; i < n; i += 2) {
      ans[i] = c2[j];
      const size_t end = i + 1 == n ? c2.back() : ans[i + 1];
      while (c2[j] != end) {
        j += 1;
        if (select(row[i], ans[i], c2[j]))
          ans[i] = c2[j];
      }
    }
    return ans;
  };
  vec_zu row(row_size);
  std::iota(row.begin(), row.end(), 0);
  vec_zu col(col_size);
  std::iota(col.begin(), col.end(), 0);
  return solve(row, col);
}

/**
 * @brief SMAWK Algorithm
 * @see http://www.cs.ust.hk/mjg_lib/bibs/DPSu/DPSu.Files/p285-aggarwal.pdf
 */
