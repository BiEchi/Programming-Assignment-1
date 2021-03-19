#include "FibonacciPQ.h"
#include <cstdlib>

using namespace std;
int main()
{
    FibonacciPQ testPQ;
    vector<Node> database = vector<Node>();

    // 数据存入
    for (int i = 0; i < 100; i++)
    {
        Node addition((30 + i), i);
        database.push_back(addition);
    }
    for (auto i = database.begin(); i != database.end(); i++)
    {
        testPQ.Insert(&(*i));
    }
    Node *min;

    min = testPQ.Popmin();
    cout << "the min is " << min->Key << endl;
    for (auto i = database.begin(); i != database.end(); i++)
    {
        if ((*i).Key == min->Key)
        {
            // erase之后会将所有数据平移，相当于更改了每个指针的值，造成指向错误
            // database.erase(i);
            (*i).Store = false;
            break;
        }
    }

    cout << endl;
    // 提取最小值
    // cout << "the pq length is " << testPQ.ReturnLength() << endl;
    // while (testPQ.ReturnLength() != 0)
    // {
    //     min = testPQ.Popmin();
    //     cout << "the min value is " << min->Key << endl;
    // }

    // remove
    for (int i = 0; i < 10; i++)
    {
        hash<int> hashfunction;
        int pos = hashfunction(10 * i) % testPQ.ReturnLength();
        int count = 0;
        while (!database[pos].Store)
        {
            count++;
            pos = hashfunction(10 * (i + count)) % testPQ.ReturnLength();
        }

        Node *remove_node = testPQ.Remove(&database[pos]);
        min = testPQ.Popmin();
        cout << "the min is " << min->Key << endl;
        for (auto i = database.begin(); i != database.end(); i++)
        {
            if (((*i).Key == min->Key) || ((*i).Key == remove_node->Key))
            {
                // erase之后会将所有数据平移，相当于更改了每个指针的值，造成指向错误
                // database.erase(i);
                (*i).Store = false;
            }
        }
    }
    cout << endl;
    // decrease key
    for (int i = 0; i < 10; i++)
    {
        hash<int> hashfunction;
        int pos = hashfunction(10 * i) % testPQ.ReturnLength();
        int count = 0;
        while (!database[pos].Store)
        {
            count++;
            pos = hashfunction(10 * (i + count)) % testPQ.ReturnLength();
        }

        testPQ.DecreaseKey(&database[pos], i);
        min = testPQ.Popmin();
        cout << "the min is " << min->Key << endl;
        for (auto i = database.begin(); i != database.end(); i++)
        {
            if (((*i).Key == min->Key))
            {
                // erase之后会将所有数据平移，相当于更改了每个指针的值，造成指向错误
                // database.erase(i);
                (*i).Store = false;
            }
        }
    }

    return 0;
}