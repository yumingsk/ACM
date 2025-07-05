# FHQ Treap

	题单：[https://www.luogu.com.cn/training/147262#problems](https://www.luogu.com.cn/training/147262#problems)

首先要阐述一点，Fhq Treap的**按大小分裂是支持区间操作的**，而**按值分裂**是**不支持区间操作**的。

## 以下数据结构的默认为小根堆

### 共同操作

#### 数组定义

$$
siz[N],A[N][2],val[N],key[N]
$$

```c++
int add(int v)
{
    siz[++tot] = 1;		//siz是大小
    val[tot] = v;		// val是数值
    key[tot] = rng();	// key是随机的数字保证优先级
    return tot;
}
//================================================
void pushup(int now)
{
    siz[now] = 1 + siz[A[now][0]] + siz[A[now][1]];
}
//================================================
int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (key[x] < key[y])
    { // 小根堆
        A[x][1] = merge(A[x][1], y);
        pushup(x);
        return x;
    }
    else
    {
        A[y][0] = merge(x, A[y][0]); // 不能写反
        pushup(y);
        return y;
    }
}
//================================================
```

### 按值分裂（不支持区间修改）

```c++
void split(int now, int k, int &x, int &y)// 按值分裂 小于等于k的放在树x ， 大于k的放在树y
{
    if (!now)
        x = y = 0; // 如果now不存在，不用分
    else
    {
        if (val[now] <= k)// 当前权值<=k
        { 
            x = now;//当前点全部给now 然后
            split(A[now][1], k, A[now][1], y);// 注意传参顺序
        }
        else
        {
            y = now; // 把当前节点归入y
            split(A[now][0], k, x, A[now][0]);
        }
        pushup(now);
    }
}
//============================查询第k小==================================
int kth(int now, int k)
{
    while (1)
    {
        if (k <= siz[A[now][0]])
            now = A[now][0];
        else if (k == siz[A[now][0]] + 1)
            return now;
        else
            k -= siz[A[now][0]] + 1, now = A[now][1];
    }
}
```

### 按大小分裂（支持区间修改，比如区间翻转）

```c++
void split(int now, int k, int &x, int &y)
{
    if (!now)
        x = y = 0;
    else
    {
        pushdown(now);
        if (siz[A[now][0]] < k) // 左儿子的树大小小于k了说明左边全部是在需要的区间内
        {
            x = now;
            split(A[now][1], k - siz[A[now][0]] - 1, A[now][1], y);//注意传参数据，和顺序
        }
        else
        {
            // 左边已经够了，右边全部保留，从左边割下来
            y = now;
            split(A[now][0], k, x, A[now][0]);
        }
        pushup(now);
    }
}
```

### 主函数操作：

#### 按值分裂的加点

```c++
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        split(root, a, x, y);
        root = merge(merge(x, add(a)), y);
    }
```

#### 按大小分裂的加点（不需要先split）

```c++
for (int i = 1; i <= n; i++)
{
        root = merge(root, add(i));
}
//=================需不需要一开始全部合并看题意=====================
//===比如银河英雄传说P4847 就不需要一开始合并， 一开始有n个节点的 n颗树
for (int i = 1; i <= n; i++)
{
       add(i);
}
```

#### 按值分裂:

```c++
// 删除一个节点（价值为a)
split(root, a, x, z);         // 先按照要删除的值a分成两棵树，小于等于a的放在x里面，大于a的放在z里面
split(x, a - 1, x, y);        // 在把x重新分一下，小于a的放在x里面，刚好等于a的就在y里面
y = merge(A[y][0], A[y][1]);  // 因为只用删除一个，就把根节点扔掉，合并一下其左儿子和右儿子
root = merge(merge(x, y), z); // 把x，y，z合并起来

// 查询a的排名
split(root, a - 1, x, y); // 先按照a-1分成两棵树，这样小于a的就在x里面，所以x+1就是a
lst = siz[x] + 1;
// cout << siz[x] + 1 << '\n'; // 所以a的值的排名就是x的排名加一
root = merge(x, y); // 最后就把之前拆开的合并一下就行了。

//整个树的第 "a"小的值
val[kth(root, a)];

//查找 a的前驱
split(root, a - 1, x, y); // 先按照a-1分成两棵树，这样小于a的就在x里面，因为x是里面最大的，所以x代表的值就是我们要找的答案
lst = val[kth(x, siz[x])];
ans ^= lst;
// cout << val[kth(x, siz[x])] << '\n'; // 用这个函数找一下原本的点的编号，因为之前建树的时候是重新排的编号
root = merge(x, y); // 不要忘记最后的合并

//查找 a的后继
split(root, a, x, y); // 按照a分成两棵树，这样大于a的就在y里面，因为y是里面最小的，所以y所代表的值就是我们要找的答案
lst = val[kth(y, 1)];
ans ^= lst;
// cout << val[kth(y, 1)] << '\n'; // 用这个函数找一下原本的点的编号，因为之前建树的时候是重新排的编号
root = merge(x, y); // 不要忘记最后的合并
```

### FHQ的可持久化

在可持久化的思想上，每次是对过去的版本进行修改，但是由于split的原因不加已修改会修改原树，所有需要在split的时候新建节点去实现可持久化，merge新建节点可写可不写

每次split(rt[i],x,x,x)其实不会改变rt[i] 也就是不需要merge

#### Split的实现参考（按值分裂）

```c++
void fuzhi(int x, int y)
{
    siz[x] = siz[y];
    val[x] = val[y];
    cnt[x] = cnt[y];
    key[x] = key[y];
    A[x][1] = A[y][1];
    A[x][0] = A[y][0];
}
//=============================================================
void split(int now, int k, int &x, int &y)
{
    if (!now)
        x = y = 0;
    else
    {
        if (val[now] <= k)
        {
            x = ++tot;
            fuzhi(x, now);
            split(A[now][1], k, A[x][1], y); // 注意传参，now是原树，需要修改的是新节点所在的树x，原树里继续递归找到需要的部分在x树上修改对应关系。
            pushup(x);
        }
        else
        {
            y = ++tot;
            fuzhi(y, now);
            split(A[now][0], k, x, A[y][0]);
            pushup(y);
        }
    }
}
```

#### Merge的实现参考（按值分裂）

```c++
int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (key[x] < key[y])
    {
        int p = ++tot;
        fuzhi(p, x);
        A[p][1] = merge(A[p][1], y);
        pushup(p);
        return p;
    }
    else
    {
        int p = ++tot;
        fuzhi(p, y);
        A[p][0] = merge(x, A[p][0]);
        pushup(p);
        return p;
    }
}
```

###
