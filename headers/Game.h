#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>


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
    Item* currentWeapon;
    Bullet* currentBullet;
    std::vector<Bullet*> playerBullets;
    std::vector<Bullet*> enemyBullets;
    std::vector<Room*> rooms;
    std::vector<Room*> initrooms;
    
    
    
    //Game font for now roboto
    sf::Font* font;
    //hp text
    sf::Text *hpText;

    float masterVolume;
    //sounds
    sf::SoundBuffer *buffer;
    sf::Sound *pickupWeapon;
    sf::SoundBuffer *menuBuffer;
    sf::SoundBuffer *gameBuffer;
    sf::SoundBuffer *gameOverBuffer; 
    sf::SoundBuffer *hitBuffer;
    sf::Sound *soundtrack;
    sf::Sound *gameSound;
    sf::Sound *gameOverSound;
    sf::Sound *hitSound;

    bool isClosed = false;
    int x=0;
    int y=0;
    int active_room=12;
    //menu stuf
    bool ismenuOpen;
    int selected = 1;
    sf::Clock clock;
    sf::Text* menuT;
    sf::Text* play;
    sf::Text* option1;
    sf::Text* option2; 
    sf::Text* quit; 
    sf::Text* info;
    sf::Text* nickname;
    sf::RectangleShape fog;
    sf::RectangleShape background;
    sf::RectangleShape fade;
    bool dark;
    bool light;
    sf::Clock fadeClock;
    int fadeOpacity;

    bool dootTP=true;
    int currentMenu = 0;
    std::string currentScreen;
    std::string tempScreen;
    int scoreFrames;
    int scoreSeconds;
    sf::Text* timer;
    bool isEnd;
    bool isLose;
    std::string nickString;
    std::string highScore;
    sf::Text* highScoreText;
    sf::Text* highScoreTime;
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
    int getRandomInt(int min,int max);
    void updatePlayerBullets();
    void updateEnemyBullets();
    void updateLoot(Room* room);
    void updateBoosts(Room* room);
    void updateWeapons(Room* room);
    void updateWalls(Room* room);
    void updateDoors(Room* room);
    void updateEnemies(Room* room);
    void renderEntitys();
    void menu();
    void mainMenu();
    void settingsMenu();
    void infoMenu();
    void init();
    void end();
    bool getEnd();
    template <typename T>
    void writeToFile(T input);
    void breakLine();
    void comma();
    bool getLose();
    void lose();
    void restart();
    void readFromFile();
    

};
void Game::restart(){
    this->menuT->setString("The binding of not isaac");
    this->dark = false;
    this->light = false;
    this->fadeClock.restart();
    this->fadeOpacity = 0;
    for(auto el:this->playerBullets){
        delete el;
    }
    this->playerBullets.clear();
    for(auto el:this->enemyBullets){
        delete el;
    }
    this->enemyBullets.clear();

    
    this->player.setHp(100);
    this->gameOverSound->stop();
    this->soundtrack->stop();
    this->gameSound->stop();
    delete this->soundtrack;
    this->soundtrack = new sf::Sound(*(this->menuBuffer));
    this->soundtrack->setVolume(this->masterVolume);
    this->soundtrack->play();
    this->ismenuOpen = true;
    this->isLose = false;
    this->isEnd = false;
    this->scoreFrames = 0;
    this->scoreSeconds = 0;
    //setting text font
    this->hpText = new sf::Text(*font); 
    this->hpText->setPosition({20.f, 20.f});
    this->hpText->setCharacterSize(20.f);
    //seting game window parameters
    

    //seting defaul player parameter
    this->player.setPosition({100.f, 100.f});
    this->player.setFont(this->font);
    this->player.initHp();


    
    //seting default bullets
    delete this->currentBullet;
    this->currentBullet = new RoundBullet();

    //setting defaul weapon
    delete this->currentWeapon;
    this->currentWeapon = new FirstWeapon();
    this->currentWeapon->setCurrentBullet(this->currentBullet);



    
    this->timer->setPosition({1500.f, 20.f});
    this->timer->setCharacterSize(60.f);
    this->timer->setString(std::to_string(this->scoreSeconds));

    fog.setFillColor(sf::Color(0, 0, 0, 230));
    fog.setSize({100.f, 35.f});

    this->background.setFillColor(sf::Color(0, 0, 0, 200));
    this->background.setSize({1600.f, 900.f});
    
    //temporary for testing
    for(auto el:this->rooms){
        delete el;
    }


    this->rooms.clear();


    //dogadac ile jakich pokoi ma byc w tych 24

    this->rooms.emplace_back(new Room(1,0,0,0,nullptr)); //0   room making
    this->rooms.emplace_back(new Room(1,0,1,1,nullptr)); //1
    this->rooms.emplace_back(new Room(1,1,0,2,nullptr)); //2
    this->rooms.emplace_back(new Room(1,1,1,3,nullptr)); //3
    this->rooms.emplace_back(new Room(1,0,2,4,nullptr)); //4
    this->rooms.emplace_back(new Room(1,0,3,5,nullptr)); //5
    this->rooms.emplace_back(new Room(1,0,4,6,nullptr)); //6
    this->rooms.emplace_back(new Room(3,1,2,7,nullptr)); //7
    this->rooms.emplace_back(new Room(1,1,3,8,nullptr)); //8
    this->rooms.emplace_back(new Room(1,1,4,9,nullptr)); //9
    this->rooms.emplace_back(new Room(1,2,0,10,nullptr)); //10
    this->rooms.emplace_back(new Room(1,2,1,11,nullptr)); //11
    this->rooms.emplace_back(new Room(7,2,2,12,&(this->player))); //12
    this->rooms.emplace_back(new Room(6,2,3,13,nullptr)); //13
    this->rooms.emplace_back(new Room(1,2,4,14,nullptr)); //14
    this->rooms.emplace_back(new Room(1,3,0,15,nullptr)); //15
    this->rooms.emplace_back(new Room(1,3,1,16,nullptr)); //16
    this->rooms.emplace_back(new Room(5,3,2,17,nullptr)); //17
    this->rooms.emplace_back(new Room(1,3,3,18,nullptr)); //18
    this->rooms.emplace_back(new Room(1,3,4,19,nullptr)); //19
    this->rooms.emplace_back(new Room(1,4,0,20,nullptr)); //20
    this->rooms.emplace_back(new Room(1,4,1,21,nullptr)); //21
    this->rooms.emplace_back(new Room(1,4,2,22,nullptr)); //22
    this->rooms.emplace_back(new Room(1,4,3,23,nullptr)); //23
    this->rooms.emplace_back(new Room(1,4,4,24,nullptr)); //24
 
    this->active_room = 11;
    this->clock.restart();//bo inaczej sie enter sam wciska lol
    
}
int Game::getRandomInt(int min,int max){
    static std::random_device rd;  // Seed
    static std::mt19937 gen(rd()); // Mersenne Twister generator
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
};
void Game::init(){
    this->fade.setFillColor(sf::Color(0, 0, 0, 0));
    this->fade.setPosition({0.f, 0.f});
    this->fade.setSize({1600.f, 900.f});
    
    


    this->masterVolume = 1.5f;
    this->currentScreen = "Window";
        //sound
    this->buffer = new sf::SoundBuffer("./Sound/pickupweapon.wav");
    this->pickupWeapon = new sf::Sound(*(this->buffer));
    this->pickupWeapon->setVolume(2.f);

    this->menuBuffer = new sf::SoundBuffer("./Sound/menu.mp3");
    this->gameBuffer = new sf::SoundBuffer("./Sound/game.mp3");
    this->gameOverBuffer = new sf::SoundBuffer("./Sound/game_over.mp3");
    this->hitBuffer = new sf::SoundBuffer("./Sound/hit.mp3");
    this->soundtrack = new sf::Sound(*(this->menuBuffer));
    this->gameSound = new sf::Sound(*(this->gameBuffer));
    this->gameOverSound = new sf::Sound(*(this->gameOverBuffer));
    this->hitSound = new sf::Sound(*(this->hitBuffer));
    this->soundtrack->setVolume(this->masterVolume);
    this->gameSound->setVolume(this->masterVolume);
    this->gameOverSound->setVolume(this->masterVolume);
    this->hitSound->setVolume(this->masterVolume);

        //seting frame limit
    
    this->videoMode.size = {800, 450};
    //makes window proportional
    this->window = new sf::RenderWindow(this->videoMode, "The binding of isaac ultimate ripoff");
    this->window->setFramerateLimit(60);
    sf::View view(sf::FloatRect({0.f, 0.f}, {1600.f, 900.f}));
    this->window->setView(view);
    
        //setting font
    this->font = new sf::Font("./Fonts/Roboto-Regular.ttf");
    //menu stuff
    this->menuT = new sf::Text(*(this->font));
    this->menuT->setPosition({50.f, 60.f});
    this->menuT->setCharacterSize(60.f);
    this->menuT->setString("The binding of not isaac");

    this->play = new sf::Text(*(this->font));
    this->play->setPosition({50.f, 200.f});
    this->play->setCharacterSize(20.f);
    this->play->setString("Play");

    this->option1 = new sf::Text(*(this->font));
    this->option1->setPosition({50.f, 250.f});
    this->option1->setCharacterSize(20.f);
    this->option1->setString("Test");

    this->option2 = new sf::Text(*(this->font));
    this->option2->setPosition({50.f, 300.f});
    this->option2->setCharacterSize(20.f);
    this->option2->setString("Settings");

    this->info = new sf::Text(*(this->font));
    this->info->setPosition({50.f, 350.f});
    this->info->setCharacterSize(20.f);
    this->info->setString("Info");

    this->nickname = new sf::Text(*(this->font));
    this->nickname->setPosition({50.f, 300.f});
    this->nickname->setCharacterSize(60.f);
    this->nickname->setString("");

    this->quit = new sf::Text(*(this->font));
    this->quit->setPosition({50.f, 400.f});
    this->quit->setCharacterSize(20.f);
    this->quit->setString("Quit");

    this->highScoreText = new sf::Text(*(this->font));
    this->highScoreText->setPosition({600.f, 200.f});
    this->highScoreText->setCharacterSize(20.f);

    this->highScoreTime = new sf::Text(*(this->font));
    this->highScoreTime->setPosition({900.f, 250.f});
    this->highScoreTime->setCharacterSize(20.f);

    this->timer = new sf::Text(*(this->font));

    
    

    

    this->restart();

    
}
Game::Game(){
    init();
}
Game::~Game(){
    delete this->window;
}
bool Game::getLose(){
    return this->isLose;
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
                if(keyPressed->scancode == sf::Keyboard::Scan::Escape && !this->getEnd()&& !this->getLose()){
                    this->ismenuOpen = !this->ismenuOpen;
                    this->currentMenu = 0;
                    this->soundtrack->stop();
                    if(this->ismenuOpen=true){
                        this->gameSound->pause();
                    }else{
                        this->gameSound->play();
                    }
                    
                    
                }
                
            }
            if(const auto* keyPressed = this->event->getIf<sf::Event::KeyPressed>()){
                //turns of on escape change later
                if(keyPressed->scancode == sf::Keyboard::Scan::O){
                    this->isLose = true;
                    this->gameSound->pause();
                    this->gameOverSound->play();
                }
                
            }
            if(const auto* keyPressed = this->event->getIf<sf::Event::KeyPressed>()){
                //turns of on escape change later
                if(keyPressed->scancode == sf::Keyboard::Scan::P){
                    this->isEnd = true;
                }
                

            }
            if(this->getEnd()){
                if(const auto* keyPressed = this->event->getIf<sf::Event::KeyPressed>() ){
                //if statements family reunion
                
                    if(keyPressed->scancode == sf::Keyboard::Scan::Backspace){
                        this->nickString = this->nickString.substr(0, this->nickString.size()-1);
                        this->nickname->setString(this->nickString);
                    }

                }
                else if (this->event->getIf<sf::Event::TextEntered>())
                {
                    int temp = event->getIf<sf::Event::TextEntered>()->unicode;
                    if((temp >= 32 && temp <=126) || (temp>=192&&temp<=255) ){
                        this->nickname->setString(this->nickname->getString()+static_cast<char>(event->getIf<sf::Event::TextEntered>()->unicode));
                        this->nickString += static_cast<char>(event->getIf<sf::Event::TextEntered>()->unicode);
                    }
                
                }
            
            }
            
                
            
        }
}
void Game::update(){
    
    this->events();

    
    //player weapon and shooting
    this->player.move();
    this->player.preUpdate();

    updatePlayerBullets();
    updateEnemyBullets();
    updateWeapons(this->rooms[active_room]);
    updateBoosts(this->rooms[active_room]);
    
    updateLoot(this->rooms[active_room]);
    updateDoors(this->rooms[active_room]);
    updateWalls(this->rooms[active_room]);
    updateEnemies(this->rooms[active_room]);
    this->player.update();
    this->currentWeapon->setCurrentPlayerBullets(this->playerBullets);
    this->currentWeapon->setPlayerPos({this->player.getPosition().x+45.f,this->player.getPosition().y+45.f});
    this->currentWeapon->update();
    this->playerBullets = this->currentWeapon->getCurrentPlayerBullets();

    if(this->scoreFrames>60){
        this->scoreSeconds++;
        this->scoreFrames = 0;
    }
    if(this->gameSound->getStatus()==sf::Sound::Status::Stopped){
        this->gameSound->play();
    }
    
    this->scoreFrames ++;
    
}
void Game::render(){
    this->window->clear(sf::Color::Black);
    
    this->renderEntitys();
    if(this->menuOpen()){
        this->menu();
    }
    if(this->getEnd()){
        this->end();
    }
    if(this->getLose()){
        this->lose();
    }
    //zabijanko gracza
    if(this->player.getHp() <= 0 && this->isLose == false){
        this->isLose = true;
        this->gameSound->stop();
        this->gameOverSound->play();
    }
    this->window->display();

}
void Game::renderEntitys(){
     //magic happens right here

    //rendering loot for testing
    //weapons vector should be inside room object


    this->rooms[this->active_room]->render(this->window);

    //rendering player bullets
    
    std::for_each(this->playerBullets.begin(), this->playerBullets.end(), [this](auto* i){i->render(this->window);});
    std::for_each(this->enemyBullets.begin(), this->enemyBullets.end(), [this](auto* i){i->render(this->window);});
    
    
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
    this->timer->setString(std::to_string(this->scoreSeconds));

    sf::RectangleShape temp = this->currentWeapon->shape;
    temp.setPosition({100.f, 20.f});
    temp.setScale({2.f, 2.f});
    sf::RectangleShape bullet = this->currentBullet->shape;
    bullet.setPosition({300.f, 20.f});
    bullet.setScale({1.5f, 1.5f});
    if(dark){
        this->light = true;
        this->dark = false;
        this->fadeOpacity = 255;
        
    }
     if(light && this->fadeClock.getElapsedTime().asSeconds() > 0.01f){
        this->fadeClock.restart();
        this->fadeOpacity -= 30.f;
        if(this->fadeOpacity <=0.f){
            this->fadeOpacity = 0;
            this->light = false;
        }
        this->fade.setFillColor(sf::Color(0, 0, 0, this->fadeOpacity));
    }
    this->window->draw(this->fade);
    this->window->draw(bullet);
    this->window->draw(temp);
    this->window->draw(*(this->hpText));
    this->window->draw(*(this->timer));
}

void Game::updateBoosts(Room* room) {
    auto& boosts = room->getBoosts();

    
    for (auto i = boosts.begin(); i != boosts.end(); ) {
        // Dereference unique_ptr to raw pointer for isColision
        if (isColision(i->get(), &player)) {
            // Handle boost effect before erasing
            if (dynamic_cast<SmallHealth*>(i->get()) != NULL) {
                this->player.changeHp(i->get()->value);
            }
            // Erase and advance iterator safely
            boosts.erase(i);
            break;
        } else {
            ++i;
        }
    }
    
    
}

void Game::updateEnemies(Room* room) {
    auto& enemies = room->getEnemies();
    auto j = enemies.begin();
    for(auto& enemy : enemies){
        //działa tylko dla tych co strzelają
        if(dynamic_cast<Turret*>(enemy) != NULL){
            enemy->setCurrentEnemyBullets(this->enemyBullets);
        }
        if(dynamic_cast<Boss*>(enemy) != NULL){
            enemy->setCurrentEnemyBullets(this->enemyBullets);
        }


        enemy->update(sf::Vector2f(this->player.getPosition().x+(this->player.getSize().x/2),this->player.getPosition().y+(this->player.getSize().y/2)));
        for(auto i = playerBullets.begin(); i != playerBullets.end();){
            if(isColision((*i),enemy)&&enemy->get_can_be_hit()){
                enemy->setHp(enemy->getHp()-(*i)->dmg);
                delete *i;
                playerBullets.erase(i);
            }else{
                i++;
            }
        };
        
        if(isColision(&player,enemy)&&this->player.getTargetable()){
            std::cout<<player.getHp()<<std::endl;
            this->player.changeHp(-enemy->getDmg());
            if(enemy->getDmg() > 0){
                this->hitSound->play();
            }
            
            std::cout<<player.getHp()<<std::endl;
            this->player.setTargetable(false);
            enemy->setCollided(true);
        }
        enemy->move(sf::Vector2f(this->player.getPosition().x+(this->player.getSize().x/2),this->player.getPosition().y+(this->player.getSize().y/2)));
        //tez dziła tylko dla tych co strzelają
        if(dynamic_cast<Turret*>(enemy) != NULL){
            this->enemyBullets = enemy->getCurrentEnemyBullet();
        }
        if(dynamic_cast<Boss*>(enemy) != NULL){
            this->enemyBullets = enemy->getCurrentEnemyBullet();
        }
        if(enemy->getHp()<=0){
            delete *j;
            enemies.erase(j);
        }else{
            j++;
        }
        
    }

    auto& spikes = room->getSpikes();
    for(auto& enemy : spikes){
        if(isColision(&player,enemy)&&this->player.getTargetable()){
            std::cout<<player.getHp()<<std::endl;
            this->player.changeHp(-enemy->getDmg());
            std::cout<<player.getHp()<<std::endl;
            this->player.setTargetable(false);
            enemy->setCollided(true);
        }
    }
}

void Game::updateWalls(Room* room){
    auto& walls = room->getWalls();

    // Reset all collision flags before checking new collisions
    this->player.resetCollisions();

    sf::FloatRect playerBounds = this->player.hitbox.getGlobalBounds();

    if(this->rooms[this->active_room]->getEnemies().size()==0&&this->rooms[this->active_room]->getCleared()==false){
        std::cout<<"spelniono warunki\n";
        std::cout<<this->rooms[this->active_room]->getCleared()<<"\n";
        int j=8;
        if(this->rooms[this->active_room]->getX()==0){
            j++;
        }
        else{
            this->rooms[this->active_room]->getWalls().erase(walls.begin() + j);
        }
        if(this->rooms[this->active_room]->getX()==4){
            j++;
        }
        else{
            this->rooms[this->active_room]->getWalls().erase(walls.begin() + j);
        }
        if(this->rooms[this->active_room]->getY()==4){
            j++;
        }
        else{
            this->rooms[this->active_room]->getWalls().erase(walls.begin() + j);
        }
        if(this->rooms[this->active_room]->getY()==0){
            j++;
        }
        else{
            this->rooms[this->active_room]->getWalls().erase(walls.begin() + j);
        }

        this->rooms[this->active_room]->setCleared(true);
    }

    for (auto& wall : walls) {
        sf::FloatRect wallBounds = wall->hitbox.getGlobalBounds();
        bool intersects = !(this->player.hitbox.getPosition().x + this->player.hitbox.getSize().x < wallBounds.position.x||  // Player is to the left of the wall
                            this->player.hitbox.getPosition().x > wallBounds.position.x + wallBounds.size.x || // Player is to the right of the wall
                            this->player.hitbox.getPosition().y + this->player.hitbox.getSize().y  < wallBounds.position.y|| // Player is above the wall
                            this->player.hitbox.getPosition().y  > wallBounds.position.y + wallBounds.size.y); 

        if (intersects) {
            float dx = (this->player.hitbox.getPosition().x+this->player.hitbox.getSize().x / 2) - (wallBounds.position.x + wallBounds.size.x / 2);
            float dy = (this->player.hitbox.getPosition().y +this->player.hitbox.getSize().y / 2) - (wallBounds.position.y + wallBounds.size.y / 2);

            float overlapX = (this->player.hitbox.getSize().x + wallBounds.size.x ) / 2 - std::abs(dx);
            float overlapY = (this->player.hitbox.getSize().y + wallBounds.size.y) / 2 - std::abs(dy);

            if (overlapX < overlapY) {
                if (dx > 0){
                    this->player.setCollidesLeft(true);
                }
                else{
                    this->player.setCollidesRight(true);
                }
            } 
            else {
                if (dy > 0){
                    this->player.setCollidesUp(true);
                }
                else{
                    this->player.setCollidesDown(true);
                }
            }
        }
    }
}

void Game::updateDoors(Room* room){


    if(this->player.getPosition().x<10){
        int d = std::count_if(this->rooms.begin(), this->rooms.end(), [&](Room* r) {
            return r->getX() < this->rooms[this->active_room]->getX();
        });
        std::cout<<this->rooms[this->active_room]->getX()<<" "<<this->rooms[this->active_room]->getY()<<"\n";
        int randomtp = getRandomInt(0,d-1);

        this->active_room=this->rooms.at(randomtp)->getId();
        for(auto el:this->playerBullets){
            delete el;
        }
        this->playerBullets.clear();
        for(auto el:this->enemyBullets){
            delete el;
        }
        this->enemyBullets.clear();
        std::cout<<this->rooms[this->active_room]->getId()<<"\n";
        std::cout<<this->rooms[this->active_room]->getX()<<" "<<this->rooms[this->active_room]->getY()<<"\n";
        this->player.setPosition(sf::Vector2f(1500.f, this->player.getPosition().y));

    }

        if(this->player.getPosition().x>1530){
        int d = std::count_if(this->rooms.begin(), this->rooms.end(), [&](Room* r) {
            return r->getX() > this->rooms[this->active_room]->getX();
        });
        std::cout<<this->rooms[this->active_room]->getX()<<" "<<this->rooms[this->active_room]->getY()<<"\n";
        int randomtp = getRandomInt(0,d-1);

        this->active_room=this->rooms.at(randomtp)->getId();
        for(auto el:this->playerBullets){
            delete el;
        }
        this->playerBullets.clear();
        for(auto el:this->enemyBullets){
            delete el;
        }
        this->enemyBullets.clear();
        std::cout<<this->rooms[this->active_room]->getId()<<"\n";
        std::cout<<this->rooms[this->active_room]->getX()<<" "<<this->rooms[this->active_room]->getY()<<"\n";
        this->player.setPosition(sf::Vector2f(30.f,this->player.getPosition().y));

    }

        if(this->player.getPosition().y>830){
        int d = std::count_if(this->rooms.begin(), this->rooms.end(), [&](Room* r) {
            return r->getY() > this->rooms[this->active_room]->getY();
        });
        std::cout<<this->rooms[this->active_room]->getX()<<" "<<this->rooms[this->active_room]->getY()<<"\n";
        int randomtp = getRandomInt(0,d-1);

        this->active_room=this->rooms.at(randomtp)->getId();
        for(auto el:this->playerBullets){
            delete el;
        }
        this->playerBullets.clear();
        for(auto el:this->enemyBullets){
            delete el;
        }
        this->enemyBullets.clear();
        std::cout<<this->rooms[this->active_room]->getId()<<"\n";
        std::cout<<this->rooms[this->active_room]->getX()<<" "<<this->rooms[this->active_room]->getY()<<"\n";
        this->player.setPosition(sf::Vector2f(this->player.getPosition().x,20.f));

    }
        if(this->player.getPosition().y<10){
        int d = std::count_if(this->rooms.begin(), this->rooms.end(), [&](Room* r) {
            return r->getY() < this->rooms[this->active_room]->getY();
        });
        std::cout<<this->rooms[this->active_room]->getX()<<" "<<this->rooms[this->active_room]->getY()<<"\n";
        int randomtp = getRandomInt(0,d-1);

        this->active_room=this->rooms.at(randomtp)->getId();
        for(auto el:this->playerBullets){
            delete el;
        }
        this->playerBullets.clear();
        for(auto el:this->enemyBullets){
            delete el;
        }
        this->enemyBullets.clear();
        std::cout<<this->rooms[this->active_room]->getId()<<"\n";
        std::cout<<this->rooms[this->active_room]->getX()<<" "<<this->rooms[this->active_room]->getY()<<"\n";
        this->player.setPosition(sf::Vector2f(this->player.getPosition().x,820.f));

    }
   
}

void Game::updateWeapons(Room* room){
  //updating loot for testing
    //in the future wepons list will be taken from room object but the rest of the logic stays the same
      //updating loot for testing
    //in the future wepons list will be taken from room object but the rest of the logic stays the same
    auto& weapons = room->getWeapons();
    int x = 0;
    for(Item* weapon:weapons){
        //checking for colision and if player pressed E 
        if(isColision(weapon, &player) && player.pressedE==true){
            //giving a player weapon on the ground and droping current weapon 
            Item* droped = currentWeapon;
            droped->updatePos({this->player.getPosition().x+20.f, this->player.getPosition().y+50.f});
            weapons.at(x) = droped;
            this->currentWeapon = weapon;
            //setting current bullets for new weapon
            this->currentWeapon->setCurrentBullet(this->currentBullet);
            this->pickupWeapon->play();
            break;
        }
        x++;
    }
    


  
}
void Game::updatePlayerBullets(){
    //updating player bullet position
    std::for_each(this->playerBullets.begin(), this->playerBullets.end(), [this](auto* i){i->update();});
    
    for(auto i = playerBullets.begin(); i != playerBullets.end();){
    
        //checking if bullet should be deleted for now only by its range
        if((*i)->isVisible==false){
            delete *i;
            playerBullets.erase(i);
            
        }else{
            i++;
        }
        
    }
       
}

void Game::updateEnemyBullets(){
    //updating player bullet position
    std::for_each(this->enemyBullets.begin(), this->enemyBullets.end(), [this](auto* i){i->update();});

    for(auto i = enemyBullets.begin(); i != enemyBullets.end();){

        //checking if bullet should be deleted for now only by its range
        if((*i)->isVisible==false){
            delete *i;
            enemyBullets.erase(i);
            
        }else{
            i++;
        }  
    }
    for(auto i = enemyBullets.begin(); i != enemyBullets.end();){
        if(isColision((*i),static_cast<Entity*>(&this->player))&&this->player.getTargetable()){
            this->player.setHp(this->player.getHp()-(*i)->dmg);
            this->hitSound->play();
            enemyBullets.erase(i);
        }else{
            i++;
        }
    }
}


void Game::updateLoot(Room* room){
    auto& loot = room->getLoot();
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
            delete *i;
            loot.erase(i);
            loot.emplace_back(droped);
            
            break;
            
        }
        
            i++;
        
    }   
}

bool Game::menuOpen(){
    
    return this->ismenuOpen;
}
void Game::menu(){

    this->events();

    //drawing
    this->window->draw(background);
    this->window->draw(fog);
        this->window->draw(*menuT);
    if(this->currentMenu == 0){
        this->mainMenu();
    }else if(this->currentMenu == 1){
        this->settingsMenu();
    }else if(this->currentMenu == 2){
        this->readFromFile();
        this->infoMenu();
        
    }
        
    
    

}
void Game::mainMenu(){
    this->play->setString("Play");
    this->option2->setString("Settings");
    this->option1->setPosition({50.f, 200.f});
    this->option2->setPosition({50.f, 250.f});
    this->info->setPosition({50.f, 300.f});
    this->quit->setPosition({50.f, 350.f});
    this->option2->setFillColor(sf::Color::White);
    this->window->draw(*play);
        this->window->draw(*option2);
        this->window->draw(*info);
        this->window->draw(*quit);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->clock.getElapsedTime().asSeconds() > 0.3f)
        {
            this->ismenuOpen = false; 
            this->gameSound->play();
            this->soundtrack->stop();
            this->clock.restart();
        }  
    }
    else if(this->selected == 2){
        fog.setPosition({option2->getPosition().x-20.f, option2->getPosition().y-5.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->clock.getElapsedTime().asSeconds() > 0.1f)
        {
            this->currentMenu = 1;
            this->selected = 1;
            this->tempScreen = this->currentScreen;
            this->clock.restart();
        }  
    }else if(this->selected == 3){
        fog.setPosition({info->getPosition().x-20.f, info->getPosition().y-5.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->clock.getElapsedTime().asSeconds() > 0.1f)
        {
            this->currentMenu = 2;
            this->clock.restart();
        }  
    }
    else if(this->selected == 4){
        fog.setPosition({quit->getPosition().x-20.f, quit->getPosition().y-5.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->clock.getElapsedTime().asSeconds() > 0.1f)
        {
            this->ismenuOpen = false;
            this->isClosed = true;
            this->clock.restart();
        }  
    }
     

    

}
void Game::settingsMenu(){
    this->play->setString("Scrren");
    this->option1->setString("Back");
    this->option1->setPosition({50.f, 250.f});
    
    this->option2->setString(this->tempScreen);
    this->option2->setPosition({200.f, 200.f});
    
    this->window->draw(*play);
        this->window->draw(*option1);
        this->window->draw(*option2);
    if(this->clock.getElapsedTime().asSeconds() > 0.1f){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            if(this->selected>1){
                this->selected --;
            }
            this->clock.restart();
            
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            if(this->selected < 2){
                this->selected ++;
            }
            this->clock.restart();
            
        }
        
            
    }
     if(this->selected == 1){
        fog.setPosition({play->getPosition().x-20.f, play->getPosition().y-5.f});
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))&& this->clock.getElapsedTime().asSeconds() > 0.3f)
        {
            
            if(this->tempScreen == "Window" ){
                this->tempScreen = "Fullscreen";
                this->option2->setFillColor(sf::Color::Red);
                
            }else if(this->tempScreen == "Fullscreen"){
                this->tempScreen = "Window";
                this->option2->setFillColor(sf::Color::Red);
                
            }
            this->clock.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->clock.getElapsedTime().asSeconds() > 0.2f)
        {
            if(this->tempScreen == "Fullscreen"){
                delete this->window;
                this->window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "The binding of isaac ultimate ripoff", sf::Style::None);
                sf::View view(sf::FloatRect({0.f, 0.f}, {1600.f, 900.f}));
                this->window->setFramerateLimit(60);
    this->window->setView(view);
            }else if(this->tempScreen == "Window"){
                delete this->window;
                this->window = new sf::RenderWindow(this->videoMode, "The binding of isaac ultimate ripoff", sf::Style::Default);
                sf::View view(sf::FloatRect({0.f, 0.f}, {1600.f, 900.f}));
                this->window->setFramerateLimit(60);
    this->window->setView(view);
            }
            this->option2->setFillColor(sf::Color::White);
            this->currentScreen = this->tempScreen;
            this->clock.restart();
            
        }    
    }else if(this->selected == 2){
        fog.setPosition({option1->getPosition().x-20.f, option1->getPosition().y-5.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->clock.getElapsedTime().asSeconds() > 0.1f)
        {
            this->currentMenu = 0;
            this->selected = 2;
            this->clock.restart();
            
        }  
    }
     

   
    
}
void Game::infoMenu(){

    this->play->setString("MOVEMENT\n\nW - move forevard\nS = move backward\nA - move left\nR - move right\nE - use\nArrow Up - shoot up\nArrow Down - shoot down\nArrow Left - shoot left\nArrow Right - shoot right\n");
    this->option1->setString("Back");
    this->play->setScale({1.2f, 1.2f});
    
    this->option1->setPosition({50.f, 600.f});
    
    this->window->draw(*play);
        this->window->draw(*option1);
        this->window->draw(*(this->highScoreText));
        this->window->draw(*(this->highScoreTime));
        
  
    
        fog.setPosition({option1->getPosition().x-20.f, option1->getPosition().y-5.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)&& this->clock.getElapsedTime().asSeconds() > 0.3f)
        {
            
            this->currentMenu = 0;
            this->clock.restart();
        }
        
    
}
void Game::end(){
    this->events();
    this->menuT->setString("You Win");
    this->timer->setPosition({50.f, 150.f});
    this->timer->setString("Your time: " + this->timer->getString()+ "\n\nEnter your nickname: ");
    this->timer->setCharacterSize(45);
    this->nickname->setCharacterSize(45);
    
    this->window->draw(this->background);
    this->window->draw(*(this->nickname));
    this->window->draw(*(this->menuT));
    this->window->draw(*(this->timer));
    //interfejs do wpisywania nicku i wyświetlanie czasu po enterze sie resetuje gra
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            writeToFile(this->scoreSeconds);
            comma();
            writeToFile(this->nickString);
            breakLine();
            this->restart();

        }
}
void Game::lose(){
    this->events();
    this->menuT->setString("You lose");
    this->timer->setPosition({50.f, 150.f});
    this->timer->setString("Your time: " + this->timer->getString());
    this->timer->setCharacterSize(45);
    this->nickname->setCharacterSize(45);
    
    
    this->window->draw(this->background);
    this->window->draw(*(this->menuT));
    this->window->draw(*(this->timer));
    //interfejs do wpisywania nicku i wyświetlanie czasu po enterze sie resetuje gra
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            this->restart();
            
        }
}
bool Game::getEnd(){
    return this->isEnd;
}
template <typename T>
void Game::writeToFile(T input){
    std::fstream file("./score.csv", std::ios::app);
    file << input;
    file.close();
}
void Game::breakLine(){
    std::fstream file("./score.csv", std::ios::app);
    file << std::endl;
    file.close();
}
void Game::comma(){
    std::fstream file("./score.csv", std::ios::app);
    file << ",";
    file.close();
}
void Game::readFromFile(){
    this->highScoreText->setString("High score\n\n");
    this->highScoreTime->setString("");
    std::ifstream file("./score.csv");
    if (file.is_open()) {
    std::string line;
    std::vector<std::pair<int, std::string>> scores;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string temp1;
        int temp2 = 0;
        std::getline(ss, temp1, ',');
        temp2 = std::stoi(temp1);
        std::getline(ss, temp1, ',');
        std::pair<int, std::string> temp3;
        temp3.first = temp2;
        temp3.second = temp1;
        scores.emplace_back(temp3);
        
    }
    std::sort(scores.begin(), scores.end(), [](auto first, auto second){return first.first < second.first;});
    for(int i = 0; i<10 && i < scores.size(); i++){
        this->highScoreText->setString(this->highScoreText->getString() + scores.at(i).second + "\n");
        this->highScoreTime->setString(this->highScoreTime->getString() +std::to_string(scores.at(i).first) + "\n");
    }
    
        

    file.close();
    }

    
    // close the file after read opeartion is complete
    
}
#endif