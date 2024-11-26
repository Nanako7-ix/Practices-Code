/*
  Blog: https://nanako7-ix.github.io/
  VJudge: Nanako7_ix
  Codeforces: Segtree7_ix
  Luogu: Nacky7_ix
*/
#include<bits/stdc++.h>
#include<bits/extc++.h>
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

// 不支持修改和区间查询
// 不设置根节点，需要用 find
// mergeall 改为返回 int
struct Treap {
    mt19937 sj;
    vector<ll> val;
    vector<int> key, ls, rs, fa, siz;
    Treap() : val(1), key(1), ls(1), rs(1), fa(1), siz(1) { }
    int add(ll x) {
        val.emplace_back(x);
        key.emplace_back((int) sj());
        siz.emplace_back(1);
        ls.emplace_back(0), rs.emplace_back(0), fa.emplace_back(0);
        return val.size() - 1;
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
    [[nodiscard]] int merge(int x, int y) {
        if(!x || !y) return x ^ y;
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
    auto splitall(int rt, Args... args) {
        constexpr int N = sizeof...(args);
        array<int, N + 1> res {forward<Args>(args)..., rt};
        for(int i = N; i; --i)
            split(res[i], res[i - 1], res[i - 1], res[i]);
        return res;
    }
    template<class... Args>
    int mergeall(Args... args) {
        int rt = 0;
        ((rt = merge(rt, args)), ...);
        return rt;
    }
    int find(int u) {
        while(fa[u]) u = fa[u];
        return u;
    }
    int rank(int x) {
        int res = 1 + siz[ls[x]];
        for(int u = x; fa[u]; u = fa[u]) {
            if(rs[fa[u]] == u) res += 1 + siz[ls[fa[u]]];
        }
        return res;
    }
};

void solve() {
    int n, m, rt = 0;
    cin >> n >> m;
    vector<int> p(n + 1);
    Treap tr;
    fu(i, 1, n) {
        int x; cin >> x;
        p[x] = i;
        rt = tr.mergeall(rt, tr.add(x));
    }
    for(int i = 1; i <= m; ++i) {
        string op;
        cin >> op;
        if(op == "Top") {
            int x; cin >> x;
            x = tr.rank(p[x]);
            auto [t1, t2, t3] = tr.splitall(rt, x - 1, x);
            rt = tr.mergeall(t2, t1, t3);
        } else if(op == "Bottom") {
            int x; cin >> x;
            x = tr.rank(p[x]);
            auto [t1, t2, t3] = tr.splitall(rt, x - 1, x);
            rt = tr.mergeall(t1, t3, t2);
        } else if(op == "Insert") {
            int x, t;
            cin >> x >> t;
            if(t == 0) continue;
            x = tr.rank(p[x]);
            if(t == 1) {
                auto [t1, t2, t3, t4] = tr.splitall(rt, x - 1, x, x + 1);
                rt = tr.mergeall(t1, t3, t2, t4);
            } else {
                auto [t1, t2, t3, t4] = tr.splitall(rt, x - 2, x - 1, x);
                rt = tr.mergeall(t1, t3, t2, t4);
            }
        } else if(op == "Ask") {
            int s; cin >> s;
            cout << tr.rank(p[s]) - 1 << endl;
        } else {
            int x; cin >> x;
            auto [t1, t2, t3] = tr.splitall(rt, x - 1, x);
            cout << tr.val[t2] << endl;
            rt = tr.mergeall(t1, t2, t3);
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
