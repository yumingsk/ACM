#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define INF 0x3f3f3f3f
#define db cout << "debug\n";

using namespace std;
const int Mod = 998244353;
using ll = long long;
const int N = 200005;
vector<ll> P[5];
// 旋转坐标平面 45 转化距离为曼哈顿距离  U= x+y V=x-y
void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        if ((x + y) % 2 == 0)
        {
            P[0].push_back(x + y);
            P[1].push_back(x - y);
        }
        else
        {
            P[2].push_back(x + y);
            P[3].push_back(x - y);
        }
    }
    ll pre = 0;
    ll ans = 0;
    for (int i = 0; i < 4; i++)
    {
        sort(P[i].begin(), P[i].end());
        int len = P[i].size();
        if (len)
            pre = P[i][0];
        for (int j = 1; j < len; j++)
        {
            ans += j * P[i][j] - pre;
            pre += P[i][j];
        }
    }
    cout << ans / 2 << '\n';
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
