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
const ll maxn = 1000005;
const ll Mod = 998244353;
const ll inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3fffffffff;
const long double pi = acosl(-1.0);

struct Query {
    int l, r, k, ans, id;
};

struct Treap {
    mt19937 sj;
    vector<ll> val, key;
    vector<int> ls, rs, siz;
    Treap(int n) : val(n + 1), key(n + 1), ls(n + 1), rs(n + 1), siz(n + 1) { }
    int cnt = 1, rt = 0;
    int add(ll x) {
        val[cnt] = x;
        key[cnt] = (ll) sj();
        siz[cnt] = 1;
        return cnt++;
    }
    void pull(int u) { siz[u] = 1 + siz[ls[u]] + siz[rs[u]]; }
    void split_val(int u, ll k, int& x, int& y) {
        if(!(x = y = u)) return;
        if(val[u] <= k) {
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
    void ins(ll x) {
        int t1, t2;
        split_val(rt, x, t1, t2);
        rt = merge(merge(t1, add(x)), t2);
    }
    void del(ll x) {
        int t1, t2, t3;
        split_val(rt, x - 1, t1, t2);
        split_val(t2, x, t2, t3);
        t2 = merge(ls[t2], rs[t2]);
        rt = merge(t1, merge(t2, t3));
    }
    ll kth(int k) {
        if(k < 1) return -INF;
        if(k > siz[rt]) return INF;
        int t1, t2, t3;
        split_rank(rt, k - 1, t1, t2);
        split_rank(t2, 1, t2, t3);
        ll res = val[t2];
        rt = merge(t1, merge(t2, t3));
        return res;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    vector<Query> query(q + 1);
    fu(i, 1, n) cin >> a[i];
    fu(i, 1, q) {
        cin >> query[i].l >> query[i].r >> query[i].k;
        query[i].id = i;
    }
    sort(query.begin() + 1, query.end(), [](Query x, Query y) {
        if(x.l == y.l) return x.r < y.r;
        return x.l < y.l;
    });

    Treap tr(n);
    for(int i = 1, l = 1, r = 0; i <= q; ++i) {
        auto& [ql, qr, k, ans, id] = query[i];
        while(r < qr) {
            tr.ins(a[++r]);
        }
        while(l < ql) {
            tr.del(a[l++]);
        }
        ans = tr.kth(k);
    }

    sort(query.begin() + 1, query.end(), [](Query x, Query y) {
        return x.id < y.id;
    });
    fu(i, 1, q) cout << query[i].ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return Nanako7_ix;
}
