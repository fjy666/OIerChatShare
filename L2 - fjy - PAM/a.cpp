// Problem: B. noip模拟测验（二）navie的图
// Contest: BNDSOJProblemParser
// URL: https://onlinejudge.bnds.cn/contest/problem?id=151&pid=1
// Memory Limit: 512 MB
// Time Limit: 2 ms

#include<stdio.h>
#include<algorithm>
#include<random>
namespace treap{
	std::mt19937 myrand(20220619);
	int tot=0,root=0;
	struct{
        int v,w,s,l,r;
    }tree[400001];
	inline void clear(){tot=root=0;}
    inline void pushup(int x){
    	if(x)tree[x].s=tree[tree[x].l].s+tree[tree[x].r].s+1;
    }
    void merge(int&rt,int x,int y){
        if(!x||!y)return (void)(rt=x|y);
        if(tree[x].w>tree[y].w)merge(tree[rt=x].r,tree[x].r,y);
        else merge(tree[rt=y].l,x,tree[y].l);
        pushup(rt);
    }
    void split(int rt,int&x,int&y,int k){
        if(!rt)return (void)(x=y=0);
        if(tree[rt].v<k)x=rt,split(tree[x].r,tree[x].r,y,k);
        else y=rt,split(tree[y].l,x,tree[y].l,k);
        pushup(rt);
    }
    void _insert(int&rt,int x){
    	if(!rt)rt=x;
        else if(tree[x].w>tree[rt].w)split(rt,tree[x].l,tree[x].r,tree[x].v),rt=x;
        else if(tree[x].v<tree[rt].v)_insert(tree[rt].l,x);
        else _insert(tree[rt].r,x);
        pushup(rt);
    }
    inline void insert(int v){_insert(root,(tree[++tot]={v,myrand(),1,0,0},tot));}
    inline int query(int l,int r){
    	int a,b,c,res;
    	return split(root,a,b,l+1),split(b,b,c,r),res=tree[b].s,merge(b,b,c),merge(root,a,b),tree[root].s-res;
    }
}
struct E{int x,y,z;bool operator<(const E&o)const{return z<o.z;}}edge[500001];
int f[400001],n,tot,c[200001],w[400001],ch[400001][2],fa[400001],sz[400001],l;
long long res;
int find(int x){return (x==f[x])?x:(f[x]=find(f[x]));}
void dfs1(int x){
	if(x>n)dfs1(ch[x][0]),dfs1(ch[x][1]);
	else treap::insert(c[x]);
}
int dfs2(int x){
	if(x>n)return dfs2(ch[x][0])+dfs2(ch[x][1]);
	return treap::query(c[x]-l,c[x]+l);
}
void dfs3(int x){
	if(x>n){
		int son=sz[ch[x][0]]<sz[ch[x][1]];
		dfs3(ch[x][!son]),treap::clear(),dfs3(ch[x][son]);
		int cnt=dfs2(ch[x][!son]);
		res+=(long long)w[x]*cnt,dfs1(ch[x][!son]);
	}else treap::insert(c[x]);
}
int main(){
    int m;
    scanf("%d%d%d",&n,&m,&l);
    for(int i=1;i<=n;++i)f[i]=i,sz[i]=1,scanf("%d",c+i);
    for(int i=1;i<=m;++i)
        scanf("%d%d%d",&edge[i].x,&edge[i].y,&edge[i].z);
    std::sort(edge+1,edge+m+1);
    tot=n;
    for(int i=1;i<=m;++i){
        int a=find(edge[i].x),b=find(edge[i].y);
        if(a!=b)w[++tot]=edge[i].z,ch[tot][0]=a,ch[tot][1]=b,sz[tot]=sz[a]+sz[b],f[a]=fa[a]=f[b]=fa[b]=f[tot]=tot;
    }
    printf("%lld",(dfs3(tot),res));
    return 0;
}
