#include <iostream>

using namespace std;

int main()
{
    int a = 1;
    for(int i = 0; i < 5; i++)
    {
        int b;
        int *ptr = &b;
        if(a)
        {
            cin >> b;
            a--;
        }
        cout << b << endl;
        cout << ptr << endl;
    }
}