## 入力
長さ $N$ の列 $A$  
長さ $M$ の列 $B$
-   $B$ は上に凸

## 出力
$C_i \mathrel := \max \limits _ j \lbrace A _ j + B _ {i - j} \rbrace$

で定義される長さ $N + M - 1$ の列 $C$

## 計算量
-   時間計算量 $\Theta ( N + M )$
-   空間計算量 $\Theta ( N + M )$

## 説明
$( N + M - 1 ) \times N$ 行列 $X$ を以下のように定義する。

$X _ {i , j} \mathrel := A _ j + B _ {i - j}$

ただし、$k \lt 0$ や $M \leq k$ に対する $B _ k$ は、十分小さい値を $B$ の凸性を保つように設定するものとする。  
目的は $C _ i = \max \limits _ j X _ {i , j}$ を計算することである。  
$B$ が上に凸であることから $X$ は (anti-)monge であり、すなわち totally monotone。よって[SMAWK Algorithm](https://noshi91.github.io/Library/library/algorithm/smawk.cpp.html) を用いると $\Theta ( N + M )$ で計算可能。

## 文献
-   [Capacitated Dynamic Programming: Faster Knapsack and Graph Algorithms](https://arxiv.org/abs/1802.06440)  
    [Axiotis-Tzamos Knapsack](https://noshi91.github.io/Library/library/algorithm/axiotis_tzamos_knapsack.cpp.html) で使用されている
