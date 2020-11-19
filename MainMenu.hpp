#pragma once
#include<iterator>
#include <list>
#include <utility>
#include <iostream>
#include "Button.hpp"
#include "TableStone.hpp"

class MainMenu {
private:
    Table* table;
    std::list<TableStone*> list_real_stones;
    std::list<std::pair<int, int>> list_coord_white_stones;
    std::list<std::pair<int, int>> list_coord_black_stones;
    int board_size;
    bool menu_table_flag;
    int scrX;
    int scrY;
    bool color;

    int middlescreenX(int& x);
    int middlescreenY(int& y);
    void if_mouse_not_on_button(Button& button, sf::RenderWindow& window, bool flag);
    bool delete_flag;   //флаг, что удалились камни
    bool suicide_flag;   //флаг попытки суицида камня
public:

    MainMenu(int& scrX, int& scrY);
    MainMenu(Table& _table);
    void print_table(sf::RenderWindow& window); //печатаем стол+камни
    void print_menu(sf::RenderWindow& window); //печатаем главное меню
    void add_stone(TableStone* stone);
    void print_window(sf::RenderWindow& window); //печатаем либо стол, либо меню
    void if_delete_stones(bool&& color);
    bool check_neighbours(int& x, int& y, bool& color, bool& last_color);
    bool check_neighbours(int& x, int& y, std::list<std::pair<int, int>>& eat, std::list<std::pair<int, int>>& eated, bool& color);
    void delete_stones(const std::pair<int, int>& eated, bool& color);
    bool check_eat_stone(int& x, int& y, bool& color,
        std::list<std::pair<int, int>>& eat, std::list<std::pair<int, int>>& eated);
    bool NOT_VACANT(int& x, int& y, bool& color);
    bool NOT_VACANT(int& x, int& y, bool&& color);
    bool VACANT(int&& x, int&& y);
    bool NOT_VACANT_ANY_LIST(int& x, int& y, std::list<std::pair<int, int>> _list);

};
std::pair<int, int> return_stone_coordinate(const std::pair<int, int>& _pair, int& tablesize);
std::list<std::pair<int, int>>::iterator& operator+=(std::list < std::pair<int, int>>::iterator& it, int x);