#include "Button.hpp"
Button::Button(double _x_t, double _y_t, std::string _text, int _text_size) {
    x_t = _x_t;
    y_t = _y_t;
    
    text_size = _text_size;
    font.loadFromFile("fonts/RodchenkoBTT.ttf"); //загружаем шрифт
    text.setString(_text);						// загружает текст
    text.setFont(font);							// устанавливаем шрифт
    text.setCharacterSize(_text_size); 					// устанавливаем размер текста

    width = text.getLocalBounds().width;
    height = text.getLocalBounds().height;

    text.setFillColor(sf::Color::Red);					// устанавливаем цвет текста
    text.setPosition(x_t - width / 2, y_t - height);						// устанавливаем координаты текста

    box.setSize(sf::Vector2f(width, height));		// устанавливаем размер кнопки
    box.setPosition(x_t - width / 2, y_t - 3 * height / 5);						// устанавливаем координаты кнопки
    box.setFillColor(sf::Color::White);	// устанавливаем цвет кнопки
    box.setOutlineThickness(2);					// устанавливаем Контур
    box.setOutlineColor(sf::Color(66, 66, 66));		// устанавливаем Цвет контура
}
//Проверка нажатия на кнопку
bool Button::ifpress(sf::Vector2i _mouse) const{
    if ((_mouse.x > (x_t - width / 2) && _mouse.x < (x_t + width / 2)) && (_mouse.y > (y_t - 3 * height / 5) && _mouse.y < (y_t + 2 * height / 5))) {
        return  true;
    }
    else {
        return false;
    }
}
//Вывод кнопки
sf::RectangleShape Button::displayButton() const{
    return box;
}
sf::Text Button::displayText() const{
    return text;
}
void Button::changeTextColor() {
    text.setFillColor(sf::Color(240, 100, 100));
}
void Button::changeTextColorBack() {
    text.setFillColor(sf::Color::Red);
}
