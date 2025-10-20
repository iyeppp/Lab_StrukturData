#include <iostream>
#include <vector>
using namespace std;

// Fungsi untuk menggabungkan dua bagian array yang sudah terurut
void merge(vector<int>& arr, int left, int mid, int right) {
   
    int n1 = mid - left + 1;  // hitung ukuran subarray kiri
    int n2 = right - mid;    // hitung ukuran subarray kanan

    vector<int> L(n1), R(n2); // buat array sementara

    // salin data ke array sementara L[] dan R[]
    for (int i = 0; i < n1; i++) 
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;    // indeks awal untuk array sementata L
    int j = 0;      // indeks awal untuk array sementara R
    int k = left; // indeks awal untuk array utama

    // proses perulangan untuk menggabungkan dua array sementara ke array utama
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { // jika array kiri lebih kecil atau sama dengan array kanan
            arr[k] = L[i]; // masukkan elemen dari array kiri ke array utama
            i++;
        } else {
            arr[k] = R[j]; // masukkan elemen dari array kanan ke array utama
            j++;
        }
        k++;
    }

    // perulangan untuk menyalin sisa elemen dari array kiri (jika ada)
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // perulangan untuk menyalin sisa elemen dari array kanan (jika ada)
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Fungsi utama merge sort
void mergeSort(vector<int>& arr, int left, int right) {
   
    if (left >= right) // jika elemen hanya 1 maka, tidak perlu dilakukan sorting jadi langsung return aja
        return;

    int mid = left + (right - left) / 2; // Menghitung indeks tengah (mid) untuk membagi array.

    mergeSort(arr, left, mid); // mergesort dipanggil secara rekursif untuk mengurutkan array kiri
    mergeSort(arr, mid + 1, right); // mergesort diapnggil secara rekursif untuk mengurutkan array kanan
   
    merge(arr, left, mid, right); // memanggil fungsi merge untuk menggabungkan 2 array (kiri dan kanan) yang sudah terurut
}

// fungsi untuk cetak array seperti biasa
void printArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main() {
    int n;
    cout << "Masukkan jumlah elemen data: ";
    cin >> n;
   
    vector<int> data(n);
    cout << "Masukkan elemen-elemen data: ";
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }
   
    // tampilan sebelum diurutkan
    cout << "Array sebelum diurutkan: ";
    printArray(data);
   
    mergeSort(data, 0, n - 1); // memanggil fungsi merge sort
   
    // tampilan setelah diurutkan
    cout << "Array setelah diurutkan: ";
    printArray(data);
   
    return 0;
}