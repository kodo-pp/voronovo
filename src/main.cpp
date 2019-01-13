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
#endif

using namespace std;

using ll = long long;
using ull = unsigned long long;


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


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;

    vector <ll> v(n);
    cin >> v;
    auto mv = v;

    vector<ll> extrs;

    ll maxv = 0;
    for (ll i = 0; i < n; ++i) {
        if (v[i] > maxv) {
            extrs.push_back(i);
            maxv = v[i];
        }
    }
    
    maxv = 0;
    for (ll i = n-1; i >= 0; --i) {
        if (v[i] > maxv) {
            extrs.push_back(i);
            maxv = v[i];
        }
    }

    sort(extrs.begin(), extrs.end());
    auto it = unique(extrs.begin(), extrs.end());
    extrs.resize(it - extrs.begin());
    
    ll m = extrs.size();
    ll sum = 0;
    for (ll i = 1; i < m; ++i) {
        auto ai = extrs[i-1];
        auto bi = extrs[i];
        auto z = min(v[ai], v[bi]);
        db(ai);
        db(bi);
        db(z);
        for (ll j = ai + 1; j <= bi - 1; ++j) {
            dbx(j);
            dbx(v[j]);
            dbx(z - v[j]);
            assert(z - v[j] >= 0);
            sum += z - v[j];
        }
    }

    cout << sum << endl;
}
