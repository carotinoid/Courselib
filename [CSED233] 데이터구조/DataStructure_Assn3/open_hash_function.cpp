#include "open_hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int OpenHashFunction::openhashing(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int sum = 0;
    for(int i = 1, j = 0; j <= to_string(key).length(); i *= 10, j++)
    {
        sum += (key / i) % 10;
    }
    return sum % index_size;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
