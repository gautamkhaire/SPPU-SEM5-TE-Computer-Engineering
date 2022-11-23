#include <bits/stdc++.h>
using namespace std;

class PageReplacement
{
private:
    int hit;            // Number of Page Hits
    int miss;           // Number of Page Faults / Page Miss
    int size;           // Cache Size
    string str;         // str is the Reference String
    vector<char> cache; // In cache the smallest unit is called Frame
public:
    PageReplacement()
    {
        hit = 0;
        miss = 0;
        cout << " Enter the size of Cache : ";
        cin >> size;

        for (int i = 0; i < size; i++)
        {
            cache.push_back(' ');
        }

        cout << " Enter the Reference String : ";
        cin >> str;
    }

    void displayCache()
    {
        for (int i = 0; i < size; i++)
        {
            cout << cache[i] << " ";
        }
        cout << endl;
    }

    void FirstInFirstOut() // FIFO Page Replacement Algorithm
    {
        int frame = 0; // Frame is termed as smallest unit of cache (frame is representing the index of cache here)
        for (int i = 0; i < str.length(); i++)
        {
            bool isPresent = false;
            for (int j = 0; j < size; j++)
            {
                if (cache[j] == str[i])
                {
                    hit++;
                    isPresent = true;
                    break;
                }
            }

            if (isPresent==false)
            {
                miss++;
                cache[frame] = str[i];
                frame++;
                frame = frame % size;
            }

            displayCache();
        }

        cout << " In First-In-First-Out (FIFO) Page Replacement Algorithm for the Reference String : " << str << " the Page Faults are : " << miss << " & Page Hits are : " << hit << endl;
    }

    int predict(int index)
    {
        int frame = -1;       // We want to know which Page is at the Farthest distance, so that we will replace that page from cache
        int farthest = index; // Storing the Reference string farthest Index
        for (int j = 0; j < size; j++)
        {
            int i;
            for (i = index; i < str.length(); i++)
            {
                if (cache[j] == str[i])
                {
                    if (farthest < i)
                    {
                        frame = j;
                        farthest = i;
                    }
                    break;
                }
            }

            if (i == str.length()) // Here, we are returning that Page from cache which is not seen in the Reference String in future
            {
                return j;
            }
        }

        return (frame == -1) ? 0 : frame;
    }
    void OptimalPageReplacement()
    {
        int frame = 0;
        for (int i = 0; i < str.length(); i++)
        {
            bool isPresent = false;
            for (int j = 0; j < size; j++)
            {
                if (cache[j] == str[i])
                {
                    hit++;
                    isPresent = true;
                    break;
                }
            }

            if (i < size && isPresent == false) // If we have empty slots in cache then we will fill them first
            {
                miss++;
                cache[frame] = str[i];
                frame++;
                frame = frame % size;
            }
            else if (isPresent == false)
            {
                miss++;
                frame = predict(i + 1); // Important: Send the next Page index of the Reference String to the predict function
                cache[frame] = str[i];
            }

            displayCache();
        }

        cout << " In Optimal Page Replacement Algorithm for the Reference String : " << str << " the Page Faults are : " << miss << " & Page Hits are : " << hit << endl;
    }

    void LeastRecentlyUsed()
    {
        int frame = 0;
        unordered_map<int, int> indexes; // {Page Number , Index Of Reference String}
        for (int i = 0; i < str.length(); i++)
        {
            bool isPresent = false;
            for (int j = 0; j < size; j++)
            {
                if (cache[j] == str[i])
                {
                    hit++;
                    isPresent = true;
                    break;
                }
            }

            if (i < size && isPresent == false) // If we have empty slots in cache then we will fill them first
            {
                miss++;
                cache[frame] = str[i];
                frame++;
                frame = frame % size;
            }
            else if (isPresent == false)
            {
                miss++;
                int leastUsedIndex = INT_MAX;
                int cacheEntry = 0;
                for (int j = 0; j < size; j++)
                {
                    if (indexes[cache[j]] < leastUsedIndex)
                    {
                        leastUsedIndex = indexes[cache[j]];
                        cacheEntry = cache[j];
                    }
                }

                for (int j = 0; j < size; j++)
                {
                    if (cache[j] == cacheEntry)
                    {
                        cache[j] = str[i];
                    }
                }
            }

            indexes[str[i]] = i;
            displayCache();
        }

        cout << " In Least-Recently-Used (LRU) Page Replacement Algorithm for the Reference String : " << str << " the Page Faults are : " << miss << " & Page Hits are : " << hit << endl;
    }
};

int main()
{
    PageReplacement obj;
    int option;
    cout << " --------------------- PAGE REPLACEMENT ALGORITHMS --------------------- " << endl;
    cout << " 1. FIRST IN FIRST OUT (FIFO) " << endl;
    cout << " 2. OPTIMAL PAGE REPLACEMENT " << endl;
    cout << " 3. LEAST RECENTLY USED (LRU) " << endl;
    cout << " 4. EXIT " << endl;
    cout << " Select the Page Replacement Algorithm : ";
    cin >> option;
    
    switch (option)
    {
    case 1:
        obj.FirstInFirstOut();
        break;
    case 2:
        obj.OptimalPageReplacement();
        break;
    case 3:
        obj.LeastRecentlyUsed();
        break;
    case 4:
        exit(0);
        break;
    }

    return 0;
}