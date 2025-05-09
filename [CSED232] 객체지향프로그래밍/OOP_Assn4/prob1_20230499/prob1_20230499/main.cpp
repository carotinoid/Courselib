#include <iostream>
#include <cmath> //round -> floor()
#include "Map.h"
#include "Character.h"
#include "Monster.h"
#include "Shop.h"

using std::cout;
using std::cin;
using std::endl;
/*----------------
# Dependency

ex)
* A
|
* B -> A is needed for B.

* Monster.h
| * Map.h
|/
* Character.h
|
* Shop.h
----------------*/

// function prototypes, comment of each function is placed in the part of function definition
void print_logo();
void show_map(Map& map, Character& player);
void show_character_status(Character& player);
void random_event(Character& player);
void shopping(Shop& shop, Character& player);
//void check_level_up(int bf[3], Character &player); //deleted, because it is not used
void fight(Character& player, Monster& monster, bool check_boss = false);
void show_changed_character_status(Character& player, int d_atk, int d_def, int d_hp, int d_mp, int d_exp, bool FORCED_PRINT_HP_CHANGE = false, bool FORCED_PRINT_MP_CHANGE = false);
void show_changed_shop_stock(Shop& shop, int n);
template <typename T>
bool check_in(T a, T b[], int size);
void game();

// check whether a (type T) is in b (type T array)
// linear search template
template <typename T>
bool check_in(T a, T b[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a == b[i]) return true;
    }
    return false;
}

// just print logo, ascii art.
void print_logo()
{
    cout << "========================================================" << endl;
    cout << "========================================================" << endl;
    cout << "========================================================" << endl;
    cout << " #######                      ######  ######  #####     " << endl;
    cout << "    #   ###### #    # #####   #     # #     # #    #    " << endl;
    cout << "    #   #       #  #   #      #     # #     # #         " << endl;
    cout << "    #   #####    ##    #      ######  ######  #  ####   " << endl;
    cout << "    #   #        ##    #      #   #   #   #   #    #    " << endl;
    cout << "    #   #       #  #   #      #    #  #    #  #    #    " << endl;
    cout << "    #   ###### #    #  #      #     # #     #  ####     " << endl;
    cout << "========================================================" << endl;
    cout << "========================================================" << endl;
    cout << "========================================================\n" << endl;
}

// Print beautiful(!) map, using ascii art.
// If player is in the position, print "You"
// If player is not in the position and unveiled, print "?"
// If player visited the position (veiled), print " ", except "S" (shop)
void show_map(Map& map, Character& player)
{
    for (int i = 0; i < 17; i++)
    {
        if (i == 0) cout << "忙式式式成式式式成式式式成式式式成式式式成式式式成式式式成式式式忖"; //first line
        else if (i == 16) cout << "戌式式式扛式式式扛式式式扛式式式扛式式式扛式式式扛式式式扛式式式戎";//last line
        else if (i % 2 == 0) cout << "戍式式式托式式式托式式式托式式式托式式式托式式式托式式式托式式式扣";//middle line
        else if (i % 2 == 1) //print each position
        {
            for (int j = 0; j < 33; j++)
            {
                if (j == 0 or j == 32 or j % 4 == 0) cout << "弛";
                else if (j % 4 == 1)
                {
                    if (i / 2 == player.get_y() && j / 4 == player.get_x()) cout << "You";
                    else if (map.isnot_veil(i / 2, j / 4)) cout << " ? ";
                    else if (map.get_map(i / 2, j / 4) == 'S') cout << " S ";
                    else cout << "   ";
                    j += 2;
                }
            }
        }
        cout << endl;
    }
}

// This function prints character status. This function is called when player select menu 2, or fight scene.
void show_character_status(Character& player)
{
    cout << "level: " << player.get_level() << endl;
    cout << "Attack: " << player.get_atk() << endl;
    cout << "Defense: " << player.get_def() << endl;
    cout << "Gold: " << player.get_gold() << endl;
    cout << "HP: " << player.get_hp() << " / " << player.get_max_hp() << endl;
    cout << "MP: " << player.get_mp() << " / " << player.get_max_mp() << endl;
    cout << "EXP: " << player.get_exp() << " / " << player.get_level() * 100 << endl;
}

// This function is not used, show_changed_character_status() is used instead of this function.
/*
void check_level_up(int bf[3], Character &player) // bf : before data
{
    if(bf[0] < player.get_level())
    {
        int diff = player.get_level() - bf[0];
        cout << "Level up!" << endl;
        cout << "===============================" << endl;
        cout << "Character status" << endl;
        cout << "Level: " << bf[0] << " => " << player.get_level() << endl;
        cout << "Attack: " << player.get_atk() - 3 * diff << " => " << player.get_atk() << endl;
        cout << "Defense: " << player.get_def() - 1 * diff << " => " << player.get_def() << endl;
        cout << "HP: " << bf[1] << " / " << player.get_max_hp() - 50 * diff << " => " << player.get_hp() << " / " << player.get_max_hp() << endl;
        cout << "MP: " << bf[2] << " / " << player.get_max_mp() - 10 * diff << " => " << player.get_mp() << " / " << player.get_max_mp() << endl;
        int exp_diff = 0;
        for(int i = bf[0]; i < player.get_level(); i++) exp_diff += i * 100;
        cout << "EXP: " << player.get_exp() + exp_diff << " / " << bf[0] * 100 << " => " << player.get_exp() << " / " << player.get_level() * 100 << endl;
        cout << "===============================" << endl;

    }
}
*/

// random event, execute when player visit "R" (random event) in the map.
void random_event(Character& player)
{
    cout << "Random encounter!" << endl;
    cout << endl;
    srand(time(NULL));
    int random_encounter = rand() % 4 + 1; // 1, 2, 3, 4
    switch (random_encounter) // 1: lost HP, 2: restore HP, 3: get gold, 4: nothing
    {
    case 1:
    {
        cout << "You lost HP..." << endl; // 30%
        int lost_hp = -floor(double(player.get_hp()) * 0.3 + 0.5);
        player.change_hp(lost_hp);
        break;
    }
    case 2: // NOW HP 30% -> what is the meaning of this?
    {       // sol) now (both curr_ and max_ are allowed.)
        cout << "You restored HP" << endl; // 30%
        int restored_hp = floor(double(player.get_hp()) * 0.3 + 0.5);
        // If restored_hp + hp is bigger than max_hp, restore only max_hp - hp.
        player.change_hp(std::min(player.get_max_hp() - player.get_hp(), restored_hp));
        break;
    }
    case 3:
    {
        cout << "You found 100 gold!" << endl;
        player.change_gold(100);
        break;
    }
    case 4:
        cout << "Nothing happened..." << endl;
        break;
    }
}

// show changed character status, when player status is changed.
// * when player is already max hp or mp, but recovery hp or mp, print changed hp or mp using "=>" even if hp or mp is not changed.
// So, FORCED_PRINT_ is used to print changed hp or mp even if hp or mp is not changed.
void show_changed_character_status(Character& player, int d_atk, int d_def, int d_hp, int d_mp, int d_exp, bool FORCED_PRINT_HP_CHANGE, bool FORCED_PRINT_MP_CHANGE) // not change, only print
{
    int d_level = 0;
    int d_max_hp = 0;
    int d_max_mp = 0; // d_ function is delta of each variables.
    if (d_exp != 0) // If player get exp, check level up
        while (player.get_exp() + d_exp > (player.get_level() + d_level) * 100)
        {
            //If level up, change some delta.
            d_exp -= (player.get_level() + d_level) * 100;
            d_level++;
            d_atk += 3;
            d_def += 1;
            d_max_hp += 50;
            d_max_mp += 10;
            d_hp = d_max_hp + player.get_max_hp() - player.get_hp();
            d_mp = d_max_mp + player.get_max_mp() - player.get_mp();
        }
    if (d_level != 0) cout << "Level up!" << endl; // If level up, print level up message.
    // If d_ is 0, Just print current status.
    // However, if d_ is not 0, print changed status using "=>"
    // Print level, atk, def, hp, mp, exp... each.
    cout << "===============================" << endl;
    cout << "Character status" << endl;
    cout << "Level: " << player.get_level();
    if (d_level != 0) cout << " => " << player.get_level() + d_level << endl;
    else cout << endl;
    cout << "Attack: " << player.get_atk();
    if (d_atk != 0) cout << " => " << player.get_atk() + d_atk << endl;
    else cout << endl;
    cout << "Defense: " << player.get_def();
    if (d_def != 0) cout << " => " << player.get_def() + d_def << endl;
    else cout << endl;
    cout << "HP: " << player.get_hp() << " / " << player.get_max_hp();
    if (d_hp != 0 || FORCED_PRINT_HP_CHANGE) cout << " => " << player.get_hp() + d_hp << " / " << player.get_max_hp() + d_max_hp << endl;
    else cout << endl;
    cout << "MP: " << player.get_mp() << " / " << player.get_max_mp();
    if (d_mp != 0 || FORCED_PRINT_MP_CHANGE) cout << " => " << player.get_mp() + d_mp << " / " << player.get_max_mp() + d_max_mp << endl;
    else cout << endl;
    cout << "EXP: " << player.get_exp() << " / " << player.get_level() * 100;
    if (d_exp != 0) cout << " => " << player.get_exp() + d_exp << " / " << (player.get_level() + d_level) * 100 << endl;
    else cout << endl;
    cout << "===============================" << endl;
}

// show changed shop stock, when player buy item in the shop.
// calculate changed stock, and print changed stock, using "=>" if stock is changed. (using conditional operator)
// argument integer 'n' is selected item number.
void show_changed_shop_stock(Shop& shop, int n) //not upper line of '='
{
    cout << "Shop item list" << endl;
    cout << "1. Attack +10 (" << shop.get_price(1) << " gold) ";
    if (n == 1) cout << "(Available) => " << (shop.get_stock(1) - 1 ? "(Available)" : "(Sold out)") << endl;
    else cout << (shop.get_stock(1) ? "(Available)" : "(Sold out)") << endl;
    cout << "2. Defense +5 (" << shop.get_price(2) << " gold) ";
    if (n == 2) cout << "(Available) => " << (shop.get_stock(2) - 1 ? "(Available)" : "(Sold out)") << endl;
    else cout << (shop.get_stock(2) ? "(Available)" : "(Sold out)") << endl;
    cout << "3. EXP +300 (" << shop.get_price(3) << " gold) ";
    if (n == 3) cout << "(Available) => " << (shop.get_stock(3) - 1 ? "(Available)" : "(Sold out)") << endl;
    else cout << (shop.get_stock(3) ? "(Available)" : "(Sold out)") << endl;
    cout << "4. Restore HP (" << shop.get_price(4) << " gold) (Always available)" << endl;
    cout << "5. Restore MP (" << shop.get_price(5) << " gold) (Always available)" << endl;
    cout << "===================================" << endl;
}

// shopping, when player visit "S" in the map,
// print shop menu, and player can buy item in the shop.
void shopping(Shop& shop, Character& player)
{
    //bool check = true;
    cout << "Welcome to the shop!" << endl; // print shop menu
    cout << "You have " << player.get_gold() << " gold." << endl;
    cout << "===================================" << endl;
    cout << "============ Item list ============" << endl;
    cout << "===================================" << endl;
    cout << endl;
    cout << "1. Attack +10 (" << shop.get_price(1) << " gold) " << (shop.get_stock(1) ? "(Available)" : "(Sold out)") << endl;
    cout << "2. Defense +5 (" << shop.get_price(2) << " gold) " << (shop.get_stock(2) ? "(Available)" : "(Sold out)") << endl;
    cout << "3. EXP +300 (" << shop.get_price(3) << " gold) " << (shop.get_stock(3) ? "(Available)" : "(Sold out)") << endl;
    cout << "4. Restore HP (" << shop.get_price(4) << " gold) (Always available)" << endl;
    cout << "5. Restore MP (" << shop.get_price(5) << " gold) (Always available)" << endl;
    cout << "6. Exit shop" << endl;
    cout << endl;
    cout << "===================================" << endl;
    //while(check)
    //{
    int shop_sel;
    int shop_list[] = { 1, 2, 3, 4, 5, 6 }, shop_list_size = 6;
    while (true)
    {
        do {
            cout << "> ";
            cin >> shop_sel; // get selected item number
        } while (!check_in(shop_sel, shop_list, shop_list_size)); // check whether selected item is in the shop list

        if (shop_sel == 6) return;

        // If selected item is not available,
        if (!shop.get_stock(shop_sel)) cout << "Selected item is not available...\n" << endl;

        // If player doesn't have enough gold,
        else if (player.get_gold() < shop.get_price(shop_sel)) cout << "You do not have enough gold...\n" << endl;

        else break;
    }
    // If player bought item,
    cout << "You bought an item!" << endl;
    cout << endl;
    switch (shop_sel)
    { // print changed status using show_changed_... function, then change player status using shop member function.
    case 1:
    {
        show_changed_character_status(player, 10, 0, 0, 0, 0);
        show_changed_shop_stock(shop, 1);
        shop.atk_up(player);
        break;
    }
    case 2:
    {
        show_changed_character_status(player, 0, 5, 0, 0, 0);
        show_changed_shop_stock(shop, 2);
        shop.def_up(player);
        break;
    }
    case 3:
    {
        show_changed_character_status(player, 0, 0, 0, 0, 300);
        show_changed_shop_stock(shop, 3);
        //int before_data[3] = {player.get_level(), player.get_hp(), player.get_mp()};
        shop.exp_up(player); //exp_up() function include levelup
        //check_level_up(before_data, player);
        break;
    }
    case 4:
    {
        show_changed_character_status(player, 0, 0, player.get_max_hp() - player.get_hp(), 0, 0, true, false);
        show_changed_shop_stock(shop, 4);
        shop.recovery_hp(player);
        break;
    }
    case 5:
    {
        show_changed_character_status(player, 0, 0, 0, player.get_max_mp() - player.get_mp(), 0, false, true);
        shop.recovery_mp(player);
        break;
    }
    //case 6: check = false; break;
    }
    // }
}

// fight with monster, when player visit "M" or "B" in the map.
void fight(Character& player, Monster& monster, bool check_boss)
{
    // if(monster.get_type() == FIRE) cout << "Fire monster appeared!" << endl;
    // else if(monster.get_type() == GRASS) cout << "Grass monster appeared!" << endl;
    // else if(monster.get_type() == WATER) cout << "Water monster appeared!" << endl;
    // cout << endl;
    cout << "Wild monster appeared!" << endl;
    cout << endl;
    while (true)
    {
        // First, check player or monster is dead.
        // If player is dead, print "You died..." and exit game.
        if (player.is_dead())
        {
            cout << endl;
            cout << "You died..." << endl;
            exit(0);
            break;
        }
        // If monster is dead, player will get reward,
        // If monster is boss, print "You win!" and exit game.
        if (monster.is_dead())
        {
            if (!check_boss)
            {
                cout << "You defeated the monster!" << endl;
                cout << "Reward: " << monster.get_reward_gold() << " gold, " << monster.get_reward_exp() << " exp" << endl;
                cout << endl;
                //int before_data[3] = {player.get_level(), player.get_hp(), player.get_mp()};
                show_changed_character_status(player, 0, 0, 0, 0, monster.get_reward_exp());
                player.change_exp(monster.get_reward_exp());
                player.change_gold(monster.get_reward_gold());
                //check_level_up(before_data, player);
                break;
            }
            if (check_boss)
            {
                cout << "You defeated the boss!" << endl;
                cout << "You win!" << endl;
                exit(0);
            }
        }
        // If player and monster are still alive,
        // 1. print each status,
        // 2. select action,
        // 3. calculate damage to monster and player, and print damage,
        cout << "===============================" << endl;
        show_character_status(player);
        cout << "===============================" << endl;
        cout << "Monster status" << endl;
        cout << "Attack: " << monster.get_atk() << endl;
        cout << "Defense: " << monster.get_def() << endl;
        cout << "HP: " << monster.get_hp() << endl;
        cout << "===============================" << endl;
        cout << "Choose your action" << endl;
        cout << "1. Meele attack" << endl;
        cout << "2. Magic attack" << endl;
        cout << "3. Fire magic attack" << endl;
        cout << "4. Grass magic attack" << endl;
        cout << "5. Water magic attack" << endl;
        int action_sel;
        int action_list[] = { 1, 2, 3, 4, 5 }, action_list_size = 5;
        do {
            cout << "> ";
            cin >> action_sel;
        } while (!check_in(action_sel, action_list, action_list_size));
        int dmg_to_monster, dmg_to_player;

        // Each player attack member function return damage to monster through the given formula, If def is bigger then atk, damage is 0. Also, if player doesn't have enough mp, damage is -1 (negative).
        switch (action_sel) {
        case 1: dmg_to_monster = player.attack_basic(monster); break;
        case 2: dmg_to_monster = player.attack_skill(monster); break;
        case 3: dmg_to_monster = player.attack_fire(monster); break;
        case 4: dmg_to_monster = player.attack_grass(monster); break;
        case 5: dmg_to_monster = player.attack_water(monster); break;
        }

        // if player defeated monster, however player still get damage.
        // So, checking monster is dead now is not necessary.

        // monster.attack member function makes circular dependency
        // dmg_to_player = monster.attack(player);
        // -----------------------------------
        dmg_to_player = monster.get_atk() - player.get_def();
        if (dmg_to_player < 0) dmg_to_player = 0; // no negative damage
        player.change_hp(-dmg_to_player);
        // -----------------------------------
        cout << endl;
        if (dmg_to_monster < 0) cout << "Not enough MP..." << endl;
        else cout << "You hit the monster with " << dmg_to_monster << " damage!" << endl;
        cout << "Monster hit you with " << dmg_to_player << " damage!" << endl;
        cout << endl;
    }
}

// main game function, this function is called when player select menu 1.
void game()
{
    // create map, player, shop object.
    Map map;
    Character player(map);
    Shop shop;
    // player.change_gold(10000); //debug
    // player.change_atk(100); //debug
    cout << "Game Start!\n\n";
    while (true)
    {
        show_map(map, player); // print map
        cout << "1. Choose direction" << endl;
        cout << "2. Show character status" << endl;
        cout << "3. Exit" << endl;
        int menu_sel;
        int menu_list[] = { 1, 2, 3 }, menu_list_size = 3;
        do {
            cout << "> ";
            cin >> menu_sel; // select menu
        } while (!check_in(menu_sel, menu_list, menu_list_size)); // check whether selected menu is in the menu list
        if (menu_sel == 3) break;    // input = 3, exit game
        else if (menu_sel == 2)      // input = 2, show character status
        {
            cout << endl;
            show_character_status(player);
            cout << endl;
        }
        else if (menu_sel == 1)      // input = 1, choose direction
        {
            cout << "Where do you want to go?" << endl;
            char dir;
            char dir_list[] = { 'w', 'a', 's', 'd' }; int dir_list_size = 4;
            while (true)             // select direction
            {
                do {
                    cout << "> ";
                    cin >> dir; // get direction
                } while (!check_in(dir, dir_list, dir_list_size)); // check whether selected direction is in the direction list

                // if player can move to the selected direction, break loop.
                // else, print "You cannot move to that direction.", and get dir again.
                if (dir == 'w') { if (player.go_up()) break; }
                else if (dir == 'a') { if (player.go_left()) break; }
                else if (dir == 's') { if (player.go_down()) break; }
                else if (dir == 'd') { if (player.go_right()) break; }
                cout << "You cannot move to that direction." << endl;
            }

            // Player can visit shop several times, even map is already veiled.
            if (!map.isnot_veil(player.get_y(), player.get_x()) && map.get_map(player.get_y(), player.get_x()) == 'S') shopping(shop, player);

            // If player visit unveiled position, veil and execute each event.
            else if (map.isnot_veil(player.get_y(), player.get_x()))
            {
                map.veil(player.get_y(), player.get_x());
                char where = map.get_map(player.get_y(), player.get_x());
                switch (where)
                {
                case 'E': break; //empty
                case 'R': { random_event(player); break; } //execute random event.
                case 'M': //fight with monster
                {
                    Monster monster(map.distance(player.get_y(), player.get_x())); fight(player, monster); break;
                }
                case 'B': //fight with boss
                {
                    Monster boss(-1);
                    fight(player, boss, true); break;
                }
                case 'S': { shopping(shop, player); break; } // visit shop
                }
            }
        }
    }
}

// main function.
int main()
{
    print_logo(); // first, print logo.
    // Then, choose menu, and start game or exit.
    cout << "----- Menu -----" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Exit" << endl;
    int menu_sel;
    int menu_list[] = { 1, 2 }, menu_list_size = 2;
    do {
        cout << "> ";
        cin >> menu_sel;
    } while (!check_in(menu_sel, menu_list, menu_list_size));
    if (menu_sel == 2)
    {
        cout << "Exit..." << endl;
        return 0;
    }
    else if (menu_sel == 1) game();
}