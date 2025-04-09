#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Player.h"
#include "Bullet.h"
#include "RoundBullet.h"
#include "Item.h"
#include "FirstWeapon.h"

class Game{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    std::optional<sf::Event> event;
    Player player;
    Item* currentWeapon;
    Bullet* currentBullet;
    std::vector<Bullet*> playerBullets;
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
    this->currentWeapon = new FirstWeapon;
    this->currentBullet = new RoundBullet;
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
    this->player.update();
    this->currentWeapon->setCurrentBullet(this->currentBullet);
    this->currentWeapon->setCurrentPlayerBullets(this->playerBullets);
    this->currentWeapon->setPlayerPos(this->player.getPosition());
    this->currentWeapon->update();
    this->currentWeapon->updatePos(this->player.getPosition());
    this->playerBullets = this->currentWeapon->getCurrentPlayerBullets();
    auto i = playerBullets.begin();
    for(Bullet* bullet: this->playerBullets){
        bullet->update();
        if(bullet->isVisible==false){
            playerBullets.erase(i);
        }
        i++;
    }
    
}
void Game::render(){
    this->window->clear();
    //magic happend right here

    this->player.render(this->window);
    this->currentWeapon->render(this->window);
    for(Bullet* bullet: this->playerBullets){
        bullet->render(this->window);
    }

    this->window->display();
}



#endif