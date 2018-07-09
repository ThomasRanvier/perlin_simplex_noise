#include <SFML/Graphics.hpp>
#include "headers/Perlin.h"
#include "headers/Simplex.h"

const int WIDTH = 1300;
const int HEIGHT = 700;

float map[WIDTH][HEIGHT];

float sumOctave(int nbIte, float x, float y, float persistence, float freq, int low, int high) {
    float maxAmp = 0;
    float amp = 1;
    float noise = 0;

    Simplex simplex;

    for(int i = 0; i < nbIte; ++i) {
        noise += simplex.noise(x * freq, y * freq) * amp;
        maxAmp += amp;
        amp *= persistence;
        freq *= 2;
    }

    noise /= maxAmp;

    return noise * (high - low) / 2 + (high + low) / 2;
}

void simplex3dWoodLike(sf::RenderWindow * window, float scale) {
    float z(0);
    Simplex simplex;

    while ((*window).isOpen())
    {
        sf::Event event;
        while ((*window).pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                (*window).close();
            }
        }
        (*window).clear();

        for (int x(0); x < WIDTH; x++) {
            for (int y(0); y < HEIGHT; y++) {
                map[x][y] = simplex.noise(x * scale, y * scale, z);

                sf::RectangleShape cell(sf::Vector2f(1, 1));
                cell.setPosition(x, y);
                float value = ((map[x][y] + 1.0) * .5) * 20;
                value -= int(value);
                value *= 255;
                cell.setFillColor(sf::Color(value, value, value));
                (*window).draw(cell);
            }
        }

        z += 2 * scale;

        (*window).display();
    }
}

void simplex3d(sf::RenderWindow * window, float scale) {
    float z(0);
    Simplex simplex;

    while ((*window).isOpen())
    {
        sf::Event event;
        while ((*window).pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                (*window).close();
            }
        }
        (*window).clear();

        for (int x(0); x < WIDTH; x++) {
            for (int y(0); y < HEIGHT; y++) {
                map[x][y] = simplex.noise(x * scale, y * scale, z);

                sf::RectangleShape cell(sf::Vector2f(1, 1));
                cell.setPosition(x, y);
                float value = (map[x][y] + 1.0) * .5;
                value -= int(value);
                value *= 255;
                cell.setFillColor(sf::Color(value, value, value));
                (*window).draw(cell);
            }
        }

        z += 5 * scale;

        (*window).display();
    }
}

void fireLike(sf::RenderWindow * window, float scale) {
    for (int x(0); x < WIDTH; x++) {
        for (int y(0); y < HEIGHT; y++) {
            map[x][y] = sumOctave(16, x, y, .5, scale, 0, 255);

            sf::RectangleShape cell(sf::Vector2f(1, 1));
            cell.setPosition(x, y);
            cell.setFillColor(sf::Color(map[x][y], map[x][y], map[x][y]));
            (*window).draw(cell);
        }
    }
    while ((*window).isOpen()) {
        sf::Event event;
        while ((*window).pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                (*window).close();
            }
        }
        (*window).display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "sfml_noise");

    Simplex simplex;
    float scale = 0.007;
    float blurr = 1;

    fireLike(&window, scale);

    //simplex3d(&window, scale);

    //simplex3dWoodLike(&window, scale);

    /**
    for (int x(0); x < WIDTH; x++) {
        for (int y(0); y < HEIGHT; y++) {
            map[x][y] = simplex.noise(x * scale, y * scale);

            sf::RectangleShape cell(sf::Vector2f(1, 1));
            cell.setPosition(x, y);
            float value = (map[x][y] + 1.0) * .5 * blurr;
            value -= int(value);
            value *= 255;

            cell.setFillColor(sf::Color(value, value, value));

            window.draw(cell);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        //window.clear();

        window.display();
    }
    **/
    return 0;
}