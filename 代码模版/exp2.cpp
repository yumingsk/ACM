#include<bits/stdc++.h>
using namespace std;
struct node
{
   char date;
   struct node *left;
   struct node *right;
};
int pos=0;//记录读入字符串的位置
node *head=NULL;//头结点
char st[10000];//用数组模拟栈并记录答案
int qq=0;//模拟栈的尾节点
int fh=0;//判断是否已经找到目标节点
char tar;
bool preoder_traversal(node* cur)
{
    if(fh==1)return true;//已经找到目标节点，不必进行多余的递归，返回值
    if(cur==NULL) return false;
  //  cout<<cur->date;
    st[qq]=(cur->date);qq++;//加入数组
    if(cur->date==tar) fh=1;//判断是否为目标
    //if(cur->left==NULL&&cur->right==NULL) cnt++;
    preoder_traversal(cur->left);//遍历左子树
    preoder_traversal(cur->right);//遍历右子树
    if(fh==0){
        qq--;
    }//在未找到目标的前提下，并且当且节点的左右子树都已经遍历完，删除该节点.
    return true;
}
void build(string &s,node* &pre)//建树
{
    if(pos>=s.size()) return ;
    if(s[pos]=='#')
    {
        pos++;
        pre=NULL;return;
    }
    node *cur=(node*)malloc(sizeof (node));
    pre=cur;
    cur->date=s[pos++];
    build(s,cur->left);
    build(s,cur->right);
}
void clear(node* &cur)
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
    cin>>tar;
    build(str,head);
    preoder_traversal(head);//先序遍历
    for(int i=0;i<qq;i++)//输出答案
    {
       cout<<st[i]<<' ';
    }cout<<"\n";
    clear(head);
    if(head == NULL) cout<<"YES\n";;
}
int main ()
{
   solve();
   return 0;
}
