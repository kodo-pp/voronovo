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
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    cin >> v;

    multiset<int> ms;
    for (int i = 0; i < k; ++i) {
        ms.insert(v[i]);
    }
    v.push_back(-0xBAD);
    for (int i = 0; i < n - k + 1; ++i) {
        cout << *ms.begin() << endl;
        ms.erase(ms.find(v[i]));
        ms.insert(v[i + k]);
    }
}
