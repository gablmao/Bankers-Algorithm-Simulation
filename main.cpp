#include <iostream>

using namespace std;

// assign global arrays
const int MAX_PROCESSES = 5;
const int MAX_RESOURCES = 5;

int available[MAX_RESOURCES];                     // number of resources available
int maximum_need[MAX_PROCESSES][MAX_RESOURCES];   // max resources one process needs to execute
int allocation[MAX_PROCESSES][MAX_RESOURCES];     // number of resources already allocated to a process
int remaining_need[MAX_PROCESSES][MAX_RESOURCES]; // number of resources a process needs to complete

/*
example array representation:
remaining_need = {
  {1, 2, 2},
  {0, 1, 0},
  {1, 0, 0},
  {1, 1, 0}
}
for each first [], another array of length in second [] is created
*/

// check if system is in a safe state or not
bool isSafeState(int processes, int resources)
{
    bool finish[MAX_PROCESSES] = {false}; // for each process, they're not completed processing yet

    // copy of the array available
    int current_available[MAX_RESOURCES];

    for (int i = 0; i < resources; i++)
    {
        current_available[i] = available[i];
    }

    // start of checking system state

    int count = 0; // keep track of which process is on
    while (count < processes)
    {
        bool found = false;

        // start going through each process
        for (int i = 0; i < processes; i++)
        {
            // check if the process is not finished executing
            if (!finish[i])
            {
                bool can_allocate = true;

                /*
                check if there is enough resources needed for process i to use.
                if the need for resources is greater than what's available,
                then the process cannot be given its resources, so flag it as false.
                */

                for (int j = 0; j < resources; j++)
                {
                    if (remaining_need[i][j] > current_available[j])
                    {
                        can_allocate = false;
                        break; // break out of this for loop
                    }
                }

                // if there IS enough resources, the process can finish
                if (can_allocate)
                {

                    /*
                    process is done with its resources, add it back to current_available
                    for the next process to have.
                    */

                    for (int k = 0; k < resources; k++)
                    {
                        current_available[k] += allocation[i][k];
                    }
                    finish[i] = true; // set tag of current process to true, meaning it has been processed
                    found = true;
                    count++; // increment to next process
                }
            }
        }

        // if no sequence can be found to finish at least one process given the available process...
        if (!found)
        {
            return false; //... system is not in safe state
        }
    }

    /*
    ... else the system is in safe state
    there's a possible "safe" sequence that every process
    can be executed with the resources provided
    */
    return true;
}

bool requestResource(int selected_process, int request[], int processes, int resources)
{

    // check if request is over the maximum need of a process
    for (int i = 0; i < resources; i++)
    {
        if (request[i] > maximum_need[selected_process][i])
        {
            return false;
        }
    }

    // check if there's enough available to provide
    // if available > request, then there's enough resources to provide what's requested
    for (int i = 0; i < resources; i++)
    {
        if (request[i] > available[i])
        {
            return false; // cannot provide
        }
    }

    // allocate request resources to process
    for (int i = 0; i < resources; i++)
    {
        available[i] -= request[i];
        allocation[selected_process][i] += request[i];
        remaining_need[selected_process][i] -= request[i];
    }

    // check if the system is in a safe state after allocation
    if (!isSafeState(processes, resources))
    {
        return false; // request cant be granted
    }

    return true; // request is granted
}

int main()
{
    int processes;
    int resources;

    cout << "Enter the number of processes: ";
    cin >> processes;

    cout << "Enter the number of resources: ";
    cin >> resources;

    cout << "Enter the available resources: ";
    for (int i = 0; i < resources; i++)
    {
        cin >> available[i];
    }

    cout << "Enter the maximum need of resources for..." << endl;
    for (int i = 0; i < processes; i++)
    { // list each process
        cout << "Process " << i << ": ";
        for (int j = 0; j < resources; j++)
        { // for each process i, store the resources needed in j in the array maximum_need
            cin >> maximum_need[i][j];
        }
    }

    cout << "Enter the allocated resources for..." << endl;
    for (int i = 0; i < processes; i++)
    { // list each process
        cout << "Process " << i << ": ";
        for (int j = 0; j < resources; j++)
        { // for each process i, store the allocations j in the array allocation
            cin >> allocation[i][j];
            remaining_need[i][j] = maximum_need[i][j] - allocation[i][j];
        }
    }

    // call function to check the state of system
    if (isSafeState(processes, resources))
    {
        cout << "System is in a safe state." << endl;
        cout << "With the resources given, it can be properly allocated to every process.";

        // handle resource request here

        // generate random process num
        int min = 0;
        int max = processes;
        int random_process = rand() % (max - min + 1) + min;

        cout << "----- NOTICE: REQUEST FOR RESOURCES FROM PROCESS " << random_process << " ------" << endl;
        int request[MAX_RESOURCES];

        cout << "Enter the request for resources for this process: ";
        for (int i = 0; i < resources; i++)
        {
            cin >> request[i];
        }

        /*
        check if request can be granted
        to be granted, check if the system is in safe state
        if not, deny the request
        */
        if (requestResource(random_process, request, processes, resources))
        {
            cout << "Request Granted. Ending program...";
        }
        else
        {
            cout << "Request has been denied. Ending program...";
        }
    }
    else
    {
        cout << "System, is not in a safe state." << endl;
        cout << "With the resources given, it cannot be properly allocated to every process. Ending program...";
    }

    return 0;
}