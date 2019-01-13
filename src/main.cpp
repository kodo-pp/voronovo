#include <bits/stdc++.h>

using namespace std;


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
    int n, m;
    cin >> n >> m;

    unordered_map<string, int> mp;
    for (int i = 0; i < m; ++i) {
        int x;
        string s;
        cin >> x >> s;
        mp[s] = x;
    }

    vector<int> v(n, 0);
    for (const auto& i : mp) {
        ++v[i.second - 1];
    }

    cout << v;
}
