#include <bits/stdc++.h> // Header yang mencakup hampir semua pustaka standar C++
using namespace std;

// Struktur data Disjoint Set Union (DSU) atau Union-Find
// Digunakan untuk melacak komponen-komponen yang terhubung
// dan mendeteksi siklus (cycle) dengan efisien.
class DSU {
    // parent[i] = parent dari elemen i
    // rank[i] = "peringkat" atau "kedalaman" dari pohon himpunan yang diwakili oleh i
    vector<int> parent, rank;
public:
    // Constructor: dipanggil saat objek DSU dibuat
    DSU(int n) {
        parent.resize(n); // Atur ukuran vektor parent
        rank.resize(n, 1);  // Atur ukuran vektor rank, inisialisasi semua rank jadi 1
        
        // Inisialisasi: Setiap elemen adalah parent dari dirinya sendiri
        for (int i = 0; i < n; i++)
            parent[i] = i; 
    }

    // Fungsi 'find' untuk menemukan perwakilan (root) dari himpunan
    // Menggunakan optimasi "Path Compression"
    int find(int i) {
        // Base case: jika i adalah parent dari dirinya sendiri, maka i adalah root
        if (parent[i] == i)
            return i;
        
        // Rekursi dengan Path Compression:
        // Cari root dari parent[i] dan langsung sambungkan i ke root tsb.
        // Ini membuat pencarian berikutnya lebih cepat.
        return parent[i] = find(parent[i]);
    }

    // Fungsi 'unite' untuk menggabungkan dua himpunan
    // Menggunakan optimasi "Union by Rank"
    void unite(int x, int y) {
        // Cari perwakilan (root) dari himpunan x dan y
        int s1 = find(x);
        int s2 = find(y);

        // Jika s1 dan s2 tidak sama, berarti x dan y ada di himpunan berbeda
        if (s1 != s2) {
            // Optimasi Union by Rank:
            // Gabungkan pohon yang lebih pendek ke pohon yang lebih tinggi
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            }
            else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            }
            else {
                // Jika rank sama, gabung salah satu (misal s2 ke s1)
                parent[s2] = s1;
                // dan naikkan rank dari s1
                rank[s1]++;
            }
        }
    }
};

// Fungsi pembanding (comparator) untuk std::sort
// Digunakan untuk mengurutkan sisi (edge) berdasarkan bobotnya
bool comparator(vector<int> &a, vector<int> &b) {
    // a[2] adalah bobot sisi a
    // b[2] adalah bobot sisi b
    return a[2] < b[2]; // Urutkan dari bobot terkecil
}

// Fungsi untuk menemukan MST menggunakan Algoritma Kruskal
int kruskalsMST(int V, vector<vector<int>> &edges) {
    
    // Langkah 1: Urutkan semua sisi (edge) berdasarkan bobotnya (ascending)
    sort(edges.begin(), edges.end(), comparator);

    // Buat objek DSU untuk V verteks
    DSU dsu(V);
    int cost = 0; // Total bobot MST
    int count = 0; // Jumlah sisi yang sudah ditambahkan ke MST

    cout << "Edges included in the MST:\n";

    // --- PERBAIKAN ---
    // Menggunakan loop for tradisional untuk kompatibilitas yang lebih baik
    // (menggantikan 'for (auto &e : edges)')
    // Langkah 2: Iterasi melalui semua sisi yang sudah terurut
    for (int i = 0; i < edges.size(); i++) {
        // Ambil referensi ke sisi (edge) saat ini
        vector<int>& e = edges[i]; 

        // Ambil verteks u, v, dan bobot w dari sisi e
        int u = e[0];
        int v = e[1];
        int w = e[2];

        // Cek apakah u dan v berada di himpunan yang berbeda
        // dsu.find(u) != dsu.find(v) berarti menambahkan sisi ini TIDAK akan membuat siklus
        if (dsu.find(u) != dsu.find(v)) {
            // Jika tidak membuat siklus:
            // 1. Gabungkan (unite) himpunan u dan v
            dsu.unite(u, v);
            
            // 2. Tambahkan bobot sisi ke total biaya
            cost += w;
            
            // 3. Cetak sisi yang ditambahkan
            cout << u << " - " << v << " (weight " << w << ")\n";
            
            // 4. Tambah hitungan sisi. Jika sudah V-1, MST selesai.
            if (++count == V - 1) 
                break; // Hentikan loop
        }
    }
    // --- AKHIR PERBAIKAN ---


    // Cetak total bobot dari MST
    cout << "Total weight of MST = " << cost << endl;
    return cost;
}

// Fungsi main (driver code)
int main() {
    int V = 9; // Jumlah verteks (0 sampai 8)

    // Daftar sisi (Edge List)
    // Format: {sumber, tujuan, bobot}
    vector<vector<int>> edges = {
        {0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11},
        {2, 3, 7}, {2, 8, 2}, {2, 5, 4}, {3, 4, 9},
        {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1},
        {6, 8, 6}, {7, 8, 7}
    };

    // Jalankan algoritma Kruskal
    kruskalsMST(V, edges);
    
    return 0; // Program selesai
}
