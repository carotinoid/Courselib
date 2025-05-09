#include "Shop.h"

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