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
const int N = 1e6 + 10;
int son[N][26], cnt[N];
int tot[N];
// tot[p]表示以p为根的子树有多少个字符串
// cnt[p]表示恰好以p结尾的字符串有多少个
int ind = 0;
int newNode()
{
    ind++;
    cnt[ind] = tot[ind] = 0;
    memset(son[ind], 0, sizeof(son[ind]));
    return ind;
}

void insert(string str)
{
    int p = 1; // 从根节点开始(注意：根节点不储存字符)查询
    tot[p]++;
    for (int i = 0; i < str.size(); i++)
    {
        int c = str[i] - 'a'; // 将a - z 共26个字母对应成 0 - 25
        if (!son[p][c])
            son[p][c] = newNode();
        // 意味着从下标为p的父节点开始搜索时，没有找到存储了c的子节点
        // 那我们便手动创建这个子节点
        tot[p = son[p][c]]++;
        // p = son[p][c]; // 将子节点下标赋给p，然后寻找下一个字符
    }
    cnt[p]++;
}
void solve()
{
    int n, k;
    cin >> n >> k;
    ind = 0;
    newNode();
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        insert(s);
    }
    int now = 1;
    while (1)
    {
        int tmp = cnt[now];
        for (int i = 0; i < 26; i++)
        {
            // cout << son[now][i] << ' ' << tot[son[now][i]] << '\n';
            if (tot[son[now][i]])
                tmp++;
        }

        // cout << tmp << '\n';
        if (tmp >= k)
        {
            if (now == 1)
            {
                cout << "EMPTY";
            }
            cout << "\n";
            return;
        }
        // cout << now << '\n';
        for (int i = 0; i < 26; i++)
        {
            if (tot[son[now][i]])
            {
                tmp = tot[son[now][i]] - 1 + tmp;
                if (tmp >= k)
                {
                    k -= tmp - tot[son[now][i]];
                    now = son[now][i];
                    cout << (char)('a' + i);
                    break;
                }
            }
        }
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
    cout << "Used " << (double)(clock() - start_time) << " ms" << endl;
#endif
    return 0;
}
