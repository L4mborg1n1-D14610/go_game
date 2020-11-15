#pragma once
#include<iterator>
#include <list>
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

    int middlescreenX(int& x);
    int middlescreenY(int& y);
    void if_mouse_not_on_button(Button& button, sf::RenderWindow& window, bool flag);
public:

    MainMenu(int& scrX, int& scrY);
    MainMenu(Table& _table);
    void print_table(sf::RenderWindow& window); //�������� ����+�����
    void print_menu(sf::RenderWindow& window); //�������� ������� ����
    void add_stone(TableStone* stone);
    void print_window(sf::RenderWindow& window); //�������� ���� ����, ���� ����
    void if_delete_stones();
    void check_neighbours(std::list < std::pair<int, int>>::iterator it,
        std::list < std::pair<int, int>>& eat,
        std::list < std::pair<int, int>>& eated,
        bool& color);
    bool VACANT(int& x, int& y, bool& color);
};
std::list<std::pair<int, int>>::iterator& operator+=(std::list < std::pair<int, int>>::iterator& it, int x);