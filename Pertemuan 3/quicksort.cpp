#include <iostream>
using namespace std;

//fungsi untuk menukar dua buah elemen
void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

//fungsi untuk memilih pivot
int partition(int arr[], int low, int high){
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while(true){
        do {
            i++;
        } while(arr[i] < pivot);

        do {
            j--;
        } while(arr[j] > pivot);

        if(i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

// fungsi rekursif
void quickSort(int arr[], int low, int high){
    if (low < high){
        int pivotindex = partition(arr, low, high);

        // panggil QS
        quickSort(arr, low, pivotindex - 1);
        quickSort(arr, pivotindex + 1, high);
    }
}

int main() {
    int n;
    cout << "Masukkan jumlah elemen data: ";
    cin >> n;

    int data[n];
    cout << "Masukkan elemen-elemen data: \n";
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    // Panggil fungsi Quick Sort untuk mengurutkan data
    quickSort(data, 0, n - 1);

    cout << "Data setelah diurutkan dari terkecil hingga terbesar:\n";
    for (int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;
}