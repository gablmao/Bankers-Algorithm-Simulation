#include <iostream>
#include <vector>

using namespace std;

//assign global arrays
const int MAX_PROCESSES = 5;
const int MAX_RESOURCES = 5;

int available[MAX_RESOURCES];
int maximum_need[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];


//check if system is in a safe state or not
bool isSafeState(int processes, int resources){
    vector<bool> finish(processes, false);  //for each process, they're not completed processing yet
    int remaining[MAX_RESOURCES];  //copy of the array available 

    for (int i=0; i<resources; i++) {
        remaining[i] = available[i];
    }

    int count=0;
    while (count<processes){
        bool found = false;



        if (!found){
            return false;  //system not in safe state
        }
    }

    return true;  //system in safe state
}

bool requestResource(int process, int request[], int processes, int resources){
    if (!isSafeState(processes, resources)){
        return false;  //request cant be granted
    }

    return true;  //request is granted
}



int main(){
    int processes;
    int resources;

    cout << "Enter the number of processes: ";
    cin >> processes;

    cout << "Enter the number of resources: ";
    cin >> resources;


    cout << "Enter the available resources (must be equal to the number of resources): ";
    for (int i=0; i<resources; i++){
        cin >> available[i];
    }

    cout << "Enter the maximum need of resources for..." << endl;
    for (int i=0; i<processes; i++){  //list each process
        cout << "Process " << i << ": ";
        for (int j=0; j<resources; j++){  //for each process i, store the resources needed in j in the array maximum_need
            cin >> maximum_need[i][j];
            need[i][j] = maximum_need[i][j];
        }
    }

    cout << "Enter the allocated resources for..." << endl; 
    for (int i=0; i<processes; i++){  //list each process
        cout << "Process " << i << ": ";
        for (int j=0; j<resources; j++){  //for each process i, store the allocations j in the array allocation
            cin >> allocation[i][j];
            need[i][j] = maximum_need[i][j] = allocation[i][j];
        }
    }

    //call function to check the state of system
    //if it's in a safe state, enter the request of any process
    //enter the process' resource request, then check if it can be granted or not
    //end program

    return 0;
}