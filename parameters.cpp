#include "parameters.h"

void updateConstants(sf::RenderWindow& window, bool& MANDELBROT, PanelButtons& panelX, PanelButtons& panelY, double& CX, double& CY, double& step)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelX.addButton.isClicked(sf::Mouse::getPosition(window)) && !MANDELBROT) {
        if (CX < 4.00)
            CX += step;
        if (CX > 4.00)
            CX = 4.00;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelX.addButton.isClicked(sf::Mouse::getPosition(window)) && !MANDELBROT) {
        panelX.addButton.shape.setFillColor(sf::Color::White);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelX.minButton.isClicked(sf::Mouse::getPosition(window)) && !MANDELBROT) {
        if (CX > -4.00)
            CX -= step;
        if (CX < -4.00)
            CX = -4.00;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelX.minButton.isClicked(sf::Mouse::getPosition(window)) && !MANDELBROT) {
        panelX.minButton.shape.setFillColor(sf::Color::White);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelY.addButton.isClicked(sf::Mouse::getPosition(window)) && !MANDELBROT) {
        if (CY < 4.00)
            CY += step;
        if (CY > 4.00)
            CY = 4.00;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelY.addButton.isClicked(sf::Mouse::getPosition(window)) && !MANDELBROT) {
        panelY.addButton.shape.setFillColor(sf::Color::White);
    }


    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelY.minButton.isClicked(sf::Mouse::getPosition(window)) && !MANDELBROT) {
        if (CY > -4.00)
            CY -= step;
        if (CY < -4.00)
            CY = -4.0;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelY.minButton.isClicked(sf::Mouse::getPosition(window)) && !MANDELBROT) {
        panelY.minButton.shape.setFillColor(sf::Color::White);
    }
}

void updateStep(sf::RenderWindow& window, PanelButtons& panelStep)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelStep.addButton.isClicked(sf::Mouse::getPosition(window))) {
        if (panelStep.step < 1.0)
            panelStep.step *= 10.0;
        panelStep.text.setString("Step : " + removeNDecimals(std::to_string(panelStep.step), 3));
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelStep.addButton.isClicked(sf::Mouse::getPosition(window))) {
        panelStep.addButton.shape.setFillColor(sf::Color::White);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelStep.minButton.isClicked(sf::Mouse::getPosition(window))) {
        if (panelStep.step > 0.001)
            panelStep.step /= 10.0;
        panelStep.text.setString("Step : " + removeNDecimals(std::to_string(panelStep.step), 3));
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && panelStep.minButton.isClicked(sf::Mouse::getPosition(window))) {
        panelStep.minButton.shape.setFillColor(sf::Color::White);
    }
}