#include<bits/stdc++.h>
#define fu(i, l, r) for(int i = l; i <= r; ++i)
#define FU(i, l, r) for(ll  i = l; i <= r; ++i)
#define re(i, l, r) for(int i = r; i >= l; --i)
#define RE(i, l, r) for(ll  i = r; i >= l; --i)
#define preset(x) fixed << setprecision(x)
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
const ll Mod = 1000000;
const ll inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3fffffffff;
const long double pi = acosl(-1.0);

struct Treap {
    mt19937 sj;
    vector<ll> val, key;
    vector<int> ls, rs, siz;
    int cnt = 1, rt = 0;
    Treap(int n) : val(n + 1), key(n + 1), ls(n + 1), rs(n + 1), siz(n + 1) {}
    int add(ll k) {
        val[cnt] = k, key[cnt] = (int)sj(), siz[cnt] = 1;
        return cnt++;
    }
    void pull(int u) {
        siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
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
        if(siz[ls[u]] + 1 == k) {
            y = rs[u], rs[u] = 0;
        } else if(siz[ls[u]] + 1 < k){
            split_rank(rs[u], k - siz[ls[u]] - 1, rs[u], y);
        } else {
            split_rank(ls[u], k, x, ls[u]);
        }
        pull(u);
    }
    [[nodiscard]] int merge(int x, int y) {
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
        rt = merge(t1, merge(t2, t3));
    }
    ll prev(ll k) {
        int t1, t2, t3;
        split_val(rt, k - 1, t1, t2);
        if(siz[t1] == 0) {
            rt = merge(t1, t2);
            return -INF;
        } else {
            split_rank(t1, siz[t1] - 1, t1, t3);
            ll res = val[t3];
            rt = merge(merge(t1, t3), t2);
            return res;
        }
    }
    ll next(ll k) {
        int t1, t2, t3;
        split_val(rt, k, t1, t2);
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
    ll work(ll k) {
        ll prv = prev(k), nxt = next(k);
        assert(prv != -INF || nxt != INF);
        if(k - prv <= nxt - k) {
            del(prv);
            return k - prv;
        } else {
            del(nxt);
            return nxt - k;
        }
    }
};

void solve() {
    int n;
    cin >> n;
    Treap a(n + 1), b(n + 1);
    int now = 0;
    ll ans = 0;
    while(n--) {
        int op, x;
        cin >> op >> x;
        if(op == 0) {
            if(now > 0) (ans += a.work(x)) %= Mod;
            else b.ins(x);
            now--;
        } else {
            if(now < 0) (ans += b.work(x)) %= Mod;
            else a.ins(x);
            now++;
        }
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return Nanako7_ix;
}
