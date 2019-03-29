//hdu3949 XOR 线性基+从高位到低位依次确定
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define ll long long
using namespace std;
char *p1,*p2,buffer[10000009];
int n,q;
ll bs[69];
int sm[69];
template<class T>
void rd(T &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void ins(ll x)
{
	for(int i=62;i>=0;i--)
		if(x&(1LL<<i))
		{
			if(bs[i])
				x^=bs[i];
			else
			{
				for(int j=0;j<i;j++)
					if(x&(1LL<<j))
						x^=bs[j];
				for(int j=i+1;j<=62;j++)
					if(bs[j]&(1LL<<i))
						bs[j]^=x;
				bs[i]=x;
				break;
			}
		}
}
ll solve(ll x)
{
	if(sm[62]>=n)
		x++;
	if(x>(1LL<<sm[62]))
		return -1;
	ll ans=0;
	for(int i=62;i>=0;i--)
		if(bs[i])
		{
			ll lsm=1LL<<(sm[i]-1);
			if(x>lsm)
			{
				x-=lsm;
				ans^=bs[i];
			}
		}
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("base.in","r",stdin);
	freopen("base.out","w",stdout);
#endif
	int t,kt=0;
	rd(t);
	while(t--)
	{
		printf("Case #%d:\n",++kt);
		rd(n);
		ll a;
		for(int i=1;i<=n;i++)
		{
			rd(a);
			ins(a);
		}
		sm[0]=(bs[0]>0);
		for(int i=1;i<=62;i++)
			sm[i]=sm[i-1]+(bs[i]>0);
		rd(q);
		for(int i=1;i<=q;i++)
		{
			rd(a);
			printf("%lld\n",solve(a));
		}
		memset(bs,0,sizeof(bs));
	}
	return 0;
}