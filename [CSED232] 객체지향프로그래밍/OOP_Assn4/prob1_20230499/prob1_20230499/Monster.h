#pragma once // It is not standard, but almost compiler support this

// #include "Character.h" //this makes circular dependency, so deleted.

enum type {FIRE, GRASS, WATER, NONE}; //enum for skill type

// The comment of each function is in the cpp file.

class Monster {
    private:
    int curr_hp;
    int atk;
    int def;
    int type;
    int reward_gold;
    int reward_exp;

    public:
    Monster(int difficulty); //constructor
    int get_atk();
    int get_def();
    int get_type();
    int get_hp();
    int get_reward_gold();
    int get_reward_exp();
    // int attack(Character &player); //this makes circular dependency
    void change_hp(int delta);
    bool is_dead();
};