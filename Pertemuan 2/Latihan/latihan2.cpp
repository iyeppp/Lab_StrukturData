#include <iostream>
using namespace std;

// Deklarasi struktur node
struct Node{
    int value;
    Node *next;
};

Node *top = NULL;

// push
void push(int n){
    Node  *newNode = new Node;
    newNode -> value = n;
    newNode -> next = top;

    top = newNode;
    cout << n << " Ditambahkan ke-stack." << endl;
}

// pop
void pop(){
    if (top == NULL){
        cout << "Stack kosong!" << endl;
        return;
    }

    Node* temp = top;
    cout << temp->value << " Dihapus dari stack." << endl;
    top = top->next;
    delete temp;
}

// display
void display(){
    if (top == NULL){
        cout << "Stack kosong!" << endl;
        return;
    }

    Node* temp = top;
    cout << "isi linked list : ";
    while (temp!= NULL){
        cout << temp -> value << " ";
        temp = temp -> next;
    }
    cout << endl;

}

int main(){
    // push dari bawah ke atas (10->20->30)
    push(10);
    push(20);
    push(30);

    display();
    pop();
    display();

}