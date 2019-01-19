//    Olymp
//    Copyright (C) 2019  Alexander Korzun
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as
//    published by the Free Software Foundation, either version 3 of the
//    License, or (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
//


#include <bits/stdc++.h>

#ifdef AAA
#define db(x) \
    std::cerr << "\x1b[1;35m[DEBUG] " << __LINE__ << "\t|\x1b[0;34m " \
    #x "\x1b[0m = \x1b[32m" << (x) << "\x1b[0m" << std::endl
#define dbx(x) \
    std::cerr << "\x1b[1;35m[DEBUG] " << __LINE__ << "\t|     \x1b[0;34m " \
    #x "\x1b[0m = \x1b[32m" << (x) << "\x1b[0m" << std::endl
#define dbs(s) \
    std::cerr << "\x1b[1;35m[DEBUG] " << __LINE__ << "\t| \x1b[0;34m " \
    << s << "\x1b[0m" << std::endl
#define dbsx(s) \
    std::cerr << "\x1b[1;35m[DEBUG] " << __LINE__ << "\t|     \x1b[0;34m " \
    << s << "\x1b[0m" << std::endl
#else
#define db(x)
#define dbx(x)
#define dbs(s)
#define dbsx(s)
#pragma GCC optimize ("O3")
#endif

using namespace std;

using ll = long long;
using ull = unsigned long long;
using LD = long double;

const LD pi = 3.141592653589793238462643383279502884L;


template <typename T>
istream& operator>>(istream& s, vector<T>& v)
{
    for (auto& i : v) {
        s >> i;
    }
    return s;
}

string output_separator = " ";


template <typename T>
ostream& operator<<(ostream& s, const vector<T>& v)
{
    for (auto& i : v) {
        s << i << output_separator;
    }
    return s;
}



int no()
{
    cout << "NO" << endl;
    return 0;
}


int yes()
{
    cout << "YES" << endl;
    return 0;
}


bool is_extr(const vector<ll>& v, ll i)
{
    if (i == 0) {
        return v[0] > v[1];
    } else if (i == (ll)v.size() - 1) {
        return v[i] > v[i-1];
    } else {
        return v[i] > v[i-1] && v[i] > v[i+1];
    }
}


ll log_up(ll n)
{
    ll log = 0;
    while ((1 << log) < n) {
        ++log;
    }
    return log;
}

ll log_down(ll n)
{
    ll log = 0;
    while ((1 << log) <= n) {
        ++log;
    }
    return log - 1;
}

template <typename T>
class SegmentTree
{
public:
    SegmentTree(const vector<T>& v, const function<T(T, T)>& func, const T& neutral):
        a(v),
        func(func),
        neutral(neutral),
        n(v.size())
    {
        build_tree();
    }

    void build_tree()
    {
        while (k <= n) {
            k *= 2;
        }
        a.resize(k, neutral);
        tree.resize(2 * k, neutral);
        add.resize(2 * k, 0);
        for (ll i = k; i < 2 * k; ++i) {
            tree[i] = a[i-k];
        }
        for (ll i = k - 1; i > 0; --i) {
            tree[i] = func(tree[2*i], tree[2*i+1]);
        }
    }

    /*
    T find(ll l, ll r)
    {
        T M = neutral;
        l += k;
        r += k;
        while (l <= r) {
            if (l % 2 == 1) {
                M = func(M, tree[l]);
            }
            if (r % 2 == 0) {
                M = func(M, tree[r]);
            }
            l = (l+1) / 2;
            r = (r-1) / 2;
        }
        return M;
    }
    */

    T find(ll l, ll r)
    {
        return _find(1, l, r, 0, k);
    }

    T _find(ll x, ll l, ll r, ll L, ll R)
    {
        push(x);
        if (R <= l || L >= r) {
            return neutral;
        } else if (R <= r && L >= l) {
            return tree[x];
        } else {
            ll M = (L + R) / 2;
            auto a = _find(2 * x,     l, r, L, M);
            auto b = _find(2 * x + 1, l, r, M, R);
            return func(a, b);
        }
    }

    void add_range(ll l, ll r, const T& v)
    {
        _add_range(1, l, r, v, 0, k);
    }


    void _add_range(ll x, ll l, ll r, const T& v, ll L, ll R)
    {
        push(x);
        if (R <= l || L >= r) {
            return;
        } else if (R <= r && L >= l) {
            add[x] += v;
        } else {
            ll M = (L + R) / 2;
            _add_range(2 * x,     l, r, v, L, M);
            _add_range(2 * x + 1, l, r, v, M, R);
        }
        push(x);
        update_tree(x/2);
    }

    void update_tree(ll x) 
    {
        if (x == 0) {
            return;
        }
        if (x < k) {
            tree[x] = func(tree[2*x], tree[2*x+1]);
        }
        update_tree(x/2);
    }

    void set(ll y, const T& v)
    {
        tree[k+y] = v;
        update_tree(k+y);
    }

    void push(ll x)
    {
        if (add[x] != 0) {
        }
        tree[x] += add[x];
        if (x < k) {
            add[2*x] += add[x];
            add[2*x+1] += add[x];
        }
        add[x] = 0;
    }

    vector<T> tree, a, add;
    function<T(T, T)> func;
    T neutral;
    ll n;
    int k = 1;
};


ll gcd(ll a, ll b)
{
    if (a == 0) {
        return b;
    } else {
        return gcd(b % a, a);
    }
}


struct Edge
{
    Edge(): a(0), b(0), w(0)
    { }

    Edge(ll a, ll b, ll w): a(a), b(b), w(w)
    { }

    bool operator<(const Edge& rhs) const
    {
        return w < rhs.w;
    }
    ll a, b, w;
};

istream& operator>>(istream& in, Edge& e)
{
    in >> e.a >> e.b >> e.w;
    return in;
}

ostream& operator<<(ostream& out, const Edge& e)
{
    out << "[" << e.a << " -> " << e.b << ": " << e.w << "]";
    return out;
}


class Dsu
{
public:
    Dsu(ll n)
        : n(n)
        , parent(n, -1)
    { }

    ll get(ll x)
    {
        ll tmp = x;
        while (parent.at(tmp) != -1) {
            tmp = parent.at(tmp);
        }

        return tmp;
    }

    void join(int a, int b)
    {
        a = get(a);
        b = get(b);
        if (a == b) {
            return;
        }

        // TODO: rank heuristic
        if (rand() & (1 << 5)) {
            parent.at(a) = b;
        } else {
            parent.at(b) = a;
        }
    }

    int n;
    vector <int> parent;
};

template <typename T>
struct Vec2
{
    Vec2(const T& x = 0, const T& y = 0): x(x), y(y)
    { }
    T x;
    T y;

    T operator*(const Vec2<T>& rhs) const
    {
        return x * rhs.x + y * rhs.y;
    }

    T operator%(const Vec2<T>& rhs) const
    {
        return x * rhs.y - y * rhs.x;
    }

    Vec2<T> operator+(const Vec2<T>& rhs) const
    {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2<T> operator-(const Vec2<T>& rhs) const
    {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2<T> operator-() const
    {
        return Vec2(-x, -y);
    }

    Vec2<T> operator*(const T& k) const
    {
        return Vec2(x * k, y * k);
    }

    Vec2<T> operator/(const T& k) const
    {
        return Vec2(x / k, y / k);
    }

    T len_sq() const
    {
        return x * x + y * y;
    }

    template <typename Out>
    Out len() const
    {
        return sqrt(static_cast<Out>(len_sq()));
    }

    LD sin(const Vec2<T>& rhs) const
    {
        return (*this % rhs) / (len<LD>() * rhs.len<LD>());
    }

    LD cos(const Vec2<T>& rhs) const
    {
        return (*this * rhs) / (len<LD>() * rhs.len<LD>());
    }

    LD tan(const Vec2<T>& rhs) const
    {
        return this->sin(rhs) / this->cos(rhs);
    }

    bool operator==(const Vec2<T>& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};


using Lvec = Vec2<LD>;

template <typename T>
istream& operator>>(istream& s, Vec2<T>& v)
{
    s >> v.x >> v.y;
    return s;
}

template <typename T>
ostream& operator<<(ostream& s, const Vec2<T>& v)
{
    s << '(' << v.x << ' ' << v.y << ')';
    return s;
}


template <typename T>
T tri_area(const Vec2<T>& AB, const Vec2<T>& AC)
{
    return (AB % AC) / 2;
}


template <typename T>
tuple<T, T, T> make_line(const Vec2<T>& a, const Vec2<T>& b)
{

    auto A = b.y - a.y;
    auto B = a.x - b.x;
    auto C = b % a;
    // C = b.x * a.y - b.y * a.x
    return make_tuple(A, B, C);
}


bool are_lines_same(ll A1, ll B1, ll C1, ll A2, ll B2, ll C2)
{
    return A1 * B2 == A2 * B1 && A1 * C2 == A2 * C1;
}


LD deg_to_rad(LD deg)
{
    return deg / 180.0 * pi;
}


LD rad_to_deg(LD rad)
{
    return rad * 180.0 / pi;
}

template <typename T>
T double_polygon_area(const vector<Vec2<T>>& pts)
{
    T sum = 0;
    ll n = pts.size();
    for (ll i = 0; i < n; ++i) {
        sum += pts[i] % pts[(i+1)%n];
    }
    return sum;
}

template <typename T>
LD polygon_area(const vector<Vec2<T>>& pts)
{
    return LD(polygon_area(pts)) / 2.0;
}


template <typename T>
using StdVectorWrapper = vector<T>;

template <
    typename Weight,
    typename Index,
    template <class> class Container1,
    template <class> class Container2
>
using GraphBase = Container1<Container2<pair<Index, Weight>>>;
using Graph = GraphBase<ll, ll, StdVectorWrapper, StdVectorWrapper>;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<ll> owners(n);
    cin >> owners;
    Graph g(n);
    for (ll i = 0; i < m; ++i) {
        ll a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back({b, owners[a] == owners[b] ? 0 : 1});
        g[b].push_back({a, owners[a] == owners[b] ? 0 : 1});
    }

    vector<ll> paths(n, -1);
    vector<ll> lengths(n, 999999999999999LL);

    deque<tuple<ll, ll, ll>> q {make_tuple(0LL, 0LL, -1LL)};
    while (!q.empty()) {
        dbs("BFS 0-1");
        ll vertex, current_weight, parent;
        tie(vertex, current_weight, parent) = q.front();
        dbx(vertex);
        dbx(current_weight);
        dbx(parent);
        q.pop_front();
        if (lengths[vertex] <= current_weight) {
            dbsx("skip");
            continue;
        }
        lengths[vertex] = current_weight;
        paths[vertex] = parent;
        for (auto& inc : g[vertex]) {
            dbx(inc.first);
            dbx(inc.second);
            if (inc.second == 0) {
                q.emplace_front(inc.first, current_weight, vertex);
            } else {
                q.emplace_back(inc.first, current_weight + 1, vertex);
            }
        }
    }
    db(paths);
    db(lengths);

    vector<ll> ans {n - 1};
    while (ans.back() != -1) {
        ans.push_back(paths[ans.back()]);
    }
    ans.pop_back();
    if (ans.back() != 0) {
        cout << "impossible" << endl;
        return 0;
    }
    reverse(ans.begin(), ans.end());

    cout << lengths.back() << ' ' << ans.size() << endl;
    for (auto& i : ans) {
        cout << i + 1 << ' ';
    }
    cout << endl;
}
