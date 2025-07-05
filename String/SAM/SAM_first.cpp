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
    static constexpr int ALPHABET_SIZE = 26; // 假设字符为小写字母
    struct Node
    {
        int len;      // 该状态的最长子串长度
        int link;     // 后缀链接
        int firstpos; // 新增字段：子串的最早结束位置
        std::array<int, ALPHABET_SIZE> next;
        Node() : len(0), link(0), firstpos(-1), next{} {}
    };
    std::vector<Node> t;
    SAM() { init(); }
    void init()
    {
        t.assign(2, Node());
        t[0].len = -1;     // 根节点的 len 初始化为 -1
        t[0].next.fill(1); // 根节点的所有转移指向初始状态 1
    }
    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) // 修改后的 extend 函数
    {
        if (t[p].next[c])
        {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1)
                return q; // 分裂状态 q，创建新状态 r

            int r = newNode();
            t[r] = t[q]; // 复制 next 和 link
            t[r].len = t[p].len + 1;
            t[r].firstpos = t[q].firstpos; // 继承 q 的 firstpos
            t[q].link = r;
            while (t[p].next[c] == q)
            {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        // 创建新状态 cur
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        t[cur].firstpos = t[cur].len - 1; // 新状态的 firstpos = len - 1
        while (!t[p].next[c])
        {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
    // 其余辅助函数保持不变
    int next(int p, int x) { return t[p].next[x]; }
    int link(int p) { return t[p].link; }
    int len(int p) { return t[p].len; }
    int firstpos(int p) { return t[p].firstpos; } // 新增函数
    int size() { return t.size(); }
};
int find_first(SAM &sam, const std::string &P)
{
    int current = 1; // 初始状态为 1
    for (char ch : P)
    {
        int c = ch - 'a';
        current = sam.next(current, c);
        if (current == 0)
            return -1; // 无法转移，子串不存在
    }
    int end_pos = sam.firstpos(current); // 最早结束位置
    return end_pos - (int)P.size() + 1;  // 转换为起始位置
}
void solve()
{
    SAM sam;
    string text = "acdabacbbadbc";
    sam.init();
    int p = 1;
    for (char ch : text)
        p = sam.extend(p, ch - 'a'); // 插入字符到 SAM
    string query = "acb";
    int pos = find_first(sam, query);
    if (pos != -1)
        std::cout << pos << std::endl;
    else
        std::cout << "None" << std::endl;
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
