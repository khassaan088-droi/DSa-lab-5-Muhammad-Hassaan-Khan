#include <iostream>
#include <string>

using namespace std;
struct Coach {
    int coachNumber;
    string coachType;
    int passengerCapacity;
    int currentPassengers;
    Coach* next;
    Coach* prev;
};

class TrainSystem {
private:
    Coach* current; 

public:
    TrainSystem() {
        current = nullptr;
    }
    void addCoach(int num, string type, int capacity, int passengers) {
        Coach* newCoach = new Coach();
        newCoach->coachNumber = num;
        newCoach->coachType = type;
        newCoach->passengerCapacity = capacity;
        newCoach->currentPassengers = passengers;
        if (current == nullptr) {
            current = newCoach;
            current->next = current;
            current->prev = current;
            cout << "First coach added successfully!\n";
            return;
        }
        Coach* tail = current->prev;

        tail->next = newCoach;
        newCoach->prev = tail;

        newCoach->next = current;
        current->prev = newCoach;

        cout << "Coach added to the train successfully!\n";
    }
    void insertAfterCoach(int targetNum, int num, string type, int capacity, int passengers) {
        if (current == nullptr) {
            cout << "The train is empty. Adding as the first coach instead.\n";
            addCoach(num, type, capacity, passengers);
            return;
        }
        Coach* target = current;
        bool found = false;

        do {
            if (target->coachNumber == targetNum) {
                found = true;
                break;
            }
            target = target->next;
        } while (target != current);

        if (!found) {
            cout << "Coach number " << targetNum << " not found!\n";
            return;
        }
        Coach* newCoach = new Coach();
        newCoach->coachNumber = num;
        newCoach->coachType = type;
        newCoach->passengerCapacity = capacity;
        newCoach->currentPassengers = passengers;
        Coach* nextCoach = target->next;

        target->next = newCoach;
        newCoach->prev = target;

        newCoach->next = nextCoach;
        nextCoach->prev = newCoach;

        cout << "Coach inserted successfully after coach " << targetNum << "!\n";
    }
    void removeCoach(int num) {
        if (current == nullptr) {
            cout << "The train is empty!\n";
            return;
        }

        Coach* temp = current;
        bool found = false;

        do {
            if (temp->coachNumber == num) {
                found = true;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!found) {
            cout << "Coach number " << num << " not found!\n";
            return;
        }

        cout << "Removing coach number: " << temp->coachNumber << "\n";
        if (temp->next == temp) {
            delete temp;
            current = nullptr;
            cout << "Train is now empty.\n";
            return;
        }

        bool wasCurrent = (temp == current);

        Coach* prevCoach = temp->prev;
        Coach* nextCoach = temp->next;

        prevCoach->next = nextCoach;
        nextCoach->prev = prevCoach;

        if (wasCurrent) {
            current = nextCoach; 
        }

        delete temp;
        cout << "Coach removed successfully.\n";
    }

    void moveForward() {
        if (current == nullptr) {
            cout << "The train is empty!\n";
            return;
        }
        current = current->next;
        cout << "Moved to next coach.\n";
        displayCurrentCoach();
    }

    void moveBackward() {
        if (current == nullptr) {
            cout << "The train is empty!\n";
            return;
        }
        current = current->prev;
        cout << "Moved to previous coach.\n";
        displayCurrentCoach();
    }
    void displayCurrentCoach() {
        if (current == nullptr) {
            cout << "No active coach.\n";
            return;
        }
        cout << "\n--- Current Coach Details ---\n";
        cout << "Coach Number : " << current->coachNumber << "\n";
        cout << "Coach Type   : " << current->coachType << "\n";
        cout << "Capacity     : " << current->passengerCapacity << "\n";
        cout << "Passengers   : " << current->currentPassengers << "\n";
        cout << "-----------------------------\n";
    }

    // 7. Display Train Clockwise (Forward)
    void displayClockwise() {
        if (current == nullptr) {
            cout << "The train is empty!\n";
            return;
        }

        Coach* temp = current;
        cout << "\n=== Train Layout (Clockwise) ===\n";
        do {
            cout << "[Coach " << temp->coachNumber << " | Type: " << temp->coachType 
                 << " | Filled: " << temp->currentPassengers << "/" << temp->passengerCapacity << "] -> ";
            temp = temp->next;
        } while (temp != current);
        cout << "(Back to start)\n================================\n";
    }

    // 8. Display Train Anti-clockwise (Backward)
    void displayAntiClockwise() {
        if (current == nullptr) {
            cout << "The train is empty!\n";
            return;
        }

        Coach* temp = current;
        cout << "\n=== Train Layout (Anti-clockwise) ===\n";
        do {
            cout << "[Coach " << temp->coachNumber << " | Type: " << temp->coachType 
                 << " | Filled: " << temp->currentPassengers << "/" << temp->passengerCapacity << "] -> ";
            temp = temp->prev;
        } while (temp != current);
        cout << "(Back to start)\n=====================================\n";
    }

    // 9. Search Coach by Number
    void searchCoach(int num) {
        if (current == nullptr) {
            cout << "The train is empty!\n";
            return;
        }

        Coach* temp = current;
        bool found = false;

        do {
            if (temp->coachNumber == num) {
                cout << "\n[Coach Found!]\n";
                cout << "Coach Number : " << temp->coachNumber << "\n";
                cout << "Coach Type   : " << temp->coachType << "\n";
                cout << "Capacity     : " << temp->passengerCapacity << "\n";
                cout << "Passengers   : " << temp->currentPassengers << "\n";
                found = true;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!found) {
            cout << "Coach number " << num << " not found!\n";
        }
    }

    // 10. Find Maximum Available Capacity (Empty Seats)
    void findMaxCapacity() {
        if (current == nullptr) {
            cout << "The train is empty!\n";
            return;
        }

        Coach* temp = current;
        Coach* bestCoach = current;
        int maxEmptySeats = (current->passengerCapacity - current->currentPassengers);

        temp = temp->next;
        while (temp != current) {
            int emptySeats = temp->passengerCapacity - temp->currentPassengers;
            if (emptySeats > maxEmptySeats) {
                maxEmptySeats = emptySeats;
                bestCoach = temp;
            }
            temp = temp->next;
        }

        cout << "\n=== Coach with Most Empty Seats ===\n";
        cout << "Coach Number : " << bestCoach->coachNumber << "\n";
        cout << "Coach Type   : " << bestCoach->coachType << "\n";
        cout << "Empty Seats  : " << maxEmptySeats << "\n";
        cout << "-----------------------------------\n";
    }
    void reverseTrain() {
        if (current == nullptr || current->next == current) {
            cout << "Train has 0 or 1 coach. Reversing has no visual effect.\n";
            return;
        }

        Coach* curr = current;
        Coach* temp = nullptr;
        do {
            temp = curr->next;
            curr->next = curr->prev;
            curr->prev = temp;
            
            curr = curr->prev; 
        } while (curr != current);

        cout << "Train direction reversed successfully by rewiring pointers[cite: 2]!\n";
    }
};

int main() {
    TrainSystem train;
    int choice, num, targetNum, cap, pass;
    string type;

    do {
        cout << "\n=== TRAIN COACH NAVIGATION SYSTEM ===\n";
        cout << "1. Add Coach (at end)\n";
        cout << "2. Insert Coach After Number\n";
        cout << "3. Remove Coach by Number\n";
        cout << "4. Move Forward\n";
        cout << "5. Move Backward\n";
        cout << "6. Display Current Coach\n";
        cout << "7. Display Train Clockwise\n";
        cout << "8. Display Train Anti-clockwise\n";
        cout << "9. Search Coach by Number\n";
        cout << "10. Find Coach with Max Empty Seats\n";
        cout << "11. Reverse Train Direction\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Coach Number: ";
                cin >> num;
                cout << "Enter Coach Type (e.g., Economy, AC): ";
                cin >> ws;
                getline(cin, type);
                cout << "Enter Passenger Capacity: ";
                cin >> cap;
                cout << "Enter Current Passengers: ";
                cin >> pass;
                train.addCoach(num, type, cap, pass);
                break;
            case 2:
                cout << "Enter existing Coach Number to insert after: ";
                cin >> targetNum;
                cout << "Enter New Coach Number: ";
                cin >> num;
                cout << "Enter Coach Type: ";
                cin >> ws;
                getline(cin, type);
                cout << "Enter Passenger Capacity: ";
                cin >> cap;
                cout << "Enter Current Passengers: ";
                cin >> pass;
                train.insertAfterCoach(targetNum, num, type, cap, pass);
                break;
            case 3:
                cout << "Enter Coach Number to remove: ";
                cin >> num;
                train.removeCoach(num);
                break;
            case 4:
                train.moveForward();
                break;
            case 5:
                train.moveBackward();
                break;
            case 6:
                train.displayCurrentCoach();
                break;
            case 7:
                train.displayClockwise();
                break;
            case 8:
                train.displayAntiClockwise();
                break;
            case 9:
                cout << "Enter Coach Number to search: ";
                cin >> num;
                train.searchCoach(num);
                break;
            case 10:
                train.findMaxCapacity();
                break;
            case 11:
                train.reverseTrain();
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
