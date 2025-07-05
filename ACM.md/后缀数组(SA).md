# 后缀数组(SA)

$$
sa[i] 表示排名为i的后缀的起始位置 \newline
 rk[i]表示起始位置为i的后缀的排名\newline
 sa[rk[i]]=rk[sa[i]]=i\newline
 height[i]表示排名为i的后缀和排名为i-1的后缀的最长公共前缀
$$

$$
height[i]=lcp(suf(sa[i-1]),suf(sa[i)))
$$

$$
令l=rk[i]，r=rk[i-1]\newline
有：height[l]>=height[r]-1\newline
   height[rk[i]]>=height[rk[i-1]]-1
$$

‍
