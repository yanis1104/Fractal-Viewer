#include <SFML/Graphics.hpp>
#include <cuda.h>
#include <cuda_runtime.h>

#include "panelButton.h"
#include "text.h"
#include "parameters.h"
#include "color.h"

__global__ void fractal_kernel(int* d_pixels, int width, int height, double x_min, double x_max, double y_min, double y_max, double CX, double CY, bool MANDELBROT) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= width || y >= height)
        return;

    double real = x_min + x * (x_max - x_min) / width;
    double imag = y_min + y * (y_max - y_min) / height;

    double z_real = real;
    double z_imag = imag;

    /*
        mandelbrot: z² + real + imag
        z² - 1
        z² -0.2 + 0.7i
    */
    if (MANDELBROT) {
        CX = real;
        CY = imag;
    }

    double cx = CX;
    double cy = CY;
    int value = 0;
    double tmp_real = z_real;
    double tmp_imag = z_imag;
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        tmp_real = z_real;
        tmp_imag = z_imag;
        if (tmp_real * tmp_real + tmp_imag * tmp_imag > 4.0f) {
            value = i;
            break;
        }
        z_real = tmp_real * tmp_real - tmp_imag * tmp_imag + cx;
        z_imag = 2 * tmp_real * tmp_imag + cy; // 2ab + b² avec (x*i)²
    }

    d_pixels[y * width + x] = value;
}

void switchMandelbrot(sf::RenderWindow &window, bool &MANDELBROT, PanelButtons &panelX, PanelButtons &panelY, Button &mandelbrotButton)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mandelbrotButton.isClicked(sf::Mouse::getPosition(window))) {
        MANDELBROT = !MANDELBROT;
        if (MANDELBROT) {
            panelX.addButton.shape.setFillColor(sf::Color(128, 128, 128));
            panelX.minButton.shape.setFillColor(sf::Color(128, 128, 128));
            panelY.addButton.shape.setFillColor(sf::Color(128, 128, 128));
            panelY.minButton.shape.setFillColor(sf::Color(128, 128, 128));
        }
        else {
            panelX.minButton.shape.setFillColor(sf::Color::White);
            panelY.addButton.shape.setFillColor(sf::Color::White);
            panelX.addButton.shape.setFillColor(sf::Color::White);
            panelY.minButton.shape.setFillColor(sf::Color::White);
        }
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mandelbrotButton.isClicked(sf::Mouse::getPosition(window))) {
        mandelbrotButton.shape.setFillColor(sf::Color::White);
    }
}

int main() {
    bool MANDELBROT = false;

    int width = WIDTH;
    int height = HEIGHT;

    dim3 block(16, 16);
    dim3 grid((width + block.x - 1) / block.x, (height + block.y - 1) / block.y);
 
    sf::Image icon;
    icon.loadFromFile("window_icon.jpg");
    // Set up the window
    sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Fractal");
    window.setFramerateLimit(30);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Set up the image
    sf::Image image;
    image.create(width, height, sf::Color::Black);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Set up the CUDA device and arrays
    int* d_pixels;
    cudaMalloc((void**)&d_pixels, width * height * sizeof(int));

    double x_min = -2.0f;
    double x_max = 1.0f;
    double y_min = -1.0f;
    double y_max = 1.0f;

    // Set up the zoom factor
    double zoom_factor = 1.0f;

    // Set up the mouse positions
    int mouse_x = 0;
    int mouse_y = 0;
    sf::Clock clock;
    bool z = true;
    bool hideButtons = false;

    PanelButtons panelX(sf::Vector2f(20, 20), sf::Vector2f(50, 20), 10, std::vector<sf::Vector2f>{sf::Vector2f(25, 8), sf::Vector2f(51, 10)}, "CX");
    PanelButtons panelY(sf::Vector2f(20, 60), sf::Vector2f(50, 60), 10, std::vector<sf::Vector2f>{sf::Vector2f(25, 48), sf::Vector2f(51, 50)}, "CY");
    PanelButtons panelStep(sf::Vector2f(20, 870), sf::Vector2f(50, 870), 10, std::vector<sf::Vector2f>{sf::Vector2f(25, 858), sf::Vector2f(51, 860)}, "Step : 0.010");
    Button mandelbrotButton(sf::Vector2f(20, 100), 10, "Mandelbrot", sf::Vector2f(50, 100));
    double CX = -0.2f;
    double CY = 0.7f;
    // Run the main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switchMandelbrot(window, MANDELBROT, panelX, panelY, mandelbrotButton);
            updateConstants(window, MANDELBROT, panelX, panelY, CX, CY, panelStep.step);
            updateStep(window, panelStep);

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
                hideButtons = !hideButtons;
            }

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                // Calculate the new zoom level
                if (z) {
                    z = false;
                    zoom_factor *= 1.0f + event.mouseWheelScroll.delta / 10.0f;
                }
                else {
                    z = true;
                    zoom_factor = 1.0;
                }

                double x_center = x_min + (x_max - x_min) * mouse_x / width;
                double y_center = y_min + (y_max - y_min) * mouse_y / height;
                x_min = x_center - (x_center - x_min) * zoom_factor;
                x_max = x_center + (x_max - x_center) * zoom_factor;
                y_min = y_center - (y_center - y_min) * zoom_factor;
                y_max = y_center + (y_max - y_center) * zoom_factor;
            }
            if (event.type == sf::Event::MouseMoved) {
                mouse_x = event.mouseMove.x;
                mouse_y = event.mouseMove.y;
            }
        }

        // Launch the kernel
        fractal_kernel << <grid, block >> > (d_pixels, width, height, x_min, x_max, y_min, y_max, CX, CY, MANDELBROT);
        // Copy the results back to the host
        int *pixels = new int[width * height];
        cudaMemcpy(pixels, d_pixels, width * height * sizeof(int), cudaMemcpyDeviceToHost);

        if (clock.getElapsedTime().asMilliseconds() > 50) {
            render_color(&image, pixels, width, height);
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            // Draw the image
            window.clear();
            window.draw(sprite);
            if (!hideButtons) {
                panelX.draw(window);
                panelY.draw(window);
                panelStep.draw(window);
                mandelbrotButton.draw(window);
                print_equation(CX, CY, MANDELBROT, window);
            }
            window.display();
            clock.restart();
        }
        // Clean up
        delete[] pixels;
    }

    cudaFree(d_pixels);

    return 0;
}