#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define INF 0x3f3f3f3f
#define L_INF 0x7f3f3f3f3f3f3f3f
#define db cout << "debug\n";

using namespace std;
const int Mod = 998244353;
using ll = long long;
// 莫比乌斯反演
//
const int N = 3e5 + 10;
int flg[N];
int p[N];
int mu[N];
int tot = 0;
void initmu(int n)
{
    mu[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!flg[i])
            p[++tot] = i, mu[i] = -1; // 定义
        for (int j = 1; j <= tot && i * p[j] <= n; ++j)
        {
            flg[i * p[j]] = 1;
            if (i % p[j] == 0)
            {
                mu[i * p[j]] = 0; // 平方因子
                break;
            }
            mu[i * p[j]] = -mu[i]; // 多一个因子
        }
    }
}

void solve()
{
    initmu(300000);
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a.begin() + 1, a.end());
    vector<int> cnt(300001, 0);
    vector<ll> sumk(300001, 0); // 存储与a[i] 互质的a[k]的因子的下标和，把a[k]的影响拆到因子去。
    vector<vector<int>> div(n + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j * j <= a[i]; j++)
        {
            if (a[i] % j == 0)
            {
                div[i].push_back(j);
                if (j * j != a[i])
                {
                    div[i].push_back(a[i] / j);
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (auto d : div[i])
        {
            ans += 1LL * mu[d] * cnt[d] * (i - 1);
            ans -= 1LL * mu[d] * sumk[d];
            sumk[d] += i;
            cnt[d]++;
        }
    }
    cout << ans << '\n';
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
    cout << "Used " << (double)(clock() - start_time) << " ms" << endl;
#endif
    return 0;
}
