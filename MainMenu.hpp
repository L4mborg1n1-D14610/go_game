#pragma once

#include <SFML/Graphics.hpp>
#include<vector>
#include<iterator>

#include "Table.hpp""
#include "TableStone.hpp"

class MainMenu
{
private:
    Table* table;
    std::vector<TableStone*> vec_stones;
public:
    MainMenu(Table &_table);
    void print_table(sf::RenderWindow& window);
    void add_stone(TableStone* stone/*, sf::RenderWindow& window, bool& color*/);
};

