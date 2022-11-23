#include <bits/stdc++.h>
using namespace std;

#define MAX 20

int n, coordinator;     // n=Number of processes , coordinator=Leader
int processStatus[MAX]; // Stores whether the process is alive or dead

void display()
{
    cout << " ---------------------------------------------------------- " << endl;
    cout << " Processes : ";
    for (int pid = 1; pid <= n; pid++)
    {
        cout << pid << "     ";
    }
    cout << endl;
    cout << " Alive :     ";
    for (int pid = 1; pid <= n; pid++)
    {
        cout << processStatus[pid] << "     ";
    }
    cout << endl;
    cout << " ---------------------------------------------------------- " << endl;
    cout << " COORDINATOR is : " << coordinator << endl;
}

void bully()
{
    int option;
    int crash, activate, flag, gid, subcoordinator; // gid=generatorID
    do
    {
        cout << " -------------------- BULLY ALGORIHTM --------------------- " << endl;
        cout << " 1. CRASH " << endl;
        cout << " 2. ACTIVATE " << endl;
        cout << " 3. DISPLAY " << endl;
        cout << " 4. EXIT " << endl;
        cout << " Enter the Option : ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << " Enter the process to crash : ";
            cin >> crash;

            if (processStatus[crash] == 1) // If process if alive, make it dead
            {
                processStatus[crash] = 0;
            }
            else
            {
                cout << " Process " << crash << " is already dead! " << endl;
            }

            do
            {
                cout << " Enter the election generator id : ";
                cin >> gid;
                if (gid == coordinator || processStatus[gid] == 0)
                {
                    cout << " Please, enter a valid generator id.... " << endl;
                }
            } while (gid == coordinator || processStatus[gid] == 0);
            flag = 0;

            if (crash == coordinator)
            {
                for (int i = gid + 1; i <= n; i++)
                {
                    cout << " Message sent from " << gid << " to " << i << endl;
                    if (processStatus[i] == 1)
                    {
                        subcoordinator = i;
                        cout << " Response sent from " << i << " to " << gid << endl;
                        flag = 1;
                    }
                }

                if (flag == 1)
                    coordinator = subcoordinator;
                else
                    coordinator = gid;
            }

            display();
            break;

        case 2:
            cout << " Enter the process ID to be activated : ";
            cin >> activate;

            if (processStatus[activate] == 0)
            {
                processStatus[activate] = 1;
            }
            else
            {
                cout << " Process " << activate << " is already alive! " << endl;
                break;
            }

            if (activate == n)
            {
                coordinator = n;
                break;
            }
            flag = 0;

            for (int i = activate + 1; i <= n; i++)
            {
                cout << " Message sent from " << activate << " to " << i << endl;
                if (processStatus[i] == 1)
                {
                    subcoordinator = i;
                    cout << " Response sent from " << i << " to " << activate << endl;
                    flag = 1;
                }
            }

            if (flag == 1)
                coordinator = subcoordinator;
            else
                coordinator = activate;

            display();
            break;

        case 3:
            display();
            break;

        case 4:
            exit(0);
            break;
        }
    } while (option >= 1 && option <= 3);
}

void ring()
{
    int option;
    int crash, activate, flag, gid, subcoordinator; // gid=generatorID
    do
    {
        cout << " -------------------- RING ALGORIHTM --------------------- " << endl;
        cout << " 1. CRASH " << endl;
        cout << " 2. ACTIVATE " << endl;
        cout << " 3. DISPLAY " << endl;
        cout << " 4. EXIT " << endl;
        cout << " Enter the Option : ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << " Enter the process to crash : ";
            cin >> crash;

            if (processStatus[crash] == 1) // If process if alive, make it dead
            {
                processStatus[crash] = 0;
            }
            else
            {
                cout << " Process " << crash << " is already dead! " << endl;
            }

            do
            {
                cout << " Enter the election generator id : ";
                cin >> gid;
                if (gid == coordinator || processStatus[gid] == 0)
                {
                    cout << " Please, enter a valid generator id.... " << endl;
                }
            } while (gid == coordinator || processStatus[gid] == 0);

            if (crash == coordinator)
            {
                subcoordinator = 1;
                for (int i = 0; i < (n + 1); i++)
                {
                    int pid = (i + gid) % (n + 1);
                    if (pid != 0)
                    {
                        if (processStatus[pid] == 1 && subcoordinator < pid)
                        {
                            subcoordinator = pid;
                        }
                        cout << "Election message sent from " << pid << ": #Msg" << subcoordinator << endl;
                    }
                }

                coordinator = subcoordinator;
            }

            display();
            break;

        case 2:
            cout << " Enter the process ID to be activated : ";
            cin >> activate;

            if (processStatus[activate] == 0)
            {
                processStatus[activate] = 1;
            }
            else
            {
                cout << " Process " << activate << " is already alive! " << endl;
                break;
            }

            subcoordinator = activate;
            for (int i = 0; i < n + 1; i++)
            {
                int pid = (i + activate) % (n + 1);

                if (pid != 0)
                {
                    if (processStatus[pid] == 1 && subcoordinator < pid)
                    {
                        subcoordinator = pid;
                    }
                    cout << "Election message passed from " << pid << ": #Msg" << subcoordinator << endl;
                }
            }

            coordinator = subcoordinator;

            display();
            break;

        case 3:
            display();
            break;

        case 4:
            exit(0);
            break;
        }

    } while (option >= 1 && option <= 3);
}

int main()
{
    cout << " Enter the number of processes : ";
    cin >> n;

    for (int pid = 1; pid <= n; pid++) // pid=processID
    {
        cout << " Enter Process " << pid << " is alive or not (0/1) : ";
        cin >> processStatus[pid];

        if (processStatus[pid] == 1)
        {
            coordinator = pid;
        }
    }
    display();
    cout << endl;

    int option;

    cout << " -------------------------- MENU -------------------------- " << endl;
    cout << " 1. BULLY ALGORITHM " << endl;
    cout << " 2. RING ALGORITHM " << endl;
    cout << " 3. DISPLAY " << endl;
    cout << " 4. EXIT " << endl;
    cout << "Enter the Option : ";
    cin >> option;

    switch (option)
    {
    case 1:
        bully();
        break;

    case 2:
        ring();
        break;

    case 3:
        display();
        break;

    case 4:
        exit(0);
        break;
    }

    return 0;
}