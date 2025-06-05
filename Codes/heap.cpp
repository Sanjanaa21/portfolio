#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Lead {
    string name;
    int score;

    // Custom comparator for max-heap
    bool operator<(const Lead& other) const {
        return score < other.score; // Max-heap (highest score at top)
    }
};

int main() {
    priority_queue<Lead> leadHeap;

    // Insert leads
    leadHeap.push({"Alice", 87});
    leadHeap.push({"Bob", 91});
    leadHeap.push({"Carol", 78});
    leadHeap.push({"Dave", 94});
    leadHeap.push({"Eve", 88});

    // Display top leads
    int topN = 3;
    cout << "Top " << topN << " Leads by Score:" << endl;
    for (int i = 0; i < topN && !leadHeap.empty(); ++i) {
        Lead topLead = leadHeap.top();
        cout << topLead.name << " (Score: " << topLead.score << ")" << endl;
        leadHeap.pop();
    }

    return 0;
}
