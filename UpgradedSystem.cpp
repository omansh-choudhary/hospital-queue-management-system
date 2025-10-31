#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

struct Patient {
    string name;
    string department;
    int priority;
    Patient* next;
    Patient(string n, string d, int p) : name(n), department(d), priority(p), next(nullptr) {}
};

class LinkedListQueue {
private:
    Patient* front;
    Patient* rear;

public:
    LinkedListQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(Patient* newPatient) {
        if (!rear) {
            front = rear = newPatient;
        } else {
            rear->next = newPatient;
            rear = newPatient;
        }
    }

    void dequeue() {
        if (!front) return;
        Patient* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
    }

    void display() {
        Patient* temp = front;
        if (!temp) {
            cout << "No patients waiting.\n";
            return;
        }
        while (temp) {
            cout << "→ " << temp->name << " (Priority: " << temp->priority << ")\n";
            temp = temp->next;
        }
    }

    bool removeByName(string name) {
        if (!front) return false;
        if (front->name == name) {
            dequeue();
            return true;
        }
        Patient* temp = front;
        while (temp->next && temp->next->name != name)
            temp = temp->next;

        if (temp->next) {
            Patient* toDelete = temp->next;
            temp->next = temp->next->next;
            if (toDelete == rear) rear = temp;
            delete toDelete;
            return true;
        }
        return false;
    }

    bool isEmpty() { return front == nullptr; }

    Patient* getFront() { return front; }
};

struct ComparePriority {
    bool operator()(Patient* a, Patient* b) {
        return a->priority < b->priority;
    }
};

class HospitalSystem {
private:
    unordered_map<string, LinkedListQueue> departmentQueues;
    priority_queue<Patient*, vector<Patient*>, ComparePriority> emergencyQueue;

public:
    void addPatient(string name, string department, int priority) {
        Patient* p = new Patient(name, department, priority);
        if (priority > 5) {
            emergencyQueue.push(p);
            cout << "Emergency patient added: " << name << " (" << department << ")\n";
        } else {
            departmentQueues[department].enqueue(p);
            cout << "Normal patient added: " << name << " (" << department << ")\n";
        }
    }

    void servePatient() {
        if (!emergencyQueue.empty()) {
            Patient* p = emergencyQueue.top();
            emergencyQueue.pop();
            cout << "Serving EMERGENCY patient: " << p->name << " (" << p->department << ")\n";
            delete p;
        } else {
            for (auto& dept : departmentQueues) {
                if (!dept.second.isEmpty()) {
                    Patient* p = dept.second.getFront();
                    cout << "Serving NORMAL patient: " << p->name << " (" << p->department << ")\n";
                    dept.second.dequeue();
                    delete p;
                    return;
                }
            }
            cout << "No patients waiting.\n";
        }
    }

    void removePatient(string department, string name) {
        if (departmentQueues.find(department) != departmentQueues.end()) {
            bool removed = departmentQueues[department].removeByName(name);
            if (removed)
                cout << "Patient " << name << " removed from " << department << " queue.\n";
            else
                cout << "Patient not found in " << department << " queue.\n";
        } else {
            cout << "Department not found.\n";
        }
    }

    void displayStatus() {
        cout << "\n=== Current Queue Status ===\n";
        cout << "Emergency Queue: " << emergencyQueue.size() << " patient(s)\n";
        for (auto& dept : departmentQueues) {
            cout << dept.first << " Department Queue:\n";
            dept.second.display();
        }
        cout << "============================\n";
    }
};

int main() {
    HospitalSystem hospital;
    int choice;

    while (true) {
        cout << "\n--- Hospital Queue Management System ---\n";
        cout << "1. Add Patient\n2. Serve Patient\n3. Remove Patient\n4. Display Status\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, department;
            int priority;
            cout << "Enter patient name: ";
            cin >> name;
            cout << "Enter department (Cardio/Dental/Ortho): ";
            cin >> department;
            cout << "Enter priority (1-10): ";
            cin >> priority;
            hospital.addPatient(name, department, priority);
        } else if (choice == 2) {
            hospital.servePatient();
        } else if (choice == 3) {
            string name, department;
            cout << "Enter department: ";
            cin >> department;
            cout << "Enter patient name to remove: ";
            cin >> name;
            hospital.removePatient(department, name);
        } else if (choice == 4) {
            hospital.displayStatus();
        } else if (choice == 5) {
            cout << "Exiting system...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
