#pragma once
#include <SFML/Graphics.hpp>
class Button {
protected:
    double width;		// Ширина Кнопки
    double height;		// Высота Кнопки
    double x_t;
    double y_t;
    int text_size;
    sf::Text text;
    sf::Font font;
    sf::RectangleShape box;	// Создаем прямоугольник с размером width, height
public:
    Button(double _x_t, double _y_t, std::string _text, int _text_size);
    bool ifpress(sf::Vector2i _mouse);
    sf::RectangleShape displayButton();
    sf::Text displayText();
    void changeTextColor();
    void changeTextColorBack();
};
