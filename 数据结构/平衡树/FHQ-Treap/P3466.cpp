/*
  Blog: https://nanako7-ix.github.io/
  VJudge: Nanako7_ix
  Codeforces: Segtree7_ix
  Luogu: Nacky7_ix
*/
#include<bits/stdc++.h>
#define fu(i, l, r) for(int i = l; i <= r; ++i)
#define FU(i, l, r) for(ll  i = l; i <= r; ++i)
#define re(i, l, r) for(int i = r; i >= l; --i)
#define RE(i, l, r) for(ll  i = r; i >= l; --i)
#define setpre(x) fixed << setprecision(x)
#define endl "\n"
#define fi first
#define se second
#define pii  pair<int, int>
#define pll  pair<ll, ll>
#define vi   vector<int>
#define vl   vector<ll>
#define vvi  vector<vector<int>>
#define vvl  vector<vector<ll>>
#define pq   priority_queue
#define eb   emplace_back
#define all(x, t) x.begin() + t, x.end()
#define Nanako7_ix 0
using ll = long long;
using namespace std;
const ll maxn = 1000005;
const ll Mod = 998244353;
const ll inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3fffffffff;
const long double pi = acosl(-1.0);
template<typename T, typename... Args> void debug(T a, Args... args) { cerr << "[" << a; ((cerr << ", " << args), ...); cerr << "]\n"; }

template<typename Val, typename Info>
struct Treap {
	static mt19937			sj;
	static vector<Val>		val;
	static vector<Info>		info;
	static vector<int>		key, ls, rs, siz;
	int rt;
	Treap() { rt = 0; }
	static int add(Val x) {
		val.emplace_back(x);
		info.emplace_back(Info(x));
		key.emplace_back((int) sj());
		siz.emplace_back(1);
		ls.emplace_back(0), rs.emplace_back(0);
		return val.size() - 1;
	}
	void pull(int u) {
		siz[u] = 1 + siz[ls[u]] + siz[rs[u]];
		info[u] = Info(val[u]) + info[ls[u]] + info[rs[u]];
	}
	void split_val(int u, Val k, int& x, int& y) {
		if(!(x = y = u)) return;
		if(val[u] <= k) {
			split_val(rs[u], k, rs[u], y);
		} else {
			split_val(ls[u], k, x, ls[u]);
		}
		pull(u);
	}
	void split_rnk(int u, int k, int& x, int& y) {
		if(!(x = y = u)) return;
		if(siz[ls[u]] + 1 <= k) {
			split_rnk(rs[u], k - siz[ls[u]] - 1, rs[u], y);
		} else {
			split_rnk(ls[u], k, x, ls[u]);
		}
		pull(u);
	}
	[[nodiscard]] int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		if(key[x] < key[y]) {
			rs[x] = merge(rs[x], y);
			pull(x);
			return x;
		} else {
			ls[y] = merge(x, ls[y]);
			pull(y);
			return y;
		}
	}
	template<class... Args>
	void mergeall(Args... args) {
		rt = 0;
		((rt = merge(rt, args)), ...);
	}
};

template<typename Val, typename Info> mt19937 Treap<Val, Info>::sj(std::chrono::steady_clock::now().time_since_epoch().count());
template<typename Val, typename Info> vector<Val> Treap<Val, Info>::val(1);
template<typename Val, typename Info> vector<Info> Treap<Val, Info>::info(1);
template<typename Val, typename Info> vector<int> Treap<Val, Info>::key(1);
template<typename Val, typename Info> vector<int> Treap<Val, Info>::ls(1);
template<typename Val, typename Info> vector<int> Treap<Val, Info>::rs(1);
template<typename Val, typename Info> vector<int> Treap<Val, Info>::siz(1);

using treap = Treap<ll, ll>;

void solve() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n + 1);
	fu(i, 1, n) cin >> a[i];

	treap tr;
	ll L, R, ans = INF, qwq;
	for(int i = 1, l = 1, r = 0; i <= n - k + 1; ++i) {
		while(r < i + k - 1) {
			int x = a[++r], t1, t2;
			tr.split_val(tr.rt, x, t1, t2);
			tr.mergeall(t1, treap::add(x), t2);
		}
		while(l < i) {
			int x = a[l++], t1, t2, t3;
			tr.split_val(tr.rt, x - 1, t1, t2);
			tr.split_val(t2, x, t2, t3);
			tr.mergeall(t1, treap::ls[t2], treap::rs[t2], t3);
		}
		assert(r - l + 1 == k);
		ll res = 0;
		int t1, t2, t3;
		tr.split_rnk(tr.rt, k / 2, t1, t2);
		tr.split_rnk(t2, 1, t2, t3);
		res += abs(treap::info[t1] - treap::siz[t1] * treap::val[t2]);
		res += abs(treap::info[t2] - treap::siz[t2] * treap::val[t2]);
		res += abs(treap::info[t3] - treap::siz[t3] * treap::val[t2]);
		if(res < ans) {
			ans = res;
			L = l, R = r, qwq = treap::val[t2];
		}
		tr.mergeall(t1, t2, t3);
	}

	cout << ans << endl;
	// assert(R - L + 1 == k);
	for(int i = 1; i <= n; ++i) {
		if(L <= i && i <= R) {
			cout << qwq << endl;
		} else cout << a[i] << endl;
	}
}

signed main() {
	cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
	int T = 1;
	// cin >> T;
	while(T--) solve();
	return Nanako7_ix;
}
