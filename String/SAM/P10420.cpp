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
struct SAM
{
    static constexpr int ALPHABET_SIZE = 26;
    struct Node
    {
        int len;
        int link;
        std::array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, next{} {}
    };
    std::vector<Node> t;
    SAM()
    {
        init();
    }
    void init()
    {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c)
    {
        if (t[p].next[c])
        {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1)
            {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next[c] == q)
            {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c])
        {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
    int next(int p, int x)
    {
        return t[p].next[x];
    }
    int link(int p)
    {
        return t[p].link;
    }
    int len(int p)
    {
        return t[p].len;
    }
    int size()
    {
        return t.size();
    }
};

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    SAM sam;
    vector<int> x;
    int p = 1;
    for (auto v : s)
    {
        x.push_back(p = sam.extend(p, v - 'a'));
    }
    vector<int> f(sam.size(), 0);
    for (auto v : x)
        f[v]++;
    // vector<ll> cnt(sam.size(), 0);
    vector<vector<int>> e(sam.size());
    for (int i = 2; i < sam.size(); i++)
    {
        e[sam.link(i)].push_back(i);
    }
    // vector<ll> ans(s.size() + 1, 0);
    vector<vector<int>> divs(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)
            divs[j].push_back(i);
    ll res = 0;
    auto find = [&](int pos, int p) -> int
    {
        if (pos <= 0)
            return 0;
        int id = upper_bound(divs[p].begin(), divs[p].end(), pos) - divs[p].begin();
        return id;
    };
    // f[i]计算的是i节点对应的集合出现的次数，即endpos大小
    auto dfs = [&](auto &&self, int u) -> void
    {
        // cnt[u] = sam.len(u) - sam.len(sam.link(u));
        // f[u] = cnt[u];
        for (auto v : e[u])
        {
            self(self, v);
            f[u] += f[v];
            // cnt[u] += cnt[v];
        }
        // if (u == 1)
        // f[u]--;
        if (u != 1)
        {
            res += find(sam.len(u), f[u]) * f[u];
            res -= find(sam.len(sam.link(u)), f[u]) * f[u];
            // cout << f[u] << ' ' << sam.len(u) << ' ' << sam.len(sam.link(u)) << '\n';
            // cout << res << '\n';
        }
        // cout << f[u] << ' ' << cnt[u] << ' ' << u << ' ' << sam.len(u) << ' ' << cnt[u] << '\n';
    };
    dfs(dfs, 1);
    // for (int i = 1; i <= s.size(); i++)
    // {
    //     cout << ans[i] << "\n";
    // }
    cout << res << '\n';
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
