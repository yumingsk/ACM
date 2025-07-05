#include <bits/stdc++.h>

using i64 = long long;
/**   后缀自动机（SAM ）
 *    2023-05-27: https://cf.dianhsu.com/gym/104353/submission/207318083
 *    2023-09-25: https://qoj.ac/submission/188106
 *    2024-04-09: https://qoj.ac/submission/384423 【模板】
 *    2024-04-09: https://qoj.ac/submission/384429 【模板】
 **/

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

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // int n;
    // std::cin >> n;

    std::string s;
    std::cin >> s;

    SAM sam;
    std::vector<int> x;
    int p = 1;
    for (int i = 0; i < s.size(); i++)
    {
        x.push_back(p = sam.extend(p, s[i] - 'a'));
        // std::cout << p << '\n';
    }
    std::vector<i64> f(sam.size(), 0);
    for (auto v : x)
    {
        std::cout << v << " ";
        f[v]++;
    }
    std::cout << "\n";
    i64 ans = 0;
    // std::cout << sam.size() << '\n';
    std::vector<std::vector<int>> e(sam.size());
    for (int i = 2; i < sam.size(); i++)
    {
        std::cout << sam.link(i) << ' ' << i << '\n';
        e[sam.link(i)].push_back(i);
    }
    for (int i = 1; i < sam.size(); i++)
    {
        std::cout << i << " " << sam.len(i) << "\n";
    }
    auto dfs = [&](auto self, int x) -> void
    {
        // std::cout << x << '\n';
        for (auto v : e[x])
        {
            self(self, v);
            f[x] += f[v];
        }
        if (f[x] > 1)
        {
            // std::cout << x << ' ' << f[x] << ' ' << sam.len(x) << '\n';
            ans = std::max(ans, 1LL * f[x] * sam.len(x));
        }
    };
    dfs(dfs, 1);
    std::cout << ans << "\n";

    return 0;
}