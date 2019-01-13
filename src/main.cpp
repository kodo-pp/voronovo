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
    queue <int> q1, q2;
    for (int i = 0; i < 5; ++i) {
        int x;
        cin >> x;
        q1.push(x);
    }
    for (int i = 0; i < 5; ++i) {
        int x;
        cin >> x;
        q2.push(x);
    }

    int turns = 0;
    
    while (true) {
        int a1 = q1.front();
        int a2 = q2.front();
        q1.pop();
        q2.pop();

        if (((a1 != 9 || a2 != 0) && a1 > a2) || (a1 == 0 && a2 == 9)) {
            q1.push(a1);
            q1.push(a2);
        } else {
            q2.push(a1);
            q2.push(a2);
        }
        ++turns;

        if (q1.empty()) {
            cout << "second " << turns << endl;
            return 0;
        } else if (q2.empty()) {
            cout << "first " << turns << endl;
            return 0;
        } else if (turns > 1000 * 1000) {
            cout << "botva" << endl;
            return 0;
        }
    }
}
