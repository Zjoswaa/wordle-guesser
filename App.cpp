#include "App.h"

App::App() {
    this->initVariables();
    this->initWindow();
}

App::~App() {
    delete this->window;
}

void App::update() {
    this->pollEvents();
}

void App::render() {
    this->window->clear();
    this->window->display();
}

bool App::running() {
    return this->window->isOpen();
}

void App::pollEvents() {
    while (this->window->pollEvent(ev)) {
        switch (ev.type) {
            // X Button
            case sf::Event::Closed:
                this->window->close();
                break;

            // Mouse Pressed
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    std::cout << "Left click" << std::endl;
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    std::cout << "Right click" << std::endl;
                }
                break;

            // Key Pressed
            case sf::Event::KeyPressed:
                switch (ev.key.code) {
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;

                    default:
                        break;
                }
            default:
                break;
        }
    }
}

void App::initVariables() {
    this->window = nullptr;
}

void App::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Title", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(fps);
}
