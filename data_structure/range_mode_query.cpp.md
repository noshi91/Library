---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Range Mode Query
    links:
    - https://scrapbox.io/data-structures/Range_Mode_Query
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/range_mode_query.cpp\"\n\n#include <cassert>\n#line 5\
    \ \"data_structure/range_mode_query.cpp\"\n#include <vector>\n\nclass range_mode_query\
    \ {\n  class b_node {\n  public:\n    usize value;\n    usize rank;\n\n    b_node(const\
    \ usize value, const usize rank) : value(value), rank(rank) {}\n  };\n\n  class\
    \ s_node {\n  public:\n    usize mode;\n    usize freq;\n\n    s_node(const usize\
    \ mode, const usize freq) : mode(mode), freq(freq) {}\n  };\n\n  std::vector<b_node>\
    \ b;\n  std::vector<std::vector<usize>> q;\n  std::vector<std::vector<s_node>>\
    \ s;\n  usize t;\n\npublic:\n  range_mode_query() = default;\n\n  range_mode_query(const\
    \ std::vector<usize> a) : t(1) {\n    const usize n = a.size();\n    b.assign(n,\
    \ b_node(0, 0));\n    q.assign(n, {});\n    while (t * t < n)\n      t += 1;\n\
    \    for (usize i = 0; i != n; i += 1) {\n      const usize e = a[i];\n      assert(e\
    \ < n);\n      b[i] = b_node(e, q[e].size());\n      q[e].push_back(i);\n    }\n\
    \    s.assign(n / t + 1, std::vector<s_node>(n / t + 1, s_node(0, 0)));\n    for\
    \ (usize f = 0; f * t <= n; f += 1) {\n      std::vector<usize> freq(n, 0);\n\
    \      s_node cur(0, 0);\n      for (usize l = f + 1; l * t <= n; l += 1) {\n\
    \        for (usize i = (l - 1) * t; i != l * t; i += 1) {\n          const usize\
    \ e = a[i];\n          freq[e] += 1;\n          if (freq[e] > cur.freq)\n    \
    \        cur = s_node(e, freq[e]);\n        }\n        s[f][l] = cur;\n      }\n\
    \    }\n  }\n\n  usize query(const usize first, const usize last) const {\n  \
    \  assert(first < last);\n    assert(last <= b.size());\n    usize bf = first\
    \ / t + 1;\n    usize bl = last / t;\n    if (bf >= bl) {\n      s_node cur(0,\
    \ 0);\n      for (usize i = first; i != last; i += 1) {\n        const b_node\
    \ &e = b[i];\n        const std::vector<usize> &v = q[e.value];\n        usize\
    \ idx;\n        while ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)\n\
    \          cur = s_node(e.value, cur.freq + 1);\n      }\n      return cur.mode;\n\
    \    }\n    s_node cur = s[bf][bl];\n    for (usize i = first; i != bf * t; i\
    \ += 1) {\n      const b_node &e = b[i];\n      const std::vector<usize> &v =\
    \ q[e.value];\n      usize idx;\n      while ((idx = e.rank + cur.freq) < v.size()\
    \ && v[idx] < last)\n        cur = s_node(e.value, cur.freq + 1);\n    }\n   \
    \ for (usize i = bl * t; i != last; i += 1) {\n      const b_node &e = b[i];\n\
    \      const std::vector<usize> &v = q[e.value];\n      usize idx;\n      while\
    \ ((idx = e.rank - cur.freq) < v.size() && v[idx] >= first)\n        cur = s_node(e.value,\
    \ cur.freq + 1);\n    }\n    return cur.mode;\n  }\n};\n\n/**\n * @brief Range\
    \ Mode Query\n * @see https://scrapbox.io/data-structures/Range_Mode_Query\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <cassert>\n#include <cstddef>\n\
    #include <vector>\n\nclass range_mode_query {\n  class b_node {\n  public:\n \
    \   usize value;\n    usize rank;\n\n    b_node(const usize value, const usize\
    \ rank) : value(value), rank(rank) {}\n  };\n\n  class s_node {\n  public:\n \
    \   usize mode;\n    usize freq;\n\n    s_node(const usize mode, const usize freq)\
    \ : mode(mode), freq(freq) {}\n  };\n\n  std::vector<b_node> b;\n  std::vector<std::vector<usize>>\
    \ q;\n  std::vector<std::vector<s_node>> s;\n  usize t;\n\npublic:\n  range_mode_query()\
    \ = default;\n\n  range_mode_query(const std::vector<usize> a) : t(1) {\n    const\
    \ usize n = a.size();\n    b.assign(n, b_node(0, 0));\n    q.assign(n, {});\n\
    \    while (t * t < n)\n      t += 1;\n    for (usize i = 0; i != n; i += 1) {\n\
    \      const usize e = a[i];\n      assert(e < n);\n      b[i] = b_node(e, q[e].size());\n\
    \      q[e].push_back(i);\n    }\n    s.assign(n / t + 1, std::vector<s_node>(n\
    \ / t + 1, s_node(0, 0)));\n    for (usize f = 0; f * t <= n; f += 1) {\n    \
    \  std::vector<usize> freq(n, 0);\n      s_node cur(0, 0);\n      for (usize l\
    \ = f + 1; l * t <= n; l += 1) {\n        for (usize i = (l - 1) * t; i != l *\
    \ t; i += 1) {\n          const usize e = a[i];\n          freq[e] += 1;\n   \
    \       if (freq[e] > cur.freq)\n            cur = s_node(e, freq[e]);\n     \
    \   }\n        s[f][l] = cur;\n      }\n    }\n  }\n\n  usize query(const usize\
    \ first, const usize last) const {\n    assert(first < last);\n    assert(last\
    \ <= b.size());\n    usize bf = first / t + 1;\n    usize bl = last / t;\n   \
    \ if (bf >= bl) {\n      s_node cur(0, 0);\n      for (usize i = first; i != last;\
    \ i += 1) {\n        const b_node &e = b[i];\n        const std::vector<usize>\
    \ &v = q[e.value];\n        usize idx;\n        while ((idx = e.rank + cur.freq)\
    \ < v.size() && v[idx] < last)\n          cur = s_node(e.value, cur.freq + 1);\n\
    \      }\n      return cur.mode;\n    }\n    s_node cur = s[bf][bl];\n    for\
    \ (usize i = first; i != bf * t; i += 1) {\n      const b_node &e = b[i];\n  \
    \    const std::vector<usize> &v = q[e.value];\n      usize idx;\n      while\
    \ ((idx = e.rank + cur.freq) < v.size() && v[idx] < last)\n        cur = s_node(e.value,\
    \ cur.freq + 1);\n    }\n    for (usize i = bl * t; i != last; i += 1) {\n   \
    \   const b_node &e = b[i];\n      const std::vector<usize> &v = q[e.value];\n\
    \      usize idx;\n      while ((idx = e.rank - cur.freq) < v.size() && v[idx]\
    \ >= first)\n        cur = s_node(e.value, cur.freq + 1);\n    }\n    return cur.mode;\n\
    \  }\n};\n\n/**\n * @brief Range Mode Query\n * @see https://scrapbox.io/data-structures/Range_Mode_Query\n\
    \ */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/range_mode_query.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/range_mode_query.cpp
layout: document
redirect_from:
- /library/data_structure/range_mode_query.cpp
- /library/data_structure/range_mode_query.cpp.html
title: Range Mode Query
---
