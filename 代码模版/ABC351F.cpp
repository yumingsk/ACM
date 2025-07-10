#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define INF 0x3f3f3f3f
#define db cout << "debug\n";

using namespace std;
const int Mod = 998244353;
using ll = long long;
const int N = 1e6 + 10;
int s[N * 4];
int a[N];
// 线段树查询区间范围内有多少个小于给定数字的个数
void build(int k, int l, int r)
{
    if (l == r)
    {
        s[k] = 0;
        return;
    }
    int mid = l + r >> 1;
    build(k << 1, l, mid);
    build(k << 1, mid + 1, r);
    s[k] = max(s[k << 1 | 1], s[k << 1]);
}
void update(int k, int l, int r, int p, int c)
{
    if (p < r || p > l)
        return;
    if (l == r && l == p)
    {
        s[p] = c;
        return;
    }
    int mid = l + r >> 1;
    update(k << 1, l, mid, p, c);
    update(k << 1 | 1, mid + 1, r, p, c);
    s[k] = max(s[k << 1], s[k << 1 | 1]);
}
int query(int k, int l, int r, int x, int y, int c)
{
    if (y < l || x > r)
        return 0;
    if (x <= l && r <= y)
    {
        if (s[k] <= c)
        {
            return (r - l + 1);
        }
        else
        {
            int mid = l + r >> 1;
            return (query(k << 1, l, mid, x, y, c) + query(k << 1 | 1, mid + 1, r, x, y, c));
        }
    }
    int mid = l + r >> 1;
    return (query(k << 1, l, mid, x, y, c) + query(k << 1 | 1, mid + 1, r, x, y, c));
}
void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        a[i] = {x, i};
    }
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    ll pre = 0;
    for (int i = 1; i <= n; i++)
    {
        int pos = a[i].second;
        int num = a[i].first;
        update(1, 1, n, pos, num);
        ans += 1LL * query(1, 1, n, 1, pos - 1, num) * num - pre;
        //  cout << query(1, 1, n, 1, pos - 1, num) << '\n';
        pre += num;
    }
    cout << ans << '\n';
}
int main()
{
    IOS;
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
