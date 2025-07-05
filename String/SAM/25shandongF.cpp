#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;

struct SAM
{
    static constexpr int ALPHABET_SIZE = 26;
    struct Node
    {
        int len;
        int link;
        array<int, ALPHABET_SIZE> next;
        Node() : len(0), link(0), next{} {}
    };
    vector<Node> t;
    SAM() { init(); }
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
    int link(int p) { return t[p].link; }
    int len(int p) { return t[p].len; }
    int size() { return t.size(); }
};

int main()
{
    IOS;
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        string s;
        cin >> n >> s;
        SAM sam;
        vector<int> last_node;
        int last = 1;
        for (char c : s)
        {
            last = sam.extend(last, c - 'a');
            last_node.push_back(last);
        }

        int node_count = sam.size();
        vector<set<int>> sets(node_count);
        for (int i = 0; i < n; i++)
        {
            sets[last_node[i]].insert(i + 1);
        }
        vector<vector<int>> tree(node_count);
        for (int i = 1; i < node_count; i++)
        {
            int fa = sam.link(i);
            tree[fa].push_back(i);
        }

        ll ans = 0;
        function<void(int)> dfs = [&](int u)
        {
            for (int v : tree[u])
            {
                dfs(v);
                if (sets[u].size() < sets[v].size())
                {
                    swap(sets[u], sets[v]);
                }
                for (int pos : sets[v])
                {
                    sets[u].insert(pos);
                }
                set<int>().swap(sets[v]); // 清空并释放内存
            }
            if (sets[u].size() < 3)
                return;
            int x = *sets[u].begin();
            int y = *sets[u].rbegin();
            if (y - x < 4)
                return;
            int mid = (x + y) / 2;
            auto it = sets[u].lower_bound(mid);
            vector<int> cand;
            if (it != sets[u].end())
                cand.push_back(*it);
            if (it != sets[u].begin())
                cand.push_back(*(prev(it)));
            for (int z : cand)
            {
                if (z <= x || z >= y)
                    continue;
                int gap1 = z - x - 1;
                int gap2 = y - z - 1;
                int p = min({sam.len(u), gap1, gap2});
                if (p < 1)
                    continue;
                ll total_len = (ll)(y - x) + p;
                if (total_len > ans)
                    ans = total_len;
            }
        };
        dfs(0);
        cout << ans << '\n';
    }
    return 0;
}