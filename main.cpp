#include <iostream>
#include <vector>

using namespace std;

int main(){
    int processes;
    int resources;

    cout << "Enter the number of processes: ";
    cin >> processes;

    cout << "Enter the number of resources: ";
    cin >> resources;

    int available[resources];
    int maximum_need[processes][resources];
    int allocation[processes][resources];

    cout << "Enter the available resources (must be equal to the number of resources): ";
    for (int i=0; i<resources; i++){
        cin >> available[i];
        //later, check if valid number of resources inputted
    }

    cout << "Enter the maximum need of resources for...";
    for (int i=0; i<processes; i++){  //list each process
        cout << "Process" << i << ": ";
        for (int j=0; j<resources; j++){  //for each process i, store the resources needed in j in the array maximum_need
            cin >> maximum_need[i][j];
        }
    }

    cout << "Enter the allocated resources for..."; 
    for (int i=0; i<processes; i++){  //list each process
        cout << "Process" << i << ": ";
        for (int j=0; j<resources; j++){  //for each process i, store the allocations j in the array allocation
            cin >> allocation[i][j];
        }
    }

    //call function to check the state of system
    //if it's in a safe state, enter the request of any process
    //enter the process' resource request, then check if it can be granted or not
    //end program

    return 0;
}