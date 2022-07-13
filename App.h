#ifndef APP_H
#define APP_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"

class App {
public:
    App();
    ~App();

    void update();
    void render();
    bool running();
    void pollEvents();

private:
    sf::RenderWindow* window;
    sf::Event ev;

    void initVariables();
    void initWindow();
};

#endif
