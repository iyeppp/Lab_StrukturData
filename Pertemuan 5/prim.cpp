#include <bits/stdc++.h> // Header ini mencakup hampir semua pustaka standar C++
using namespace std;

// Fungsi utilitas untuk menemukan verteks dengan
// nilai kunci (key) minimum, dari himpunan verteks
// yang belum termasuk dalam MST (Minimum Spanning Tree)
int minKey(vector<int> &key, vector<bool> &mstSet) {
  
    // Inisialisasi nilai minimum dengan nilai tak terhingga
    int min = INT_MAX, min_index;

    // Loop melalui semua verteks
    for (int v = 0; v < mstSet.size(); v++) {
        // Cek apakah verteks v belum ada di MST DAN nilai kuncinya lebih kecil dari min
        if (mstSet[v] == false && key[v] < min) {
            // Jika ya, perbarui min dan simpan indeksnya
            min = key[v];
            min_index = v;
        }
    }

    // Kembalikan indeks dari verteks dengan kunci minimum
    return min_index;
}

// Fungsi utilitas untuk mencetak
// MST yang telah dikonstruksi yang disimpan di parent[]
void printMST(vector<int> &parent, vector<vector<int>> &graph) {
    cout << "Edge \tWeight\n"; // Cetak header tabel
    int totalWeight = 0; // Inisialisasi total bobot
    
    // Loop mulai dari 1 (karena verteks 0 adalah root dan tidak punya parent)
    for (int i = 1; i < graph.size(); i++) {
        // Cetak sisi (edge) dari parent[i] ke i beserta bobotnya
        cout << parent[i] << " - " << i << " \t" << graph[parent[i]][i] << endl;
        // Tambahkan bobot sisi ini ke total bobot
        totalWeight += graph[parent[i]][i];
    }
    // Cetak total bobot dari MST
    cout << "Total weight of MST = " << totalWeight << endl;
}


// Fungsi untuk membangun dan mencetak MST untuk
// sebuah graf yang direpresentasikan menggunakan
// representasi matriks adjasensi (adjacency matrix)
void primMST(vector<vector<int>> &graph) {
    
    // Dapatkan jumlah verteks (simpul) dalam graf
    int V = graph.size();

    // Array untuk menyimpan MST yang telah dibangun
    // parent[i] akan menyimpan parent dari verteks i
    vector<int> parent(V);

    // Nilai kunci (key) yang digunakan untuk memilih sisi (edge) dengan bobot minimum
    vector<int> key(V);

    // Untuk merepresentasikan himpunan verteks yang sudah termasuk dalam MST
    vector<bool> mstSet(V);

    // Inisialisasi semua kunci (key) sebagai INFINITE (tak terhingga)
    // dan mstSet sebagai false (belum ada di MST)
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Selalu sertakan verteks pertama (verteks 0) di MST.
    // Buat kuncinya 0 agar verteks ini dipilih sebagai
    // verteks pertama.
    key[0] = 0;
    
    // Node pertama selalu merupakan root dari MST
    // Root tidak memiliki parent, jadi kita set -1
    parent[0] = -1;

    // MST akan memiliki V-1 sisi (edge)
    // Loop ini berjalan V-1 kali
    for (int count = 0; count < V - 1; count++) {
        
        // TODO (Langkah 1): Pilih verteks 'u' dengan nilai kunci (key) terkecil
        // yang belum termasuk dalam MST.
        int u = minKey(key, mstSet);

        // TODO (Langkah 2): Tandai verteks 'u' yang dipilih sebagai bagian dari MST
        mstSet[u] = true;

        // TODO (Langkah 3): Perbarui nilai kunci (key) dan indeks parent
        // dari verteks-verteks yang bertetangga dengan 'u'.
        
        // Loop melalui semua verteks (v)
        for(int v = 0; v < V; v++) {
            
            // Cek kondisi berikut:
            // 1. graph[u][v] != 0 (ada sisi/edge antara u dan v)
            // 2. mstSet[v] == false (verteks v belum ada di MST)
            // 3. graph[u][v] < key[v] (bobot sisi (u,v) lebih kecil dari kunci v saat ini)
            if(graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                // Jika semua kondisi terpenuhi, perbarui parent dari v menjadi u
                parent[v] = u;
                // dan perbarui kunci dari v menjadi bobot sisi (u,v)
                key[v] = graph[u][v];
            }
        }
    }

    // Setelah loop selesai, cetak MST yang telah dibangun
    printMST(parent, graph);
}

// Kode Driver (fungsi main)
int main() {
    // Representasi graf menggunakan matriks adjasensi
    // baris dan kolom mewakili verteks 0 hingga 8
    // graph[i][j] = bobot sisi antara i dan j
    // 0 berarti tidak ada sisi langsung
     vector<vector<int>> graph = {
        // 0   1   2   3   4   5   6   7   8
        { 0,  4,  0,  0,  0,  0,  0,  8,  0 }, // 0
        { 4,  0,  8,  0,  0,  0,  0, 11,  0 }, // 1
        { 0,  8,  0,  7,  0,  4,  0,  0,  2 }, // 2
        { 0,  0,  7,  0,  9, 14,  0,  0,  0 }, // 3
        { 0,  0,  0,  9,  0, 10,  0,  0,  0 }, // 4
        { 0,  0,  4, 14, 10,  0,  2,  0,  0 }, // 5
        { 0,  0,  0,  0,  0,  2,  0,  1,  6 }, // 6
        { 8, 11,  0,  0,  0,  0,  1,  0,  7 }, // 7
        { 0,  0,  2,  0,  0,  0,  6,  7,  0 }  // 8
     };

    // Cetak solusinya dengan memanggil fungsi primMST
    primMST(graph);

    return 0; // Program berakhir
}
