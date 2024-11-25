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

struct Treap {
    mt19937 sj;
    vector<int> ls, rs, fa, siz;
    vector<ll> key;
    Treap(int n) : ls(n + 1), rs(n + 1), fa(n + 1), siz(n + 1), key(n + 1) {
        int rt = 0;
        fu(i, 1, n) {
            key[i] = (ll)sj(), siz[i] = 1;
            rt = merge(rt, i);
        }
    }
    void pull(int u) {
        siz[u] = 1 + siz[ls[u]] + siz[rs[u]];
    }
    void split(int u, int k, int& x, int& y, int fx = 0, int fy = 0) {
        if(!(x = y = u)) return;
        if(siz[ls[u]] + 1 <= k) {
            fa[u] = fx;
            split(rs[u], k - siz[ls[u]] - 1, rs[u], y, u, fy);
        } else {
            fa[u] = fy;
            split(ls[u], k, x, ls[u], fx, u);
        }
        pull(u);
    }
    int merge(int x, int y) {
        if(!x || !y) return x + y;
        if(key[x] > key[y]) {
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
    int find(int x) {
        while(fa[x]) x = fa[x];
        return x;
    }
    ll rank(int x) {
        int res = 1 + siz[ls[x]];
        for(int u = x; fa[u]; u = fa[u])
            if(u == rs[fa[u]]) res += 1 + siz[ls[fa[u]]];
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Treap tr(n);
    stack<int> stk;
    vector<int> vis(n + 1);
    while(m--) {
        char op;
        cin >> op;
        if(op == 'D') {
            int x, t1, t2;
            cin >> x;
            stk.push(x); vis[x] = 1;
            tr.split(tr.find(x), tr.rank(x) - 1, t1, t2);
            tr.split(t2, 1, t1, t2);
        } else if(op == 'R') {
            int x = stk.top();
            stk.pop(); vis[x] = 0;
            if(x > 1 && !vis[x - 1]) tr.merge(tr.find(x - 1), tr.find(x));
            if(x < n && !vis[x + 1]) tr.merge(tr.find(x), tr.find(x + 1));
        } else {
            int x; cin >> x;
            cout << tr.siz[tr.find(x)] - vis[x] << endl;
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
