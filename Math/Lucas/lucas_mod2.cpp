#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define INF 0x3f3f3f3f
#define L_INF 0x7f3f3f3f3f3f3f3f
#define db cout << "debug\n";
#define int long long
using namespace std;
const int Mod = 998244353;
using ll = long long;
const int MAX = 1e6 + 5;
const int MOD = 1e9 + 7;
// lucas定理
// 求C(m,n) % p
// 预处理逆元
int inv[MAX];
void load_inv(int n)
{
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
}

// 预处理阶乘
int fac[MAX];
void load_fac(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % MOD;
}

// 预处理阶乘的逆元
int ifc[MAX];
void load_ifc(int n)
{
    ifc[0] = 1;
    for (int i = 1; i <= n; i++)
        ifc[i] = ifc[i - 1] * inv[i] % MOD;
}
void init(int n)
{
    load_inv(n);
    load_fac(n);
    load_ifc(n);
}
// 询问排列数与组合数
int A(int m, int n) { return 0 <= n and n <= m ? fac[m] * ifc[m - n] % MOD : 0; }
int C(int m, int n) { return 0 <= n and n <= m ? fac[m] * ifc[n] % MOD * ifc[m - n] % MOD : 0; }
inline ll lucas(ll m, ll n, ll p)
{
    if (m == 0)
        return 1;
    return lucas(m / p, n / p, p) % p * C(m % p, n % p) % p;
}
void solve()
{
    int n;
    int k;
    cin >> n >> k;
    init(1000000);
    cout << C(4, 2) * C(8, 4) << endl;
    for (int i = 0; i < n; i++)
    {
        if (lucas(n - 1, i, 2) == 1)
            cout << k << ' ';
        else
            cout << 0 << ' ';
    }
    cout << "\n";
}
signed main()
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
