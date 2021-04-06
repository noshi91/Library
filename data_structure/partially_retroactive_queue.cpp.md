---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Partially Retroactive Queue
    links:
    - https://erikdemaine.org/papers/Retroactive_TALG/paper.pdf
  bundledCode: "#line 1 \"data_structure/partially_retroactive_queue.cpp\"\n#include\
    \ <cassert>\n#include <iterator>\n#include <list>\n\ntemplate <class T> class\
    \ partially_retroactive_queue {\n  class node_type;\n\npublic:\n  using time_type\
    \ = typename std::list<node_type>::const_iterator;\n\nprivate:\n  class node_type\
    \ {\n    friend partially_retroactive_queue;\n\n    T value;\n    bool in_queue;\n\
    \    node_type(const T value) : value(value), in_queue() {}\n  };\n\n  std::list<node_type>\
    \ list;\n  typename std::list<node_type>::iterator front_itr;\n\npublic:\n  partially_retroactive_queue()\
    \ : list(), front_itr(list.end()) {}\n\n  time_type now() const { return list.cend();\
    \ }\n\n  bool empty() const { return front_itr == list.end(); }\n\n  T front()\
    \ const {\n    assert(!empty());\n    return front_itr->value;\n  }\n\n  time_type\
    \ insert_push(const time_type time, const T x) {\n    const auto itr = list.insert(time,\
    \ node_type(x));\n    if (itr == list.begin() || !std::prev(itr)->in_queue) {\n\
    \      itr->in_queue = false;\n      --front_itr;\n      front_itr->in_queue =\
    \ true;\n    } else {\n      itr->in_queue = true;\n    }\n    return time_type(itr);\n\
    \  }\n  void erase_push(const time_type time) {\n    assert(time != now());\n\
    \    if (time == list.cbegin() || !std::prev(time)->in_queue) {\n      front_itr->in_queue\
    \ = false;\n      ++front_itr;\n    }\n    list.erase(time);\n  }\n  void insert_pop()\
    \ {\n    assert(!empty());\n    front_itr->in_queue = false;\n    ++front_itr;\n\
    \  }\n  void erase_pop() {\n    assert(front_itr != list.begin());\n    --front_itr;\n\
    \    front_itr->in_queue = true;\n  }\n};\n\n/**\n * @brief Partially Retroactive\
    \ Queue\n * @see https://erikdemaine.org/papers/Retroactive_TALG/paper.pdf\n */\n"
  code: "#include <cassert>\n#include <iterator>\n#include <list>\n\ntemplate <class\
    \ T> class partially_retroactive_queue {\n  class node_type;\n\npublic:\n  using\
    \ time_type = typename std::list<node_type>::const_iterator;\n\nprivate:\n  class\
    \ node_type {\n    friend partially_retroactive_queue;\n\n    T value;\n    bool\
    \ in_queue;\n    node_type(const T value) : value(value), in_queue() {}\n  };\n\
    \n  std::list<node_type> list;\n  typename std::list<node_type>::iterator front_itr;\n\
    \npublic:\n  partially_retroactive_queue() : list(), front_itr(list.end()) {}\n\
    \n  time_type now() const { return list.cend(); }\n\n  bool empty() const { return\
    \ front_itr == list.end(); }\n\n  T front() const {\n    assert(!empty());\n \
    \   return front_itr->value;\n  }\n\n  time_type insert_push(const time_type time,\
    \ const T x) {\n    const auto itr = list.insert(time, node_type(x));\n    if\
    \ (itr == list.begin() || !std::prev(itr)->in_queue) {\n      itr->in_queue =\
    \ false;\n      --front_itr;\n      front_itr->in_queue = true;\n    } else {\n\
    \      itr->in_queue = true;\n    }\n    return time_type(itr);\n  }\n  void erase_push(const\
    \ time_type time) {\n    assert(time != now());\n    if (time == list.cbegin()\
    \ || !std::prev(time)->in_queue) {\n      front_itr->in_queue = false;\n     \
    \ ++front_itr;\n    }\n    list.erase(time);\n  }\n  void insert_pop() {\n   \
    \ assert(!empty());\n    front_itr->in_queue = false;\n    ++front_itr;\n  }\n\
    \  void erase_pop() {\n    assert(front_itr != list.begin());\n    --front_itr;\n\
    \    front_itr->in_queue = true;\n  }\n};\n\n/**\n * @brief Partially Retroactive\
    \ Queue\n * @see https://erikdemaine.org/papers/Retroactive_TALG/paper.pdf\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/partially_retroactive_queue.cpp
  requiredBy: []
  timestamp: '2020-02-28 14:18:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/partially_retroactive_queue.cpp
layout: document
redirect_from:
- /library/data_structure/partially_retroactive_queue.cpp
- /library/data_structure/partially_retroactive_queue.cpp.html
title: Partially Retroactive Queue
---
