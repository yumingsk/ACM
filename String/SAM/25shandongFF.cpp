#pragma GCC optimize(3, "Ofast", "inline")
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
    int next(int p, int x) { return t[p].next[x]; }
    int link(int p) { return t[p].link; }
    int len(int p) { return t[p].len; }
    int size() { return t.size(); }
};
void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    SAM sam;
    vector<int> lst_node;
    int p = 1;
    for (auto c : s)
    {
        p = sam.extend(p, c - 'a');
        lst_node.push_back(p);
    }
    int siz = sam.size();
    vector<set<int>> endpos(siz + 1);
    for (int i = 0; i < n; i++)
    {
        endpos[lst_node[i]].insert(i + 1);
    }
    vector<vector<int>> tr(siz + 1);
    for (int i = 1; i < siz; i++)
    {
        tr[sam.link(i)].push_back(i);
    }
    int ans = 0;
    auto dfs = [&](auto &&self, int u) -> void
    {
        for (auto v : tr[u])
        {
            self(self, v);
            if (endpos[u].size() < endpos[v].size())
            {
                // endpos[u].swap(endpos[v]);
                swap(endpos[u], endpos[v]);
            }
            for (int pos : endpos[v])
            {
                endpos[u].insert(pos);
            }
            // endpos[v].clear();
            set<int>().swap(endpos[v]); // 清空并释放内存
        }
        if (endpos[u].size() < 3)
            return;
        int x = *endpos[u].begin();
        int z = *endpos[u].rbegin();
        if (z - x < 4)
            return;
        int mid = (x + z) / 2;
        auto it = endpos[u].lower_bound(mid);
        vector<int> tmp;
        if (it != endpos[u].end())
            tmp.push_back(*it);
        if (it != endpos[u].begin())
            tmp.push_back(*(prev(it)));
        for (auto y : tmp)
        {

            int gap1 = y - x - 1; // 2
            int gap2 = z - y - 1; // 4
            int p = min({sam.len(u), gap1, gap2});
            if (p < 1)
                continue;
            ans = max(ans, z - x + p);
        }
    };
    dfs(dfs, 1);
    cout << ans << '\n';
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
