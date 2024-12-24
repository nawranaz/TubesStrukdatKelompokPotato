#include <iostream>
#include "sosmed.h"
using namespace std;

int main() {
    Graph G;
    initGraph(G);

    int pilihan;
    string input1, input2, input3;

    addUser(G, "Ade");
    addUser(G, "Budi");
    addUser(G, "Caca");
    addUser(G, "Darren");
    addUser(G, "Eka");
    addUser(G, "Fateh");
    addUser(G, "Gita");
    addUser(G, "Hana");
    addUser(G, "Ira");
    addUser(G, "Joko");

    addFollow(G, "Ade", "Budi", "Kantor_A");
    addFollow(G, "Budi", "Ade", "Kantor_A");
    addFollow(G, "Ade", "Gita", "Telkom");
    addFollow(G, "Ade", "Caca", "Telkom");
    addFollow(G, "Caca", "Ade", "Telkom");
    addFollow(G, "Caca", "Fateh", "Telkom");
    addFollow(G, "Fateh", "Ade", "Telkom");
    addFollow(G, "Budi", "Darren", "ITB");
    addFollow(G, "Darren", "Eka", "ITB");
    addFollow(G, "Eka", "Darren", "ITB");
    addFollow(G, "Fateh", "Gita", "UKM_B");
    addFollow(G, "Fateh", "Hana", "UKM_B");
    addFollow(G, "Hana", "Fateh", "UKM_B");
    addFollow(G, "Gita", "Fateh", "UKM_B");
    addFollow(G, "Ira", "Gita", "Kosan_B");

    do {
    cout << "\n===== MENU SOSIAL GRAPH =====\n";
    cout << "1. Tambah User\n";
    cout << "2. Tambah Follow\n";
    cout << "3. Hapus User\n";
    cout << "4. Unfollow\n";
    cout << "5. Tampilkan Semua Koneksi\n";
    cout << "6. Tampilkan Anggota Komunitas\n";
    cout << "7. Tampilkan Following\n";
    cout << "8. Tampilkan Anggota Komunitas yang Diikuti\n";
    cout << "9. Keluar\n";
    cout << "Pilih menu: ";
    cin >> pilihan;

        switch(pilihan) {
            case 1:
                buildGraph(G);
                break;

            case 2:
                cout << "User yang follow: ";
                cin >> input1;
                cout << "User yang difollow: ";
                cin >> input2;
                cout << "Nama komunitas: ";
                cin >> input3;
                addFollow(G, input1, input2, input3);
                break;

            case 3:
                cout << "Masukkan user yang akan dihapus: ";
                cin >> input1;
                deleteUser(G, input1);
                break;

            case 4:
                cout << "User yang unfollow: ";
                cin >> input1;
                cout << "User yang di-unfollow: ";
                cin >> input2;
                unFollow(G, input1, input2);
                break;

            case 5:
                showAllConnection(G);
                break;

            case 6:
                cout << "Masukkan nama komunitas: ";
                cin >> input1;
                showCommunityMember(G, input1);
                break;

            case 7:
                cout << "Masukkan nama user: ";
                cin >> input1;
                showFollowing(G, input1);
                break;

            case 8:
                cout << "Masukkan nama user: ";
                cin >> input1;
                cout << "Masukkan nama komunitas: ";
                cin >> input2;
                showFollowedCommunityMember(G, input1, input2);
                break;

            case 9:
                cout << "Terima kasih!\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 9);

    return 0;
}
