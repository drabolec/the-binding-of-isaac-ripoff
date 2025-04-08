#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

class Game{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
public:
    Game();
    virtual ~Game();
    bool running();
    void events();
    void update();
};
Game::Game(){
    this->videoMode.size = {1000, 1000};
    this->window = new sf::RenderWindow(this->videoMode, "The binding of isaac ultimate ripoff");
}
Game::~Game(){
    this->window->close();
}

bool Game::running(){
    return this->window->isOpen();
}
void Game::events(){
    while (const std::optional event = this->window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                this->window->close();
        }
}
void Game::update(){
    this->events();
    this->window->clear();
    //magic happend right here

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    this->window->draw(shape);
    this->window->display();
}


#endif