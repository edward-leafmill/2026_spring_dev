#include <iostream>
#include <iomanip>
#include <print>

using namespace std;

int main() {

    // 3 5
    // 9.8 3.14

    float a, b;
    cin >> a >> b;

    // 5.00 + 3.00 = 8.00
    // 5.00 - 3.00 = 2.00
    // 5.00 * 3.00 = 15.00
    // 5.00 / 3.00 = 1.67

    // cout << fixed << setprecision(2);
    // cout << a << " + " << b << " = " << a+b << '\n';
    // cout << a << " - " << b << " = " << a-b << '\n';
    // cout << a << " * " << b << " = " << a*b << '\n';
    // cout << a << " / " << b << " = " << a/b << '\n';

    print("{:.2f} / {:.2f} = {:.2f}\n", a, b, a/b);
    print("{} / {} = {:.2f}\n", a, b, a/b);

    return 0;
}