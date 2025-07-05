// #pragma GCC optimize(3, "Ofast", "inline")
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

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;
    vector<int> nxt(n + 1, 0);
    string t;
    cin >> t;
    int m = t.size();
    t = ' ' + t;
    fill(nxt.begin(), nxt.end(), 0);
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j && t[i] != t[j + 1])
            j = nxt[j];
        if (t[i] == t[j + 1])
            j++;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++)
    {
        while (j && s[i] != t[j + 1])
            j = nxt[j];
        if (s[i] == t[j + 1])
            j++;
        if (j == m)
        {
            cout << i - m + 1 << "\n";
            // j = nxt[j];
            j = nxt[j];
        }
    }
    for (int i = 1; i <= m; i++)
        cout << nxt[i] << " \n"[i == m];
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
