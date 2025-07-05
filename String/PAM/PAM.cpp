/**   回文自动机（PAM）
 *   2023-05-19: https://ac.nowcoder.com/acm/contest/view-submission?submissionId=62237107&returnHomeType=1&uid=329687984
 *    2024-04-09: https://qoj.ac/submission/384435 【模板】
 **/
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
struct PAM
{
    static constexpr int ALPHABET_SIZE = 26;
    struct Node
    {
        int len;
        int link;
        int cnt;
        std::array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, cnt{}, next{} {}
    };
    std::vector<Node> t;
    int suff;
    std::string s;
    PAM()
    {
        init();
    }
    void init()
    {
        t.assign(2, Node());
        t[0].len = -1;
        suff = 1;
        s.clear();
    }
    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }
    bool add(char c)
    {
        int pos = s.size();
        s += c;
        int let = c - 'a';
        int cur = suff, curlen = 0;
        while (true)
        {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
            {
                break;
            }
            cur = t[cur].link;
        }
        if (t[cur].next[let])
        {
            suff = t[cur].next[let];
            return false;
        }
        int num = newNode();
        suff = num;
        t[num].len = t[cur].len + 2;
        t[cur].next[let] = num;
        if (t[num].len == 1)
        {
            t[num].link = 1;
            t[num].cnt = 1;
            return true;
        }
        while (true)
        {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
            {
                t[num].link = t[cur].next[let];
                break;
            }
        }
        t[num].cnt = 1 + t[t[num].link].cnt;
        return true;
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
