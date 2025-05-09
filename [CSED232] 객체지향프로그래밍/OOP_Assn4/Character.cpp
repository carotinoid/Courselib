#include "Character.h"
#include <cmath> //round -> floor()

Character::Character(Map &map) //constructor
{
    x = map.get_start_x(); //get start position from map
    y = map.get_start_y();
    attack = 10; //default stats
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

// Using go_ functions, player character can move in the map, without going out of the map.
// Then, return true if the character can move, false if not.
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

// get_ functions are used to get the private variables.
int Character::get_x()
{
    return x;
}
int Character::get_y()
{
    return y;
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

// change_ functions are also used to change the private variables.
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

// level_up function is used to level up the character.
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

// recovery_ functions makes curr_ to max_ of hp or mp.
void Character::recovery_hp()
{
    curr_hp = max_hp;
}
void Character::recovery_mp()
{
    curr_mp = max_mp;
}

// is_dead function returns true if the character is dead.
bool Character::is_dead()
{
    return curr_hp <= 0;
}

// attack_ functions are used to attack the monster with each type, and return the damage.
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