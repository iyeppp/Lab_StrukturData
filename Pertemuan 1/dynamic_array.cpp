#include <iostream>
using namespace std;

int main(){
    system ("cls");
    int n;
    cout << "masukkan jumlah elemen array : ";
    cin >> n;

    int* arr = new int[n];

    cout << "masukkan " << n << " angka: \n";
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }

    cout << "Isi array : ";
    for (int i = 0; i<n;i++){
        cout << arr[i] << " ";
    }

    delete[] arr;
    return 0;
}