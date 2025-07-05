``` c++
int cnt = 1;
struct kkk
{
    int son[26];
    int fail = 0, flag = 0;
    vector<int> vec;
    void clear()
    {
        //  memset(son, 0, sizeof(son));
        for (int i = 0; i < 26; i++)
            son[i] = 0;
        fail = flag = 0;
        vec.clear();
    }
} trie[N];
int vis[N];
int n;
void insert(string &s, int num)
{
    int u = 1, len = s.size();
    for (int i = 0; i < len; i++)
    {
        int v = s[i] - 'a';
        if (!trie[u].son[v])
            trie[u].son[v] = ++cnt;
        u = trie[u].son[v];
    }
    trie[u].flag = num;
    trie[u].vec.push_back(num);
    //   cout << u << "!!!!!!!!!" << endl;
}

void getFail()
{
    for (int i = 0; i < 26; i++)
        trie[0].son[i] = 1;
    queue<int> q;
    q.push(1);
    trie[1].fail = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        int Fail = trie[u].fail;
        for (int i = 0; i < 26; i++)
        {
            int v = trie[u].son[i];
            if (!v)
            {
                trie[u].son[i] = trie[Fail].son[i];
                continue;
            }
            trie[v].fail = trie[Fail].son[i];
            q.push(v);
        }
    }
}
void query(string s)
{
    int u = 1, len = s.size();
    for (int i = 0; i < len; i++)
    {
        int v = s[i] - 'a';
        int k = trie[u].son[v];
        while (k > 1)
        {
            if (trie[k].flag)
            {
                vis[k]++;
            }
            k = trie[k].fail;
        }
        u = trie[u].son[v];
    }
}
``` 