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


int main()
{
    vector<Student> v;

    {
        int g;
        string s;
        while (cin >> g >> s) {
            v.push_back({g, s});
        }
    }

    stable_sort(v.begin(), v.end());

    output_separator = "\n";
    cout << v << endl;
}
