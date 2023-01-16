#pragma once

#include <SFML/Graphics.hpp>

class Button
{
    public:
        Button();
        Button(sf::Vector2f pos, int radius, const char* text, sf::Vector2f textPos);
        virtual ~Button();
        bool isClicked(sf::Vector2i mousePos);
        void draw(sf::RenderWindow& window);
        void setStep(const double &step);
        sf::CircleShape shape;
        sf::Vector2f pos;
        int radius;
        double step;
        sf::Font font;
        sf::Text text;
};