#ifndef INCLUDE_MAINMENU_HPP_
#define INCLUDE_MAINMENU_HPP_

#pragma once
#include<SFML/Network.hpp>
#include<iterator>
#include <list>
#include <utility>
#include <memory>
#include <thread>
#include "Button.hpp"
#include "TableStone.hpp"
#include "for_mainmenu.hpp"

class MainMenu {
private:
    Table* table;
    std::list<std::shared_ptr<TableStone>> list_real_stones;
    std::list<std::pair<int, int>> list_coord_white_stones;
    std::list<std::pair<int, int>> list_coord_black_stones;
    int board_size;
    bool menu_table_flag;
    int scrX;
    int scrY;
    bool color;
    bool delete_flag;   //����, ��� ��������� �����
    bool suicide_flag;   //���� ������� ������� �����
    sf::IpAddress ip;
    sf::TcpSocket socket;
    std::string loby_name;
    bool host_flag;
    bool waiting_answer_flag; //for threads & block interface
    bool creator; //true - loby is created
    bool changed_score;
    bool disconnect_flag; // false if player disconnected   
    bool dont_eat_flag; // true if need erase last stone
    int white_score;
    int black_score;
    std::pair<int, int> last_eated_stone;
    std::pair<int, int> last_pushed_stone;
    void print_table(sf::RenderWindow& window); //�������� ����+�����
    void print_menu(sf::RenderWindow& window); //�������� ������� ����
    void add_stone(std::shared_ptr<TableStone> stone);
    bool check_neighbours(int& x, int& y, bool& color_, bool& last_color);
    bool check_neighbours(int& x, int& y, std::list<std::pair<int, int>>& eat, std::list<std::pair<int, int>>& eated, bool& color_);
    void delete_stones(const std::pair<int, int>& eated, bool& color_);
    bool check_eat_stone(int& x, int& y, bool& color_,
        std::list<std::pair<int, int>>& eat, std::list<std::pair<int, int>>& eated);
    bool NOT_VACANT(int& x, int& y, bool& color_);
    bool NOT_VACANT(int& x, int& y, bool&& color_);
    bool VACANT(int&& x, int&& y);
    bool NOT_VACANT_ANY_LIST(int& x, int& y, std::list<std::pair<int, int>> _list);
    static void wait_connect(MainMenu* obj);
    static void wait_stone(MainMenu* obj, std::shared_ptr<TableStone> stone);
    static void wait_first_stone(MainMenu* obj);
    void if_delete_stones(bool&& color_);
public:
    MainMenu(int& _scrX, int& _scrY);
    MainMenu(Table& _table);
    void print_window(sf::RenderWindow& window); //�������� ���� ����, ���� ����
};
#endif // INCLUDE_MAINMENU_HPP_
