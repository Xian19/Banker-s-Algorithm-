#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Number of processes and resources
const int NUM_PROCESSES = 5;
const int NUM_RESOURCES = 3;

// Available resources
vector<int> available_resources {3, 3, 2};

// Maximum demand of each process
vector<vector<int>> max_demand {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// Allocated resources for each process
vector<vector<int>> allocated_resources {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// Need of each process
vector<vector<int>> need(NUM_PROCESSES, vector<int>(NUM_RESOURCES));

// Function to calculate the need matrix
void calculate_need_matrix() {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max_demand[i][j] - allocated_resources[i][j];
        }
    }
}

// Function to check if a state is safe
bool is_safe_state(vector<int>& safe_sequence) {
    calculate_need_matrix();
    vector<int> work = available_resources;
    vector<bool> finish(NUM_PROCESSES, false);
    int num_finished_processes = 0;

    while (num_finished_processes < NUM_PROCESSES) {
        bool found_safe_process = false;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                bool can_be_allocated = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_be_allocated = false;
                        break;
                    }
                }
                if (can_be_allocated) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocated_resources[i][j];
                    }
                    finish[i] = true;
                    found_safe_process = true;
                    num_finished_processes++;
                    safe_sequence.push_back(i);
                    break;
                }
            }
        }
        if (!found_safe_process) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<int> safe_sequence;
    if (is_safe_state(safe_sequence)) {
        cout << "The system is in a safe state" << endl;
        cout << "Safe sequence: ";
        for (int i = 0; i < safe_sequence.size(); i++) {
            cout << safe_sequence[i] << " ";
        }
        cout << endl;
    } else {
        cout << "The system is in an unsafe state" << endl;
    }
    return 0;
}
