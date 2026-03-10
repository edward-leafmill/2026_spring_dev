#include <iostream>
#include <print>

using namespace std;

int main() {
    float a, b;
    cin >> a >> b;

    print("{:.2f} + {:.2f} = {:.2f}\n", a, b, a + b);
    print("{:.2f} - {:.2f} = {:.2f}\n", a, b, a - b);
    print("{:.2f} * {:.2f} = {:.2f}\n", a, b, a * b);
    print("{:.2f} / {:.2f} = {:.2f}\n", a, b, a / b);
    
    return 0;
}