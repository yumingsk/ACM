#include <bits/stdc++.h>

using i64 = long long;

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

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    SAM sam;

    for (int i = 0; i < n; i++)
    {
        std::string s;
        std::cin >> s;
        int p = 1; // 清空
        for (auto c : s)
        {
            p = sam.extend(p, c - 'a');
        }
    }
    i64 ans = 0;
    for (int i = 2; i < sam.size(); i++)
        ans += sam.len(i) - sam.len(sam.link(i));
    std::cout << ans << "\n";
    // std::cout << sam.size() - 1 << '\n';

    return 0;
}