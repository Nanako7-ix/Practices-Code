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

template<class Info>
struct Treap {
    mt19937 sj;
    vector<Info> info;
    vector<ll> val, key;
    vector<int> ls, rs, siz;
    int rt = 0, cnt = 1;
    Treap(int sz) : info(sz + 1), val(sz + 1), key(sz + 1), ls(sz + 1), rs(sz + 1), siz(sz + 1) { }
    int add(ll k) {
        val[cnt] = k;
        key[cnt] = (ll)sj();
        siz[cnt] = 1;
        info[cnt] = Info(k);
        return cnt++;
    }
    void pull(int u) {
        siz[u] = 1 + siz[ls[u]] + siz[rs[u]];
        info[u] = Info(val[u]) + info[ls[u]] + info[rs[u]];
    }
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
        rt = merge(merge(t1, t2), t3);
    }
    ll prv(ll x) {
        int t1, t2, t3;
        split_val(rt, x - 1, t1, t2);
        if(siz[t1] == 0) {
            rt = merge(t1, t2);
            return -INF;
        } else {
            int rk = siz[t1] - 1;
            split_rank(t1, rk, t1, t3);
            ll res = val[t3];
            rt = merge(merge(t1, t3), t2);
            return res;
        }
    }
    ll nxt(ll x) {
        int t1, t2, t3;
        split_val(rt, x, t1, t2);
        if(siz[t2] == 0) {
            rt = merge(t1, t2);
            return INF;
        } else {
            split_rank(t2, 1, t2, t3);
            ll res = val[t2];
            rt = merge(t1, merge(t2, t3));
            return res;
        }
    }
    ll kth(ll x) {
        if(x < 1) return -INF;
        if(x > siz[rt]) return INF;
        int t1, t2, t3;
        split_rank(rt, x - 1, t1, t2);
        split_rank(t2, 1, t2, t3);
        ll res = val[t2];
        rt = merge(t1, merge(t2, t3));
        return res;
    }
    ll rank(ll x) {
        int t1, t2;
        split_val(rt, x - 1, t1, t2);
        ll res = siz[t1] + 1;
        rt = merge(t1, t2);
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1), b(m + 1);
    fu(i, 1, n) cin >> a[i];
    fu(i, 1, m) cin >> b[i];

    int k = 0, cnt = 1;
    Treap<ll> tr(n);
    fu(i, 1, n) {
        tr.ins(a[i]);
        while(cnt <= m && i == b[cnt]) {
            cnt++;
            cout << tr.kth(++k) << endl;
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
