#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct Patient {
    string name;
    string department;
    int priority;
};

struct ComparePriority {
    bool operator()(Patient const& p1, Patient const& p2) {
        return p1.priority < p2.priority;
    }
};

class HospitalSystem {
private:
    unordered_map<string, queue<Patient>> departmentQueues;
    priority_queue<Patient, vector<Patient>, ComparePriority> emergencyQueue;

public:
    HospitalSystem() {
        departmentQueues["Cardio"] = queue<Patient>();
        departmentQueues["Dental"] = queue<Patient>();
        departmentQueues["Ortho"] = queue<Patient>();
    }

    void addPatient(string name, string department, int priority) {
        Patient p = {name, department, priority};
        if (priority > 5) {
            emergencyQueue.push(p);
            cout << "🚨 Emergency patient added: " << name << " (" << department << ")\n";
        } else {
            if (departmentQueues.find(department) == departmentQueues.end()) {
                departmentQueues[department] = queue<Patient>();
            }
            departmentQueues[department].push(p);
            cout << "👤 Normal patient added: " << name << " (" << department << ")\n";
        }
    }

    void servePatient() {
        if (!emergencyQueue.empty()) {
            Patient p = emergencyQueue.top();
            emergencyQueue.pop();
            cout << "\n✅ Serving EMERGENCY patient: " << p.name << " (" << p.department << ")\n";
        } else {
            bool served = false;
            for (auto& dept : departmentQueues) {
                if (!dept.second.empty()) {
                    Patient p = dept.second.front();
                    dept.second.pop();
                    cout << "\n🩺 Serving NORMAL patient: " << p.name << " (" << p.department << ")\n";
                    served = true;
                    break;
                }
            }
            if (!served) cout << "\n⚠️ No patients waiting.\n";
        }
    }

    void displayStatus() {
        cout << "\n=== Current Queue Status ===\n";
        cout << "Emergency Queue: " << emergencyQueue.size() << " patient(s)\n";
        for (auto& dept : departmentQueues) {
            cout << dept.first << " Department Queue: " << dept.second.size() << " patient(s)\n";
        }
        cout << "============================\n";
    }
};

int main() {
    HospitalSystem hospital;
    int choice;

    while (true) {
        cout << "\n--- Hospital Queue Management System ---\n";
        cout << "1. Add Patient\n2. Serve Patient\n3. Display Status\n4. Exit\n";
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
        } 
        else if (choice == 2) {
            hospital.servePatient();
        } 
        else if (choice == 3) {
            hospital.displayStatus();
        } 
        else if (choice == 4) {
            cout << "\nExiting system... Thank you!\n";
            break;
        } 
        else {
            cout << "\n❌ Invalid choice. Try again.\n";
        }
    }

    return 0;
}
