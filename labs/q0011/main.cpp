#include <iostream>
#include <iomanip>
#include <print>

using namespace std;

int main() {

    // 5
    // John 80
    // Jane 75
    // James 90
    // Jennifer 95
    // Josh 85

    int n;
    cin >> n;

    int sum = 0;
    int highest_score = 0;
    string highest_name;

    for (int i=0; i<n; ++i){
        string name;
        int score;
        cin >> name >> score;

        sum += score;
        if (highest_score < score){
            highest_score = score;
            highest_name = name;
        }
    }

    cout << "Average: " << sum/n << '\n';
    cout << "Highest: " << highest_name << " " << highest_score<< '\n';

    return 0;
}