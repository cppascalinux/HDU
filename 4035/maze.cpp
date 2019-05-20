//2019.05.20
//HDU4035 Maze 期望dp+系数表示法
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define db double
#define eps 1e-10
using namespace std;
char *p1,*p2,buffer[10000009];
int n,tot,err;
int hd[10009],eg[20009],nxt[20009];
int deg[10009];
db k[10009],e[10009];
db fa[10009],fb[10009],fc[10009];
void clr()
{
	memset(hd,0,sizeof(hd));
	memset(deg,0,sizeof(deg));
	tot=err=0;
}
int sgn(db x)
{
	return x>eps?1:(x<-eps?-1:0);
}
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fat)
{
	db t=(1-k[x]-e[x])/deg[x],h=1;
	fa[x]=k[x],fb[x]=t,fc[x]=1-k[x]-e[x];
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fat)
		{
			int v=eg[i];
			dfs(v,x);
			h-=t*fb[v];
			fa[x]+=t*fa[v];
			fc[x]+=t*fc[v];
		}
	if(sgn(h)==0)
	{
		err=1;
		return;
	}
	fa[x]/=h,fb[x]/=h,fc[x]/=h;
}
void solve()
{
	db t=1-fa[1];
	if(sgn(t)==0)
		err=1;
	db ans=fc[1]/t;
	if(err)
		printf("impossible\n");
	else
		printf("%.10lf\n",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
#endif
	int t,ttt=0;
	rd(t);
	while(t--)
	{
		printf("Case %d: ",++ttt);
		rd(n);
		for(int i=1,a,b;i<=n-1;i++)
		{
			rd(a),rd(b);
			ins(a,b),ins(b,a);
			deg[a]++,deg[b]++;
		}
		for(int i=1,a,b;i<=n;i++)
		{
			rd(a),rd(b);
			k[i]=a/100.0,e[i]=b/100.0;
		}
		dfs(1,0);
		solve();
		clr();
	}
	return 0;
}