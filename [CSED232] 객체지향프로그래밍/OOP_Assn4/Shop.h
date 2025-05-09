#pragma once // It is not standard, but almost compiler support this
#include "Character.h" //dependency

// The comment of each function is in the cpp file.

class Shop {
    private:
    int atk_price;
    int def_price;
    int exp_price;
    int hp_price;
    int mp_price;
    int atk_stock;
    int def_stock;
    int exp_stock;

    public:
    Shop();
    void atk_up(Character &player);
    void def_up(Character &player);
    void exp_up(Character &player);
    void recovery_hp(Character &player);
    void recovery_mp(Character &player);
    int get_price(int n);
    int get_stock(int n);
};