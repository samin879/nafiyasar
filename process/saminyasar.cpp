#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class RAG {
private:
    unordered_map<string, vector<string>> graph; // Adjacency list for the graph
    unordered_set<string> processes;            // Set of all processes
    unordered_set<string> resources;            // Set of all resources
    vector<pair<string, string>> deadlocks;     // Stores deadlock edges

    bool dfs(const string& node, unordered_set<string>& visited, unordered_set<string>& recursionStack) {
        if (recursionStack.find(node) != recursionStack.end()) {
            return true; // Cycle detected
        }
        if (visited.find(node) != visited.end()) {
            return false; // Already visited, no cycle
        }

        visited.insert(node);
        recursionStack.insert(node);

        for (const string& neighbor : graph[node]) {
            if (dfs(neighbor, visited, recursionStack)) {
                deadlocks.push_back({node, neighbor}); // Store deadlock edge
                return true;
            }
        }

        recursionStack.erase(node);
        return false;
    }

public:
    void addEdge(const string& process, const string& resource) {
        graph[process].push_back(resource);
        processes.insert(process);
        resources.insert(resource);
    }

    bool detectDeadlock() {
        unordered_set<string> visited;
        unordered_set<string> recursionStack;
        deadlocks.clear(); // Clear previous deadlock data

        for (const string& process : processes) {
            if (visited.find(process) == visited.end()) {
                if (dfs(process, visited, recursionStack)) {
                    cout << "Deadlock detected!" << endl;
                    printDeadlock();
                    return true;
                }
            }
        }

        cout << "No deadlock detected." << endl;
        return false;
    }

    void printDeadlock() {
        cout << "Deadlock involves the following processes and resources:" << endl;
        for (const auto& edge : deadlocks) {
            cout << "Process " << edge.first << " -> Resource " << edge.second << endl;
        }
    }
};

int main() {
    RAG rag;

    // Add edges to the RAG (process -> resource)
    rag.addEdge("P1", "R1");
    rag.addEdge("P2", "R2");
    rag.addEdge("P3", "R3");
    rag.addEdge("R1", "P2");
    rag.addEdge("R2", "P3");
    rag.addEdge("R3", "P1");

    // Detect and print deadlock
    rag.detectDeadlock();

    return 0;
}