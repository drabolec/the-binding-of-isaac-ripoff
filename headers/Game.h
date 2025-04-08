#ifndef GAME_H
#define GAME_H


#include "Player.h"

class Game{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    std::optional<sf::Event> event;
    Player player;
public:
    Game();
    virtual ~Game();
    bool running();
    void events();
    void update();
    void render();
};
Game::Game(){
    this->videoMode.size = {1000, 1000};
    this->window = new sf::RenderWindow(this->videoMode, "The binding of isaac ultimate ripoff");
    sf::Vector2f pos(100.f, 100.f);
    this->player.setPosition(pos);
    this->window->setFramerateLimit(60);
}
Game::~Game(){
    delete this->window;
}

bool Game::running(){
    return this->window->isOpen();
}
void Game::events(){
    while (this->event = this->window->pollEvent())
        {
            if (this->event->is<sf::Event::Closed>()){
                this->window->close();
            }else if(const auto* keyPressed = this->event->getIf<sf::Event::KeyPressed>()){
                //turns of on escape change later
                if(keyPressed->scancode == sf::Keyboard::Scan::Escape){
                    this->window->close();
                }
                
            }
                
            
        }
}
void Game::update(){
    this->events();
    this->player.update(this->window);
    
}
void Game::render(){
    this->window->clear();
    //magic happend right here

    this->player.render(this->window);

    this->window->display();
}


#endif