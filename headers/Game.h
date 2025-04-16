#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Player.h"

#include "Bullet.h"
#include "RoundBullet.h"
#include "FastBullet.h"

#include "Item.h"
#include "FirstWeapon.h"
#include "ThreeBulletWeapon.h"
#include "MiniGunWeapon.h"

#include "Ammo.h"
#include "rbAmmo.h"
#include "fastAmmo.h"

#include "Boost.h"
#include "SmallHealth.h"

class Game{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    //event handling variable
    std::optional<sf::Event> event;
    Player player;
    Item* currentWeapon;
    Bullet* currentBullet;
    std::vector<Bullet*> playerBullets;

    //Game font for now roboto
    sf::Font* font;
    //hp text
    sf::Text *hpText;

    //temporary for testing
    std::vector<Item*> weapons;

    std::vector<Ammo*> loot;

    std::vector<Boost*> boosts;

public:
    Game();
    virtual ~Game();
    bool running();
    void events();
    void update();
    void render();
    bool isColision(Entity* e1, Entity* e2);
    void interf();
    

};
Game::Game(){
    //setting font
    this->font = new sf::Font("./Fonts/Roboto-Regular.ttf");
    //setting text font
    this->hpText = new sf::Text(*font); 
    this->hpText->setPosition({20.f, 20.f});
    this->hpText->setCharacterSize(20.f);
    //seting game window parameters
    this->videoMode.size = {1600, 900};
    //makes window unresizable and sets its parameters
    this->window = new sf::RenderWindow(this->videoMode, "The binding of isaac ultimate ripoff", sf::Style::Close);

    //seting defaul player parameter
    this->player.setPosition({100.f, 100.f});
    this->player.setFont(this->font);
    this->player.initHp();

    //seting frame limit
    this->window->setFramerateLimit(60);
    
    //seting default bullets
    this->currentBullet = new RoundBullet;

    //setting defaul weapon
    this->currentWeapon = new FirstWeapon;
    this->currentWeapon->setCurrentBullet(this->currentBullet);


    
    //temporary for testing
    this->weapons.emplace_back(new FirstWeapon);
    this->weapons.at(0)->updatePos({500.f, 500.f});
    this->weapons.emplace_back(new ThreeBulletWeapon);
    this->weapons.at(1)->updatePos({500.f, 600.f});
    this->weapons.emplace_back(new MiniGunWeapon);
    this->weapons.at(2)->updatePos({500.f, 700.f});


    this->loot.emplace_back(new rbAmmo);
    this->loot.at(0)->setPosition({800.f, 300.f});
    this->loot.emplace_back(new fastAmmo);
    this->loot.at(1)->setPosition({800.f, 400.f});

    this->boosts.emplace_back(new SmallHealth);
    this->boosts.at(0)->setPosition({900.f, 400.f});


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
    this->currentWeapon->setCurrentPlayerBullets(this->playerBullets);
    this->currentWeapon->setPlayerPos({this->player.getPosition().x+45.f,this->player.getPosition().y+45.f});
    this->currentWeapon->update();
    this->playerBullets = this->currentWeapon->getCurrentPlayerBullets();
    

    //updating player bullet position
    for(auto i = playerBullets.begin(); i != playerBullets.end();){
        //updating position
        (*i)->update();
        //checking if bullet should be deleted for now only by its range
        if((*i)->isVisible==false){
            playerBullets.erase(i);
            
        }else{
            i++;
        }
        
    }

    //updating loot for testing
    //in the future wepons list will be taken from room object but the rest of the logic stays the same
    int x = 0;
    for(Item* weapon:weapons){
        //checking for colision and if player pressed E 
        if(isColision(weapon, &player) && player.pressedE==true){
            //giving a player weapon on the ground and droping current weapon 
            Item* droped = currentWeapon;
            droped->updatePos({this->player.getPosition().x+20.f, this->player.getPosition().y+80.f});
            this->weapons.at(x) = droped;
            this->currentWeapon = weapon;
            //setting current bullets for new weapon
            this->currentWeapon->setCurrentBullet(this->currentBullet);
            break;
        }
        x++;
    }

    for(auto i = boosts.begin(); i != boosts.end();){
        //checking for colision and if player pressed E 
        if(isColision((*i), &player)){
            //erasing boost and acordinglyt to its type changing player propertys
            this->boosts.erase(i);
            if(dynamic_cast<SmallHealth*>((*i)) != NULL){
                this->player.changeHp((*i)->value);  
            }
            
        }
        else{
            i++;
        }
    }
    for(auto i = loot.begin(); i != loot.end();){
        if(isColision((*i), &player)&&player.pressedE==true){
            //change boolets acordingly
            Bullet* temp = this->currentBullet;
            Ammo* droped;
            if(dynamic_cast<RoundBullet*>(temp)!=NULL){
                droped = new rbAmmo;
                droped->setPosition({this->player.getPosition().x+45.f, this->player.getPosition().y+45.f});
            }else if(dynamic_cast<FastBullet*>(temp)!=NULL){
                droped = new fastAmmo;
                droped->setPosition({this->player.getPosition().x+45.f, this->player.getPosition().y+45.f});
            }
            currentBullet = (*i)->getType();
            this->currentWeapon->setCurrentBullet(this->currentBullet);
            loot.erase(i);
            loot.emplace_back(droped);
            break;
            
        }
        
            i++;
        
    }
    
    
}
void Game::render(){
    this->window->clear(sf::Color(120, 120, 120));
    //magic happens right here

    //rendering loot for testing
    //weapons vector should be inside room object
    for(Item* weapon:weapons){
        weapon->render(this->window);
    }

    for(Ammo* ammo:loot){
        ammo->render(this->window);
    }

    this->player.render(this->window);
    

    for(Boost* boost:boosts){
        boost->render(this->window);
    }
    //rendering player bullets
    for(Bullet* bullet: this->playerBullets){
        bullet->render(this->window);
    }

    //rendering player
    this->player.render(this->window);

    //rendering and updating interface
    interf();

    this->window->display();

}
//collision detection
bool Game::isColision(Entity* e1, Entity* e2){
    if(e1->hitbox.getGlobalBounds().findIntersection(e2->hitbox.getGlobalBounds())){
        return true;
    }
    return false;
}
void Game::interf(){
    this->hpText->setString(std::to_string(this->player.getHp()) + " hp");
    sf::RectangleShape temp = this->currentWeapon->shape;
    temp.setPosition({100.f, 20.f});
    temp.setScale({2.f, 2.f});
    sf::RectangleShape bullet = this->currentBullet->shape;
    bullet.setPosition({300.f, 20.f});
    bullet.setScale({1.5f, 1.5f});
    this->window->draw(bullet);
    this->window->draw(temp);
    this->window->draw(*(this->hpText));
}



#endif