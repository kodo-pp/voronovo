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


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    {
        int n;
        cin >> n;
    }
    string s;
    cin >> s;
    sort(s.begin(), s.end());

    array<int, 256> a;
    for (auto& i : a) {
        i = 0;
    }

    for (auto& c : s) {
        ++a[c];
    }

    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < a[i]/2; ++j) {
            cout << static_cast<char>(i);
        }
    }
    for (int i = 0; i < 256; ++i) {
        if (a[i] % 2 == 1) {
            cout << static_cast<char>(i);
            break;
        }
    }
    for (int i = 255; i >= 0; --i) {
        for (int j = 0; j < a[i]/2; ++j) {
            cout << static_cast<char>(i);
        }
    }
}
