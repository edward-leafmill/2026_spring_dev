#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

int main(){
    
    cout << "hello, world!" << '\n';

    // 5
    // John 80
    // Jane 75
    // James 90
    // Jennifer 95
    // Josh 85

    int n;
    cin >> n;
    if (n <=0 ) return -1;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int sum = 0;
    string highest_name;
    int highest_score = 0;

    for (int i=0; i<n; ++i){
        string name;
        int score;
        
        cin >> name >> score;
        sum += score;
        if (highest_score < score ){
            highest_score = score;
            highest_name = name;
        }
    }

    cout << "Average: " << sum/n << '\n';
    cout << "Highest: " << highest_name << " " << highest_score << '\n';

    return 0;
}