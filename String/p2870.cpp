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
// sa[i]表示排名为i的后缀的起始位置
// rk[i]表示起始位置为i的后缀的排名
// sa[rk[i]]=rk[sa[i]]=i
// height[i]表示排名为i的后缀和排名为i-1的后缀的最长公共前缀

const int N = 1e6 + 10;
char s[N];
int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N], height[N];
void get_SA()
{
    // int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        while (s[i] < 'A' || s[i] > 'Z')
            cin >> s[i];
        s[(n << 1) - i + 2] = s[i];
    }
    n = n * 2 + 1;
    // cout << s << '\n';
    int m = 128;
    int p = 0;
    for (int i = 1; i <= n; i++)
        cnt[rk[i] = s[i]]++;
    for (int i = 1; i <= m; i++)
        cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--)
        sa[cnt[rk[i]]--] = i;

    for (int w = 1; w < n; w <<= 1, m = p)
    { // m = p 即为值域优化
        int cur = 0;
        for (int i = n - w + 1; i <= n; i++)
            id[++cur] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w)
                id[++cur] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++)
            cnt[rk[i]]++;
        for (int i = 1; i <= m; i++)
            cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--)
            sa[cnt[rk[id[i]]]--] = id[i];
        p = 0;
        memcpy(oldrk, rk, sizeof(oldrk));
        for (int i = 1; i <= n; i++)
        {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
                rk[sa[i]] = p;
            else
                rk[sa[i]] = ++p;
        }
        if (p == n)
            break; // p = n 时无需再排序
    }
    string ans = "";
    n = (n - 1) / 2;
    // cout << n << '\n';
    int l = 1, r = n;
    while (l <= r)
    {
        if (l == r)
        {
            ans += s[l++];
            continue;
        }
        if (s[r] == s[l])
        {
            // cout << l << ' ' << 2 * (n + 1) - r << ' ' << r << '\n';
            if (rk[l] < rk[2 * (n + 1) - r])
                ans += s[l++];
            else
                ans += s[r--];
        }
        else
        {
            if (s[r] < s[l])
                ans += s[r--];
            else
                ans += s[l++];
        }
    }
    int tot = 0;
    for (auto v : ans)
    {
        cout << v;
        tot++;
        if (tot % 80 == 0)
            cout << '\n';
    }
}

void solve()
{
    get_SA();
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
    // cin >> t;
    while (t--)
    {
        solve();
    }
#ifndef ONLINE_JUDGE
    // cout << "Used " << (double)(clock() - start_time) << " ms" << endl;
#endif
    return 0;
}
