// Program C++ untuk mencari Minimum Spanning Tree (MST)
// dari sebuah graf menggunakan Algoritma Reverse Delete
#include<bits/stdc++.h> // Header library standar C++ (mencakup semua library yang umum digunakan)
using namespace std;

// Membuat alias tipe data (shortcut) untuk pair<int, int> agar lebih mudah ditulis
typedef pair<int, int> iPair;

// Kelas Graph merepresentasikan sebuah graf tidak berarah (undirected graph)
// menggunakan representasi adjacency list
class Graph
{
    int V;    // Jumlah vertex (simpul)
    list<int> *adj; // Pointer ke array adjacency list (untuk menyimpan tetangga dari tiap vertex)
    
    // Vektor untuk menyimpan semua edge. Format: {bobot, {vertex1, vertex2}}
    vector< pair<int, iPair> > edges;

    // Fungsi utilitas rekursif untuk Depth First Search (DFS)
    // Digunakan untuk mengecek apakah graf terhubung
    void DFS(int v, bool visited[]);

public:
    Graph(int V);   // Constructor (Konstruktor)

    // fungsi untuk menambahkan edge (rusuk) ke graf
    void addEdge(int u, int v, int w);

    // Mengembalikan true jika graf terhubung (connected)
    bool isConnected();

    // Fungsi utama yang mengimplementasikan algoritma Reverse Delete MST
    void reverseDeleteMST();
};

// Implementasi Konstruktor Graph
Graph::Graph(int V)
{
    this->V = V;
    // Alokasikan memori untuk array adjacency list sebanyak V
    adj = new list<int>[V];
}

// Implementasi fungsi untuk menambah edge
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(v); // Tambahkan v ke daftar tetangga u
    adj[v].push_back(u); // Tambahkan u ke daftar tetangga v (karena graf tidak berarah)
    
    // Simpan edge beserta bobotnya ke dalam vektor edges
    edges.push_back({w, {u, v}});
}

// Implementasi fungsi utilitas DFS
void Graph::DFS(int v, bool visited[])
{
    // Tandai node saat ini sebagai sudah dikunjungi
    visited[v] = true;

    // Lakukan rekursi untuk semua vertex yang bertetangga dengan
    // vertex ini
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i]) // Jika tetangga (*i) belum dikunjungi...
            DFS(*i, visited); // ...kunjungi tetangga tersebut
}

// Mengembalikan true jika graf terhubung, selain itu false
bool Graph::isConnected()
{
    bool visited[V];
    // Inisialisasi semua vertex sebagai 'belum dikunjungi'
    memset(visited, false, sizeof(visited));

    // Cari semua vertex yang dapat dijangkau dari vertex pertama (vertex 0)
    // (Kita bisa mulai dari vertex manapun, di sini kita pilih 0)
    DFS(0, visited);

    // Periksa apakah semua vertex telah dikunjungi
    for (int i=1; i<V; i++)
        if (visited[i] == false)
            // Jika ada satu saja vertex yang tidak terjangkau (false)
            return false; // Graf tidak terhubung

    // Jika semua vertex terjangkau dari vertex 0
    return true; // Graf terhubung
}

// ------ Bagian Utama Algoritma Reverse Delete -----
// Ide utamanya: Mulai dengan semua edge, lalu hapus edge
// satu per satu dari yang terberat, selama penghapusan
// tersebut tidak membuat graf menjadi tidak terhubung.
void Graph::reverseDeleteMST()
{
    // 1. Urutkan semua edge berdasarkan bobotnya (cost) secara menaik (ascending)
    sort(edges.begin(), edges.end());

    int mst_wt = 0;   // Inisialisasi total bobot MST
    cout << "Edge (rusuk) yang termasuk dalam MST:\n";

    // 2. Iterasi melalui semua edge yang *sudah diurutkan*,
    //    namun dalam urutan *menurun* (decreasing) dari bobot terbesar ke terkecil.
    for (int i=edges.size()-1; i>=0; i--)
    {
        // Ambil detail edge saat ini
        int u = edges[i].second.first;
        int v = edges[i].second.second;

        // 3. Hapus (sementara) edge (u, v) dari graf (dari adjacency list)
        adj[u].remove(v); // Hapus v dari daftar tetangga u
        adj[v].remove(u); // Hapus u dari daftar tetangga v

        // 4. Periksa apakah graf *masih* terhubung setelah edge dihapus
        if (isConnected() == false)
        {
            // Jika graf menjadi *tidak* terhubung (disconnected) setelah penghapusan,
            // berarti edge tersebut adalah "bridge" (jembatan) dan penting untuk MST.
            
            // 5. Tambahkan kembali edge tersebut ke graf.
            adj[u].push_back(v);
            adj[v].push_back(u);

            // Edge ini adalah bagian dari MST
            cout << "(" << u << ", " << v << ") \n";
            // Tambahkan bobot edge ini ke total bobot MST
            mst_wt += edges[i].first;
        }
        // else
        // {
        //    Jika isConnected() == true, berarti edge tersebut redundan
        //    (ada jalur lain antar u dan v).
        //    Edge tersebut bisa dihapus secara permanen (kita tidak melakukan apa-apa,
        //    edge tetap terhapus dari adj list).
        // }
    }

    cout << "Total bobot MST adalah " << mst_wt;
}

// Kode driver (fungsi main untuk menjalankan program)
int main()
{
    // Buat graf seperti pada contoh
    int V = 9;
    Graph g(V);

    // menambahkan edge-edge ke dalam graf
    // format: g.addEdge(vertex1, vertex2, bobot)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    // Panggil fungsi untuk mencari dan mencetak MST
    g.reverseDeleteMST();
    
    return 0;
}