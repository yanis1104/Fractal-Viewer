#pragma once

#include <SFML/Graphics.hpp>

void print_equation(double CX, double CY, bool MANDELBROT, sf::RenderWindow& window);
std::string removeNDecimals(std::string C, const int N);