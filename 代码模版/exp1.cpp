#include<bits/stdc++.h>
using namespace std;
struct node
{
   char date;
   struct node *left;
   struct node *right;
};
int pos=0;
int cnt=0;
node *head=NULL;
bool preoder_traversal(node* cur)
{
    if(cur==NULL) return false;
     cout<<cur->date;
    if(cur->left==NULL&&cur->right==NULL) cnt++;//叶子节点计数
    preoder_traversal(cur->left);
    preoder_traversal(cur->right);
    return true;
}
bool inorder_traversal(node* cur)
{
    if(cur==NULL)return false;
    inorder_traversal(cur->left);
    cout<<cur->date;
    inorder_traversal(cur->right);
    return true;
}
bool postorder_traversal(node* cur)
{
    if(cur==NULL)return false;
    postorder_traversal(cur->left);
    postorder_traversal(cur->right);
    cout<<cur->date;
    return true;
}


void build(string &s,node* &pre)
{
    if(pos>=s.size())return ;
    if(s[pos]=='#')
    {
        pos++;
        pre=NULL;return;
    }
    node *cur=new(node);
    pre=cur;
    cur->date=s[pos++];
    build(s,cur->left);
    build(s,cur->right);
}

void clear(node *cur)
{
    if(cur==NULL) return ;
    clear(cur->left);
    clear(cur->right);
    free(cur);
    return ;
}
void solve()
{
    string str;
    cin>>str;
    build(str,head);
    if(preoder_traversal(head))cout<<"\n";
    if(inorder_traversal(head))cout<<"\n";
    if(postorder_traversal(head))cout<<"\n";
    cout<<cnt<<"\n";
    clear(head);
}
int main ()
{
    solve();
    return 0;
}