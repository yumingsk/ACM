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
// SAM / SA + 马拉车
const int M = 1e9 + 7;

vector<int> manacher(string s)
{
    string t = "#";
    for (auto c : s)
        t += c, t += '#';
    int n = t.size();
    vector<int> r(n);
    for (int i = 0, j = 0; i < n; i++)
    {
        if (2 * j - i >= 0 && j + r[j] > i)
            r[i] = min(r[2 * j - i], j + r[j] - i);
        while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]])
            r[i]++;
        if (i + r[i] > j + r[j])
            j = i;
    }
    return r;
}
struct SAM
{
    static constexpr int ALPHABET_SIZE = 27;
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
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    string rs = s, rt = t;
    ll ans = 0;
    reverse(rs.begin(), rs.end()), reverse(rt.begin(), rt.end());
    {
        vector<int> revd = manacher(s);
        vector<int> tmpd(n + 2, 0);
        for (int i = 1; i < revd.size(); i++)
        {
            // cout << revd[i] << " \n"[i == revd.size() - 1];
            int r = (i + 1) / 2;
            int len = (revd[i]) / 2;
            int l = r - len + 1;
            tmpd[l]++;
            tmpd[r + 1]--;
            // cout << l << ' ' << r << '\n';
        }
        // 马拉车预处理出tmpd[i] 表示下标i为左端点的回文串个数为tmpd[i]个
        for (int i = 1; i <= n + 1; i++)
            tmpd[i] = tmpd[i - 1] + tmpd[i];
        // for (int i = 1; i <= n; i++)
        // {
        //     cout << tmpd[i] << " \n"[i == n];
        // }
        SAM sam;
        int p = 1;
        vector<int> siz((n + m + 1) * 2, 0);
        vector<int> sum((n + m + 1) * 2, 0);
        vector<int> c((n + m + 1) * 2, 0);
        vector<int> cc((n + m + 1) * 2, 0);
        for (int i = 0; i < s.size(); i++)
        {
            p = sam.extend(p, s[i] - 'a');
            sum[p] += tmpd[i + 2] + 1; // 这里+1指是可以不选i+2位置也就是空
            // cout << tmpd[i + 2] << '\n';
        }
        p = sam.extend(p, 26);
        for (int i = 0; i < rt.size(); i++)
        {
            p = sam.extend(p, rt[i] - 'a');
            siz[p] += 1;
        }
        for (int i = 2; i < sam.size(); ++i)
            c[sam.len(i)]++;
        for (int i = 1; i < sam.size(); ++i)
            c[i] += c[i - 1];
        for (int i = 2; i < sam.size(); ++i)
            cc[c[sam.len(i)]--] = i;
        for (int i = sam.size() - 1; i >= 2; --i)
            siz[sam.link(cc[i])] = (siz[sam.link(cc[i])] + siz[cc[i]]) % M, sum[sam.link(cc[i])] = (sum[sam.link(cc[i])] + sum[cc[i]]) % M;

        // vector<vector<int>> e(sam.size());
        // for (int i = 2; i < sam.size(); i++)
        //     e[sam.link(i)].push_back(i);
        // auto dfs = [&](auto &&self, int u) -> void
        // {
        //     for (auto v : e[u])
        //     {
        //         self(self, v);
        //         sum[u] = (sum[u] + sum[v]) % M;
        //         siz[u] = (siz[u] + siz[v]) % M;
        //     }
        // };
        // dfs(dfs, 1);
        for (int i = 2; i < sam.size(); i++)
        {
            int len = sam.len(i) - sam.len(sam.link(i));
            ans = (ans + 1LL * siz[i] * sum[i] % M * len % M) % M;
        }
    }
    {
        vector<int> revd = manacher(rt);
        vector<int> tmpd(m + 2, 0);
        // db;
        for (int i = 1; i < revd.size(); i++)
        {
            // cout << revd[i] << " \n"[i == revd.size() - 1];
            int r = (i + 1) / 2;
            int len = (revd[i]) / 2;
            int l = r - len + 1;
            tmpd[l]++;
            tmpd[r + 1]--;
            // cout << l << ' ' << r << '\n';
        }
        // 马拉车预处理出tmpd[i] 表示下标i为左端点的回文串个数为tmpd[i]个
        for (int i = 1; i <= m + 1; i++)
            tmpd[i] = tmpd[i - 1] + tmpd[i];
        SAM sam;
        int p = 1;
        vector<int> siz((n + m + 1) * 2, 0);
        vector<int> sum((n + m + 1) * 2, 0);
        for (int i = 0; i < rt.size(); i++)
        {
            p = sam.extend(p, rt[i] - 'a');
            sum[p] += tmpd[i + 2]; // 这里指是必须选i+2位置
        }
        p = sam.extend(p, 26);
        for (int i = 0; i < s.size(); i++)
        {
            p = sam.extend(p, s[i] - 'a');
            siz[p] += 1;
        }
        vector<int> c((n + m + 1) * 2, 0);
        vector<int> cc((n + m + 1) * 2, 0);
        for (int i = 2; i < sam.size(); ++i)
            c[sam.len(i)]++;
        for (int i = 1; i < sam.size(); ++i)
            c[i] += c[i - 1];
        for (int i = 2; i < sam.size(); ++i)
            cc[c[sam.len(i)]--] = i;
        for (int i = sam.size() - 1; i >= 2; --i)
            siz[sam.link(cc[i])] = (siz[sam.link(cc[i])] + siz[cc[i]]) % M, sum[sam.link(cc[i])] = (sum[sam.link(cc[i])] + sum[cc[i]]) % M;

        // vector<vector<int>> e(sam.size());
        // for (int i = 2; i < sam.size(); i++)
        //     e[sam.link(i)].push_back(i);
        // auto dfs = [&](auto &&self, int u) -> void
        // {
        //     for (auto v : e[u])
        //     {
        //         self(self, v);
        //         sum[u] = (sum[u] + sum[v]) % M;
        //         siz[u] = (siz[u] + siz[v]) % M;
        //     }
        // };
        // dfs(dfs, 1);

        for (int i = 2; i < sam.size(); i++)
        {
            int len = sam.len(i) - sam.len(sam.link(i));
            ans = (ans + 1LL * siz[i] * sum[i] % M * len % M) % M;
        }
    }
    cout << ans << '\n';
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
// cout << "Used " << (double)(clock() - start_time) << " ms" << endl;
#endif
    return 0;
}
