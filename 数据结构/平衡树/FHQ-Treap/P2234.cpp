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
const ll Mod = 998244353;
const ll inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3fffffffff;
const long double pi = acosl(-1.0);

struct Treap {
    mt19937 sj;
    vector<int> val, siz, key, ls, rs;
    int cnt = 1, rt = 0;
    Treap(int n) : val(n + 1), siz(n + 1), key(n + 1), ls(n + 1), rs(n + 1) { }
    int add(int x) {
        val[cnt] = x, siz[cnt] = 1, key[cnt] = (int)sj();
        return cnt++;
    }
    void pull(int u) {
        siz[u] = 1 + siz[ls[u]] + siz[rs[u]];
    }
    void split(int u, int k, int& x, int& y) {
        if(!(x = y = u)) return;
        if(val[x] <= k) {
            split(rs[u], k, rs[u], y);
        } else {
            split(ls[u], k, x, ls[u]);
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
    void ins(int x) {
        int t1, t2;
        split(rt, x, t1, t2);
        rt = merge(merge(t1, add(x)), t2);
    }
    int kth(int k) {
        if(k < 1) return -inf;
        if(k > siz[rt]) return inf;
        int u = rt;
        while(1) {
            if(siz[ls[u]] >= k) u = ls[u];
            else {
                k -= siz[ls[u]] + 1;
                if(!k) return val[u];
                u = rs[u];
            }
        }
    }
    int prv(int x) {
        int t1, t2;
        split(rt, x, t1, t2);
        int sz = siz[t1];
        rt = merge(t1, t2);
        return kth(sz);
    }
    int nxt(int x) {
        int t1, t2;
        split(rt, x, t1, t2);
        int sz = siz[t1] + 1;
        rt = merge(t1, t2);
        return kth(sz);
    }
};

void solve() {
    ll n, sum = 0;
    cin >> n >> sum;
    Treap tr(n);
    tr.ins(sum);
    
    for(int i = 2; i <= n; ++i) {
        int x, t1, t2;
        cin >> x;
        tr.split(tr.rt, x, t1, t2);
        int sz = tr.siz[t1];
        tr.rt = tr.merge(t1, t2);
        sum += min(tr.kth(sz + 1) - x, x - tr.kth(sz));
        tr.ins(x);
    }

    cout << sum << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return Nanako7_ix;
}
