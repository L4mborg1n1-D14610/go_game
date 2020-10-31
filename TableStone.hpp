#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Table.hpp"

class TableStone : Table{
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
    TableStone(sf::Vector2i&& _mouse, Table& table, bool _stone_color); 
    sf::CircleShape displaystone() const; //����� ����� �� �����
};

