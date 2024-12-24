#include "sosmed.h"
#include <iostream>
using namespace std;
void createUser(string newUserID, adrUser &v) {
    v = new User;
    idUser(v) = newUserID;
    nextUser(v) = NULL;
    firstFollow(v) = NULL;
}

void initGraph(Graph &G) {
    firstUser(G) = NULL;
}

void addUser(Graph &G, string newUserID) {
    adrUser v;
    createUser(newUserID, v);
    if (firstUser(G) == NULL) {
        firstUser(G) = v;
    } else {
        adrUser temp = G.firstUser;
        while (nextUser(temp) != NULL) {
            temp = nextUser(temp);
        }
        nextUser(temp) = v;
    }
}

void buildGraph(Graph &G) {
    string inputstring;
    cout << "Masukkan 0 untuk berhenti." << endl;
    cout << "Masukkan Nama :";
    while (true) {
        cin >> inputstring;
        if(inputstring == "0"){
            break;
        }
        addUser(G, inputstring);
        cout << "Masukkan Nama: ";
    }
}

void addFollow(Graph &G, string ygFollow, string ygDifollow, string namaKomunitas) {
    adrUser v = firstUser(G);
    while (v != NULL && idUser(v) != ygFollow) {
        v = nextUser(v);
    }
    if (v == NULL) {
        cout << "User " << ygFollow << " tidak ditemukan!" << endl;
        return;
    }
    adrFollow newFollow = new Follow;
    destUserID(newFollow) = ygDifollow;
    komunitas(newFollow) = namaKomunitas;
    nextFollow(newFollow) = NULL;
    if (firstFollow(v) == NULL) {
        firstFollow(v) = newFollow;
    } else {
        adrFollow temp = firstFollow(v);
        while (nextFollow(temp) != NULL) {
            temp = nextFollow(temp);
        }
        nextFollow(temp) = newFollow;
    }
}

void deleteUser(Graph &G, string userID){
     adrUser userToDelete = firstUser(G);
    while (userToDelete != NULL && idUser(userToDelete) != userID) {
        userToDelete = nextUser(userToDelete);
    }

    if (userToDelete == NULL) {
        cout << "User tidak ditemukan" << endl;
        return;
    }

    adrUser currentUser = firstUser(G);
    while (currentUser != NULL) {
        if (currentUser != userToDelete) {
            adrFollow followPtr = firstFollow(currentUser);
            adrFollow prevFollow = NULL;

            while (followPtr != NULL) {
                if (destUserID(followPtr) == userID) {
                    if (prevFollow == NULL) {
                        firstFollow(currentUser) = nextFollow(followPtr);
                    } else {
                        nextFollow(prevFollow) = nextFollow(followPtr);
                    }

                    adrFollow toDelete = followPtr;
                    followPtr = nextFollow(followPtr);
                    delete toDelete;
                } else {
                    prevFollow = followPtr;
                    followPtr = nextFollow(followPtr);
                }
            }
        }
        currentUser = nextUser(currentUser);
    }

    adrFollow followPtr = firstFollow(userToDelete);
    while (followPtr != NULL) {
        adrFollow toDelete = followPtr;
        followPtr = nextFollow(followPtr);
        delete toDelete;
    }

    adrUser prev = NULL;
    currentUser = firstUser(G);
    while (currentUser != NULL && currentUser != userToDelete) {
        prev = currentUser;
        currentUser = nextUser(currentUser);
    }

    if (prev == NULL) {
        firstUser(G) = nextUser(userToDelete);
    } else {
        nextUser(prev) = nextUser(userToDelete);
    }

    delete userToDelete;
    cout << "User " << userID << " berhasil dihapus" << endl;
}

void unFollow(Graph &G, string ygFollow, string ygDifollow){
    adrUser u = firstUser(G);
    while(u != NULL && idUser(u) != ygFollow){
        u = nextUser(u);
    }

    if(u == NULL){
        cout<< "User tidak ditemukan" << endl;
        return;
    }
    adrFollow f = firstFollow(u);
    adrFollow prev = NULL;
    while(f != NULL && destUserID(f) != ygDifollow){
        prev = f;
        f = nextFollow(f);
    }

    if(f == NULL){
        cout << "User tidak mengikuti atau kesalahan pada nama." << endl;
        return;
    }

    if (prev == NULL){
        firstFollow(u) = nextFollow(f);
    } else {
        nextFollow(prev) = nextFollow(f);
    }

    delete f;
}

void showAllConnection(Graph G) {
    if (firstUser(G) == NULL) {
        cout << "graf kosong" << endl;
    } else {
        adrUser v = firstUser(G);
        while (v != NULL) {
            cout << idUser(v) << ": ";
            adrFollow e = firstFollow(v);
            if (e == NULL) {
                cout << "tidak ada user yang diikuti";
            } else {
                while (e != NULL) {
                    cout  << "-> " << destUserID(e) << "(" << komunitas(e) << ") ";
                    e = nextFollow(e);
                }
            }
            cout << endl;
            v = nextUser(v);
        }
    }
}

void showCommunityMember(Graph G, string komunitas){
    if (firstUser(G) == NULL){
        cout << "Graph kosong, tidak bisa menampilkan komunitas" << endl;
    } else {
        adrUser u = firstUser(G);
        bool adaAnggota = false;
        cout << "Daftar nama anggota komunitas " << komunitas << endl;
        while(u != NULL){
              adrFollow f = firstFollow(u);
              bool sudahDicetak = false;
              while(f != NULL){
                if(komunitas(f) == komunitas){
                    if(!sudahDicetak){
                        cout << idUser(u) << "->"  << destUserID(f) <<endl;
                        sudahDicetak = true;
                        adaAnggota = true;
                        break;
                    }
                }
                f = nextFollow(f);
              }
            cout << endl;
            u = nextUser(u);
        }
        if(!adaAnggota){
            cout << "Komunitas tidak memiliki anggota." << endl;
        }
    }
}

void showFollowing(Graph G, string nama){
    adrUser u = firstUser(G);
     while (u != NULL){
        if(idUser(u) == nama){
            break;
        }
        u = nextUser(u);
    }

    if(u == NULL){
        cout << "User tidak ditemukan." << endl;
        return;
    }

    adrFollow f = firstFollow(u);
    if (f == NULL) {
        cout << "tidak ada user yang diikuti"<<endl;
    } else {
        cout << "User yang diikuti " << nama << endl;
        while (f != NULL) {
            cout << destUserID(f) << "(" << komunitas(f) << ") ";
            f = nextFollow(f);
        }
        cout << endl;
    }
}

void showFollowedCommunityMember(Graph G, string nama, string komunitas){
    adrUser u = firstUser(G);
    while (u != NULL){
        if(idUser(u) == nama){
            break;
        }
        u = nextUser(u);
    }

    if(u == NULL){
        cout << "User tidak ditemukan." << endl;
        return;
    } else {
        adrFollow  f = firstFollow(u);
        if(f == NULL){
            cout << "User sama sekali tidak berhubungan dengan user lain." << endl;
        } else {
            cout << "Anggota dari komunitas " << komunitas << " yang diikuti " << nama << endl;
            while(f != NULL){
                if(komunitas(f) == komunitas){
                    cout << destUserID(f);
                }
                f = nextFollow(f);
                if(f!= NULL){
                    cout << " ";
                }
            }
            cout <<endl;
        }
    }
}

