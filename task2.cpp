SS#include <iostream>
#include <string>

using namespace std;
struct Photo {
    int photoId;
    string photoName;
    string dateTaken;
    string location;
    Photo* next;
    Photo* prev;
};

class CircularPhotoAlbum {
private:
    Photo* current; 

public:
    CircularPhotoAlbum() {
        current = nullptr;
    }
    void addPhoto(int id, string name, string date, string loc) {
        Photo* newPhoto = new Photo();
        newPhoto->photoId = id;
        newPhoto->photoName = name;
        newPhoto->dateTaken = date;
        newPhoto->location = loc;
        if (current == nullptr) {
            current = newPhoto;
            current->next = current;
            current->prev = current;
            cout << "Photo added as the first item in the album!\n";
            return;
        }
        Photo* tail = current->prev;

        tail->next = newPhoto;
        newPhoto->prev = tail;

        newPhoto->next = current;
        current->prev = newPhoto;

        cout << "Photo added to the album successfully!\n";
    }
    void insertAfterCurrent(int id, string name, string date, string loc) {
        if (current == nullptr) {
            addPhoto(id, name, date, loc);
            return;
        }

        Photo* newPhoto = new Photo();
        newPhoto->photoId = id;
        newPhoto->photoName = name;
        newPhoto->dateTaken = date;
        newPhoto->location = loc;

        Photo* nextPhoto = current->next;

        current->next = newPhoto;
        newPhoto->prev = current;

        newPhoto->next = nextPhoto;
        nextPhoto->prev = newPhoto;

        cout << "Photo inserted successfully after current photo!\n";
    }
    void removePhotoById(int id) {
        if (current == nullptr) {
            cout << "Album is empty. No photos to remove.\n";
            return;
        }

        Photo* temp = current;
        bool found = false;
        do {
            if (temp->photoId == id) {
                found = true;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!found) {
            cout << "Photo with ID " << id << " not found.\n";
            return;
        }

        cout << "Removing photo: " << temp->photoName << " (ID: " << temp->photoId << ")\n";
        if (temp->next == temp) {
            delete temp;
            current = nullptr;
            cout << "Album is now empty.\n";
            return;
        }
        bool wasCurrent = (temp == current);

        Photo* prevNode = temp->prev;
        Photo* nextNode = temp->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        if (wasCurrent) {
            current = nextNode; 
        }

        delete temp;
        cout << "Photo deleted successfully.\n";
    }
    void removeCurrentPhoto() {
        if (current == nullptr) {
            cout << "No current photo to remove.\n";
            return;
        }
        removePhotoById(current->photoId);
    }
    void moveNext() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }
        current = current->next;
        cout << "Moved to next photo.\n";
        displayCurrentPhoto();
    }
    void movePrevious() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }
        current = current->prev;
        cout << "Moved to previous photo.\n";
        displayCurrentPhoto();
    }
    void displayCurrentPhoto() {
        if (current == nullptr) {
            cout << "No active photo.\n";
            return;
        }
        cout << "\n--- Current Selected Photo ---\n";
        cout << "ID=" << current->photoId << "\n";
        cout << "Name=" << current->photoName << "\n";
        cout << "Date=" << current->dateTaken << "\n";
        cout << "Location=" << current->location << "\n";
        cout << "------------------------------\n";
    }
    void displayForward() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }

        Photo* temp = current;
        cout << "\n=== Album Forward (From Current) ===\n";
        do {
            cout << "ID: " << temp->photoId << " | Name: " << temp->photoName 
                 << " | Date: " << temp->dateTaken << " | Location: " << temp->location << "\n";
            temp = temp->next;
        } while (temp != current); 
        cout << "====================================\n";
    }
    void displayBackward() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }

        Photo* temp = current;
        cout << "\n=== Album Backward (From Current) ===\n";
        do {
            cout << "ID: " << temp->photoId << " | Name: " << temp->photoName 
                 << " | Date: " << temp->dateTaken << " | Location: " << temp->location << "\n";
            temp = temp->prev;
        } while (temp != current);
        cout << "=====================================\n";
    }
    void searchPhoto(int id) {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }

        Photo* temp = current;
        bool found = false;

        do {
            if (temp->photoId == id) {
                cout << "\n[Photo Found!]\n";
                cout << "ID       : " << temp->photoId << "\n";
                cout << "Name     : " << temp->photoName << "\n";
                cout << "Date     : " << temp->dateTaken << "\n";
                cout << "Location : " << temp->location << "\n";
                found = true;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!found) {
            cout << "Photo with ID " << id << " not found in the album.\n";
        }
    }
    void countPhotos() {
        if (current == nullptr) {
            cout << "Total photos in album: 0\n";
            return;
        }

        int count = 0;
        Photo* temp = current;
        do {
            count++;
            temp = temp->next;
        } while (temp != current);

        cout << "Total photos in album: " << count << "\n";
    }
};

int main() {
    CircularPhotoAlbum album;
    int choice, id;
    string name, date, location;

    do {
        cout << "\n=== CIRCULAR PHOTO ALBUM SYSTEM ===\n";
        cout << "1. Add Photo (at end)\n";
        cout << "2. Insert Photo After Current\n";
        cout << "3. Remove Photo by ID\n";
        cout << "4. Remove Current Photo\n";
        cout << "5. Move Next Photo\n";
        cout << "6. Move Previous Photo\n";
        cout << "7. Display Current Photo\n";
        cout << "8. Display Album Forward\n";
        cout << "9. Display Album Backward\n";
        cout << "10. Search Photo by ID\n";
        cout << "11. Count Total Photos\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            case 2:
                cout << "Enter Photo ID (integer): ";
                cin >> id;
                cout << "Enter Photo Name: ";
                cin >> ws; // clear input buffer
                getline(cin, name);
                cout << "Enter Date Taken (e.g., YYYY-MM-DD): ";
                getline(cin, date);
                cout << "Enter Location: ";
                getline(cin, location);
                
                if (choice == 1) {
                    album.addPhoto(id, name, date, location);
                } else {
                    album.insertAfterCurrent(id, name, date, location);
                }
                break;
            case 3:
                cout << "Enter Photo ID to remove: ";
                cin >> id;
                album.removePhotoById(id);
                break;
            case 4:
                album.removeCurrentPhoto();
                break;
            case 5:
                album.moveNext();
                break;
            case 6:
                album.movePrevious();
                break;
            case 7:
                album.displayCurrentPhoto();
                break;
            case 8:
                album.displayForward();
                break;
            case 9:
                album.displayBackward();
                break;
            case 10:
                cout << "Enter Photo ID to search: ";
                cin >> id;
                album.searchPhoto(id);
                break;
            case 11:
                album.countPhotos();
                break;
            case 12:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 12);

    return 0;
}
