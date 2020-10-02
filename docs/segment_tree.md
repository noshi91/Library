## Operations

モノイド$M$の列$(a_1, a_2, \dots, a_n)$を扱う.
空間計算量$\Theta(n)$

-   $\mathtt{new}()$
    -   列の項がすべて$M$の単位元であるSegment Treeを作成する.
    -   時間計算量[$ \Theta(n)$]
-   $\mathtt{build}(a_1, a_2, \dots, a_n)$
    -   与えられた列を表現するSegment Treeを作成する.
    -   時間計算量$\Theta(n)$
-   $\mathtt{set}(i, x)$
    -   $a_i$に$x$を代入する.
    -   時間計算量$O(\log n)$
-   $\mathtt{fold}(l, r)$
    -   $a_l \cdot a_{l+1} \cdot \dots \cdot a_r$を計算する.
    -   時間計算量$O(\log n)$
