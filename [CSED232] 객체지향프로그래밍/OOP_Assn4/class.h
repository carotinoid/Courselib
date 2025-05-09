#pragma once
//TODO devide each class to a single file
enum type {FIRE, GRASS, WATER, NONE};

class Character;
class Monster;
class Shop;
class Map;

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
    Character(Map &map);
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

class Map {
    private:
    char map[8][8];
    bool map_veil[8][8];
    int start_x;
    int start_y;

    public:
    Map();
    int distance(int y, int x);
    int get_start_x();
    int get_start_y();
    void veil(int y, int x);
    bool isnot_veil(int y, int x);
    char get_map(int y, int x);
};

class Monster {
    private:
    int curr_hp;
    int atk;
    int def;
    int type;
    int reward_gold;
    int reward_exp;

    public:
    Monster(int difficulty);
    int get_atk();
    int get_def();
    int get_type();
    int get_hp();
    int get_reward_gold();
    int get_reward_exp();
    int attack(Character &player);
    void change_hp(int delta);
    bool is_dead();
};

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