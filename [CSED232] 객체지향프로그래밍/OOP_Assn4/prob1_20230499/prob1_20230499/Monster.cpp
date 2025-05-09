#include "Monster.h"
#include <cstdlib> //rand(), srand()
#include <cmath> //round -> floor()
#include <ctime> //time()

Monster::Monster(int difficulty) //constructor
{
    srand(time(NULL));
    type = rand() % 4; // 0 : fire, 1 : grass, 2 : water 3: NONE (enum type)
    if(difficulty < 0) //If difficulty is negative integer, boss
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
        // all the stats are based on difficulty through the formula
    }
}

// Because all variables are private, we need to make get_ functions.
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

// int Monster::attack(Character &player) //this makes circular dependency
// {
//     int dmg = atk - player.get_def();
//     if(dmg < 0) dmg - 0; // no negative damage
//     player.change_hp(- dmg);
//     return dmg;
// }

// Also, because of private.
void Monster::change_hp(int delta)
{
    curr_hp += delta;
}

// Return true if monster is dead.
bool Monster::is_dead()
{
    return curr_hp <= 0;
}