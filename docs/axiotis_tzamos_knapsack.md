## 入力
非負整数 $T$
長さ $N$ の正整数列 $w$
長さ $N$ の非負整数列 $v$

## 出力
$x _ i \in \lbrace 0 , 1 \rbrace$

$\displaystyle \sum x _ i w _ i \le T$

を満たす列 $x$ について

$\displaystyle \sum x _ i v _ i$

の最大値

## 計算量
$D$ を $w$ の種類数とする
-   時間計算量 $\Theta ( N \log ( N ) + T D )$
-   空間計算量 $\Theta ( N + T )$

## 説明
${\rm dp} \lbrack i \rbrack \mathrel := w$ の総和 $i$ で達成される $v$ の総和の最大値

最初

${\rm dp} \lbrack i \rbrack = \begin{cases} 0 \  ( i = 0 ) \\ - \infty \  ( i \neq 0 ) \end{cases}$

であり、各 $w '$ について $w _ j = w '$ となる $j$ でまとめて $\rm dp$ を更新していく。そのような $j$ について $v _ j$ を降順にソートした列を $v '$ とすると、$\rm dp$ の更新は以下のように表せる。

$\displaystyle {\rm dp} \lbrack i \rbrack \leftarrow \max \limits _ k \lbrace {\rm dp} \lbrack i - k w ' \rbrack + \sum \limits _ {0 \le l \lt k} v ' _ l \rbrace$

これは $\rm dp$ を $w '$ 間隔で取り出した列に $v '$ の累積和を (max,+)-convolution する操作である。$v '$ が広義単調減少であるから、その累積和は上に凸である。よって [Concave Max Plus Convlution](https://noshi91.github.io/Library/library/algorithm/concave_max_plus_convolution.cpp.html) を用いて高速に計算することが出来る。  
$1$ 回の更新につきソートと加えて $\Theta ( T )$ 掛かるため、全体では $\Theta ( N \log ( N ) + T D )$ となる。

## 文献
-   [Capacitated Dynamic Programming: Faster Knapsack and Graph Algorithms](https://arxiv.org/abs/1802.06440)  
    $3.1 \  {\rm Knapsack}$ に記述がある 

## 語
#### (max,+)-convolution
[Concave Max Plus Convlution](https://noshi91.github.io/Library/library/algorithm/concave_max_plus_convolution.cpp.html)

## その他
-   アルゴリズムの名前について  
    Axiotis-Tzamos は論文の著者名から取ったが、正式な / 主流な名前は知らないため注意
    ご存知の方は教えて頂けると嬉しいです
