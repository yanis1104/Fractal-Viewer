#pragma once

#include "button.h"

class PanelButtons
{
    public:
        PanelButtons(sf::Vector2f posMin, sf::Vector2f posAdd, int radius, std::vector<sf::Vector2f> signPos, const char *C);
        virtual ~PanelButtons();
        void draw(sf::RenderWindow &window);
        Button minButton;
        Button addButton;
        sf::Text text;
        sf::Font font;
        double step;
};