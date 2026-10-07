#include <iostream>
#include <string>

using namespace std;

// node struct for doubly linked list
struct SongNode {
    int songID;
    string songName;
    string duration;
    SongNode* prev;
    SongNode* next;
};

// playlist class using doubly linked list
class Playlist {
private:
    SongNode* head;
    SongNode* tail;
    SongNode* currentSong; // pointer to current playing song
public:
    // constructor
    Playlist() {
        head = nullptr;
        tail = nullptr;
        currentSong = nullptr;
    }
    //adding song at the end of playlist
    void addSong(int id, string name, string dur) {
        SongNode* newNode = new SongNode();
        newNode->songID = id;
        newNode->songName = name;
        newNode->duration = dur;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            currentSong = head;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "song added successfully." << endl;
    }
    // delete song by id
    void deleteSong(int id) {
        if (head == nullptr) {
            cout << "playlist is empty." << endl;
            return;
        }
        SongNode* temp = head;
        while (temp != nullptr && temp->songID != id) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "song with id " << id << " not found." << endl;
            return;
        }
        // update current song pointer if deleting the currently playing song
        if (currentSong == temp) {
            if (temp->next != nullptr) {
                currentSong = temp->next;
            } else {
                currentSong = temp->prev;
            }
        }
        // if single node
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
            currentSong = nullptr;
        }
        // if deleting head node
        else if (temp == head) {
            head = head->next;
            head->prev = nullptr;
        }
        // if deleting tail node
        else if (temp == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        // if deleting middle node
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;
        cout << "song with id " << id << " deleted successfully." << endl;
    }
    // display playlist forward (head to tail)
    void displayForward() {
        if (head == nullptr) {
            cout << "playlist is empty." << endl;
            return;
        }
        cout << "\nplaylist (forward):" << endl;
        SongNode* temp = head;
        while (temp != nullptr) {
            cout << "id: " << temp->songID << "\n name: " << temp->songName << " \n duration: " << temp->duration << endl;
            temp = temp->next;
        }
    }
    // display playlist backward 
    void displayBackward() {
        if (tail == nullptr) {
            cout << "playlist is empty." << endl;
            return;
        }
        cout << "\nplaylist (backward):" << endl;
        SongNode* temp = tail;
        while (temp != nullptr) {
            cout << "id: " << temp->songID << " \n name: " << temp->songName << " \n duration: " << temp->duration << endl;
            temp = temp->prev;
        }
    }
    // search song by id
    void searchSong(int id) {
        if (head == nullptr) {
            cout << "playlist is empty." << endl;
            return;
        }
        SongNode* temp = head;
        while (temp != nullptr) {
            if (temp->songID == id) {
                cout << "song found: ID = " << temp->songID << "\n Name = " << temp->songName << "\n Duration = " << temp->duration << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "song with id " << id << " not found." << endl;
    }
    // play next song
    void playNext() {
        if (head == nullptr || currentSong == nullptr) {
            cout << "playlist is empty." << endl;
            return;
        }
        if (currentSong->next == nullptr) {
            cout << "already at the end of playlist. current song: " << currentSong->songName << endl;
        } else {
            currentSong = currentSong->next;
            cout << "now playing: " << currentSong->songName << endl;
        }    }

    // play previous song
    void playPrevious() {
        if (head == nullptr || currentSong == nullptr) {
            cout << "playlist is empty." << endl;
            return;
        }
        if (currentSong->prev == nullptr) {
            cout << "already at the beginning of playlist. current song: " << currentSong->songName << endl;
        } else {
            currentSong = currentSong->prev;
            cout << "now playing: " << currentSong->songName << " (" << currentSong->duration << ")" << endl;
        }
    }

    // reverse playlist in place by swapping pointers
    void reversePlaylist() {
        if (head == nullptr || head->next == nullptr) {
            cout << "playlist reversed." << endl;
            return;
        }
        SongNode* curr = head;
        SongNode* temp = nullptr;

        // swap prev and next pointers for each node
        while (curr != nullptr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        // swap head and tail
        tail = head;
        head = temp->prev;
        cout << "playlist reversed successfully in place." << endl;
    }

    // destructor to free memory
    ~Playlist() {
        SongNode* temp = head;
        while (temp != nullptr) {
            SongNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        currentSong = nullptr;
    }
};

int main() {
    Playlist playlist;
    int choice, id;
    string name, dur;

    do {
        cout << "\n1 Add Song" << endl;
        cout << "2 Delete Song" << endl;
        cout << "3 Display Playlist Forward" << endl;
        cout << "4 Display Playlist Backward" << endl;
        cout << "5 Search Song" << endl;
        cout << "6 Play Next Song" << endl;
        cout << "7 Play Previous Song" << endl;
        cout << "8 Reverse Playlist" << endl;
        cout << "9 Exit" << endl;
        cout << "enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Song ID: ";
                cin >> id;
                cin.ignore();
                cout << "enter song name: ";
                getline(cin, name);
                cout << "enter duration (e.g 3:45): ";
                getline(cin, dur);
                playlist.addSong(id, name, dur);
                break;
            case 2:
                cout << "Enter song ID to delete: ";
                cin >> id;
                playlist.deleteSong(id);
                break;
            case 3:
                playlist.displayForward();
                break;
            case 4:
                playlist.displayBackward();
                break;
            case 5:
                cout << "Enter song ID to search: ";
                cin >> id;
                playlist.searchSong(id);
                break;
            case 6:
                playlist.playNext();
                break;
            case 7:
                playlist.playPrevious();
                break;
            case 8:
                playlist.reversePlaylist();
                break;
            case 9:
                cout << "exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 9);
    return 0;
}