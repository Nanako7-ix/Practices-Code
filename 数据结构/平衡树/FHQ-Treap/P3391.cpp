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
    int cnt = 1, rt = 0;
    vector<int> val, siz, ls, rs, key, rev;
    mt19937 rd;
    template<class it>
    Treap(int n, it a) : val(n + 1), siz(n + 1), ls(n + 1), rs(n + 1), key(n + 1), rev(n + 1) {
        rt = add(*a);
        for(int i = 1; i < n; ++i) {
            rt = merge(rt, add(*(a + i)));
        }
    }
    int add(int x) {
        val[cnt] = x;
        siz[cnt] = 1;
        key[cnt] = (int)rd();
        return cnt++;
    }
    void push(int u) {
        if(rev[u]) {
            swap(ls[u], rs[u]);
            rev[ls[u]] ^= 1;
            rev[rs[u]] ^= 1;
            rev[u] = 0;
        }
    }
    void pull(int u) {
        siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
    }
    void split(int u, int k, int& x, int& y) {
        push(u);
        if(!(x = y = u)) return;
        if(siz[ls[u]] + 1 == k) {
            y = rs[u], rs[u] = 0;
        } else if(siz[ls[u]] + 1 < k) {
            split(rs[u], k - siz[ls[u]] - 1, rs[u], y);
        } else {
            split(ls[u], k, x, ls[u]);
        }
        pull(u);
    }
    [[nodiscard]] int merge(int x, int y) {
        push(x), push(y);
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
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 2);
    iota(a.begin(), a.end(), 0);
    Treap tr(n, a.begin() + 1);
    
    for(int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        int t1, t2, t3;
        tr.split(tr.rt, r, t1, t2);
        tr.split(t1, l - 1, t1, t3);
        tr.rev[t3] ^= 1;
        tr.rt = tr.merge(tr.merge(t1, t3), t2);
    }

    for(int i =  1; i <= n; ++i) {
        int t1, t2;
        tr.split(tr.rt, 1, t1, t2);
        cout << tr.val[t1] << ' ';
        tr.rt = t2;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return Nanako7_ix;
}
