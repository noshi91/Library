## 入力
$N \times N$ 下三角行列 $A$
-   $A$ は totally monotone
-   出力の一部を使用しても良い（後述）

## 出力
各 $i$ について $\mathop {\rm arg \, min} \limits _ j A _ {i , j}$

## 計算量
-   時間計算量 $\Theta ( N )$
-   空間計算量 $\Theta ( N )$

## 説明
$A$ について、行の添え字は $1$ から、列の添え字は $0$ から始まるものとする。

大雑把に言えば、このアルゴリズムはある種の動的計画法を高速化するものである。
出力の値は $i$ の昇順に計算され、$A _ {i , j}$ の値は
$j$ についての $\mathop {\rm arg \, min} \limits _ k A _ {j , k}$
が計算された後にアクセス出来れば良い。
したがって $A _ {i , j}$ は ${\rm dp} \lbrack j \rbrack$ から
${\rm dp} \lbrack i \rbrack$ への遷移とみなすことが出来る。
[SMAWK Algorithm](https://noshi91.github.io/Library/library/algorithm/smawk.cpp.html)
を on-line な動的計画法に適用出来るよう工夫したものとも言える。
実際、アルゴリズムの内容も SMAWK Algorithm に類似している。

## 文献
-   Larmore, L. L., & Schieber, B. (1991). On-line dynamic programming with applications to the prediction of RNA secondary structure. Journal of Algorithms, 12(3), 490-515.

## 語

#### totally monotone
[SMAWK Algorithm](https://noshi91.github.io/Library/library/algorithm/smawk.cpp.html) を参照せよ。
ただしこのページでは文献に合わせて、$\min$ による定義を採用している。

## その他
-   実装例の引数 $\rm select$ について

    ${\rm select} ( i , j , k ) \mathrel := A _ {i , j}$ と $A _ {i , k} \  ( j \lt k )$ を比較して、前者を選ぶ場合 false、後者を選ぶ場合 true

-   実装例の引数 $\rm update$ について

    ${\rm update} ( i , k )$ が呼ばれたとき、$\mathop {\rm arg \, min} \limits _ j A _ {i , j} = k$ である。この関数は $i$ の昇順に呼ばれる。
