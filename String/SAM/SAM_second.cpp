#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
using namespace std;
struct SAM
{
    static constexpr int ALPHABET_SIZE = 26; // 假设字符为小写字母
    struct Node
    {
        int len;                        // 状态对应的最长子串长度
        int first_pos;                  // 最早结束位置（用于计算起始位置）
        bool is_clone;                  // 是否为克隆状态（用于去重）
        array<int, ALPHABET_SIZE> next; // 状态转移
        vector<int> inv_link;           // 后缀链接的逆（用于遍历所有关联状态）
        Node() : len(0), first_pos(-1), is_clone(false), next{0} {}
    };
    vector<Node> t;
    vector<int> link; // 后缀链接表（link[v]表示状态v的后缀链接）
    SAM() { init(); }
    void init()
    {
        t.assign(2, Node());
        link.resize(2);
        t[0].len = -1;      // 根节点的特殊长度
        t[0].next.fill(1);  // 根节点的转移指向初始状态
        link[0] = -1;       // 根节点无后缀链接
        t[1].first_pos = 0; // 初始状态的结束位置为0
        link[1] = 0;        // 初始状态的后缀链接指向根节点
    }
    int new_state()
    {
        t.emplace_back();
        link.push_back(0);
        return t.size() - 1;
    }
    // 核心扩展函数（参数p为当前状态，c为字符）
    int extend(int p, int c)
    {
        if (t[p].next[c])
        {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1)
            {
                return q; // 无需分裂，直接返回已有状态
            }
            // 分裂状态q为r和q（克隆操作）
            int r = new_state();
            t[r] = t[q];                     // 复制所有属性
            t[r].len = t[p].len + 1;         // 更新长度
            t[r].is_clone = true;            // 标记为克隆状态
            t[r].first_pos = t[q].first_pos; // 继承原始状态的结束位置
            link[q] = r;                     // 原状态的后缀链接指向克隆状态
            link[r] = link[q];               // 克隆状态继承原后缀链接
            while (t[p].next[c] == q)        // 更新转移路径
            {
                t[p].next[c] = r;
                p = link[p];
            }
            return r;
        }
        int cur = new_state(); // 创建新状态（非克隆）
        t[cur].len = t[p].len + 1;
        t[cur].first_pos = t[cur].len - 1; // 结束位置为当前字符索引
        t[cur].is_clone = false;
        while (!t[p].next[c]) // 构建后缀链接
        {
            t[p].next[c] = cur;
            p = link[p];
        }
        link[cur] = extend(p, c); // 递归处理
        return cur;
    }
    void build_inv_links() // 构建后缀链接的逆（必须在所有extend操作后调用）
    {
        for (int v = 1; v < (int)t.size(); ++v)
        {
            if (link[v] > 0)
            {
                t[link[v]].inv_link.push_back(v);
            }
        }
    }
    void dfs_cur(int v, int p_len, vector<int> &res) // 递归收集所有出现位置（辅助函数）
    {
        if (!t[v].is_clone)
        { // 仅处理原始状态
            res.push_back(t[v].first_pos - p_len + 1);
        }
        for (int u : t[v].inv_link)
        {
            dfs_cur(u, p_len, res);
        }
    }
    vector<int> query(const string &str) // 查询主函数（返回所有起始位置）
    {
        vector<int> res;
        int cur = 1;        // 初始状态
        for (char ch : str) // 沿着模式串转移
        {
            int c = ch - 'a';
            cur = t[cur].next[c];
            if (cur == 0)
                return res; // 不存在该模式串
        }
        dfs_cur(cur, str.size(), res);
        sort(res.begin(), res.end()); // 按位置排序
        return res;
    }
};
int main()
{
    SAM sam;
    string text = "abcabadabca";
    int p = 1;
    for (int i = 0; i < (int)text.size(); ++i) // 构建SAM
        p = sam.extend(p, text[i] - 'a');
    sam.build_inv_links(); // 必须调用
    vector<string> test_cases = {"ab", "ca", "abc", "d", "abca"};
    for (auto &s : test_cases)
    {
        auto positions = sam.query(s);
        cout << "模式串 \"" << s << "\" 出现位置: ";
        for (int pos : positions)
            cout << pos << " ";
        cout << endl;
    }
    return 0;
}