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
// https://codeforces.com/contest/1972/problem/D2
// https://www.luogu.com.cn/problem/CF1967B2
// 给你两个正整数 n,m <=2e6
// 计算满足以下条件的有序数对 (a,b)
// 的个数：1≤a≤n, 1≤b≤m  b⋅gcd(a,b)是 a+b的倍数
void solve()
{
    int n, m;
    cin >> n >> m;
    ll ans = 0;
    for (int i = 1; i <= sqrt(n); i++)
    {
        for (int j = 1; j <= sqrt(m); j++)
        {
            if (__gcd(i, j) != 1)
                continue;
            // cout << i << ' ' << j << '\n ';
            // cout << __gcd(i, j) << '\n';
            int maxx = min(n / i, m / j);
            ans += maxx / (i + j);
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
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifndef ONLINE_JUDGE
    cout << "Used " << (double)(clock() - start_time) << " ms" << endl;
#endif
    return 0;
}
