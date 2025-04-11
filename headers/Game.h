#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Player.h"
#include "Bullet.h"
#include "RoundBullet.h"
#include "Item.h"
#include "FirstWeapon.h"
#include "rbAmmo.h"
#include "Ammo.h"

class Game{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    std::optional<sf::Event> event;
    Player player;
    Item* currentWeapon;
    Bullet* currentBullet;
    std::vector<Bullet*> playerBullets;
    //temporary for testing
    std::vector<Item*> weapons;
    std::vector<Ammo*> loot;
public:
    Game();
    virtual ~Game();
    bool running();
    void events();
    void update();
    void render();
    bool isColision(Entity* e1, Entity* e2);
    

};
Game::Game(){
    this->videoMode.size = {1600, 900};
    this->window = new sf::RenderWindow(this->videoMode, "The binding of isaac ultimate ripoff");
    sf::Vector2f pos(100.f, 100.f);
    this->player.setPosition(pos);
    this->window->setFramerateLimit(60);
    this->currentWeapon = new FirstWeapon;
    this->currentBullet = new RoundBullet;

    //temporary for testing
    this->weapons.emplace_back(new FirstWeapon);
    this->weapons.at(0)->updatePos({500.f, 500.f});

    this->loot.emplace_back(new rbAmmo);
    this->loot.at(0)->setPosition({800.f, 400.f});

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

    //player weapon and shooting
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

    //updating loot for testing
    int x = 0;
    for(Item* weapon:weapons){
        if(isColision(weapon, &player) && player.changeWeapon==true){
            
            Item* droped = currentWeapon;
            droped->updatePos(this->player.getPosition());
            this->weapons.at(x) = droped;
            this->currentWeapon = weapon;
        }
        x++;
    }
    
    
}
void Game::render(){
    this->window->clear();
    //magic happend right here

    //rendering loot for testing
    for(Item* weapon:weapons){
        weapon->render(this->window);
    }
    for(Ammo* ammo:loot){
        ammo->render(this->window);
    }

    this->player.render(this->window);
    this->currentWeapon->render(this->window);
    for(Bullet* bullet: this->playerBullets){
        bullet->render(this->window);
    }
    

    this->window->display();
}
//collision detection
bool Game::isColision(Entity* e1, Entity* e2){
    if(e1->hitbox.getGlobalBounds().findIntersection(e2->hitbox.getGlobalBounds())){
        return true;
    }
    return false;
}



#endif