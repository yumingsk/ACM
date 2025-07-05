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
    string s;
    cin >> s;
    SAM sam;
    int p = 1;
    vector<int> x;
    for (auto c : s)
    {
        x.push_back(p = sam.extend(p, c - 'a'));
    }
    vector<ll> f(sam.size(), 0); // 计算endpos大小
    for (auto v : x)
    {
        f[v]++;
    }
    int op;
    cin >> op;
    int k;
    cin >> k;
    vector<vector<int>> e(sam.size());
    for (int i = 2; i < sam.size(); i++)
    {
        // cout << sam.link(i) << ' ' << i << '\n';
        e[sam.link(i)].push_back(i);
    }
    auto dfs = [&](auto &&self, int u) -> void
    {
        for (auto v : e[u])
        {
            self(self, v);
            f[u] += f[v];
        }
    };
    dfs(dfs, 1);
    // for(int )
    if (op == 0)
        for (int i = 1; i < sam.size(); i++)
            f[i] = 1;
    f[1] = 0;
    vector<ll> ans(sam.size(), 0);
    auto dfs_yu = [&](auto &&self, int u) -> void
    {
        if (ans[u])
            return;
        ans[u] = f[u];
        for (int j = 0; j < 26; j++)
        {
            if (sam.next(u, j))
            {
                self(self, sam.next(u, j));
                ans[u] += ans[sam.next(u, j)];
            }
        }
    };
    dfs_yu(dfs_yu, 1);
    // cout << ans[1] << '\n';
    // for (int i = 1; i < sam.size(); i++)
    // {
    //     cout << f[i] << ' ';
    // }
    // cout << '\n';
    if (ans[1] < k)
    {
        cout << "-1\n";
        return;
    }
    auto dfs_k = [&](auto &&self, int u, int y) -> void
    {
        // cout << u << ' ' << y << '\n';
        if (y <= f[u])
            return;
        y -= f[u];
        for (int i = 0; i < 26; i++)
        {
            int v = sam.next(u, i);
            if (!v)
                continue;
            if (y > ans[v])
            {
                y -= ans[v];
                continue;
            }
            cout << char(i + 'a');
            self(self, sam.next(u, i), y);
            return;
        }
    };
    dfs_k(dfs_k, 1, k);
    cout << '\n';
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
