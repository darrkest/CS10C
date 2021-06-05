#include <iostream>
#include "Playlist.h"

using namespace std;

void PrintMenu(string title);

PlaylistNode* head = nullptr;
PlaylistNode* tail = nullptr;

int main() {
    string playlistTitle;
    cout << "Enter playlist's title:" << endl;                                                                  // Ask for playlist title
    getline(cin, playlistTitle);
    cout << endl;
    PrintMenu(playlistTitle);                                                                                   
    return 0;
}

void PrintMenu(string title) {
    char userInput;
    while (userInput != 'q') {                                                                                  // While 'q' isn't input, print the menu and ask for an input
        cout << title << " PLAYLIST MENU" << endl;
        cout << "a - Add song" << endl;
        cout << "d - Remove song" << endl;
        cout << "c - Change position of song" << endl;
        cout << "s - Output songs by specific artist" << endl;
        cout << "t - Output total time of playlist (in seconds)" << endl;
        cout << "o - Output full playlist" << endl;
        cout << "q - Quit" << endl;
        cout << endl;
        cout << "Choose an option:";
        cin >> userInput;
        cin.ignore();
        cout << endl;

        if (userInput == 'a') {                                                                                 // If input is 'a' (add song)
            string songID;
            string songName;
            string artistName;
            int songLength;
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;                                                          // Ask for new song details (uniqueID, name, artist, length)
            cin >> songID;
            cin.ignore();
            cout << "Enter song's name:" << endl;
            getline(cin, songName);
            cout << "Enter artist's name:" << endl;
            getline(cin, artistName);
            cout << "Enter song's length (in seconds):" << endl;
            cin >> songLength;
            cin.ignore();
            cout << endl;
           
            PlaylistNode* newNode = new PlaylistNode(songID, songName, artistName, songLength);                 // Create a node with the new song
            if (head == nullptr) {                                                                              // If the playlist is empty, set the node as the head and tail
                head = newNode;
                tail = newNode;
            }
            else {                                                                                              // If not, then insert the new song after the tail and set it as the tail
                tail->InsertAfter(newNode);
                tail = newNode;
            }
        }

        else if (userInput == 'd') {
            string songID;
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;                                                          // Ask for song ID to remove
            cin >> songID;
            cin.ignore();

            string removedName;                                                                                 // Create a string to store the name of the song being removed
            if (head->GetID() == songID) {                                                                      // Check if the first song on the playlist is the song being removed
                removedName = head->GetSongName();                                                                  // If it's the head, set removedName as the head's name
                PlaylistNode* temp = head->GetNext();                                                               // Create a temporary node that starts with the 2nd node in the playlist
                delete head;                                                                                        // Delete head since that's what is being removed
                head = temp;                                                                                        // Set head to what was originally the 2nd song of the playlist
                cout << "\"" << removedName << "\"" << " removed." << endl << endl;
            }
            else {                                                                                              // If the song being removed is not the head,
                PlaylistNode* i = head;                                                                         // Create a node to walk through the entire playlist (i)
                for (i = head; i != nullptr; i = i->GetNext())  {                                               // Walk through the playlist
                    PlaylistNode* removed = i->GetNext();                                                       // Create a node to keep track of a song in advance
                    if (removed->GetID() == songID) {                                                           // If the next song is the one being removed...
                        removedName = removed->GetSongName();                                                   // Set removedName as the song's name of the node
                        i->SetNext(removed->GetNext());                                                         // Make the current node skip over the one being removed, and point to the one after
                        delete removed;                                                                         // Delete the node being removed
                        cout << "\"" << removedName << "\"" << " removed." << endl << endl;
                        break;
                    }
                }
            }
        }
        
        else if (userInput == 'c') {
            int songPos = 0;
            int tempMax = 0;
            int i = 0;
            string newSongName;
            PlaylistNode* dataAt = nullptr;
            PlaylistNode* tempPointer = nullptr;

            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl; 
            cin >> songPos;                                 // Ask for position of song you want to move
            tempMax = songPos;      
            dataAt = head;          
            tempPointer = head;       
            i = 1;
            while (i < songPos) {                           // Traverse the playlist until the song node that is at the given position is found
                tempPointer = dataAt;               
                dataAt = dataAt->GetNext();
                ++i;
            }
            newSongName = dataAt->GetSongName();            // Once that node is found, get the song name stored in the node
            if (head == dataAt) {                           // If the head is the same node that we want to move, then
                head = dataAt->GetNext();                   // Make the 2nd node in the playlist the head
            }

            else if (tail == dataAt) {                      // In the case that the node is found at the end of the playlist,
                tempPointer->SetNext(tail->GetNext() );     // Make the 2nd to last song node point to the end of the playlist, which is null  
                tail = tempPointer;                         // And make it the tail
            }

            else {
                tempPointer->SetNext(dataAt->GetNext() );   // Otherwise set the node previous to the node being moved to point to the one after
            }
            cout << "Enter new position for song:";
            cin >> songPos;                                 // Ask for position you want to move the song to
            cout << endl;
            tempPointer = head;
            i = 2;           
            while (i < songPos) {                           // Look for the node that is before the position you want to place the song at
                tempPointer = tempPointer->GetNext();
                ++i;
            }
            if (songPos <= 1) {                             // If the specified position is either less than the beginning or is at the beginning then the song is placed first in the playlist
                dataAt->SetNext(head);                      // Make the head equal to the node that was moved since it's the first song now
                head = dataAt;
            }

            else if (songPos > (tempMax - 1)) {             // If the position given is greater than the size of the list then the song that is moved is placed at the end, as the tail 
                tail = dataAt;                              
                tempPointer->InsertAfter(dataAt); 
            }
            else {                                          // Otherwise, put the song after the song in the playlist that is before the given position
                tempPointer->InsertAfter(dataAt); 
            }
            cout << "\"" << newSongName << "\" moved to position " << songPos << endl << endl; 
        }

        else if (userInput == 's') {                                                                            // If input is 's' (output songs by specific artist)
            string userArtist;
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;                                                             // Ask for artist's name
            getline(cin, userArtist);
            cout << endl;
            PlaylistNode* i = head;                                                                             // Create a node the same as head to walk through the whole playlist
            int songCounter = 1;                                                                                // Keeps count of the position of the songs in the playlist
            for (i = head; i != nullptr; i = i->GetNext())  {                                                   // Walks through the whole playlist
                if (i->GetArtistName() == userArtist) {                                                         // If the current song has the same artist name as the one input, print the node
                    cout << songCounter << "." << endl;
                    i->PrintPlaylistNode();
                    cout << endl;
                }
                songCounter = songCounter + 1;                                                                  // After every loop, up the song counter's position
            }
        }

        else if (userInput == 't') {                                                                            // If input is 't' (output total time of playlist)
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            PlaylistNode* i = head;                                                                             // Create a node the same as head to walk through the whole playlist
            int totalTime = 0;                                                                                  // Create something to keep track of total time
            for (i = head; i != nullptr; i = i->GetNext()) {                                                    // Walks through the whole playlist
                totalTime = totalTime + i->GetSongLength();                                                     // Increase the total time of the playlist every time a new song appears in the loop
            }
            cout << "Total time: " << totalTime << " seconds" << endl << endl;                                        // Output the total time of the playlist
        }

        else if (userInput == 'o') {                                                                            // If input is 'o' (output full playlist)
            cout << title << " - OUTPUT FULL PLAYLIST" << endl;
            if (head == nullptr) {                                                                              // Checks if the playlist is empty, then outputs "Playlist is empty"
                cout << "Playlist is empty" << endl << endl;
            }
            else {                                                                                              
                PlaylistNode* i = head;                                                                         // If not, create a node the same as head to walk through the whole playlist
                int songCounter = 1;                                                                            // Keeps count of the position of the songs in the playlist
                for (i = head; i != nullptr; i = i->GetNext()) {                                                // Walks through the whole playlist
                    cout << songCounter << "." << endl;                                                         // Print the current node until the playlist ends   
                    i->PrintPlaylistNode();
                    cout << endl;
                    songCounter = songCounter + 1;
                }
            }
        }
    }
}