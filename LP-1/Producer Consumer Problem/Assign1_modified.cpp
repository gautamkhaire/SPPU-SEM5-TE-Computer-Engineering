#include <bits/stdc++.h>
#include <mutex>
using namespace std;

struct semaphore{
    int value;
    queue<int> q;     
};

class Semaphore{
    semaphore s;
    int currItemNum;
public:
    Semaphore(){
        // 0 because initially item can be produced
        s.value = 0;
        currItemNum = 0;
    }

    void produce(){
        char ch;
        do{
            s.value = s.value - 1;

            if(s.value < 0){
                s.q.push(currItemNum);
                currItemNum++;
                cout << "Item " << currItemNum << " produced" << "\n";
            }
            else{
                cout << "All threads busy" << "\n";
                return;
            }

            cout << "Do you want to continue producing ? (y/n)" << "\n";
            cin >> ch; 
        }while(ch == 'y');
    }

    void consume(){
        char ch;
        do{
            if(currItemNum <= 0){
                cout << "No item available" << "\n";
                return;
            }

            s.value = s.value + 1;

            if(s.value <= 0){
                int item = s.q.front();
                s.q.pop();
                cout << "Item " << item + 1 << " consumed" << "\n";
                currItemNum--;
            }
            else{
                cout << "All threads busy" << "\n";
                return;
            }

            cout << "Do you want to continue consuming ? (y/n)" << "\n";
            cin >> ch; 
        }while(ch == 'y');
    }

    void itemsAvailable(){
        cout << "Total :- " << currItemNum << " items available" << "\n";
        return;
    }

    void giveLockValue(){
        cout << "Lock value :- " << s.value << "\n";
    }

};

class Mutex{
    // 0 -> Unlock state;
    // 1 -> Locked state 
    int lockState; 
    int currItemNum;
    int itemNum = 1;
    int consumedItem = itemNum;
    mutex m;
public:
    Mutex(){
        // 0 because initially item can be produced
        lockState = 0;
        currItemNum = 0;
    }

    void setLockState(){
        lockState = 1;
    }

    void unSetLockState(){
        lockState = 0;
    }

    void produce(){
        if(lockState == 1){
            cout << "Thread is busy" << "\n";
            return; 
        }

        m.lock();
        cout << "Item " << itemNum << " produced" << "\n";
        currItemNum++;
        itemNum++;
        m.unlock(); 

        lockState = 0;
        return;
    } 

    void consume(){
        if(lockState == 1){
            cout << "Thread is busy" << "\n";
            return;
        }

        m.lock();
        if(currItemNum <= 0){
            cout << "!!! No item available !!!" << "\n";
            m.unlock();
            return;
        }
        cout << "Item " << itemNum - currItemNum << " consumed" << "\n";
        currItemNum--;
        consumedItem--;
        m.unlock(); 

        lockState = 0;
        return;
    }

    void itemsAvailable(){
        cout << "Total :- " << currItemNum << " items available" << "\n";
        return;
    }

};

int main(){

    cout << "------------MUTEX--------------" << "\n";    
    Mutex mt;
    while(1){
        cout << "1. Produce" << "\n";
        cout << "2. Consume" << "\n";
        cout << "3. Set lock state" << "\n";
        cout << "4. Unset unlock state" << '\n';
        cout << "5. Items available" << "\n";
        cout << "6. Exit" << "\n";

        int op;
        cout << "Enter your choice :- ";
        cin >> op;

        bool flag = 1;
        switch(op){
            case 1:
            {
                mt.produce();
                break;
            }
            case 2:
            {
                mt.consume();
                break;
            }
            case 3:
            {
                mt.setLockState();
                break;
            }
            case 4:
            {
                mt.unSetLockState();
                break;
            }
            case 5:
            {
                mt.itemsAvailable();
                break;
            }
            case 6:
                flag = 0;
                break;
            default:
                cout << "Enter valid input" << "\n";
        }
        if(!flag) break;
    }

    cout << "--------------- SEMAPHORE ------------" << "\n";
    Semaphore sp;
    while(1){
        cout << "1. Produce" << "\n";
        cout << "2. Consume" << "\n";
        cout << "3. Items available" << "\n";
        cout << "4. Lock Value" << "\n";
        cout << "5. Exit" << "\n";

        int op;
        cout << "Enter your choice :- ";
        cin >> op;

        switch(op){
            case 1:
            {
                sp.produce();
                break;
            }
            case 2:
            {
                sp.consume();
                break;
            }
            case 3:
            {
                sp.itemsAvailable();
                break;
            }
            case 4:
            {
                sp.giveLockValue();
                break;
            }
            case 5:
                exit(0);
            default:
                cout << "Enter valid input" << "\n";
        }
        
    }

    return 0;
}