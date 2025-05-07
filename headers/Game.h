#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "Player.h"

#include "Bullet.h"
#include "RoundBullet.h"
#include "FastBullet.h"

#include "Item.h"
#include "FirstWeapon.h"
#include "Room.h"
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
    std::unique_ptr<Item> currentWeapon;
    std::unique_ptr<Bullet> currentBullet;
    std::vector<Bullet*> playerBullets;
    std::vector<std::unique_ptr<Room>> rooms;
    //Game font for now roboto
    sf::Font* font;
    //hp text
    sf::Text *hpText;
    //sounds
    sf::SoundBuffer *buffer;
    sf::Sound *pickupWeapon;

    bool isClosed = false;
    int active_room=0;
    //menu stuf
    bool ismenuOpen = true;
    int selected = 1;
    sf::Clock clock;
    sf::Text* menuT;
    sf::Text* play;
    sf::Text* option1;
    sf::Text* option2; 
    sf::Text* quit; 
    sf::RectangleShape fog;
    //temporary for testing

public:
    Game();
    virtual ~Game();
    bool running();
    bool menuOpen();
    void events();
    void update();
    void render();
    bool isColision(Entity* e1, Entity* e2);
    void interf();
    void updatePlayerBullets();
    void updateLoot(Room* room);
    void updateBoosts(Room* room);
    void updateWeapons(Room* room);
    void updateWalls(Room* room);
    void pause();
    void renderEntitys();
    void menu();
    

};
Game::Game(){
    //setting font
    this->font = new sf::Font("./Fonts/Roboto-Regular.ttf");
    //setting text font
    this->hpText = new sf::Text(*font); 
    this->hpText->setPosition({20.f, 20.f});
    this->hpText->setCharacterSize(20.f);
    //seting game window parameters
    this->videoMode.size = {800, 450};
    //makes window proportional
    this->window = new sf::RenderWindow(this->videoMode, "The binding of isaac ultimate ripoff");
    sf::View view(sf::FloatRect({0.f, 0.f}, {1600.f, 900.f}));
    this->window->setView(view);

    //seting defaul player parameter
    this->player.setPosition({100.f, 100.f});
    this->player.setFont(this->font);
    this->player.initHp();

    //seting frame limit
    this->window->setFramerateLimit(60);
    
    //seting default bullets
    this->currentBullet = std::make_unique<RoundBullet>();

    //setting defaul weapon
    this->currentWeapon = std::make_unique<FirstWeapon>();
    this->currentWeapon->setCurrentBullet(this->currentBullet.get());
    //sound
    this->buffer = new sf::SoundBuffer("./Sound/pickupweapon.wav");
    this->pickupWeapon = new sf::Sound(*(this->buffer));
    this->pickupWeapon->setVolume(2.f);


    //menu stuff
    this->menuT = new sf::Text(*(this->font));
    this->menuT->setPosition({50.f, 60.f});
    this->menuT->setCharacterSize(60.f);
    this->menuT->setString("Menu");

    this->play = new sf::Text(*(this->font));
    this->play->setPosition({50.f, 200.f});
    this->play->setCharacterSize(20.f);
    this->play->setString("Play");

    this->option1 = new sf::Text(*(this->font));
    this->option1->setPosition({50.f, 250.f});
    this->option1->setCharacterSize(20.f);
    this->option1->setString("Option1");

    this->option2 = new sf::Text(*(this->font));
    this->option2->setPosition({50.f, 300.f});
    this->option2->setCharacterSize(20.f);
    this->option2->setString("Option2");

    this->quit = new sf::Text(*(this->font));
    this->quit->setPosition({50.f, 350.f});
    this->quit->setCharacterSize(20.f);
    this->quit->setString("Quit");

    fog.setFillColor(sf::Color(50, 50, 50, 30));
    fog.setSize({100.f, 35.f});
    
    //temporary for testing
    this->rooms.emplace_back(std::make_unique<Room>(1)); //room making

}
Game::~Game(){
    delete this->window;
}

bool Game::running(){
    return this->window->isOpen();
}
void Game::events(){
    if(isClosed){
        this->window->close();
    }
    while (this->event = this->window->pollEvent())
        {
            if (this->event->is<sf::Event::Closed>()){
                this->window->close();
            }else if(const auto* keyPressed = this->event->getIf<sf::Event::KeyPressed>()){
                //turns of on escape change later
                if(keyPressed->scancode == sf::Keyboard::Scan::Escape){
                    pause();
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
    

    updatePlayerBullets();

    updateWeapons(this->rooms[active_room].get());

    updateBoosts(this->rooms[active_room].get());
    
    updateLoot(this->rooms[active_room].get());

    updateWalls(this->rooms[active_room].get());
    
    
}
void Game::render(){
    this->window->clear(sf::Color(120, 120, 120));
   
    this->renderEntitys();

    this->window->display();

}
void Game::renderEntitys(){
     //magic happens right here

    //rendering loot for testing
    //weapons vector should be inside room object


    for (const auto& roomPtr : rooms) {
        Room* room = roomPtr.get();
        if (room->getIsActive()) {
            room->render(this->window);
        }
    }

    //rendering player bullets
    for(Bullet* bullet: this->playerBullets){
        bullet->render(this->window);
    }

    //rendering player
    this->player.render(this->window);

    //rendering and updating interface
    interf();
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


void Game::updateBoosts(Room* room) {
    auto& boosts = room->getBoosts();
    for (auto i = boosts.begin(); i != boosts.end(); ) {
        // Dereference unique_ptr to raw pointer for isColision
        if (isColision(i->get(), &player)) {
            // Handle boost effect before erasing
            if (auto smallHealth = dynamic_cast<SmallHealth*>(i->get())) {
                this->player.changeHp(smallHealth->value);
            }
            // Erase and advance iterator safely
            i = boosts.erase(i);
        } else {
            ++i;
        }
    }
}

void Game::updateWalls(Room* room){
    auto& walls = room->getWalls();
    for(auto i = walls.begin(); i != walls.end();){
        if(isColision(i->get(), &player)){
            if(this->player.getState()==2){
                player.setHitWallWE(1);
            }
            if(this->player.getState()==3){
                player.setHitWallWE(2);
            }
            if(this->player.getState()==4){
                player.setHitWallNS(1);
            }
            if(this->player.getState()==5){
                player.setHitWallNS(2);
            }
        }
    }
}

void Game::updateWeapons(Room* room){
     //updating loot for testing
    //in the future wepons list will be taken from room object but the rest of the logic stays the same
    auto& weapons = room->getWeapons();
    for(auto i = weapons.begin(); i != weapons.end();){
        //checking for colision and if player pressed E 
        if(isColision(i->get(), &player) && player.pressedE==true){
            //giving a player weapon on the ground and droping current weapon 
            std::unique_ptr<Item> droped = std::move(currentWeapon);
            droped->updatePos({this->player.getPosition().x+20.f, this->player.getPosition().y+80.f});
            *i = std::move(droped);
            //setting current bullets for new weapon
            this->currentWeapon = std::move(*i);
            this->currentWeapon->setCurrentBullet(this->currentBullet.get());
            this->pickupWeapon->play();
            break;
        }
    }
}
void Game::updatePlayerBullets(){
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
}
void Game::updateLoot(Room* room){
    auto& loot = room->getLoot();
    for(auto i = loot.begin(); i != loot.end();){
        std::cout << "Checking loot item: " << i->get() << std::endl;
        if(isColision((i->get()), &player)&&player.pressedE==true){
            //change boolets acordingly
            Bullet* temp = this->currentBullet.get();
            Ammo* droped;
            if(dynamic_cast<RoundBullet*>(temp)!=NULL){
                droped = new rbAmmo;
                droped->setPosition({this->player.getPosition().x+45.f, this->player.getPosition().y+45.f});
            }else if(dynamic_cast<FastBullet*>(temp)!=NULL){
                droped = new fastAmmo;
                droped->setPosition({this->player.getPosition().x+45.f, this->player.getPosition().y+45.f});
            }
            std::cout<<"working\n";
            currentBullet = std::unique_ptr<Bullet>(dynamic_cast<Bullet*>(i->release()));
            std::cout<<"working\n";
            this->currentWeapon->setCurrentBullet(this->currentBullet.get());
            std::cout<<"working\n";
            loot.erase(i);
            std::cout<<"working\n";
            loot.emplace_back(droped);
            std::cout<<"working\n";
            break;
        }
            i++;
    }   
}
void Game::pause(){
    sf::Text pause(*(this->font));
    pause.setString("PAUSE");
    pause.setCharacterSize(60.f);
    pause.setPosition({700, 100});
    pause.setFillColor(sf::Color::Black);

    sf::RectangleShape fog;
    fog.setFillColor(sf::Color(0, 0, 0, 50));
    fog.setSize({1600, 900});
    
    
    bool p = true;
    while(p && !isClosed){
        while (this->event = this->window->pollEvent())
        {
            if (this->event->is<sf::Event::Closed>()){
                this->isClosed = true;
                
            }else if(const auto* keyPressed = this->event->getIf<sf::Event::KeyPressed>()){
                //turns of on escape change later
                if(keyPressed->scancode == sf::Keyboard::Scan::Escape){
                    p = false;
                }
                
            }
                
            
        }
        
        this->window->clear(sf::Color(120, 120, 120));
        this->renderEntitys();

        this->window->draw(fog);
        this->window->draw(pause);
        
        
        this->window->display();
    }
}
bool Game::menuOpen(){
    return this->ismenuOpen;
}
void Game::menu(){

    while (this->event = this->window->pollEvent())
        {
            if (this->event->is<sf::Event::Closed>()){
                this->ismenuOpen = false;
                this->isClosed = true;
            } 
        }
    this->window->clear(sf::Color(150, 150, 150));
    
    
    if(this->clock.getElapsedTime().asSeconds() > 0.1f){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            if(this->selected>1){
                this->selected --;
            }
            this->clock.restart();
            
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            if(this->selected < 4){
                this->selected ++;
            }
            this->clock.restart();
            
        }
            
    }
     

    if(this->selected == 1){
        fog.setPosition({play->getPosition().x-20.f, play->getPosition().y-5.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            this->ismenuOpen = false; 
        }  
    }else if(this->selected == 2){
        fog.setPosition({option1->getPosition().x-20.f, option1->getPosition().y-5.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            //magic
        }  
    }else if(this->selected == 3){
        fog.setPosition({option2->getPosition().x-20.f, option2->getPosition().y-5.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            //magic
        }  
    }
    else if(this->selected == 4){
        fog.setPosition({quit->getPosition().x-20.f, quit->getPosition().y-5.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            this->ismenuOpen = false;
            this->isClosed = true;
        }  
    }

    //drawing
    this->window->draw(*menuT);
    this->window->draw(fog);
    this->window->draw(*play);
    this->window->draw(*option1);
    this->window->draw(*option2);
    this->window->draw(*quit);

    this->window->display();
}

#endif