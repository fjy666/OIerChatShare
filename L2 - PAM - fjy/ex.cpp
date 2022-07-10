#include <bits/stdc++.h>
// using namespace std;
#define int long long
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

namespace FastIO { //by fjy666
	char OBuf[1 << 23], *p = OBuf;
	inline void pc(char c) { *p++=c; }
	inline void out(ll x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
	// inline void out(int x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
	inline void out(char *s) { if(*s) pc(*s),out(s+1); }
	inline void flush(void) { fwrite(OBuf,p - OBuf,1,stdout); }
	struct _Flusher{ ~_Flusher(){ flush(); } } flusher;

	char IBuf[1 << 23], *i1 = IBuf,*i2 = IBuf;
	inline char gc(void) { return (i1 == i2 && (i2 = (i1 = IBuf) + fread(IBuf,1,1 << 23,stdin),i1 == i2)) ? EOF : *i1++; }
	inline int in(void) {
		char c = gc(); int x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
	}
	inline ll inl(void) {
	char c = gc(); ll x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
	}
} using FastIO::pc; using FastIO::out; using FastIO::gc; using FastIO::in; using FastIO::inl;
const int kN = 500050 << 2;
#define div _fefq
ll tag[kN], sum[kN], set[kN], div[kN];
void pushup(int x) {
	if(tag[x << 1] != -1 && tag[x << 1 | 1] != -1 && tag[x << 1] == tag[x << 1 | 1]) 
		tag[x] = tag[x << 1];
	else tag[x] = -1; 
	sum[x] = sum[x << 1] + sum[x << 1 | 1];
}
void pushdown(int x,int L,int R) {
	//先 set 后 div
	if(set[x] != -1) {
		tag[x << 1] = tag[x << 1 | 1] = set[x << 1] = set[x << 1 | 1] = set[x];
		sum[x << 1] = (mid - L + 1) * set[x]; sum[x << 1 | 1] = (R - mid) * set[x];
		div[x << 1] = div[x << 1 | 1] = -1;
		set[x] = -1;
	}
	if(div[x] != -1) {
		tag[x << 1] /= div[x]; tag[x << 1 | 1] /= div[x];
		set[x << 1] /= div[x]; set[x << 1 | 1] /= div[x];
		sum[x << 1] = (mid - L + 1) * tag[x << 1]; sum[x << 1 | 1] = (R - mid) * tag[x << 1 | 1];
		div[x << 1] = div[x << 1 | 1] = div[x]; 
		div[x] = -1;
	}
}
void divide(int x, int L, int R, int l, int r, int d) {
	if(l <= L && R <= r && tag[x] != -1) { 
		sum[x] = (R - L + 1) * (tag[x] / d); 
		tag[x] /= d;  if(set[x] != -1) set[x] /= d; div[x] = d; return; 
	}
	pushdown(x,L,R);
	if(l <= mid) divide(x << 1,L,mid,l,r,d);
	if(mid < r) divide(x << 1 | 1, mid + 1, R, l,r,d);
	pushup(x);
}
ll query(int x, int L, int R, int l,int r) {
	if(l <= L && R <= r) return sum[x];
	pushdown(x,L,R); ll ans = 0;
	if(l <= mid) ans += query(x << 1,L,mid,l,r);
	if(mid < r) ans += query(x << 1 | 1, mid + 1, R, l,r);
	pushup(x); return ans;
}
void assign(int x,int L, int R, int l, int r, int d) {
	if(l <= L && R <= r) { set[x] = tag[x] = d, sum[x] = (R - L + 1) * d; div[x] = -1; return; }
	pushdown(x,L,R);
	if(l <= mid) assign(x << 1,L,mid,l,r,d);
	if(mid < r) assign(x << 1 | 1,mid + 1,R,l,r,d);
	pushup(x);
}
signed main() {
	memset(tag,-1,sizeof(tag));
	memset(set,-1,sizeof(set));
	memset(div,-1,sizeof(div));
	int n = in(), q = in();
	_rep(i,1,n) assign(1,1,n,i,i,in());
	while(q--) {
		int op = in(), l = in(), r = in();
		if(op == 1) divide(1,1,n,l,r,in());
		if(op == 2) assign(1,1,n,l,r,in());
		if(op == 3) printf("%lld\n", query(1,1,n,l,r));
		// _rep(i,1,n) printf("%d ", query(1,1,n,i,i));
		// puts("");
	}
	return 0;
}