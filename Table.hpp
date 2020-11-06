#pragma once
#include <SFML/Graphics.hpp>

#include "math_functions.hpp"

class Table {
private:
    double x_t;
    double y_t;
    int tablesize; //9x9/13x19/19x19
    sf::Texture tableimage;
    sf::Sprite tablesprite;
    sf::Sprite Tablestone_sprite;  //спрайт камня
protected:
    std::vector<int> doats_coordinate_x; //координаты пересечений на доске
    std::vector<int> doats_coordinate_y;
    std::pair<int, int> Checkcoordinate(sf::Vector2i _mouse, int radius, int size, Table&& table) const; //возвращает координату камня, зависящую от координаты курсора
    std::pair<int, int> Checkcoordinate(sf::Vector2i _mouse, int radius, int size, Table& table) const;
public:
    Table();
    Table(int& _tablesize);
    Table(int&& _tablesize);
    int return_tablesize() const;
    sf::Sprite displaytablesprite() const;
    std::vector<int>::iterator return_iter_x();
    std::vector<int>::iterator return_iter_y();
    bool checkStoneCursor(sf::Vector2i _mouse); //проверяет, находится ли курсор в области, доступной для создания камня
};


