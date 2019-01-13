#include <bits/stdc++.h>

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

    ll maxs = 0;

    for (ll i = 0; i < n+1; ++i) {
        if (st.empty()) {
            st.push(i);
            continue;
        }
        if (v[st.top()] <= v[i]) {
            st.push(i);
            continue;
        } else {
            ll cnt = 1;
            while (!st.empty() && v[st.top()] >= v[i]) {
                maxs = max(maxs, cnt * v[st.top()]);
                st.pop();
                ++cnt;
            }
            st.push(i);
        }
    }
    cout << maxs << endl;
}
