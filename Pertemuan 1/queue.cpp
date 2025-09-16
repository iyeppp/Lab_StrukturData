#include <iostream>
using namespace std;

#define max 6
int queue[max];
int front = -1, rear = -1;

// enqueue
void enq(int value){
    if (rear == max -1){
        cout << "Queue penuh!" << endl;
    } else{
        if (front == -1) 
        front = 0;
        rear++;
        queue[rear] = value;
        cout << value << " Masuk ke queue." << endl;
    }
}

// dequeue
void deq(){
    if (front == -1 || front > rear){
        cout << " queue kosong!" << endl;
    } else{
        cout << queue[front] << " keluar dari queue." << endl;
        front++;
    }
}

// display
void display(){
    if ( front == -1 || front > rear){
        cout << " queue kosong!" << endl;
    } else{
        cout << "isi queue : ";
        for (int i = front; i <= rear; i++){
            cout << queue[i] << " ";
        }
        cout << endl;
    }
}

int main(){
    enq(1);
    enq(2);
    enq(3);
    enq(4);
    enq(5);

    display();
    enq(6);
    display();
    deq();
    display();

    return 0;
}