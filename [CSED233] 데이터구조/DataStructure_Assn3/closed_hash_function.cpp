#include "closed_hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

int ClosedHashFunction::Realclosedhashing(int key, int attempt, int d1, int k)
{
    int sum = 0;
    for(int i = 1, j = 0; j <= to_string(key).length(); i *= 10, j++) 
        sum += (key / i) % 10;
    int hx = sum % index_size;

    if(attempt == 1) return hx + 0;
    int di = d1;
    int shift_times = attempt - 2;
    while(shift_times--)
    {
        di = (di << 1);
        if(di >= index_size) di = (di - index_size) ^ k;
    }
    return (hx + di) % index_size;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int ClosedHashFunction::closedhashing(int key, int attempt)
{ // total, collision -> pseudo-random probing
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return 0;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int ClosedHashFunction::closedhashing1(int key)
{ // digit-folding method
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return 0;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int ClosedHashFunction::closedhashing2(int attempt)
{ // shift-register sequence
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return 0;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
