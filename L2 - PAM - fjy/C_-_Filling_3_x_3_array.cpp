#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

namespace FastIO { //by fjy666
	char OBuf[1 << 23], *p = OBuf;
	inline void pc(char c) { *p++=c; }
	inline void out(ll x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
	inline void out(int x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
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

int main() {
	int h1 = in(), h2 = in(), h3 = in(),
		w1 = in(), w2 = in(), w3 = in();
	int cnt = 0;
	_rep(a11, 1, min(h1 - 2, w1 - 2)) 
		_rep(a21, 1, min(w1 - a11 - 1, h2 - 2)) 
			_rep(a12, 1, min(h1 - a11 - 1, w2 - 2))
				_rep(a22, 1, min(h2 - a21 - 1, w2 - a12 - 1)) {
					int a31 = w1 - a11 - a21, a13 = h1 - a11 - a12;
					int a32 = w2 - a12 - a22, a23 = h2 - a21 - a22;
					int a33_1 = h3 - a31 - a32; 
					int a33_2 = w3 - a13 - a23;
					if(a33_1 > 0 && a33_2 > 0 && a33_1 == a33_2) ++cnt;
				} 
	out(cnt);
	return 0;
}
//丢人啊。。。