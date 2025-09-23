#include <iostream>
#include <unordered_map>
#include <ctime>
using namespace std;

// ---------------- Commit Node ----------------
class CommitNode {
public:
    int commit_id;            // Unique ID for each version
    string content;           // File content of this version
    string timestamp;         // Time when commit was made
    CommitNode* prev;         // Link to previous commit
    CommitNode* next;         // Link to next commit

    // Constructor
    CommitNode(int id, string text) {
        commit_id = id;
        content = text;

        // Save current system time as timestamp
        time_t now = time(0);
        timestamp = ctime(&now);

        prev = NULL;
        next = NULL;
    }
};

// ---------------- Version Control System ----------------
class VersionControl {
private:
    CommitNode* head;   // First commit
    CommitNode* current; // Current commit pointer
    unordered_map<int, CommitNode*> commit_map; // For fast lookup
    int commit_count;   // To assign commit IDs

public:
    // Constructor
    VersionControl() {
        head = NULL;
        current = NULL;
        commit_count = 0;
    }

    // Commit a new version
    void commit(string content) {
        commit_count++;
        CommitNode* newCommit = new CommitNode(commit_count, content);

        if (current != NULL) {
            current->next = newCommit;
            newCommit->prev = current;
        } else {
            head = newCommit;
        }

        current = newCommit;
        commit_map[commit_count] = newCommit;

        cout << "\n[master " << newCommit->commit_id << "] " << content << "\n";
    }

    // Undo → move to previous version (silent, no print)
    void undo() {
        if (current != NULL && current->prev != NULL) {
            current = current->prev;
        } else {
            cout << "\nNo previous version available.\n";
        }
    }

    // Redo → move to next version
    void redo() {
        if (current != NULL && current->next != NULL) {
            current = current->next;
            cout << "\nHEAD moved forward to commit " << current->commit_id 
                 << " -> \"" << current->content << "\"\n";
        } else {
            cout << "\nNo next version available.\n";
        }
    }

    // Show commit history (like git log)
    void showHistory() {
        CommitNode* temp = head;
        if (temp == NULL) {
            cout << "\nNo commits yet.\n";
            return;
        }
        cout << "\n=== Git Commit History (latest on top) ===\n";
        
        // Move to last commit
        while (temp->next != NULL) temp = temp->next;

        // Print backwards
        while (temp != NULL) {
            cout << "commit " << temp->commit_id;
            if (temp == current) cout << " (HEAD -> master)";
            cout << "\nDate:   " << temp->timestamp
                 << "Message: " << temp->content << "\n\n";
            temp = temp->prev;
        }
    }

    // Access version by commit ID (like git checkout <id>)
    void accessVersion(int id) {
        if (commit_map.find(id) != commit_map.end()) {
            current = commit_map[id];
            cout << "\nSwitched to commit " << id 
                 << " -> \"" << current->content << "\"\n";
        } else {
            cout << "\nInvalid commit ID.\n";
        }
    }
};

// ---------------- Main Program ----------------
int main() {
    VersionControl vcs;
    int choice;
    string content;
    int commitID;

    while (true) {
        cout << "\n======= VERSION CONTROL SYSTEM MENU =======\n";
        cout << "1. Commit a new version\n";
        cout << "2. Undo (checkout previous commit)\n";
        cout << "3. Redo (checkout next commit)\n";
        cout << "4. Show commit history (git log)\n";
        cout << "5. Access commit by ID (git checkout <id>)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter commit message/content: ";
                getline(cin, content);
                vcs.commit(content);
                break;

            case 2:
                vcs.undo();
                break;

            case 3:
                vcs.redo();
                break;

            case 4:
                vcs.showHistory();
                break;

            case 5:
                cout << "Enter commit ID: ";
                cin >> commitID;
                vcs.accessVersion(commitID);
                break;

            case 6:
                cout << "\nExiting Version Control System. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
