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


struct Student
{
    int grade;
    string name;

    bool operator<(const Student& rhs) const
    {
        return grade < rhs.grade;
    }
};

ostream& operator<<(ostream& s, const Student st)
{
    s << st.grade << " " << st.name;
    return s;
}


int no()
{
    cout << "no" << endl;
    return 0;
}


int yes()
{
    cout << "yes" << endl;
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
        //dbs("find(x = " << x << ", L = " << L << ", R = " << R << ", l = " << l << ", r = " << r);
        //dbx(add[x]);
        //dbx(tree[x]);
        //dbsx("push(" << x << ")");
        push(x);
        //dbx(add[x]);
        //dbx(tree[x]);
        if (R <= l || L >= r) {
            //dbsx("No intersection");
            return neutral;
        } else if (R <= r && L >= l) {
            //dbsx("Full entry");
            return tree[x];
        } else {
            //dbsx("Branching");
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
        //dbs("add_range(x = " << x << ", L = " << L << ", R = " << R << ", l = " << l << ", r = " << r << ", v = " << v);
        //dbx(add[x]);
        //dbx(tree[x]);
        //dbsx("push(" << x << ")");
        push(x);
        //dbx(add[x]);
        //dbx(tree[x]);
        if (R <= l || L >= r) {
            //dbsx("No intersection");
            return;
        } else if (R <= r && L >= l) {
            //dbsx("Full entry");
            add[x] += v;
        } else {
            //dbsx("Branching");
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
            //dbs("==> PUSH " << x);
            //db(tree[x]);
            //db(add[x]);
            //dbs("==> END PUSH");
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
    Dsu(const vector <ll>& _v)
        : v(_v)
        , n(_v.size())
        , parent(n, -1)
    { }

    int get(int x)
    {
        dbs("get(" << x << ")");
        int tmp = x;
        while (parent.at(tmp) != -1) {
            dbsx(tmp);
            tmp = parent.at(tmp);
            dbsx(tmp);
        }

        return tmp;
    }

    void join(int a, int b)
    {
        dbs("join(" << a << ", " << b << ")");
        a = get(a);
        b = get(b);
        dbx(a);
        dbx(b);
        if (a == b) {
            return;
        }

        if (rand() & (1 << 5)) {
            parent.at(a) = b;
        } else {
            parent.at(b) = a;
        }
    }

    int n;
    vector <int> parent;
    vector <ll> v;
};

struct NonCollinearError: public std::exception
{ };


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

    bool operator==(const Vec2<T>& rhs)
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
    s << v.x << ' ' << v.y;
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


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll A, B, C;
    cin >> A >> B >> C;

    Vec2<ll> m;
    cin >> m;
    
    cout << B << ' ' << -A << ' ' << A * m.y - B * m.x << endl;
}
