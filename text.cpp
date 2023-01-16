#include "text.h"

std::string removeNDecimals(std::string C, const int N)
{
    int comaPos = 0;

    for (int i = 0; i < (int)C.size(); i++) {
        if (C[i] == '.') {
            comaPos = i;
            break;
        }
    }
    for (int i = (int)C.size() - 1, j = 0; i > comaPos && j < N; i--, j++) {
        C.pop_back();
    }
    return C;
}

void print_equation(double CX, double CY, bool MANDELBROT, sf::RenderWindow& window)
{
    static sf::Font font;
    static bool is_font_loaded = false;
    static sf::Text text;
    static std::string _CX = removeNDecimals(std::to_string(CX), 3);
    static std::string _CY = removeNDecimals(std::to_string(CY), 3);

    if (!is_font_loaded) {
        is_font_loaded = true;
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setPosition(20, 910);
        text.setCharacterSize(20);
    }
    _CX = removeNDecimals(std::to_string(CX), 3);
    _CY = removeNDecimals(std::to_string(CY), 3);
    if (!MANDELBROT)
        text.setString(((CX >= 0) ? "Z² +" : "Z² ") + _CX + ((CY >= 0) ? " +" : " ") + _CY + "i");
    else
        text.setString("Z² + c");
    window.draw(text);
}