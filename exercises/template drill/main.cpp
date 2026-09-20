
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
class S {
    T val;

public:
    S(T value) : val{value} {}

    T& access();

    const T& access() const;

    S& operator=(const T& value);
};

template<typename T>
T& S<T>::access()
{
    return val;
}

template<typename T>
const T& S<T>::access() const
{
    return val;
}

template<typename T>
S<T>& S<T>::operator=(const T& value)
{
    val = value;
    return *this;
}

template<typename T>
void read_val(T& v)
{
    cin >> v;
}

int main()
{
    S<int> si{10};
    S<char> sc{'a'};
    S<double> sd{3.14};
    S<string> ss{"hello"};
    S<vector<int>> svi{{1, 2, 3}};

    cout << si.access() << '\n';
    cout << sc.access() << '\n';
    cout << sd.access() << '\n';
    cout << ss.access() << '\n';

    for (int x : svi.access())
        cout << x << ' ';

    cout << '\n';

    si = 50;
    cout << si.access() << '\n';

    int x;
    read_val(x);
    cout << x << '\n';
}