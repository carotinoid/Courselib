#pragma once // It is not standard, but almost compiler support this

// The comment of each function is in the cpp file.

class Map {
    private:
    char map[8][8];
    bool map_veil[8][8];
    int start_x;
    int start_y;

    public:
    Map(); //constructor
    int distance(int y, int x);
    int get_start_x();
    int get_start_y();
    void veil(int y, int x);
    bool isnot_veil(int y, int x);
    char get_map(int y, int x);
};