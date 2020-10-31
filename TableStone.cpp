#include "TableStone.hpp"
    TableStone::TableStone(sf::Vector2i&& _mouse, Table& table, bool _stone_color) {
        switch (table.return_tablesize()) {
        case 1:
            radius = 34;
            size = 9;
            break;
        case 2:
            radius = 25;
            size = 13;
            break;
        case 3:
            radius = 18;
            size = 19;
            break;
        default: break;
        }
        stone_color = _stone_color;
        stone.setRadius(radius);
        x_t = std::get<0>(Checkcoordinate(_mouse, radius, size, table));
        y_t = std::get<1>(Checkcoordinate(_mouse, radius, size, table));
        if (x_t && y_t) {
            stone.setPosition(x_t - radius, y_t - radius);
            if (stone_color) {
                Tablestone_texture.loadFromFile("Images/WhiteTexture.png");
            }
            else {
                Tablestone_texture.loadFromFile("Images/BlackTexture.png");
            }
            stone.setTexture(&Tablestone_texture);
        }

    };

    sf::CircleShape TableStone::displaystone() const {
        return stone;
    };

