#include "color.h"
#include "parameters.h"

extern std::vector<sf::Color> palette{ sf::Color(66, 30, 15), sf::Color(25, 7, 26), sf::Color(9, 1, 47), sf::Color(4, 4, 73), sf::Color(0, 7, 100), sf::Color(12, 44, 138), sf::Color(24, 82, 177), sf::Color(57, 125, 209), sf::Color(134, 181, 229), sf::Color(211, 236, 248), sf::Color(241, 233, 191), sf::Color(248, 201, 91), sf::Color(255, 170, 0), sf::Color(204, 128, 0), sf::Color(153, 87, 0), sf::Color(106, 52, 3) };

void render_color(sf::Image* image, int* pixels, int width, int height)
{
    // Update the image
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int value = pixels[y * width + x];
            //sf::Color color(value % 8 * 32, value % 4 * 64, value % 2 * 128);
            //sf::Color color(value % 8 * 32, value % 4 * 32, value % 2 * 32);
            //sf::Color color(value % 4 * 32, value % 4 * 32, value % 8 * 16);
            //sf::Color color(value % 32 * 32, value % 32 * 32, value % 32 * 32);
            //sf::Color color(log(value % 32) * 32, log(value % 32) * 32, log(value % 32) * 32); //INSANE
            //sf::Color color(log(value % 128) * 128, log(value % 128) * 128, log(value % 128) * 32);
            //sf::Color color(log(value % 32) * 128, log(value % 32) * 128, log(value % 32) * 64);
            //sf::Color color(log(value % 8) * r, log(value % 8) * g, log(value % 8) * b);
            //sf::Color color = interpolation(value % 2 * (palette.size() - 1));

            sf::Color color = sf::Color::Black;
            if (value < MAX_ITERATIONS && value > 0)
                color = palette[value % (palette.size() - 1)];
            image->setPixel(x, y, color);
        }
    }
}