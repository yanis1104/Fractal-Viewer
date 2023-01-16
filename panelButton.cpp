#include "panelButton.h"

PanelButtons::PanelButtons(sf::Vector2f posMin, sf::Vector2f posAdd, int radius, std::vector<sf::Vector2f> signPos, const char *C)
{
    this->step = 0.010;
    this->addButton.pos = posAdd;
    this->addButton.radius = radius;
    this->addButton.step = 0.01;
    this->addButton.shape.setPosition(this->addButton.pos);
    this->addButton.shape.setRadius((float)this->addButton.radius);
    this->addButton.shape.setFillColor(sf::Color::White);

    this->minButton.pos = posMin;
    this->minButton.radius = radius;
    this->minButton.step = 0.01;
    this->minButton.shape.setPosition(this->minButton.pos);
    this->minButton.shape.setRadius((float)this->minButton.radius);
    this->minButton.shape.setFillColor(sf::Color::White);

    this->font.loadFromFile("arial.ttf");
    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(signPos[1].x + 30, signPos[1].y + 12);
    this->text.setCharacterSize(15);
    this->text.setString(sf::String(C));

    this->minButton.text.setFont(this->minButton.font);
    this->minButton.text.setFillColor(sf::Color::Black);
    this->minButton.text.setPosition(signPos[0].x, signPos[0].y);
    this->minButton.text.setCharacterSize(30);
    this->minButton.text.setString("-");

    this->addButton.text.setFont(this->addButton.font);
    this->addButton.text.setFillColor(sf::Color::Black);
    this->addButton.text.setPosition(signPos[1].x, signPos[1].y);
    this->addButton.text.setCharacterSize(30);
    this->addButton.text.setString("+");
}

PanelButtons::~PanelButtons()
{
}

void PanelButtons::draw(sf::RenderWindow &window)
{
    window.draw(this->text);
    window.draw(this->addButton.shape);
    window.draw(this->minButton.shape);
    window.draw(this->minButton.text);
    window.draw(this->addButton.text);
}