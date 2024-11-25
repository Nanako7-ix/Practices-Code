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
const ll maxn = 100005;
const ll Mod = 998244353;
const ll inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3fffffffff;
const long double pi = acosl(-1.0);

struct Treap {
    mt19937 rd;
    vector<ll> val;
    vector<int> ls, rs, key, siz;
    int cnt, rt, t1, t2, t3;
    Treap(int sz) : val(sz), ls(sz), rs(sz), key(sz), siz(sz), cnt(1), rt(0) {}
    int add(ll x) {
        key[cnt] = (int)rd();
        val[cnt] = x;
        siz[cnt] = 1;
        return cnt++;
    }
    void upd(int x) {
        siz[x] = siz[ls[x]] + siz[rs[x]] + 1;
    }
    void split_val(int u, ll k, int& x, int& y) {
        if(!(x = y = u)) return;
        if(val[u] > k) {
            y = u;
            split_val(ls[u], k, x, ls[u]);
        }
        else {
            x = u;
            split_val(rs[u], k, rs[u], y);
        }
        upd(u);
    }
    [[nodiscard]] int merge(int x, int y) {
        if(!x || !y) return x + y;
        if(key[x] > key[y]) {
            rs[x] = merge(rs[x], y);
            upd(x);
            return x;
        } else {
            ls[y] = merge(x, ls[y]);
            upd(y);
            return y;
        }
    }
    void ins(ll x) {
        split_val(rt, x, t1, t2);
        rt = merge(merge(t1, add(x)), t2);
    }
    void del(ll x) {
        split_val(rt, x, t1, t2);
        split_val(t1, x - 1, t1, t3);
        t3 = merge(ls[t3], rs[t3]);
        rt = merge(merge(t1, t3), t2);
    }
    int rank(ll x) {
        split_val(rt, x - 1, t1, t2);
        int res = siz[t1];
        rt = merge(t1, t2);
        return res + 1;
    }
    ll kth(int x) {
        int u = rt;
        while(1) {
            if(x <= siz[ls[u]]) u = ls[u];
            else {
                x -= siz[ls[u]] + 1;
                if(!x) return val[u];
                u = rs[u];
            }
        }
    }
    ll pre(ll x) {
        split_val(rt, x - 1, t1, t2);
        int sz = siz[t1];
        rt = merge(t1, t2);
        return kth(sz);
    }
    ll nxt(ll x) {
        split_val(rt, x, t1, t2);
        int sz = siz[t1] + 1;
        rt = merge(t1, t2);
        return kth(sz);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Treap tr((n + m) << 1);
    fu(i, 1, n) {
        ll x; cin >> x;
        tr.ins(x);
    }

    ll last = 0, ans = 0;
    while(m--) {
        int op, x;
        cin >> op >> x;
        x ^= last;
        if(op == 1) {
            tr.ins(x);
        } else if(op == 2) {
            tr.del(x);
        } else if(op == 3) {
            ans ^= (last = tr.rank(x));
        } else if(op == 4) {
            ans ^= (last = tr.kth(x));
        } else if(op == 5) {
            ans ^= (last = tr.pre(x));
        } else ans ^= (last = tr.nxt(x));
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
