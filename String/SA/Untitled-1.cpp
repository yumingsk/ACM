#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define INF 0x3f3f3f3f
#define L_INF 0x7f3f3f3f3f3f3f3f
#define db cout << "debug\n";

using namespace std;
const int Mod = 1e9 + 7;

using ll = long long;

ll qpow(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % Mod;
        a = a * a % Mod;
        b /= 2;
    }
    return res;
}
void solve()
{
    // cout << qpow(2, Mod - 2) * 3 % Mod + 1 << '\n';
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = ' ' + s;
    vector<int> f(n + 2, 0);
    for (int i = n; i >= 1; i--)
    {
        if (s[i] == '1')
            f[i] = (f[i + 1] + 1LL * qpow(2, Mod - 2) * (1 - f[i + 1] + Mod) % Mod) % Mod;
        else
            f[i] = qpow(2, Mod - 2) * f[i + 1] % Mod;
    }
    // cout << (qpow(4, Mod - 2) * 5 % Mod) << '\n';
    // cout << f[1] << '\n';
    // cout << (n - 1 + f[2]) % Mod << '\n';
    cout << ((1LL - f[2] + Mod) % Mod * (n - 1) % Mod + 1LL * f[2] * n % Mod) % Mod << '\n';
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
