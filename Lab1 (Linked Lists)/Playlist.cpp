#include <iostream>
#include "Playlist.h"
using namespace std;

PlaylistNode::PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string newID, string newSong, string newArtist, int newLength) {
    uniqueID = newID;
    songName = newSong;
    artistName = newArtist;
    songLength = newLength;
    nextNodePtr = nullptr;
}

string PlaylistNode::GetID() const {
    return uniqueID;
}
string PlaylistNode::GetSongName() const{
    return songName;
}

string PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

void PlaylistNode::SetNext(PlaylistNode* newNode) {
    nextNodePtr = newNode;
}

void PlaylistNode::InsertAfter(PlaylistNode* newNode) {
    PlaylistNode* temp = nextNodePtr;
    nextNodePtr = newNode;
    newNode->SetNext(temp);
}

void PlaylistNode::PrintPlaylistNode() {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}
