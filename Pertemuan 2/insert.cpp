#include <iostream>
using namespace std;

// Deklarasi struktur node
struct Node{
    int value;
    Node *next;
};

Node *tail = NULL;
Node *head = NULL;

// Insert di depan
void inserFirst(int n){
    Node  *newNode = new Node;
    newNode -> value = n;
    newNode -> next = NULL;

    if(head==NULL){
        head = newNode;
        tail = head;
    } else{
        newNode -> next = head;
        head = newNode;
    }
}

// Insert di belakang
void insertLast(int n){
    Node *newNode = new Node;
    newNode -> value = n;
    newNode -> next = NULL;

    if(head==NULL){
        head = newNode;
        tail = head;
    } else{
        tail -> next = newNode;
        tail = newNode;
    }
}

// Insert setelah node dengan nilai tertentu 
void insertAfter(int n, int check){
    if(head==NULL){
    cout << "List kosong, insert di depan dahulu" << endl;
    return;
    }

    Node *newNode = new Node;
    newNode -> value = n;
    newNode -> next = NULL;

    Node *p = head;
    while (p != NULL && p -> value != check){
        p = p -> next;
    }

    if(p==NULL){
        cout << "Node dengan nilai " << check << " tidak ditemukan" << endl;
        delete newNode;
    } else{
        newNode -> next = p -> next;
        p -> next = newNode;
        if (p == tail){
            tail == newNode;
        }
    }
}

// Cetak isi linked list
void printList(){
    Node *temp = head;
    cout << "isi linked list : ";
    while (temp!= NULL){
        cout << temp -> value << " -> ";
        temp = temp -> next;
    }
    cout << "NULL" << endl;
}

int main(){
    inserFirst(10);
    insertLast(20);
    insertLast(30);
    insertAfter(25, 20);
    inserFirst(5);

    printList();
    return 0;
}
