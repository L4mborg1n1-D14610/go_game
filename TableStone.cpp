#include "TableStone.hpp"
    TableStone::TableStone() {
        x_t = 0;
        y_t = 0;
        radius = 0;
        size = 0;
    }
    TableStone::TableStone(sf::Vector2i&& _mouse, Table& table, bool _stone_color) {
        switch (table.return_tablesize()) {
        case 1:
            radius = 38;
            size = 9;
            break;
        case 2:
            radius = 28;
            size = 13;
            break;
        case 3:
            radius = 20;
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
    TableStone::TableStone(TableStone& _stone) {
        this->x_t = _stone.x_t;
        this->y_t = _stone.y_t;
        this->radius = _stone.radius;
        this->Tablestone_texture = _stone.Tablestone_texture;
        this->Tablestone_sprite = _stone.Tablestone_sprite;
        this->stone = _stone.stone;
        this->stone_color = _stone.stone_color;
        this->size = _stone.size;
        
    }
    TableStone TableStone::operator=(TableStone& _stone) {
        this->x_t = _stone.x_t;
        this->y_t = _stone.y_t;
        this->radius = _stone.radius;
        this->Tablestone_texture = _stone.Tablestone_texture;
        this->Tablestone_sprite = _stone.Tablestone_sprite;
        this->stone = _stone.stone;
        this->stone_color = _stone.stone_color;
        this->size = _stone.size;
        return *this;
    }
    void TableStone::change_tablestone(sf::Vector2i&& _mouse, Table& table, bool _stone_color) {
/*        switch (table.return_tablesize()) {
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
        stone.setRadius(radius);*/
        this->x_t = std::get<0>(Checkcoordinate(_mouse, radius, size, table));
        this->y_t = std::get<1>(Checkcoordinate(_mouse, radius, size, table));
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
    bool TableStone::check_stone() {
        if (this->x_t == 0 || this->y_t == 0) {
            return false;
        }  else {
            return true;
        }
    }
    sf::CircleShape TableStone::displaystone() const {
        return stone;
    };

