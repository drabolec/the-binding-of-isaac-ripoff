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
    sf::Font getFont();
    

};
Game::Game(){
    //setting font
    this->font = new sf::Font("./Fonts/Roboto-Regular.ttf");
    //seting game window parameters
    this->videoMode.size = {1600, 900};
    this->window = new sf::RenderWindow(this->videoMode, "The binding of isaac ultimate ripoff");

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


    this->loot.emplace_back(new rbAmmo);
    this->loot.at(0)->setPosition({800.f, 400.f});

    this->boosts.emplace_back(new SmallHealth);
    this->boosts.at(0)->setPosition({800.f, 800.f});


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
    this->currentWeapon->setPlayerPos(this->player.getPosition());
    this->currentWeapon->update();
    this->currentWeapon->updatePos(this->player.getPosition());
    this->playerBullets = this->currentWeapon->getCurrentPlayerBullets();

    //updating player bullet position
    auto i = playerBullets.begin();
    for(Bullet* bullet: this->playerBullets){
        //updating position
        bullet->update();
        //checking if bullet should be deleted for now only by its range
        if(bullet->isVisible==false){
            playerBullets.erase(i);
        }
        i++;
    }

    //updating loot for testing
    //in the future wepons list will be taken from room object but the rest of the logic stays the same
    int x = 0;
    for(Item* weapon:weapons){
        //checking for colision and if player pressed E 
        if(isColision(weapon, &player) && player.pressedE==true){
            //giving a player weapon on the ground and droping current weapon 
            Item* droped = currentWeapon;
            droped->updatePos(this->player.getPosition());
            this->weapons.at(x) = droped;
            this->currentWeapon = weapon;
            //setting current bullets for new weapon
            this->currentWeapon->setCurrentBullet(this->currentBullet);
        }
        x++;
    }
    auto y = boosts.begin();
    for(Boost* boost:boosts){
        //checking for colision and if player pressed E 
        if(isColision(boost, &player)){
            //erasing boost and acordinglyt to its type changing player propertys
            this->boosts.erase(y);
            if(dynamic_cast<SmallHealth*>(boost) != NULL){
                this->player.changeHp(boost->value);  
            }
            
        }
        y++;
    }
    auto a = loot.begin();
    for(Ammo* ammo:loot){
        if(isColision(ammo, &player)&&player.pressedE==true){
            //change boolets acordingly
            Bullet* temp = this->currentBullet;
            Ammo* droped;
            if(dynamic_cast<RoundBullet*>(temp)!=NULL){
                droped = new rbAmmo;
                droped->setPosition(this->player.getPosition());
            }
            currentBullet = ammo->getType();
            loot.erase(a);
            loot.emplace_back(droped);
            
        }
        a++;
    }
    
    
}
void Game::render(){
    this->window->clear();
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
    this->currentWeapon->render(this->window);

    for(Boost* boost:boosts){
        boost->render(this->window);
    }
    //rendering player bullets
    for(Bullet* bullet: this->playerBullets){
        bullet->render(this->window);
    }

    //rendering player
    this->player.render(this->window);

    //rendering current weapon
    this->currentWeapon->render(this->window);


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