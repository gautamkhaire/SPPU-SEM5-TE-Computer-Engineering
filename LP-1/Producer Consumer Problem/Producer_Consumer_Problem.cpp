#include <bits/stdc++.h>
#include <mutex>
using namespace std;
struct semaphore
{
    int value;
    queue<int> q;
};
class Semaphore
{
    semaphore s;
    int currentItemNum;

    public:
    Semaphore()
    {
        // 0 because initailly item can be produced
        s.value=0;
        currentItemNum=1;
    }

    void produce()
    {
        char ch;
        do
        {
            s.value=s.value-1;
            if(s.value < 0)
            {
                s.q.push(currentItemNum);
                cout<<"Item "<<currentItemNum<<" Produced "<<endl;
                currentItemNum++;
            }
            else
            {
                cout<<"All Threads are Busy"<<endl;
                return ;
            }

            cout<<"Do you want to continue producing ? (y/n) : "<<endl;
            cin>>ch;
        } while (ch=='y');
    }

    void consume()
    {
        char ch;
        do
        {
            if(currentItemNum<=0)
            {
                cout<<"No Items available"<<endl;
                return ;
            }

            s.value=s.value+1;
            if(s.value <= 0)
            {
                int item=s.q.front();
                s.q.pop();
                cout<<"Item "<<item<<" Consumed "<<endl;
                currentItemNum--;
            }
            else
            {
                cout<<"All Threads are Busy"<<endl;
                return ;
            }

            cout<<"Do you want to continue consuming ? (y/n) : "<<endl;
            cin>>ch;
        } while (ch=='y');
    }

    void itemsAvailable()
    {
        cout<<"Total :- "<<(currentItemNum-1)<<" items available "<<endl;
        return ;
    }

    void giveLockValue()
    {
        cout<<"Lock Value :- "<<s.value<<endl;
        return ;
    }
};

class Mutex
{
    
};
int main()
{
    Semaphore sp;
    cout<<" ----------------- SEMAPHORE ----------------- "<<endl;
    int option;
    do
    {
        cout<<" 1. Produce "<<endl;
        cout<<" 2. Consume "<<endl;
        cout<<" 3. Items Available "<<endl;
        cout<<" 4. Lock Value "<<endl;
        cout<<" 5. Exit "<<endl;
        cout<<" Enter the option : ";
        cin>>option;

        switch(option)
        {
            case 1:
                sp.produce();
                break;
            case 2:
                sp.consume();
                break;
            case 3:
                sp.itemsAvailable();
                break ;   
            case 4:
                sp.giveLockValue();
                break ;
            case 5:
                exit(0);
            default :
                cout<<" Enter a valid option "<<endl;                 
        }
    } while (option>=1 && option<=4);
    
    return 0;
}