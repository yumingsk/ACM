# 动态dp

## 广义矩阵乘法

$$
C_{i,j}=\max{A_{i,k}+B_{k,j}}
$$

$$
\begin{pmatrix}
   a & b \\
  
    c & d
\end{pmatrix}
\begin{pmatrix}
   e   \\
   f
\end{pmatrix} = 
\begin{pmatrix}
   \max{(a+e,b+f)}  \\
  \max{(c+e,d+f)}
\end{pmatrix}
$$

## 矩阵乘法

$$
C_{i,j} = \sum A_{i,k}*B_{k,j}

\\
\begin{pmatrix}
   a & b \\
  
    c & d
\end{pmatrix}
\begin{pmatrix}
   e   \\
   f
\end{pmatrix} = 
\begin{pmatrix}
   ae+bf  \\
  ce+df
\end{pmatrix}
$$

‍

‍
