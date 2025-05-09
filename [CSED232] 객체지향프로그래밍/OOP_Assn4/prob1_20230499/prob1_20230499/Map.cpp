#include "Map.h"

Map::Map() // constructor
{
    start_x = 0; //start position
    start_y = 0;
    char map_initialization[8][8] = { // map initialization
        {'E', 'R', 'M', 'M', 'R', 'E', 'M', 'M'},
        {'M', 'E', 'R', 'E', 'M', 'R', 'E', 'R'},
        {'R', 'M', 'E', 'E', 'M', 'E', 'M', 'M'},
        {'M', 'E', 'R', 'S', 'M', 'M', 'E', 'R'},
        {'M', 'M', 'E', 'R', 'E', 'R', 'M', 'E'},
        {'E', 'R', 'M', 'E', 'M', 'E', 'E', 'R'},
        {'M', 'E', 'R', 'M', 'M', 'E', 'R', 'M'},
        {'E', 'E', 'M', 'E', 'R', 'M', 'E', 'B'}
    };
    char map_initialization_modified_for_debug[8][8] = { //for debug
        {'E', 'R', 'M', 'B', 'R', 'E', 'M', 'M'},
        {'S', 'E', 'R', 'E', 'M', 'R', 'E', 'R'},
        {'R', 'M', 'E', 'E', 'M', 'E', 'M', 'M'},
        {'M', 'E', 'R', 'S', 'M', 'M', 'E', 'R'},
        {'M', 'M', 'E', 'R', 'E', 'R', 'M', 'E'},
        {'E', 'R', 'M', 'E', 'M', 'E', 'E', 'R'},
        {'M', 'E', 'R', 'M', 'M', 'E', 'R', 'M'},
        {'E', 'E', 'M', 'E', 'R', 'M', 'E', 'B'}
    };
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            map_veil[i][j] = true;
            map[i][j] = map_initialization[i][j];
            //map[i][j] = map_initialization_modified_for_debug[i][j];
        }
    }
    veil(start_y, start_x); // start position is already unveiled before start.
}
/* map, E : empty, M : monster, R : random, S : shop, B : boss*/

// get_ functions are used to get the private variables.
int Map::get_start_x()
{
    return start_x;
}
int Map::get_start_y()
{
    return start_y;
}

// distance function calculates the Manhattan distance from the start position.
// distance will be used to difficulty of monster.
int Map::distance(int y, int x)
{
    return ((y - start_y > 0) ? y - start_y : start_y - y)
            + ((x - start_x > 0) ? x - start_x : start_x - x);
}

// isnot_veil function checks if the position is unveiled.
bool Map::isnot_veil(int y, int x)
{
    return map_veil[y][x];
}

// veil function veils the position.
void Map::veil(int y, int x)
{
    map_veil[y][x] = false;
}

// get_map function returns the map character of the position.
char Map::get_map(int y, int x)
{
    return map[y][x];
}