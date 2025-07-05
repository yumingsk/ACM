#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define INF 0x3f3f3f3f
#define L_INF 0x7f3f3f3f3f3f3f3f
#define db cout << "debug\n";

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int Mod = 998244353;
using ll = long long;
// sa[i]表示排名为i的后缀的起始位置
// rk[i]表示起始位置为i的后缀的排名
// sa[rk[i]]=rk[sa[i]]=i
// height[i]表示排名为i的后缀和排名为i-1的后缀的最长公共前缀
class SuffixArray
{
public:
    string s; // 输入的字符串
    int n;    // 字符串长度
    vector<int> sa, rk, oldrk, id, cnt, height;
    const int N = 1e6 + 10;
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

void solve()
{
    string s;
    cin >> s;
    SuffixArray SA(s);
    SA.buildSA();
    s = ' ' + s;
    int maxx = *max_element(SA.height.begin(), SA.height.end());
    if (maxx == 0)
    {
        cout << "No repetitions found!" << '\n';
        return;
    }
    int cur = 0;
    for (int i = 1; i < SA.height.size(); i++)
        if (SA.height[i] == maxx)
        {
            for (int j = 0; j < maxx; j++)
                cout << s[SA.sa[i] + j];
            cur = i;
            break;
        }
    cout << ' ';
    int ret = 0;
    for (int i = cur; i < SA.height.size(); i++)
        if (SA.height[i] == maxx)
            ret++;
        else
            break;
    cout << ret + 1 << '\n';
}
int main()
{
    IOS;
// freopen("in.txt", "r", stdin);
// freopen("out.txt", "w", stdout);
#ifndef ONLINE_JUDGE
    clock_t start_time = clock();
#endif
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifndef ONLINE_JUDGE
// cout << "Used " << (double)(clock() - start_time) << " ms" << endl;
#endif
    return 0;
}
