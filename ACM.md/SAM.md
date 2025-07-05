# SAM

[https://www.luogu.com.cn/problem/P4770](https://www.luogu.com.cn/problem/P4770)

状态数<=2*n-1

转移数<=3*n-4

应用：

### 基数排序实现，siz累加出来就是该节点的endpos集合大小，sum是对应贡献(依据题目而定）

ps：基数排序比dfs更快

```c++
        vector<int> c((n + m + 1) * 2, 0);
        vector<int> cc((n + m + 1) * 2, 0);
        for (int i = 2; i < sam.size(); ++i)
            c[sam.len(i)]++;
        for (int i = 1; i < sam.size(); ++i)
            c[i] += c[i - 1];
        for (int i = 2; i < sam.size(); ++i)
            cc[c[sam.len(i)]--] = i;
        for (int i = sam.size() - 1; i >= 2; --i)
            siz[sam.link(cc[i])] = (siz[sam.link(cc[i])] + siz[cc[i]]) % M, sum[sam.link(cc[i])] = (sum[sam.link(cc[i])] + sum[cc[i]]) % M;

```

### 检查字符串是否出现

> 给一个文本串 T 和多个模式串 P ，我们要检查字符串 P 是否作为 T 的一个子串出现。
>
> ```c++
> bool is_substring(const SAM& sam, const string& query) {
>     int current = 1; // 初始状态为 1
>     for (char ch : query) {
>         int c = ch - 'a';
>         current = sam.next(current, c); // 尝试转移
>         if (current == 0) {
>             return false; // 无法转移，说明子串不存在
>         }
>     }
>     return true; // 所有字符均成功转移
> }
> ```

### 不同子串个数（本质不同）

> 给一个字符串 S ，计算不同子串的个数。
>
> 写法1:根据转移边（转移边构成DAG）跑不同路径计数（可以拓扑、DFS)
>
> ```c++
>     auto dfs = [&](auto &&self, int x) -> i64 { // 在SAM上跑dfs
>         if (ans[x])
>             return ans[x];
>         for (int i = 0; i < 26; i++)
>             if (sam.next(x, i))
>                 ans[x] += self(self, sam.next(x, i)) + 1;
>         return ans[x];
>     };
> // 也可以一开始f[i]=1,表示到每个节点各自代表一条路径。f表示恰好在i节点结束的路径数
> // ans[i]表示以i为前缀的串总和。
>    vector<ll> ans(sam.size(), 0);
>     auto dfs_yu = [&](auto &&self, int u) -> void
>     {
>         if (ans[u])
>             return;
>         ans[u] = f[u];
>         for (int j = 0; j < 26; j++)
>         {
>             if (sam.next(u, j))
>             {
>                 self(self, sam.next(u, j));
>                 ans[u] += ans[sam.next(u, j)];
>             }
>         }
>     };
>
> ```

写法2:根据link边（后缀链接树）树形dp

```c++

	auto dfs = [&](auto self, int x) -> void
    {
        f[x] = sam.len(x) - sam.len(sam.link(x));//每个节点的子串个数
        for (auto y : adj[x])
        {
            self(self, y);
            f[x] += f[y];
        }
    };

```

### 计算所有节点的endpos 大小

> 通过预处理不是复制的的点的f[u] =1，然后树形dp预处理出所有节点endpos集合的大小
>
> ```c++
>     int p = 1;
>     vector<int> x;
>     for (auto c : s)
>         x.push_back(p = sam.extend(p, c - 'a'));
>     vector<ll> f(sam.size(), 0); // 计算endpos大小
>     for (auto v : x)
>         f[v]++;
> ```
>
> ```c++
>     auto dfs = [&](auto &&self, int u) -> void
>     {
>         for (auto v : e[u])
>         {
>             self(self, v);
>             f[u] += f[v];
>         }
>     };
> ```

### 计算所有节点的endpos 是什么 （通过Set维护,但是存不下来， 需要顺便进行计算）

```c++
		vector<int> last_node;
        int last = 1;
        for (char c : s)
        {
            last = sam.extend(last, c - 'a');
            last_node.push_back(last);
        }

        int node_count = sam.size();
        vector<set<int>> sets(node_count); // 通过set 处理出SAM所有节点的出现位置, 也就是endpos 集合大小
        for (int i = 0; i < n; i++)
        {
            sets[last_node[i]].insert(i + 1);
        }
        vector<vector<int>> tree(node_count);
        for (int i = 1; i < node_count; i++)
        {
            int fa = sam.link(i);
            tree[fa].push_back(i);
        }
 	 	function<void(int)> dfs = [&](int u)
        {
            for (int v : tree[u])
            {
                dfs(v);
                if (sets[u].size() < sets[v].size())
                {
                    swap(sets[u], sets[v]);
                }
                for (int pos : sets[v])
                {
                    sets[u].insert(pos);
                }
                set<int>().swap(sets[v]); // 清空并释放内存
            }
            // ---------------计算-----------------
        };
```

‍

### 所有不同子串的总长度

> 给定一个字符串 S ，计算所有不同子串的总长度。
>
> 本题做法与上一题类似，只是现在我们需要考虑分两部分进行动态规划：不同子串的数量 d_v 和它们的总长度 ans_v 。
>
> 我们已经在上一题中介绍了如何计算 d_v 。 ans_v 的值可以通过以下递推式计算：
>
> $$
> ans_u=∑d_v+ans_v
> $$
>
> ‍
>
> 我们取每个邻接结点 w 的答案，并加上 dw （因为从状态 v 出发的子串都增加了一个字符）。
>
> 算法的时间复杂度仍然是 O(∣S∣) 。

### 

### 字典序第 k 大子串

> 给定一个字符串 S 。多组询问，每组询问给定一个数 Ki ，查询 S 的所有子串中字典序第 Ki 大的子串。
>
> 解决这个问题的思路可以从解决前两个问题的思路发展而来。字典序第 k 大的子串对应于 SAM 中字典序第 k 大的路径，因此在计算每个状态的路径数后，我们可以很容易地从 SAM 的根开始找到第 k 大的路径。
>
> $$
> ans_u=\sum ans_v +f_u
> $$
>
> 预处理的时间复杂度为 O(∣S∣) ，单次查询的复杂度为 O(∣ans∣⋅∣Σ∣) （其中 ans 是查询的答案， ∣Σ∣ 为字符集的大小）。
>
> ans的预处理要在DAG上跑dfs或者是拓扑
>
> ```c++
>     vector<ll> ans(sam.size(), 0);
>     auto dfs_yu = [&](auto &&self, int u) -> void
>     {
>         if (ans[u])
>             return;
>         ans[u] = f[u];
>         for (int j = 0; j < 26; j++)
>         {
>             if (sam.next(u, j))
>             {
>                 self(self, sam.next(u, j));
>                 ans[u] += ans[sam.next(u, j)];
>             }
>         }
>     };
> ```
>
> ```c++
>     //f[u] 是恰好在u节点停止的个数，ans[u]是以u节点作为前缀字符串的总共个数
> 	//如果是本质不同的子串那么f[u]=1（u!=1)
> 	//如果是本质可以相同的子串那么f[u] = |ebdpos[u]| 计算方法参考上面
> 	auto dfs_k = [&](auto &&self, int u, int y) -> void
>     {
>         if (y <= f[u])
>             return;
>         y -= f[u];
>         for (int i = 0; i < 26; i++)
>         {
>             int v = sam.next(u, i);
>             if (!v)
>                 continue;
>             if (y > ans[v])
>             {
>                 y -= ans[v];
>                 continue;
>             }
>             cout << char(i + 'a');
>             self(self, sam.next(u, i), y);
>             return;
>         }
>     };
>     dfs_k(dfs_k, 1, k);
> ```

### 最小循环移位

> 给定一个字符串 S 。找出字典序最小的循环移位。
>
> 容易发现字符串 S+S 包含字符串 S 的所有循环移位作为子串。
>
> 所以问题简化为在 S+S 对应的后缀自动机上寻找最小的长度为 ∣S∣ 的路径，这可以通过平凡的方法做到：我们从初始状态开始，贪心地访问最小的字符即可。
>
> 总的时间复杂度为 O(∣S∣) 。

### 出现次数（对应的endpos集合大小 = cnt)

> 对于一个给定的文本串 T ，有多组询问，每组询问给一个模式串 P ，回答模式串 P 在字符串 T 中作为子串出现了多少次。
>
> 预处理 cntv ，如果它不是通过复制创建的（且它不是初始状态 1），我们将它的 cnt 初始化为 1。
>
> 在后缀链接树上进行树形dp
>
> $$
> cnt_{link_u}+=cnt_u
> $$

### 第一次出现的位置

> 给定一个文本串 T ，多组查询。每次查询字符串 P 在字符串 T 中第一次出现的位置（ P 的开头位置）。
>
> 要重新维护一属性为first_pos，作为该节点（子串）最早的出现位置，全代码参考SAM_FIRST

### 所有出现的位置

> 问题同上，这一次需要查询文本串 T 中模式串出现的所有位置。
>
> 全代码参考SAM_SECOND

### 最短的没有出现的字符串

> 给定一个字符串 S 和一个特定的字符集，我们要找一个长度最短的没有在 S 中出现过的字符串。
>
> 设 dp_u表示到点 u时的最短长度
>
> 如果这个点有不是S中字符的出边 dp_u=1,否则 dp_u=1+min{dp_v}

### 两个字符串的最长公共子串

> 给定两个字符串 S 和 T ，求出最长公共子串，公共子串定义为在 S 和 T 中都作为子串出现过的字符串 X
>
> 直接把T扔到S 的自动机上跑匹配就行了

### 多个字符串间的最长公共子串

> 给定 k 个字符串 Si 。我们需要找到它们的最长公共子串，即作为子串出现在每个字符串中的字符串 X 。
>
> 可以SA

### 多个字符串间的本质不同的子串

> 建立伪广义SAM,每次清空初始位置指针
>
> ```c++
>     for (int i = 0; i < n; i++)
>     {
>         std::string s;
>         std::cin >> s;
>         int p = 1; // 清空
>         for (auto c : s)
>             p = sam.extend(p, c - 'a');
>     }
>     i64 ans = 0;
>     for (int i = 2; i < sam.size(); i++)
>         ans += sam.len(i) - sam.len(sam.link(i));
>     std::cout << ans << "\n";
> ```

‍
