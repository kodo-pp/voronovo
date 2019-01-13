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
    auto pairs = [](char a, char b) -> bool {
        return (a == '(' && b == ')')
            || (a == ')' && b == '(')
            || (a == '[' && b == ']')
            || (a == ']' && b == '[')
            || (a == '{' && b == '}')
            || (a == '}' && b == '{');
    };
    auto opens = [](char a) -> bool {
        return a == '(' || a == '[' || a == '{';
    };

    string s;
    cin >> s;
    stack<char> st;

    for (char c : s) {
        if (opens(c)) {
            st.push(c);
        } else {
            if (st.empty()) {
                return no();
            }
            if (!pairs(st.top(), c)) {
                return no();
            }
            st.pop();
        }
    }
    if (!st.empty()) {
        return no();
    }
    return yes();
}
