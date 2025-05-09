#include "class.h"
#include <cstdlib>
#include <cmath>
#include <iostream> // debug

Character::Character(Map &map)
{
    x = map.get_start_x();
    y = map.get_start_y();
    attack = 10;
    defense = 2;
    gold = 0;
    max_hp = 100;
    curr_hp = 100;
    max_mp = 20;
    curr_mp = 20;
    max_exp = 100;
    curr_exp = 0;
    level = 1;
}
int Character::get_x()
{
    return x;
}
int Character::get_y()
{
    return y;
}
bool Character::go_up()
{
    if(y > 0)
    {
        y--;
        return true;
    }
    return false;
}
bool Character::go_down()
{
    if(y < 7)
    {
        y++;
        return true;
    }
    return false;
}
bool Character::go_left()
{
    if(x > 0)
    {
        x--;
        return true;
    }
    return false;
}
bool Character::go_right()
{
    if(x < 7)
    {
        x++;
        return true;
    }
    return false;
}
int Character::get_exp()
{
    return curr_exp;
}
int Character::get_gold()
{
    return gold;
}
int Character::get_atk()
{
    return attack;
}
int Character::get_def()
{
    return defense;
}
int Character::get_hp()
{
    return curr_hp;
}
int Character::get_mp()
{
    return curr_mp;
}
int Character::get_level()
{
    return level;
}
int Character::get_max_hp()
{
    return max_hp;
}
int Character::get_max_mp()
{
    return max_mp;
}
void Character::change_atk(int delta)
{
    attack += delta;
}
void Character::change_def(int delta)
{
    defense += delta;
}
void Character::change_exp(int delta)
{
    curr_exp += delta;
    while(curr_exp > max_exp)
    {
        level_up();
    }
}
void Character::change_hp(int delta)
{
    curr_hp += delta;
    if(curr_hp > max_hp)
    {
        curr_hp = max_hp;
    }
}
void Character::change_gold(int delta)
{
    gold += delta;
}
void Character::level_up()
{
    level++;
    attack += 3;
    defense ++;
    curr_exp -= max_exp;
    max_exp = level * 100;
    max_hp += 50;
    max_mp += 10;
    recovery_hp();
    recovery_mp();
}
void Character::recovery_hp()
{
    curr_hp = max_hp;
}
void Character::recovery_mp()
{
    curr_mp = max_mp;
}
bool Character::is_dead()
{
    return curr_hp <= 0;
}
int Character::attack_basic(Monster &monster)
{
    int dmg = attack - monster.get_def();
    if(dmg < 0) dmg = 0; // no negative damage
    monster.change_hp(- dmg);
    return dmg;
}
int Character::attack_skill(Monster &monster)
{
    int dmg = -1;
    if(curr_mp >= 15)
    {
        curr_mp -= 15;
        dmg = floor(double(attack) * 1.5 + 0.5) - monster.get_def();
        if(dmg < 0) dmg = 0; // no negative damage
        monster.change_hp(- dmg); // rounds, +0.5 then floor
    }
    return dmg;
}
int Character::attack_fire(Monster &monster)
{
    int dmg = -1;
    if(curr_mp >= 15)
    {
        curr_mp -= 15;
        if(monster.get_type() == GRASS)
        {
            dmg = attack * 2 - monster.get_def();
            if(dmg < 0) dmg = 0; // no negative damage
            monster.change_hp(- dmg);
        }
        else
        {
            dmg = attack - monster.get_def();
            if(dmg < 0) dmg = 0; // no negative damage
            monster.change_hp(- dmg);
        }
    }
    return dmg;
}
int Character::attack_grass(Monster &monster)
{
    int dmg = -1;
    if(curr_mp >= 15)
    {
        curr_mp -= 15;
        if(monster.get_type() == WATER)
        {
            dmg = attack * 2 - monster.get_def();
            if(dmg < 0) dmg = 0; // no negative damage
            monster.change_hp(- dmg);
        }
        else
        {
            dmg = attack - monster.get_def();
            if(dmg < 0) dmg = 0; // no negative damage
            monster.change_hp(- dmg);
        }
    }
    return dmg;
}
int Character::attack_water(Monster &monster)
{
    int dmg = -1;
    if(curr_mp >= 15)
    {
        curr_mp -= 15;
        if(monster.get_type() == FIRE)
        {
            dmg = attack * 2 - monster.get_def();
            if(dmg < 0) dmg = 0; // no negative damage
            monster.change_hp(- dmg);
        }
        else
        {
            dmg = attack - monster.get_def();
            if(dmg < 0) dmg = 0; // no negative damage
            monster.change_hp(- dmg);
        }
    }
    return dmg;
}

Map::Map()
{
    start_x = 0;
    start_y = 0;
    char map_initialization[8][8] = {
        /*
        E R M M R E M M
        M E R E M R E R
        R M E E M E M M
        M E R S M M E R
        M M E R E R M E
        E R M E M E E R
        M E R M M E R M
        E E M E R M E B
        */
        {'E', 'R', 'M', 'M', 'R', 'E', 'M', 'M'},
        {'M', 'E', 'R', 'E', 'M', 'R', 'E', 'R'},
        {'R', 'M', 'E', 'E', 'M', 'E', 'M', 'M'},
        {'M', 'E', 'R', 'S', 'M', 'M', 'E', 'R'},
        {'M', 'M', 'E', 'R', 'E', 'R', 'M', 'E'},
        {'E', 'R', 'M', 'E', 'M', 'E', 'E', 'R'},
        {'M', 'E', 'R', 'M', 'M', 'E', 'R', 'M'},
        {'E', 'E', 'M', 'E', 'R', 'M', 'E', 'B'}
    };
    char map_initialization_modified_for_debug[8][8] = {
        {'E', 'R', 'M', 'M', 'R', 'E', 'M', 'M'},
        {'M', 'E', 'R', 'E', 'M', 'R', 'E', 'R'},
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
            map[i][j] = map_initialization_modified_for_debug[i][j];
        }
    }
    veil(start_y, start_x);
}
/* map, E : empty, M : monster, R : random, S : shop, B : boss*/
int Map::get_start_x()
{
    return start_x;
}
int Map::get_start_y()
{
    return start_y;
}
int Map::distance(int y, int x)
{
    return ((y - start_y > 0) ? y - start_y : start_y - y)
            + ((x - start_x > 0) ? x - start_x : start_x - x);
}
bool Map::isnot_veil(int y, int x)
{
    return map_veil[y][x];
}
void Map::veil(int y, int x)
{
    map_veil[y][x] = false;
}
char Map::get_map(int y, int x)
{
    return map[y][x];
}

Monster::Monster(int difficulty)
{
    srand(time(NULL));
    type = rand() % 4; // 0 : fire, 1 : grass, 2 : water  3: NONE(enum type)
    if(difficulty < 0) //boss
    {
        curr_hp = 200;
        atk = 30;
        def = 10;
        reward_gold = 1000; //dummy
        reward_exp = 1000; //dummy
    }
    else
    {
        curr_hp = 50 + difficulty * 5;
        atk = 5 + difficulty * 2;
        def = 2 + floor(double(difficulty) / 2 + 0.5); // rounds, +0.5 then floor
        reward_gold = 100 + difficulty * 10;
        reward_exp = 100 + difficulty * 10;
    }
    
}
int Monster::get_atk()
{
    return atk;
}
int Monster::get_def()
{
    return def;
}
int Monster::get_type()
{
    return type;
}
int Monster::get_hp()
{
    return curr_hp;
}
int Monster::get_reward_gold()
{
    return reward_gold;
}
int Monster::get_reward_exp()
{
    return reward_exp;
}
int Monster::attack(Character &player)
{
    int dmg = atk - player.get_def();
    if(dmg < 0) dmg - 0; // no negative damage
    player.change_hp(- dmg);
    return dmg;
}
void Monster::change_hp(int delta)
{
    curr_hp += delta;
}
bool Monster::is_dead()
{
    return curr_hp <= 0;
}

Shop::Shop()
{
    atk_price = 700;
    def_price = 700;
    exp_price = 700;
    hp_price = 500;
    mp_price = 500;
    atk_stock = 1;
    def_stock = 1;
    exp_stock = 1;
}
void Shop::atk_up(Character &player)
{
    if(player.get_gold() >= atk_price && atk_stock > 0)
    {
        player.change_gold(- atk_price);
        player.change_atk(10);
        atk_stock--;
    }
}
void Shop::def_up(Character &player)
{
    if(player.get_gold() >= def_price && def_stock > 0)
    {
        player.change_gold(- def_price);
        player.change_def(5);
        def_stock--;
    }
}
void Shop::exp_up(Character &player)
{
    if(player.get_gold() >= exp_price && exp_price > 0)
    {
        player.change_gold(- exp_price);
        player.change_exp(300);
        exp_stock--;
    }
}
void Shop::recovery_hp(Character &player)
{
    if(player.get_gold() >= hp_price)
    {
        player.change_gold(- hp_price);
        player.recovery_hp();
    }
}
void Shop::recovery_mp(Character &player)
{
    if(player.get_gold() >= mp_price)
    {
        player.change_gold(- mp_price);
        player.recovery_mp();
    }
}
int Shop::get_price(int n)
{
    switch(n)
    {
        case 1:
            return atk_price;
        case 2:
            return def_price;
        case 3:
            return exp_price;
        case 4:
            return hp_price;
        case 5:
            return mp_price;
        default:
            return -1;
    }
}
int Shop::get_stock(int n)
{
    switch(n)
    {
        case 1:
            return atk_stock;
        case 2:
            return def_stock;
        case 3:
            return exp_stock;
        default:
            return -1;
    }
}