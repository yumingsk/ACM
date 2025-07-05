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
const int N = 2e5 * 32 + 10;
struct node
{
    int ch[2];
    int sum;
} tr[N];
int rt[N];
const int M = 30;
int tot = 0;

void insert(int &p, int t, const int x)
{
    tr[++tot] = tr[p];
    p = tot;
    ++tr[p].sum;
    if (t < 0)
        return;
    int v = (x >> t) & 1;
    insert(tr[p].ch[v], t - 1, x);
}
int query(int lp, int rp, int x)
{
    int res = 0;
    for (int k = 30; k >= 0; k--)
    {
        int qw = ((x >> k) & 1) ^ 1;
        if (tr[tr[rp].ch[qw]].sum - tr[tr[lp].ch[qw]].sum > 0)
        {
            res |= (1 << k);
            if (rp != 0)
                rp = tr[rp].ch[qw];
            if (lp != 0)
                lp = tr[lp].ch[qw];
        }
        else
        {
            if (rp != 0)
                rp = tr[rp].ch[qw ^ 1];
            if (lp != 0)
                lp = tr[lp].ch[qw ^ 1];
        }
    }
    return res;
}
void solve()
{
    tot = 0;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        rt[i] = rt[i - 1];
        insert(rt[i], M, x);
    }
    while (q--)
    {
        int l, r, x;
        cin >> l >> r >> x;
        cout << query(rt[l - 1], rt[r], x) << "\n";
    }
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
