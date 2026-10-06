#include <iostream>
#include <string>

using namespace std;
struct Tab {
    int tabId;
    string title;
    string url;
    Tab* next;
    Tab* prev;
};

class BrowserTabManager {
private:
    Tab* current; 

public:
    BrowserTabManager() {
        current = nullptr;
    }
    void openNewTab(int id, string title, string url) {
        Tab* newTab = new Tab();
        newTab->tabId = id;
        newTab->title = title;
        newTab->url = url;
        if (current == nullptr) {
            current = newTab;
            current->next = current;
            current->prev = current;
            cout << "Opened first tab successfully!\n";
            return;
        }
        Tab* nextTab = current->next;
        current->next = newTab;
        newTab->prev = current;
        
        newTab->next = nextTab;
        nextTab->prev = newTab;
        
      
        current = newTab;
        cout << "Opened new tab successfully!\n";
    }
    void closeCurrentTab() {
        if (current == nullptr) {
            cout << "No tabs open to close.\n";
            return;
        }

        cout << "Closing tab: " << current->title << "\n";
        if (current->next == current) {
            delete current;
            current = nullptr;
            cout << "All tabs closed. Browser is empty.\n";
            return;
        }
        Tab* prevTab = current->prev;
        Tab* nextTab = current->next;

        prevTab->next = nextTab;
        nextTab->prev = prevTab;

        delete current;
        current = nextTab;
        cout << "Tab closed. Switched to next tab.\n";
    }
    void moveNext() {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }
        current = current->next;
        cout << "Moved to next tab.\n";
        displayCurrentTab();
    }
    void movePrevious() {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }
        current = current->prev;
        cout << "Moved to previous tab.\n";
        displayCurrentTab();
    }
    void displayCurrentTab() {
        if (current == nullptr) {
            cout << "No active tab.\n";
            return;
        }
        cout << "\n==== Active Tab Details ====\n";
        cout << "ID = " << current->tabId << "\n";
        cout << "Title =" << current->title << "\n";
        cout << "URL =" << current->url << "\n";
        cout << "===============================\n";
    }
    void displayForward() {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }

        Tab* temp = current;
        cout << "\n--- Tabs Forward (From Current) ---\n";
        do {
            cout << "ID: " << temp->tabId << " | Title: " << temp->title << " | URL: " << temp->url << "\n";
            temp = temp->next;
        } while (temp != current);
        cout << "-----------------------------------\n";
    }
    void displayBackward() {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }

        Tab* temp = current;
        cout << "\n--- Tabs Backward (From Current) ---\n";
        do {
            cout << "ID: " << temp->tabId << " | Title: " << temp->title << " | URL: " << temp->url << "\n";
            temp = temp->prev;
        } while (temp != current); 
        cout << "------------------------------------\n";
    }
    void searchTab(int id) {
        if (current == nullptr) {
            cout << "No tabs open to search.\n";
            return;
        }
        Tab* temp = current;
        bool found = false;

        do {
            if (temp->tabId == id) {
                cout << "\n[Tab Found!]\n";
                cout << "ID    : " << temp->tabId << "\n";
                cout << "Title : " << temp->title << "\n";
                cout << "URL   : " << temp->url << "\n";
                found = true;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!found) {
            cout << "Tab with ID " << id << " not found.\n";
        }
    }
};

int main() {
    BrowserTabManager browser;
    int choice, id;
    string title, url;

    do {
        cout << "\n=== BROWSER TAB MANAGER  ===\n";
        cout << "1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next Tab\n";
        cout << "4. Move Previous Tab\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab by ID\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Tab ID (integer): ";
                cin >> id;
                cout << "Enter Website Title: ";
                cin >> ws; 
                getline(cin, title);
                cout << "Enter URL: ";
                cin >> url;
                browser.openNewTab(id, title, url);
                break;
            case 2:
                browser.closeCurrentTab();
                break;
            case 3:
                browser.moveNext();
                break;
            case 4:
                browser.movePrevious();
                break;
            case 5:
                browser.displayCurrentTab();
                break;
            case 6:
                browser.displayForward();
                break;
            case 7:
                browser.displayBackward();
                break;
            case 8:
                cout << "Enter Tab ID to search: ";
                cin >> id;
                browser.searchTab(id);
                break;
            case 9:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
