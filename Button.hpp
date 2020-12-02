#pragma once
#include <SFML/Graphics.hpp>

class Button {
protected:
    double width;		// ������ ������
    double height;		// ������ ������
    double x_t;
    double y_t;
    unsigned int text_size;
    std::string str_text;
    sf::Text text;
    sf::Font font;
    sf::RectangleShape box;	// ������� �������������
public:
    Button(double _x_t, double _y_t, std::string _text, int _text_size);
    Button(double _x_t, double _y_t, int _text_size);
    bool ifpress(sf::Vector2i _mouse) const;
    sf::RectangleShape displayButton() const;
    sf::Text displayText() const;
    void add_letter(char a);
    void delete_letter(char a);
    void changeTextColor();
    void changeTextColorBack();
};
