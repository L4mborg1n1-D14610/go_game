#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Table.hpp"

class TableStone : Table{
private:
    int x_t; //координаты камн€
    int y_t;
    int radius; //радиус камн€
    sf::Texture Tablestone_texture; //текстура камн€
    sf::Sprite Tablestone_sprite;
    sf::CircleShape stone; //окружность камн€
    bool stone_color; //true - white, false - black
    int size; //длина доски
protected:

public:
    TableStone(sf::Vector2i&& _mouse, Table& table, bool _stone_color); 
    sf::CircleShape displaystone() const; //вывод камн€ на экран
};

