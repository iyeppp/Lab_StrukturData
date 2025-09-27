#include <iostream>
#include <stack>
using namespace std;

int main(){
    stack<int>s;
    int input;

    // input berhenti kalau kamu menginput huruf
    while(cin >> input){
        s.push(input);
    } do {
        cout << s.top() << " "; s.pop();
    } while (s.size() != 0);
    cout << endl;

    return 0;
}
