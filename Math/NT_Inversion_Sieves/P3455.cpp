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

const int N = 5e4 + 10;
int primes[N];
int st[N];
int mu[N];
int cnt = 0;
int pre_mu[N];
void get_prime(int n)
{
    mu[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
            primes[cnt++] = i, mu[i] = -1;
        for (int j = 0; j < cnt && primes[j] * i <= n; j++)
        {
            st[i * primes[j]] = 1;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
            mu[i * primes[j]] = -mu[i];
        }
    }
    // for (int i = 0; i < cnt; i++)
    //     cout << primes[i] << " \n"[i == cnt - 1];
    for (int i = 1; i <= n; i++)
    {
        // cout << mu[i] << " \n"[i == n];
        pre_mu[i] = pre_mu[i - 1] + mu[i];
    }
}
ll f(int n, int m)
{
    // cout << n << ' ' << m << '\n';
    ll res = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1)
    {
        r = min(n / (n / l), m / (m / l));
        r = min({r, n, m});
        // cout << r << ' ' << n / l << ' ' << m / l << '\n';
        res += 1LL * (pre_mu[r] - pre_mu[l - 1]) * (n / l) * (m / l);
    }
    return res;
}
void solve()
{
    int a, b, k;
    cin >> a >> b >> k;
    cout << f(a / k, b / k) << '\n';
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
    get_prime(N - 1);
    while (t--)
    {
        solve();
    }
#ifndef ONLINE_JUDGE
// cout << "Used " << (double)(clock() - start_time) << " ms" << endl;
#endif
    return 0;
}
