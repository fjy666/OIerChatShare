#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 1006000, p = 19930726;
int n = in();
ll k = inl();
int ch[kN][26], fail[kN], len[kN], nc, last, degree[kN], in1[kN];
ll cnt[kN];
char s[kN];
void build(void) { nc = 1, fail[0] = fail[1] = 1, len[1] = -1; }
int get_fail(int x,int i) { while(s[i - len[x] - 1] != s[i]) x = fail[x]; return x; }
void insert(int i) {
	int x = get_fail(last, i);
	if(!ch[x][s[i] - 'a']) {
		++nc, len[nc] = len[x] + 2, fail[nc] = ch[get_fail(fail[x], i)][s[i] - 'a'], 
		ch[x][s[i] - 'a'] = nc; ++degree[fail[nc]];
	}
	last = ch[x][s[i] - 'a']; ++cnt[last];
}
struct Triple {
	int length;
	ll count;
	int node;
	bool operator < (const Triple &rhs) const {
		return length < rhs.length;
	}
};
priority_queue<Triple,vector<Triple>,less<Triple> > q;
void dfs(int x) {
	// printf("x = %d, turn = %d\n", x, turn);
	_rep(i, 0, 25) if(ch[x][i])	dfs(ch[x][i]);
	if(degree[x] == 0) q.push(Triple{len[x], cnt[x], x});
}
int fpm(int a, ll b) {
	int res = 1;
	for(;b; b >>= 1, a = (ll) a * a % p) if(b & 1) res = (ll) res * a % p;
	return res;
}
int main() { 
	scanf("%s", s + 1);
	build();
	_rep(i,1,n) insert(i);
	dfs(1), dfs(0);
	ll res = 1;
	while(!q.empty() && k > 0) {
		Triple u = q.top(); q.pop();
		if(fail[u.node] > 1) {
			int fa = fail[u.node];
			cnt[fa] += u.count;
			--degree[fa];
			if(!degree[fa])
				q.push(Triple{len[fa], cnt[fa], fa});
		}
		if(u.length & 1) { //必须为奇数
			ll red = min(k, u.count);
			res = res * fpm(u.length, red) % p;
			k -= red; 
		}
	}
	if(k > 0) puts("-1"); else printf("%lld\n", res);
	return 0;
}