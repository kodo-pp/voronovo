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

    ll n;
    cin >> n;
    vector<ll> v(n);
    cin >> v;
    v.push_back(0);

    stack<ll> st;
    ll sum = 0;

    for (ll i = 0; i < n; ++i) {
        db(i);
        if (st.empty()) {
            dbsx("Stack is empty");
            st.push(i);
            continue;
        }
        if (v[st.top()] >= v[i]) {
            dbsx("Descending");
            st.push(i);
            continue;
        }
        dbsx("Ascending, unwinding stack");
        dbx(st.top());
        dbx(v[st.top()]);
        dbx(i-1);
        dbx(v[i-1]);
        // assert(v[st.top()] >= v[i-1]);  <--- THIS IS WRONG


        while (!st.empty() && v[st.top()] <= v[i-1]) {
            dbsx("Pop v[" << st.top() << "] = " << v[st.top()]);
            st.pop();
        }

        if (st.empty()) {
            dbsx("After unwinding stack is empty");
            st.push(i);
        } else {
            dbsx("Found left max: v[" << st.top() << "] = " << v[st.top()]);
            dbsx(
                "Add " << ((i-1) - st.top()) << " * " <<
                (min(v[i], v[st.top()]) - v[i-1]) << " = " << ((i-1) - st.top()) *
                (min(v[i], v[st.top()]) - v[i-1])
            );
            sum += ((i-1) - st.top()) * (min(v[i], v[st.top()]) - v[i-1]);
            st.push(i);
        }
    }

    cout << sum << endl;
}
