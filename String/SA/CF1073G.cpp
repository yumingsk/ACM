// #pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define INF 0x3f3f3f3f
#define L_INF 0x7f3f3f3f3f3f3f3f
#define db cout << "debug\n";

using namespace std;
const int Mod = 998244353;
using ll = long long;
#define int long long
// sa[i]表示排名为i的后缀的起始位置
// rk[i]表示起始位置为i的后缀的排名
// sa[rk[i]]=rk[sa[i]]=i
// height[i]表示排名为i的后缀和排名为i-1的后缀的最长公共前缀
// https://codeforces.com/contest/1073/problem/G
class SuffixArray
{
public:
    string s; // 输入的字符串
    int n;    // 字符串长度
    vector<int> sa, rk, oldrk, id, cnt, height;
    const int N = 2e5 + 10;
    SuffixArray(const string &str)
    {
        s = " " + str; // 加上一个虚拟的前缀字符，使字符串从1开始
        n = s.size() - 1;
        sa.resize(n + 1);
        rk.resize(n * 2 + 1);
        oldrk.resize(n * 2 + 1);
        id.resize(n + 1);
        cnt.resize(N + 1); // 值域
        height.resize(n + 1);
    }
    void buildSA() // 构建后缀数组
    {
        int m = 128; // 字符集的大小（可以根据输入字符集调整）
        int p = 0;
        // 初始rk和sa
        for (int i = 1; i <= n; ++i)
            cnt[rk[i] = s[i]]++;
        for (int i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i)
            sa[cnt[rk[i]]--] = i;
        for (int w = 1;; w <<= 1, m = p)
        {
            int cur = 0;
            for (int i = n - w + 1; i <= n; ++i)
                id[++cur] = i;
            for (int i = 1; i <= n; ++i)
                if (sa[i] > w)
                    id[++cur] = sa[i] - w;
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 1; i <= n; ++i)
                cnt[rk[i]]++;
            for (int i = 1; i <= m; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; --i)
                sa[cnt[rk[id[i]]]--] = id[i];
            p = 0;
            memcpy(oldrk.data(), rk.data(), sizeof(int) * (n * 2 + 1));
            for (int i = 1; i <= n; ++i)
            {
                if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
                    rk[sa[i]] = p;
                else
                    rk[sa[i]] = ++p;
            }
            if (p == n)
                break; // 排序完毕
        }
        for (int i = 1, k = 0; i <= n; ++i) // 构建LCP数组
        {
            if (rk[i] == 0)
                continue;
            if (k)
                --k;
            while (s[i + k] == s[sa[rk[i] - 1] + k])
                ++k;
            height[rk[i]] = k;
        }
    }
};
const int N = 2e5 + 10;
int ST[N][20];
int n;
int tmpa[N];
void init_ST()
{
    for (int i = 1; i <= n; i++)
        ST[i][0] = tmpa[i];
    for (int j = 1; j <= 19; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            ST[i][j] = min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
}
int ST_query(int l, int r)
{
    int k = log2(r - l + 1);
    return min(ST[l][k], ST[r - (1 << k) + 1][k]);
}
int vis[N * 4];
ll s[N * 4];
int maxx[N * 4];
void pushup(int k)
{
    s[k] = s[k << 1] + s[k << 1 | 1];
    maxx[k] = max(maxx[k << 1], maxx[k << 1 | 1]);
}
void build(int k, int l, int r)
{
    if (l == r)
    {
        s[k] = 0;
        vis[k] = -1;
        maxx[k] = 0;
        return;
    }
    int mid = l + r >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
}
void pushdown(int k, int l, int r)
{
    if (vis[k] != -1)
    {
        int mid = l + r >> 1;
        int tmp = vis[k];
        vis[k << 1] = tmp;
        vis[k << 1 | 1] = tmp;
        maxx[k << 1] = tmp;
        maxx[k << 1 | 1] = tmp;
        s[k << 1] = 1LL * (mid - l + 1) * tmp;
        s[k << 1 | 1] = 1LL * (r - mid) * tmp;
        vis[k] = -1;
    }
}
int TEST = 0;
void update(int k, int l, int r, int x, int y, int v)
{

    if (y < l || x > r)
        return;
    // if (TEST)
    // {
    //     db;
    //     cout << k << " " << l << ' ' << r << ' ' << x << ' ' << y << ' ' << v << '\n';
    // }
    if (x <= l && r <= y)
    {
        vis[k] = v;
        s[k] = v * (r - l + 1);
        maxx[k] = v;
        return;
    }
    pushdown(k, l, r);
    int mid = l + r >> 1;
    update(k << 1, l, mid, x, y, v);
    update(k << 1 | 1, mid + 1, r, x, y, v);
    pushup(k);
}
ll querysum(int k, int l, int r, int x, int y)
{
    if (y < l || r < x)
        return 0;
    if (x <= l && r <= y)
    {
        return s[k];
    }
    int mid = l + r >> 1;
    pushdown(k, l, r);
    return querysum(k << 1, l, mid, x, y) + querysum(k << 1 | 1, mid + 1, r, x, y);
}
int querymax(int k, int l, int r, int x, int y)
{
    if (y < l || r < x)
        return 0;
    if (x <= l && r <= y)
    {
        return maxx[k];
    }
    int mid = l + r >> 1;
    pushdown(k, l, r);
    // pushup(k);
    return max(querymax(k << 1, l, mid, x, y), querymax(k << 1 | 1, mid + 1, r, x, y));
}
// 找区间中最左边的大于等于v的位置
int findl(int k, int l, int r, int x, int y, int v)
{
    if (l == r)
        return l;
    pushdown(k, l, r);
    int mid = l + r >> 1;
    if (maxx[k << 1] >= v)
        return findl(k << 1, l, mid, x, y, v);
    else
        return findl(k << 1 | 1, mid + 1, r, x, y, v);
}
// 找区间中最右边的大于等于v的位置
int findr(int k, int l, int r, int x, int y, int v)
{
    if (l == r)
        return l;
    pushdown(k, l, r);
    int mid = l + r >> 1;
    if (maxx[k << 1 | 1] >= v)
        return findr(k << 1 | 1, mid + 1, r, x, y, v);
    else
        return findr(k << 1, l, mid, x, y, v);
}
void solve()
{
    int m;
    cin >> n >> m;
    string str;
    cin >> str;
    SuffixArray SA(str);
    SA.buildSA();
    vector<int> height = SA.height;
    vector<int> rk = SA.rk;
    for (int i = 1; i <= n; i++)
        tmpa[i] = height[i];
    init_ST();
    build(1, 1, n);
    while (m--)
    {
        int siza, sizb;
        cin >> siza >> sizb;
        vector<int> A(siza + 1, 0);
        vector<int> B(sizb + 1, 0);
        for (int i = 1; i <= siza; i++)
            cin >> A[i];
        for (int i = 1; i <= sizb; i++)
            cin >> B[i];
        sort(A.begin() + 1, A.end(), [&](int i, int j)
             { return rk[i] < rk[j]; });
        sort(B.begin() + 1, B.end(), [&](int i, int j)
             { return rk[i] < rk[j]; });
        auto getHeight_min = [&](int posA, int posB)
        {
            if (posA == posB)
                return n - posA + 1;
            return ST_query(rk[posA] + 1, rk[posB]);
        };
        ll ANS = 0;
        {
            update(1, 1, n, 1, n, 0);
            int cura = 0;
            for (int i = 1; i <= sizb; i++)
            {
                if (cura != 0 && i != 1)
                {
                    int add_min = getHeight_min(B[i - 1], B[i]);
                    if (querymax(1, 1, n, 1, cura) >= add_min)
                    {
                        int pos = findl(1, 1, n, 1, cura, add_min);
                        update(1, 1, n, pos, cura, add_min);
                    }
                }
                while (cura + 1 <= siza && rk[A[cura + 1]] <= rk[B[i]])
                {
                    cura++;
                    update(1, 1, n, cura, cura, getHeight_min(A[cura], B[i]));
                }
                ANS += s[1];
            }
        }
        {
            update(1, 1, n, 1, n, 0);
            int cura = siza + 1;
            for (int i = sizb; i >= 1; i--)
            {
                if (cura != siza + 1 && i != sizb)
                {
                    int add_min = getHeight_min(B[i], B[i + 1]);
                    if (querymax(1, 1, n, cura, siza) > add_min)
                    {
                        int pos = findr(1, 1, n, cura, siza, add_min);
                        update(1, 1, n, cura, pos, add_min);
                    }
                }
                while (cura - 1 >= 1 && rk[A[cura - 1]] > rk[B[i]])
                {
                    cura--;
                    update(1, 1, n, cura, cura, getHeight_min(B[i], A[cura]));
                }
                ANS += s[1];
            }
        }
        cout << ANS << '\n';
    }
}
signed main()
{
    // IOS;
    int t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }

    return 0;
}
