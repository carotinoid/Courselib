#pragma once // It is not standard, but almost compiler support this
#include "Map.h" //dependency
#include "Monster.h" //dependency

// ! comment of each memeber function is in Character.cpp

class Character {
    private:
    int attack;
    int defense;
    int gold;
    int level;
    int max_hp;
    int curr_hp;
    int max_mp;
    int curr_mp;
    int max_exp;
    int curr_exp;
    int x;
    int y;

    public:
    Character(Map &map); //constructor
    bool go_up();
    bool go_down();
    bool go_left();
    bool go_right();
    int get_x();
    int get_y();
    int attack_basic(Monster &monster);
    int attack_skill(Monster &monster);
    int attack_fire(Monster &monster);
    int attack_grass(Monster &monster);
    int attack_water(Monster &monster);
    int get_exp();
    int get_gold();
    int get_atk();
    int get_def();
    int get_hp();
    int get_mp();
    int get_level();
    int get_max_hp();
    int get_max_mp();
    void change_atk(int delta);
    void change_def(int delta);
    void change_exp(int delta);
    void change_hp(int delta);
    void change_gold(int delta);
    void level_up();
    void recovery_hp();
    void recovery_mp();
    bool is_dead();
};