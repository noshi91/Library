## 入力
$N \times M$ 行列 $A$
-   $A$ は totally monotone

## 出力
各 $i$ について $\mathop {\rm arg \, max} \limits _ j A _ {i , j}$

## 計算量
-   時間計算量 $\Theta ( N + M )$
-   空間計算量 $\Theta ( N + M )$

## 説明
$N \times M$ 行列 $A$ について、いずれかの行で最大値を取り得る高々 $N$ 個の列を $\Theta ( N + M )$ で取り出すアルゴリズムが存在する。(reduce)  
$1$ つ飛ばしに $N / 2$ 個程度の行を取り出し、reduce することで $N , M$ 共に半分になった問題を解く。  
monotone 性から、飛ばした行の $\mathop {\rm arg \, max}$ を復元する。(interpolate)

## 文献
-   [Totally Monotone Matrix Searching (SMAWK algorithm)](https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/)  
    週刊 spaghetti_source  
    日本語

-   [The SMAWK Algorithm (pdf)](http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf)  
    具体例が図示されている

-   [Geometric applications of a matrix-searching algorithm](https://link.springer.com/article/10.1007%2FBF01840359)  
    SMAWK Algorithm が提案された論文

## 語
#### monotone
$A$ が monotone であるとは、任意の $i \lt j$ に対して

$\mathop {\rm arg \, max} \limits _ k A _ {i , k} \le \mathop {\rm arg \, max} \limits _ k A _ {j , k}$

が成立することを指す。  
ただし適切な tie-break により $\mathop {\rm arg \, max}$ は $1$ つに定まるとする。  
$\mathop {\rm arg \, min}$ による定義も存在するので注意。

#### totally monotone
$A$ が totally monotone であるとは、その任意の部分行列が monotone であることを指す。  
同値な定義に「$A$ の任意の $2 \times 2$ 部分行列が monotone」がある。

## その他
-   実装例の引数 $\rm select$ の定義  
    ${\rm select} ( i , j , k ) \mathrel := A _ {i , j}$ と $A _ {i , k} \  ( j \lt k )$ を比較して、前者を選ぶ場合 false、後者を選ぶ場合 true
