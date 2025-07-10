#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define INF 0x3f3f3f3f
#define db cout << "debug\n";

using namespace std;
const int Mod = 998244353;
using ll = long long;
int Next_ACCEPT[6] = {1, 3, 3, 5, 16, 20};
int Next_WA[2] = {23, 1};

void solve()
{
    ll ans = 0;
    int n, k;
    cin >> n >> k;
    vector<char> s(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    vector<vector<int>> f(n + 2, vector<int>(27, -1));
    // 序列自动机 维护第i个位置右边出现字符j的第一个位置
    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= 26; j++)
        {
            f[i][j] = f[i + 1][j];
        }
        f[i][s[i] - 64] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        int t1 = i;
        for (int j = 0; j < 6; j++)
        {
            if (j == 2 && s[t1] == 'C')
                t1 = f[t1 + 1][Next_ACCEPT[j]];
            else
                t1 = f[t1][Next_ACCEPT[j]];
            if (t1 == -1)
                break;
        }

        if (t1 == -1)
            continue;
        int t2 = i;
        for (int j = 0; j < 2; j++)
        {
            t2 = f[t2][Next_WA[j]];
            if (t2 == -1)
                break;
        }
        if (t2 != -1 && t2 <= t1)
            continue;
        if (t2 == -1)
        {
            if (i + k - 1 > n)
                continue;
            else
            {
                ans = ans + n - max(i + k - 1, t1) + 1;
            }
        }
        else
        {
            if (i + k - 1 >= t2)
                continue;
            else
            {
                ans = ans + t2 - max(t1, i + k - 1);
            }
        }
    }
    cout << ans << '\n';
}
int main()
{
    IOS;
    int t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
    return 0;
}
