# parametric_heap
```
template <T, Minimize = true, Compare = std::less<T>>
class parametric_heap;
```

`parametric_heap` は数の組 (a, b) の多重集合を管理するデータ構造です。
直線の削除が可能な Convex Hull Trick と理解することも出来ます。

## テンプレート引数
|引数名||
|:---|:---|
|`T`|数値の型|
|`Minimize`|`true` で最小化、`false` で最大化します。デフォルトは `true` です。|
|`Compare`|< に相当する比較関数。デフォルトは `std::less<T>` です。|

## メンバ関数

n を要素数とします。

|メンバ関数名|効果|時間計算量|
|:---|:---|:---|
|`explicit parametric_heap(Compare comp_ = Compare())`|`comp_` を比較関数として、空の状態で構築します。|Θ(1)|
|`bool empty() const`|空の場合 `true`、空でない場合 `false` を返します。|Θ(1)|
|`void insert(const T &a, const T &b)`|(a, b) を追加します。|Θ(log(n)^2)|
|`bool erase(const T &a, const T &b)`|(a, b) を削除します。<br>削除に成功した場合 `true`、失敗した場合 `false` を返します。<br>複数存在する場合、そのうち 1 つを削除します。|Θ(log(n)^2)|
|`std::pair<T, T> top(const T &x) const`|ax + b を最小化するような (a, b) を返します。<br>`Minimize` が `false` の場合、最大化するものを返します。<br>複数存在する場合にどれを返すかは未規定です。<br>空の場合 abort します。|Θ(log(n))|

## 注意事項

多重集合を管理します。
すなわち、同じ (a, b) を繰り返し `insert` するとそれだけ要素数が増えます。
また、(`std::multiset` と異なり) `erase` によっても 1 つずつ消えます。

`T`, `Compare` が満たすべき条件は、大雑把には

-   `T` が実数の部分集合である。
-   `T` 同士の加算と乗算は `T` を実数として見たときと同じ挙動をする。
-   `Compare` による比較は、`T` を実数として見たときの < と同じ挙動をする。

と表現されます。したがって、オーバーフローを無視すれば `int` や有理数型を `T`
に用いることが出来ます。 また、誤差を度外視すれば `double`
も用いることが出来ます。

特に、`Compare` は < (`less`) であることに注意してください。> (`greater`) や <=
(`less_equal`) にすると壊れます。最大化したい場合、`Compare` ではなく `Minimize`
の方で調整してください。


計算の過程で最大 `8 * a * a * b` 程度の大きさの値が現れます。
したがって、これにより `T` がオーバーフローしないようにしてください。
`__int128_t` が必要になることも多いと思われます。

## 参考文献

-   Overmars, M. H., & Van Leeuwen, J. (1981).
    Maintenance of configurations in the plane.
    Journal of computer and System Sciences, 23(2), 166-204.

-   Kaplan, H., Tarjan, R. E., & Tsioutsiouliklis, K. (2001, January).
    Faster kinetic heaps and their use in broadcast scheduling.
    In SODA (Vol. 1, pp. 836-844).
