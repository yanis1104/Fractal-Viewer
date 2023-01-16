#include "button.h"

Button::Button()
{
    this->radius = 0;
    this->step = 0.01;
    this->font.loadFromFile("arial.ttf");
}

Button::Button(sf::Vector2f pos, int radius, const char* text, sf::Vector2f textPos)
{
    this->pos = pos;
    this->radius = radius;
    this->shape.setPosition(this->pos);
    this->shape.setRadius((float)this->radius);
    this->shape.setFillColor(sf::Color::White);
    this->step = 0.01;
    this->font.loadFromFile("arial.ttf");

    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(textPos.x, textPos.y);
    this->text.setCharacterSize(15);
    this->text.setString(text);
}

Button::~Button()
{
}

bool Button::isClicked(sf::Vector2i mousePos)
{
    if (this->shape.getGlobalBounds().contains((sf::Vector2f)mousePos)) {
        this->shape.setFillColor(sf::Color(128, 128, 128));
        return true;
    }
    return false;
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(this->shape);
    window.draw(this->text);
}

void Button::setStep(const double& step)
{
    this->step = step;
}