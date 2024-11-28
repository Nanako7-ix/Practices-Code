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

namespace treap {
    using Val = ll;
    using Info = ll;
    mt19937 sj(time(0));
    Val val[int(1e7)];
    Info info[int(1e7)];
    int siz[int(1e7)], key[int(1e7)], ls[int(1e7)], rs[int(1e7)], fa[int(1e7)];
    int cnt = 1;
    int add(Val x) {
        val[cnt] = x;
        info[cnt] = Info(x);
        key[cnt] = (int) sj();
        siz[cnt] = 1;
        ls[cnt] = 0, rs[cnt] = 0;
        return cnt++;
    }
    void pull(int u) {
        siz[u] = 1 + siz[ls[u]] + siz[rs[u]];
        info[u] = Info(val[u]) + info[ls[u]] + info[rs[u]];
    }
    void split_val(int u, Val k, int& x, int& y, int fx = 0, int fy = 0) {
        if(!(x = y = u)) return;
        if(val[u] <= k) {
            fa[u] = fx;
            split_val(rs[u], k, rs[u], y, u, fy);
        } else {
            fa[u] = fy;
            split_val(ls[u], k, x, ls[u], fx, u);
        }
        pull(u);
    }
    void split_rnk(int u, int k, int& x, int& y, int fx = 0, int fy = 0) {
        if(!(x = y = u)) return;
        if(siz[ls[u]] + 1 <= k) {
            fa[u] = fx;
            split_rnk(rs[u], k - siz[ls[u]] - 1, rs[u], y, u, fy);
        } else {
            fa[u] = fy;
            split_rnk(ls[u], k, x, ls[u], fx, u);
        }
        pull(u);
    }
    int merge(int x, int y) {
        if(!x || !y) return x | y;
        if(key[x] < key[y]) {
            rs[x] = merge(rs[x], y);
            if(rs[x]) fa[rs[x]] = x;
            pull(x);
            return x;
        } else {
            ls[y] = merge(x, ls[y]);
            if(ls[y]) fa[ls[y]] = y;
            pull(y);
            return y;
        }
    }
    template<class... Args>
    [[nodiscard]] int mergeall(Args... args) {
        int rt = 0;
        ((rt = merge(rt, args)), ...);
        return rt;
    }
    int rank(int x) {
        int res = siz[ls[x]] + 1;
        for(int u = x; fa[u]; u = fa[u])
            if(u == rs[fa[u]])
                res += siz[ls[fa[u]]] + 1;
        return res;
    }
    int find(int x) {
        while(fa[x]) x = fa[x];
        return x;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        treap::add(x);
    }

    for(int i = 1; i <= m; ++i) {
        char op; cin >> op;
        if(op == 'M') {
            int x, y;
            cin >> x >> y;
            x = treap::find(x);
            y = treap::find(y);
            if(x == y) continue;
            treap::merge(y, x);
        } else if(op == 'D') {
            int x, t1, t2;
            cin >> x;
            int rk = treap::rank(x);
            int rt = treap::find(x);
            treap::split_rnk(rt, rk - 1, t1, t2);
        } else {
            int x, y;
            cin >> x >> y;
            int rtx = treap::find(x);
            int rty = treap::find(y);
            if(rtx != rty) {
                cout << "-1\n";
                continue;
            }
            int rkx = treap::rank(x);
            int rky = treap::rank(y);
            if(rkx > rky) swap(rkx, rky);
            int t1, t2, t3;
            treap::split_rnk(rtx, rky, t1, t3);
            treap::split_rnk(t1, rkx - 1, t1, t2);
            cout << treap::info[t2] << endl;
            treap::mergeall(t1, t2, t3);
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return Nanako7_ix;
}
