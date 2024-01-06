#include <iostream>

using namespace std;

//assign global arrays
const int MAX_PROCESSES = 5;
const int MAX_RESOURCES = 5;

int available[MAX_RESOURCES];  //number of resources available
int maximum_need[MAX_PROCESSES][MAX_RESOURCES];  //max resources one process can request
int allocation[MAX_PROCESSES][MAX_RESOURCES];  //number of resources allocated to a process
int need[MAX_PROCESSES][MAX_RESOURCES];  //number of resources a process needs to complete


/*
example array representation:
need = {
  {1, 2, 2},
  {0, 1, 0},
  {1, 0, 0},
  {1, 1, 0}
}
for each first [], another array of length in second [] is created
*/


//check if system is in a safe state or not
bool isSafeState(int processes, int resources){
    bool finish[MAX_PROCESSES] = {false};  //for each process, they're not completed processing yet
    
    //copy of the array available 
    int current_available[MAX_RESOURCES];  

    for (int i=0; i<resources; i++) {
        current_available[i] = available[i];
    }


    //start of checking system state
    int count=0;
    while (count<processes){
        bool found = false;

        //start going through each process
        for (int i=0; i<processes; i++){
            //check the resource availability for each process
            if (!finish[i]){
                bool can_allocate = true;

                /*
                check if there is enough resources needed for process i to use.
                if the need for resources is greater than what's available,
                then the process cannot be given its resources, so flag it as false.
                */

                for (int j=0; j<resources; j++){
                    if (need[i][j] > current_available[j]){
                        can_allocate = false;  
                        break;  //end loop, go to next process
                    }
                }

                //if there IS enough resources, the process can finish
                if (can_allocate){

                    /*
                    process is done with its resources, add it back to current_available
                    for the next process to have.

                    allocation array is used, not the need array because it's what the system has 
                    provided. 
                    */

                    for (int k=0; k<resources; k++){
                        current_available[k] += allocation[i][k];
                    }
                    finish[i] = true;  //set tag of current process to true, meaning it has been processed
                    count++;  //increment to next process
                    found = true;
                }
            }
        }


        //if no sequence can be found to finish at least one process given the available process...
        if (!found){
            return false;  //... system is not in safe state
        }
    }

    return true;  //... else the system is in safe state
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

    cout << "Enter the allocated resources for..." << endl; 
    for (int i=0; i<processes; i++){  //list each process
        cout << "Process " << i << ": ";
        for (int j=0; j<resources; j++){  //for each process i, store the allocations j in the array allocation
            cin >> allocation[i][j];
            need[i][j] = maximum_need[i][j] - allocation[i][j];
        }
    }

    cout << "Enter the maximum need of resources for..." << endl;
    for (int i=0; i<processes; i++){  //list each process
        cout << "Process " << i << ": ";
        for (int j=0; j<resources; j++){  //for each process i, store the resources needed in j in the array maximum_need
            cin >> maximum_need[i][j];
            need[i][j] = maximum_need[i][j];
        }
    }



    //call function to check the state of system


    if (isSafeState(processes, resources)){
        cout << "System is in a safe state";
        cout << "The resources given, it can be properly allocated to every process.";

        //if it's in a safe state, enter the request of any process
        //enter the process' resource request, then check if it can be granted or not

        
    } else {
        cout << "System, is not in a safe state";
        cout << "With the resources given, it cannot be properly allocated to every process. Ending program...";
    }

    return 0;
}