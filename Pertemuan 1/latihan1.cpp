#include <iostream>
using namespace std;

#define maksimal 5
int stack [maksimal];
int top = -1;

//PUSH
void push(int value){
    if (top == maksimal){
        cout << "Stack penuh !" << endl;

    } else{
        top++;
        stack[top] = value;
        cout << value << " ditambahkan dalam stack" << endl;
    }
}

//pop
void pop(){
    if (top == -1){
        cout << "Stack kosong !" << endl;
    } else{
        cout << "\n" << stack[top] << " dihapus dari stack." << endl;
        top--;
    }
}

//nampilin stack
void display (){
    if (top == -1){
        cout << "Stack kosong" << endl;

    } else{
        cout << "\nisi stackk : \n";
        for (int i = top; i >= 0; i--){
            cout << stack[i] << " ";
        }
        //cout << endl << "isi array (index 0 ke maksimal-1)" << endl;
        //for (int i = 0; i < top; i++){
        //    cout << "[ " << i << " ]" << stack[i] << " ";
        //}
        //cout << endl;
    }
}

int main(){
    for (int i = 1; i < 6; i++){
        push(i*10);
    }
    for (int i = 0; i < 5; i++){
        display();
        pop();
    }

    display();
    return 0;
}
