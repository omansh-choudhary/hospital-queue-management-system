#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Patient {
    string name;
    int id;
};

int main() {
    queue<Patient> hospitalQueue;
    int choice = 0;
    int idCounter = 1;

    while (true) {
        cout << "\n--- Hospital Queue System (Existing Version) ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Patient p;
            cout << "Enter patient name: ";
            cin >> p.name;
            p.id = idCounter++;
            hospitalQueue.push(p);
            cout << "Patient added successfully.\n";
        } 
        else if (choice == 2) {
            if (hospitalQueue.empty()) {
                cout << "No patients in queue.\n";
            } else {
                cout << "Serving patient: " << hospitalQueue.front().name << endl;
                hospitalQueue.pop();
            }
        } 
        else if (choice == 3) {
            if (hospitalQueue.empty()) {
                cout << "Queue is empty.\n";
            } else {
                queue<Patient> temp = hospitalQueue;
                cout << "Current Queue:\n";
                while (!temp.empty()) {
                    cout << "ID: " << temp.front().id << " | Name: " << temp.front().name << endl;
                    temp.pop();
                }
            }
        } 
        else if (choice == 4) {
            cout << "Exiting system.\n";
            break;
        } 
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
