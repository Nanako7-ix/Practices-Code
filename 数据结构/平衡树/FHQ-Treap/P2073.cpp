#include<bits/stdc++.h>
#define fu(i, l, r) for(int i = l; i <= r; ++i)
#define FU(i, l, r) for(ll  i = l; i <= r; ++i)
#define re(i, l, r) for(int i = r; i >= l; --i)
#define RE(i, l, r) for(ll  i = r; i >= l; --i)
#define setpre(x) fixed << setprecision(x)
#define var auto
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
const ll maxn = 100005;
const ll Mod = 998244353;
const ll inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3fffffffff;
const long double pi = acosl(-1.0);

struct Treap {
    mt19937 sj;
    vector<pll> val, sum;
    vector<ll> key;
    vector<int> siz, ls, rs;
    int rt = 0, cnt = 1;
    Treap(int n) : val(n + 1), sum(n + 1), key(n + 1), siz(n + 1), ls(n + 1), rs(n + 1) { }
    int add(pll x) {
        key[cnt] = (ll) sj();
        val[cnt] = x;
        sum[cnt] = x;
        siz[cnt] = 1;
        return cnt++;
    }
    void pull(int u) {
        siz[u] = 1 + siz[ls[u]] + siz[rs[u]];
        sum[u].fi = val[u].fi + sum[ls[u]].fi + sum[rs[u]].fi;
        sum[u].se = val[u].se + sum[ls[u]].se + sum[rs[u]].se;
    }
    void split_val(int u, ll k, int& x, int& y) {
        if(!(x = y = u)) return;
        if(val[u].se <= k) {
            split_val(rs[u], k, rs[u], y);
        } else {
            split_val(ls[u], k, x, ls[u]);
        }
        pull(u);
    }
    void split_rank(int u, int k, int& x, int& y) {
        if(!(x = y = u)) return;
        if(siz[ls[u]] + 1 <= k) {
            split_rank(rs[u], k - siz[ls[u]] - 1, rs[u], y);
        } else {
            split_rank(ls[u], k, x, ls[u]);
        }
        pull(u);
    }
    int merge(int x, int y) {
        if(!x || !y) return x + y;
        if(key[x] > key[y]) {
            rs[x] = merge(rs[x], y);
            pull(x);
            return x;
        } else {
            ls[y] = merge(x, ls[y]);
            pull(y);
            return y;
        }
    }
    void ins(pll x) {
        int t1, t2, t3;
        split_val(rt, x.se, t1, t2);
        split_val(t1, x.se - 1, t1, t3);
        if(siz[t3]) {
            rt = merge(merge(t1, t3), t2);
        } else {
            rt = merge(merge(t1, add(x)), t2);
        }
    }
    void del(ll x) {
        int t1, t2, t3;
        split_val(rt, x - 1, t1, t2);
        split_val(t2, x, t2, t3);
        t2 = merge(ls[t2], rs[t2]);
        rt = merge(merge(t1, t2), t3);
    }
};

void solve() {
    Treap tr(maxn);
    while(1) {
        int op; cin >> op;
        if(op == -1) break;
        if(op == 1) {
            int w, c;
            cin >> w >> c;
            tr.ins({w, c});
        } else if(op == 2) {
            int qwq;
            tr.split_rank(tr.rt, tr.siz[tr.rt] - 1, tr.rt, qwq);
        } else {
            int qwq;
            tr.split_rank(tr.rt, 1, qwq, tr.rt);
        }
    }
    auto [x, y] = tr.sum[tr.rt];
    cout << x << ' ' << y << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return Nanako7_ix;
}
