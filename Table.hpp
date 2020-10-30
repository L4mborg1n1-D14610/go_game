#pragma once
#include <SFML/Graphics.hpp>
class Table
{
private:
    double x_t;
    double y_t;
    int tablesize;
    sf::Texture tableimage;
    sf::Sprite tablesprite;
public:
    Table(double _x_t, double _y_t, int _tablesize) {
        x_t = _x_t;
        y_t = _y_t;
        tablesize = _tablesize;
        switch (tablesize) {
        case 1:
            tableimage.loadFromFile("Images/smalltable.png");
        case 2:
            tableimage.loadFromFile("Images/mediumtable.png");
        case 3:
            tableimage.loadFromFile("Images/bigtable.png");
        }
        tablesprite.setTexture(tableimage);
        tablesprite.setPosition(x_t, y_t);
    }
    sf::Sprite displaytablesprite() {
        return tablesprite;
    }
};


