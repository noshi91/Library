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
    document_title: Persistent Skew Binary Random Access List
    links:
    - https://scrapbox.io/data-structures/Skew_Binary_List
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/persistent_skew_binary_random_access_list.cpp\"\n\n#include\
    \ <cassert>\n#line 5 \"data_structure/persistent_skew_binary_random_access_list.cpp\"\
    \n#include <memory>\n#include <utility>\n\ntemplate <class T, class Size = usize>\n\
    class persistent_skew_binary_random_access_list {\n  using Self = persistent_skew_binary_random_access_list;\n\
    \n  class tree_type;\n  using tree_ptr = std::shared_ptr<const tree_type>;\n \
    \ class tree_type {\n  public:\n    T value;\n    tree_ptr left;\n    tree_ptr\
    \ right;\n\n    tree_type(const T value, const tree_ptr left, const tree_ptr right)\n\
    \        : value(value), left(left), right(right) {}\n\n    T lookup(const Size\
    \ size, const Size index) const {\n      if (index == 0) {\n        return value;\n\
    \      } else {\n        assert(size != 1);\n        const Size rem_index = index\
    \ - 1;\n        const Size ch_size = size / 2;\n        if (rem_index < ch_size)\
    \ {\n          return left->lookup(ch_size, rem_index);\n        } else {\n  \
    \        return right->lookup(ch_size, rem_index - ch_size);\n        }\n    \
    \  }\n    }\n    tree_ptr update(const Size size, const Size index, const T x)\
    \ const {\n      if (index == 0) {\n        return make_tree(x, left, right);\n\
    \      } else {\n        assert(size != 1);\n        const Size rem_index = index\
    \ - 1;\n        const Size ch_size = size / 2;\n        if (rem_index < ch_size)\
    \ {\n          return make_tree(value, left->update(ch_size, rem_index, x), right);\n\
    \        } else {\n          return make_tree(value, left,\n                 \
    \          right->update(ch_size, rem_index - ch_size, x));\n        }\n     \
    \ }\n    }\n  };\n\n  class digit_type;\n  using digit_ptr = std::shared_ptr<const\
    \ digit_type>;\n  class digit_type {\n  public:\n    Size size;\n    tree_ptr\
    \ tree;\n    digit_ptr next;\n\n    digit_type(const Size size, const tree_ptr\
    \ tree, const digit_ptr next)\n        : size(size), tree(tree), next(next) {}\n\
    \n    T lookup(const Size index) const {\n      if (index < size) {\n        return\
    \ tree->lookup(size, index);\n      } else {\n        return next->lookup(index\
    \ - size);\n      }\n    }\n    digit_ptr update(const Size index, const T x)\
    \ const {\n      if (index < size) {\n        return make_digit(size, tree->update(size,\
    \ index, x), next);\n      } else {\n        return make_digit(size, tree, next->update(index\
    \ - size, x));\n      }\n    }\n  };\n\n  template <class... Args> static tree_ptr\
    \ make_tree(Args &&... args) {\n    return std::make_shared<tree_type>(std::forward<Args>(args)...);\n\
    \  }\n  template <class... Args> static digit_ptr make_digit(Args &&... args)\
    \ {\n    return std::make_shared<digit_type>(std::forward<Args>(args)...);\n \
    \ }\n\n  digit_ptr root;\n\n  persistent_skew_binary_random_access_list(const\
    \ digit_ptr root)\n      : root(root) {}\n\npublic:\n  persistent_skew_binary_random_access_list()\
    \ = default;\n\n  bool empty() const { return !root; }\n\n  T operator[](const\
    \ Size index) const { return root->lookup(index); }\n  T front() const { return\
    \ root->tree->value; }\n\n  Self update(const Size index, const T x) const {\n\
    \    return Self(root->update(index, x));\n  }\n  Self push_front(const T x) const\
    \ {\n    if (root && root->next && root->size == root->next->size) {\n      return\
    \ Self(make_digit(1 + root->size + root->next->size,\n                       \
    \      make_tree(x, root->tree, root->next->tree),\n                         \
    \    root->next->next));\n    } else {\n      return Self(make_digit(1, make_tree(x,\
    \ nullptr, nullptr), root));\n    }\n  }\n  Self pop_front() const {\n    if (root->size\
    \ == 1) {\n      return Self(root->next);\n    } else {\n      const Size ch_size\
    \ = root->size / 2;\n      return Self(\n          make_digit(ch_size, root->tree->left,\n\
    \                     make_digit(ch_size, root->tree->right, root->next)));\n\
    \    }\n  }\n};\n\n/**\n * @brief Persistent Skew Binary Random Access List\n\
    \ * @see https://scrapbox.io/data-structures/Skew_Binary_List\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <cassert>\n#include <cstddef>\n\
    #include <memory>\n#include <utility>\n\ntemplate <class T, class Size = usize>\n\
    class persistent_skew_binary_random_access_list {\n  using Self = persistent_skew_binary_random_access_list;\n\
    \n  class tree_type;\n  using tree_ptr = std::shared_ptr<const tree_type>;\n \
    \ class tree_type {\n  public:\n    T value;\n    tree_ptr left;\n    tree_ptr\
    \ right;\n\n    tree_type(const T value, const tree_ptr left, const tree_ptr right)\n\
    \        : value(value), left(left), right(right) {}\n\n    T lookup(const Size\
    \ size, const Size index) const {\n      if (index == 0) {\n        return value;\n\
    \      } else {\n        assert(size != 1);\n        const Size rem_index = index\
    \ - 1;\n        const Size ch_size = size / 2;\n        if (rem_index < ch_size)\
    \ {\n          return left->lookup(ch_size, rem_index);\n        } else {\n  \
    \        return right->lookup(ch_size, rem_index - ch_size);\n        }\n    \
    \  }\n    }\n    tree_ptr update(const Size size, const Size index, const T x)\
    \ const {\n      if (index == 0) {\n        return make_tree(x, left, right);\n\
    \      } else {\n        assert(size != 1);\n        const Size rem_index = index\
    \ - 1;\n        const Size ch_size = size / 2;\n        if (rem_index < ch_size)\
    \ {\n          return make_tree(value, left->update(ch_size, rem_index, x), right);\n\
    \        } else {\n          return make_tree(value, left,\n                 \
    \          right->update(ch_size, rem_index - ch_size, x));\n        }\n     \
    \ }\n    }\n  };\n\n  class digit_type;\n  using digit_ptr = std::shared_ptr<const\
    \ digit_type>;\n  class digit_type {\n  public:\n    Size size;\n    tree_ptr\
    \ tree;\n    digit_ptr next;\n\n    digit_type(const Size size, const tree_ptr\
    \ tree, const digit_ptr next)\n        : size(size), tree(tree), next(next) {}\n\
    \n    T lookup(const Size index) const {\n      if (index < size) {\n        return\
    \ tree->lookup(size, index);\n      } else {\n        return next->lookup(index\
    \ - size);\n      }\n    }\n    digit_ptr update(const Size index, const T x)\
    \ const {\n      if (index < size) {\n        return make_digit(size, tree->update(size,\
    \ index, x), next);\n      } else {\n        return make_digit(size, tree, next->update(index\
    \ - size, x));\n      }\n    }\n  };\n\n  template <class... Args> static tree_ptr\
    \ make_tree(Args &&... args) {\n    return std::make_shared<tree_type>(std::forward<Args>(args)...);\n\
    \  }\n  template <class... Args> static digit_ptr make_digit(Args &&... args)\
    \ {\n    return std::make_shared<digit_type>(std::forward<Args>(args)...);\n \
    \ }\n\n  digit_ptr root;\n\n  persistent_skew_binary_random_access_list(const\
    \ digit_ptr root)\n      : root(root) {}\n\npublic:\n  persistent_skew_binary_random_access_list()\
    \ = default;\n\n  bool empty() const { return !root; }\n\n  T operator[](const\
    \ Size index) const { return root->lookup(index); }\n  T front() const { return\
    \ root->tree->value; }\n\n  Self update(const Size index, const T x) const {\n\
    \    return Self(root->update(index, x));\n  }\n  Self push_front(const T x) const\
    \ {\n    if (root && root->next && root->size == root->next->size) {\n      return\
    \ Self(make_digit(1 + root->size + root->next->size,\n                       \
    \      make_tree(x, root->tree, root->next->tree),\n                         \
    \    root->next->next));\n    } else {\n      return Self(make_digit(1, make_tree(x,\
    \ nullptr, nullptr), root));\n    }\n  }\n  Self pop_front() const {\n    if (root->size\
    \ == 1) {\n      return Self(root->next);\n    } else {\n      const Size ch_size\
    \ = root->size / 2;\n      return Self(\n          make_digit(ch_size, root->tree->left,\n\
    \                     make_digit(ch_size, root->tree->right, root->next)));\n\
    \    }\n  }\n};\n\n/**\n * @brief Persistent Skew Binary Random Access List\n\
    \ * @see https://scrapbox.io/data-structures/Skew_Binary_List\n */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/persistent_skew_binary_random_access_list.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/persistent_skew_binary_random_access_list.cpp
layout: document
redirect_from:
- /library/data_structure/persistent_skew_binary_random_access_list.cpp
- /library/data_structure/persistent_skew_binary_random_access_list.cpp.html
title: Persistent Skew Binary Random Access List
---
