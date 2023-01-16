#pragma once

#include "panelButton.h"
#include "text.h"

const int WIDTH = 1500;
const int HEIGHT = 950;
const int MAX_ITERATIONS = 1000;

void updateConstants(sf::RenderWindow& window, bool& MANDELBROT, PanelButtons& panelX, PanelButtons& panelY, double& CX, double& CY, double& step);
void updateStep(sf::RenderWindow& window, PanelButtons& panelStep);