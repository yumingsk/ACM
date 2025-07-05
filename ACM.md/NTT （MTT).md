# NTT （MTT) 

$$
C_k=\sum_{i+j=k}A_i*B_j
$$

$$
C_k=\sum_{(i+j)\%n=k}A_i*B_j
$$

对于形式2的NTT结果存在平移性质：

$$
(1,0,1,1)^{n} 和(1,1,0,1)^{n} \newline
$$

在k=4的情况下的NTT结果是符合循环位移的也就是后者的结果是前者结果的左移n%k*（dis(两个0的位置差)）

‍

原根转化乘为加

预处理质数的原根

```c++
int get_minimum_primitive_root(int m)
{
    int phiM = phi(m);
    for (int i = 1;; ++i)
    {
        if (__gcd(i, m) != 1)
            continue;
        auto factors = get_factors(phiM);
        bool ok = true;
        for (auto e : factors)
            if (e != phiM && qpow(i, e, m) == 1)
            {
                ok = false;
                break;
            }
        if (ok)
            return i;
    }
}
```

$$
g^{val_x} =x (mod \space p)
$$

```c++
    static int val[MAXN];
    val[0] = -1; // x->l(x);   p=7 g=3 为例
    //  0   2   1   4   5   3    0
    //  g^0 g^2 g^1 g^4 g^5 g^3 |g^6	
    //  1   2   3   4   5   6   |7  这里开始循环
    for (int i = 0, j = 1; i < p - 1; ++i)
    {
        val[j] = i;
        j = (ll)j * g % p;
    }
```
