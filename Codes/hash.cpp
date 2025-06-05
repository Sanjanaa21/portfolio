#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Structure to represent a Salesforce record
struct Record {
    string id;
    string object;
    string name;
    string type;
    string last_modified;
};

// Hash map to store record ID -> list of versions
unordered_map<string, vector<Record>> salesforce_backup;

// Function to backup a record
void backupRecord(const Record& r) {
    salesforce_backup[r.id].push_back(r);
    cout << "Record " << r.id << " backed up. Total versions: "
         << salesforce_backup[r.id].size() << endl;
}

// Function to restore the latest version of a record
void restoreLatest(const string& id) {
    if (salesforce_backup.find(id) != salesforce_backup.end()) {
        const Record& latest = salesforce_backup[id].back();
        cout << "\nRestoring latest version of " << id << ":\n";
        cout << "Object: " << latest.object << endl;
        cout << "Name: " << latest.name << endl;
        cout << "Type: " << latest.type << endl;
        cout << "Last Modified: " << latest.last_modified << endl;
    } else {
        cout << "Record ID " << id << " not found." << endl;
    }
}

// Function to view all versions of a record
void viewVersions(const string& id) {
    if (salesforce_backup.find(id) != salesforce_backup.end()) {
        cout << "\nAll versions for " << id << ":\n";
        int version = 1;
        for (const Record& r : salesforce_backup[id]) {
            cout << "Version " << version++ << ": "
                 << r.name << " (Modified: " << r.last_modified << ")\n";
        }
    } else {
        cout << "No versions found for " << id << "." << endl;
    }
}

// Function to restore a specific version of a record
void restoreVersion(const string& id, int version) {
    if (salesforce_backup.find(id) != salesforce_backup.end()) {
        auto& versions = salesforce_backup[id];
        if (version >= 1 && version <= versions.size()) {
            const Record& r = versions[version - 1];
            cout << "\nRestoring version " << version << " of " << id << ":\n";
            cout << "Object: " << r.object << endl;
            cout << "Name: " << r.name << endl;
            cout << "Type: " << r.type << endl;
            cout << "Last Modified: " << r.last_modified << endl;
        } else {
            cout << "Invalid version number." << endl;
        }
    } else {
        cout << "Record not found." << endl;
    }
}

// Main function
int main() {
    // Sample records
    Record r1 = {"ACC001", "Account", "Acme Corp", "Customer", "2025-06-01"};
    Record r2 = {"ACC001", "Account", "Acme Corporation", "Customer", "2025-06-04"};
    Record r3 = {"CON001", "Contact", "Jane Doe", "Individual", "2025-06-02"};

    // Perform backup operations
    backupRecord(r1);
    backupRecord(r2);
    backupRecord(r3);

    // Restore and view operations
    restoreLatest("ACC001");
    viewVersions("ACC001");
    restoreVersion("ACC001", 1);

    return 0;
}
