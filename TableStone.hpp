#pragma once
#include <vector>
#include "Table.hpp"

class TableStone : Table {
private:
    int x_t; //���������� �����
    int y_t;
    int radius; //������ �����
    sf::Texture Tablestone_texture; //�������� �����
    sf::Sprite Tablestone_sprite;
    sf::CircleShape stone; //���������� �����
    bool stone_color; //true - white, false - black
    int size; //����� �����
protected:

public:
    TableStone();
    TableStone(TableStone& stone);
    TableStone(sf::Vector2i&& _mouse, Table& table, bool _stone_color);
    void change_tablestone(sf::Vector2i&& _mouse, Table& table, bool _stone_color);
    bool check_stone();
    bool check_color();
    TableStone operator=(TableStone& _stone);
    sf::CircleShape displaystone() const; //����� ����� �� �����
    std::pair<int, int> stone_coords(Table* _table); //first - horisontal, second - vertical
};
