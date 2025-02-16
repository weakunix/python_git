#include <cstdio>
#include <iostream>
#include <algorithm>
#define macro_expand(x) #x
#define print_macro(x) printf("%s\n",macro_expand(x))
#define FOR(i,l,r) for(int i=(l),i##ADJK=(r);i<=i##ADJK;++i)
#define ROF(i,r,l) for(int i=(r),i##ADJK=(l);i>=i##ADJK;--i)
using namespace std;
typedef long long LL;
const int MN=305,Mod=1e9+7;
int ad(int x,int y){return ((x+y)>=Mod)?(x+y-Mod):(x+y);}
int dc(int x,int y){return ((x-y)<0)?(x-y+Mod):(x-y);}
int ml(int x,int y){return (LL)x*y%Mod;}
int add(int &x,int y){return ((x+=y)>=Mod)?(x-=Mod):x;}
int dec(int &x,int y){return ((x-=y)<0)?(x+=Mod):x;}
int ksm(int x,int y){
	int ret=1;
	for(;y;y>>=1,x=ml(x,x))if(y&1)ret=ml(ret,x);
	return ret;
}
int N,A[MN],B[MN],c[MN*2],totc,len,id[MN][MN];
int totid;
void get_id(int l,int r){
	if(id[l][r])return;
	id[l][r]=++totid;
	if(l > r or l==r)return;
	if((r-l+1)&1){
		int mid=(l+r)>>1;
		get_id(l,mid-1),get_id(mid+1,r);
		get_id(l,mid-2),get_id(mid,r);
		get_id(l,mid),get_id(mid+2,r);
	}else{
		int mid=(l+r)>>1;
		get_id(l,mid-1),get_id(mid+1,r);
		get_id(l,mid),get_id(mid+2,r);
	}
}
int f[3005][MN];
bool vis[3005];
int now_val;
void calc(int l,int r){
	if(vis[id[l][r]])return;
    //cout << l << " " << r << "\n"; //TODO
	vis[id[l][r]]=1;
	FOR(i,1,len)f[id[l][r]][i]=0;
	if(l>r)f[id[l][r]][0]=1;
	else{
		int pos[]={0,0,0,0},top=0; // static 的使用……
		top=0;
		int mid=(l+r)>>1;
		if(r-l+1==1)top=1,pos[1]=mid;
		else if((r-l+1)&1)top=3,pos[1]=mid,pos[2]=mid-1,pos[3]=mid+1;
		else top=2,pos[1]=mid,pos[2]=mid+1;
		FOR(i,1,top){
			int p=pos[i];
            calc(l,p-1),calc(p+1,r);
			if(A[p]<=now_val&&now_val<B[p]){
				FOR(j,1,len)
					add(f[id[l][r]][j],ml(f[id[l][p-1]][j],f[id[p+1][r]][j-1]));
			}
		}
	}
	FOR(j,1,len)add(f[id[l][r]][j],f[id[l][r]][j-1]);
}
int caf[MN],fac[MN];
void lagrange(int l,int r){
	if(l+N>=r){FOR(i,1,totid)f[i][0]=f[i][r-l+1];return;}
	int pro=1,x=r-l+1;
	static int inv[MN];
	FOR(i,1,N+1)pro=ml(pro,x-i),inv[i]=ksm(x-i,Mod-2);
	FOR(j,1,totid)f[j][0]=0;
	FOR(j,1,N+1){
		int post=ml(pro,ml(inv[j],ml(caf[j-1],((N+1-j)&1)?(Mod-caf[N+1-j]):caf[N+1-j])));
		FOR(i,1,totid)add(f[i][0],ml(f[i][j],post));
	}
}
void init(int L){
	fac[0]=1;
	FOR(i,1,L)fac[i]=ml(fac[i-1],i);
	caf[L]=ksm(fac[L],Mod-2);
	ROF(i,L-1,0)caf[i]=ml(caf[i+1],i+1);
}
int main(){
	scanf("%d",&N);
	init(N+1);
	fac[0]=1;
	FOR(i,1,N+1)fac[i]=ml(fac[i-1],i);
	caf[N+1]=ksm(fac[N+1],Mod-2);
	FOR(i,1,N)scanf("%d%d",&A[i],&B[i]),c[++totc]=A[i],c[++totc]=++B[i];
	sort(c+1,c+totc+1);
	totc=unique(c+1,c+totc+1)-c-1;
	FOR(i,1,N){
		A[i]=lower_bound(c+1,c+totc+1,A[i])-c;
		B[i]=lower_bound(c+1,c+totc+1,B[i])-c;
	}
	get_id(1,N);

	FOR(i,1,totc-1){
		len=min(c[i+1]-c[i],N+1);
		now_val=i;
		FOR(j,0,totid)vis[j]=0;

        //cout << "\n" << i << "\n"; //TODO

		//FOR(l,1,N)FOR(r,l,N)if(id[l][r])calc(l,r); // 不能直接calc(1,N)
        calc(1, N); //TODO

		lagrange(c[i],c[i+1]-1);
	}
	printf("%d\n",f[id[1][N]][0]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}

