#ifndef SOSMED_H_INCLUDED
#define SOSMED_H_INCLUDED
#include <iostream>

#define firstUser(G) (G).firstUser
#define idUser(P) (P)->idUser
#define nextUser(P) (P)->nextUser
#define firstFollow(P) (P)->firstFollow
#define destUserID(P) (P)->destUserID
#define komunitas(P) (P)->komunitas
#define nextFollow(P) (P)->nextFollow
using namespace std;

struct User;
struct Follow;

typedef User* adrUser;
typedef Follow* adrFollow;

struct User{
    string idUser;
    adrUser nextUser;
    adrFollow firstFollow;
};

struct Follow {
    string destUserID;
    string komunitas;
    adrFollow nextFollow;
};

struct Graph {
    adrUser firstUser;
};

void createUser(string newUserID, adrUser &v);
void initGraph(Graph &G);
void addUser(Graph &G, string newUserID);
void buildGraph(Graph &G);
void addFollow(Graph &G, string ygFollow, string ygDifollow, string komunitas);
void deleteUser(Graph &G, string userID);
void unFollow(Graph &G, string ygFollow, string ygDifollow);
void showAllConnection(Graph G);
void showCommunityMember(Graph G, string komunitas);
void showFollowing(Graph G, string nama);
void showFollowedCommunityMember(Graph G, string nama, string komunitas);

#endif // SOSMED_H_INCLUDED
