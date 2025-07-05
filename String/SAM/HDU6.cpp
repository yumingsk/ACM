#include <bits/stdc++.h>
#define I inline
#define int long long
using namespace std;

const int mod = 1e9 + 7;
const int N = 301000;
char rs[N << 2], s[N << 2], t[N << 2];
int p[N << 2], d[N << 2];
int n, m;

I void add(int &x, int y)
{
    x += y;
    x = (x >= mod ? x - mod : x);
}
struct SAM
{
    int cnt, last, link[N << 2], len[N << 2], siz[N << 2], sum[N << 2], ch[N << 2][27], c[N << 2], cc[N << 2];
#define M(x) memset(x, 0, sizeof(x));
#define Clr(x, r, v)             \
    for (int i = 0; i <= r; ++i) \
    {                            \
        x[i] = v;                \
    }
    I void init()
    {
        //	M(ch); M(link); M(len); M(siz); M(c); M(cc); M(sum); cout<<cnt<<endl;
        Clr(link, cnt, 0);
        Clr(c, cnt, 0);
        Clr(cc, cnt, 0);
        Clr(sum, cnt, 0);
        Clr(siz, cnt, 0);
        Clr(len, cnt, 0);
        for (int i = 0; i <= cnt; ++i)
            memset(ch[i], 0, sizeof(ch[i]));
        link[0] = -1;
        cnt = last = 0;
    }
    I void insert(int x, int sz, int sm)
    {
        int cur = ++cnt, p = last;
        siz[cur] = sz;
        sum[cur] = sm % mod;
        len[cur] = len[p] + 1;
        while (p != -1 && !ch[p][x])
            ch[p][x] = cur, p = link[p];
        if (p == -1)
        {
            link[cur] = 0;
        }
        else
        {
            int q = ch[p][x];
            if (len[q] == len[p] + 1)
                link[cur] = q;
            else
            {
                int clone = ++cnt;
                len[clone] = len[p] + 1;
                link[clone] = link[q];
                memcpy(ch[clone], ch[q], sizeof(ch[q]));
                while (p != -1 && ch[p][x] == q)
                    ch[p][x] = clone, p = link[p];
                link[q] = link[cur] = clone;
            }
        }
        last = cur;
    }
    I void tsort()
    {
        for (int i = 1; i <= cnt; ++i)
            c[len[i]]++;
        for (int i = 1; i <= cnt; ++i)
            c[i] += c[i - 1];
        for (int i = 1; i <= cnt; ++i)
            cc[c[len[i]]--] = i;
        for (int i = cnt; i >= 1; --i)
            add(siz[link[cc[i]]], siz[cc[i]]), add(sum[link[cc[i]]], sum[cc[i]]);
    }
} sam;

I void prework()
{
    rs[0] = '*';
    rs[1] = '|';
    for (int i = 1; i <= n; ++i)
        rs[i * 2] = s[i], rs[i * 2 + 1] = '|';
    rs[n * 2 + 2] = '?';
    rs[n * 2 + 3] = 0;
}
I void Nanachar()
{
    prework();
    int R = 0, mid = 0;
    for (int i = 0; i <= n + 1; ++i)
        d[i] = 0;
    for (int i = 1; i <= n * 2 + 2; ++i)
        p[i] = 0;
    for (int i = 1; i <= n * 2 + 2; ++i)
    {
        if (i < R)
            p[i] = min(p[mid * 2 - i], R - i + 1);
        while (rs[p[i] + i] == rs[i - p[i]] && i + p[i] <= n * 2 + 2)
            p[i]++;
        if (i + p[i] - 1 > R)
            R = i + p[i] - 1, mid = i;
    }
    for (int i = 2; i <= n * 2 + 2; ++i)
    {
        int l = i - p[i] + 1 >> 1, r = i >> 1;
        d[l]++;
        d[r]--;
    }

    for (int i = 1; i <= n; ++i)
        d[i] += d[i - 1];

    //	for(int i=1;i<=n*2+2;++i) cout<<rs[i]; cout<<endl;
    //	for(int i=1;i<=n*2+2;++i) cout<<p[i]; cout<<endl;
    // for (int i = 0; i <= n; ++i)
    //     cout << d[i] << ' ';
    // cout << endl;
}
I int work(int ad)
{

    Nanachar();
    sam.init();
    // cout << n << '\n';
    for (int i = 1; i <= n; ++i)
    {
        sam.insert(s[i] - 'a' + 1, 0, d[i] + ad);
        // cout << d[i] << " \n"[i == n];
    }
    sam.insert(0, 0, 0);
    for (int i = 1; i <= m; ++i)
    {
        sam.insert(t[i] - 'a' + 1, 1, 0);
    }
    sam.tsort();
    int ret = 0;
    for (int i = 1; i <= sam.cnt; ++i)
    {
        int len = sam.len[i] - sam.len[sam.link[i]];
        //		cout<<"!!"<<len<<' '<<sam.len[i]<<' '<<sam.siz[i]<<' '<<sam.sum[i]<<endl;
        add(ret, sam.siz[i] * sam.sum[i] % mod * len % mod);
    }
    return ret;
}
I void solve()
{
    scanf("%lld %lld", &n, &m);
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    for (int i = 1; i <= m / 2; ++i)
        swap(t[i], t[m - i + 1]);

    int ans = 0;
    add(ans, work(1));
    for (int i = 1; i <= max(m, n); ++i)
        swap(s[i], t[i]);
    swap(m, n);
    add(ans, work(0));
    printf("%lld\n", ans);
}
signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
}