#ifndef ROOM_H
#define ROOM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Door.h"
#include "Wall.h"
#include "Item.h"
#include "Ammo.h"
#include "Boost.h"
#include "Bullet.h"
#include "RoundBullet.h"
#include "FastBullet.h"
#include "Turret.h"
#include "Dumb.h"
#include "Spike.h"
#include "Ram.h"
#include "Spike2.h"
#include "FirstWeapon.h"
#include "ThreeBulletWeapon.h"
#include "MiniGunWeapon.h"
#include "rbAmmo.h"
#include "fastAmmo.h"
#include "SmallHealth.h"
#include "whiteDumb.h"
#include "greenDumb.h"
#include "redDumb.h"

class Room {
    public:
        Room();
        Room(int a,int b, int c,int d);
        virtual ~Room();
        void render(sf::RenderTarget* target);
        void update();
        bool getIsActive(){ return isActive; };
        int getId(){ return id; };
        int getX();
        int getY();
        int getRandomInt(int min,int max);
        std::vector<Item*>& getWeapons();
        std::vector<std::unique_ptr<Boost>>& getBoosts();
        std::vector<Ammo*>& getLoot();
        std::vector<std::unique_ptr<Wall>>& getWalls();
        std::vector<std::unique_ptr<Door>>& getDoors();
        std::vector<Enemy*>& getEnemies();
        sf::RectangleShape floor;
        sf::Texture* texture;
    private:
        bool isActive=true;
        int type_id;
        sf::RectangleShape shape;
        std::vector<Enemy*> enemies;
        std::vector<std::unique_ptr<Door>> doors;
        std::vector<std::unique_ptr<Wall>> walls;
        std::vector<Item*> weapons;
        std::vector<Ammo*> loot;
        std::vector<std::unique_ptr<Boost>> boosts;
        int x;
        int y;
        int id;
};
        int Room::getX(){
            return x;
        };
        int Room::getY(){return y;};
std::vector<Item*>& Room::getWeapons() { return weapons; };
std::vector<Ammo*>& Room::getLoot() { return loot; };
std::vector<Enemy*>& Room::getEnemies() { return enemies; };
std::vector<std::unique_ptr<Boost>>& Room::getBoosts() { return this->boosts; };
std::vector<std::unique_ptr<Wall>>& Room::getWalls() { return walls; };
std::vector<std::unique_ptr<Door>>& Room::getDoors() { return doors; };

Room::Room(){
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(200.f, 200.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));
};
Room::Room(int a,int b, int c,int d){
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(1600.f, 900.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));
    this->type_id=a;
    this->x=b;
    this->y=c;
    this->id=d;
    this->walls.emplace_back(new Wall(1));
    this->walls.emplace_back(new Wall(2));
    this->walls.emplace_back(new Wall(3));
    this->walls.emplace_back(new Wall(4));
    this->walls.emplace_back(new Wall(5));
    this->walls.emplace_back(new Wall(6));
    this->walls.emplace_back(new Wall(7));
    this->walls.emplace_back(new Wall(8));
    this->texture = new sf::Texture("./Textures/floor.png");
    this->texture->setRepeated(true);
    this->floor.setPosition({0.f, 0.f});
    this->floor.setSize({1600.f, 900.f});
    
    this->floor.setTexture(this->texture);
    this->floor.setTextureRect(*(new sf::IntRect({0, 0}, {400, 225})));
    if(type_id==1){
        this->doors.emplace_back(new Door(1));
        this->doors.emplace_back(new Door(2));
        this->doors.emplace_back(new Door(3));
        this->doors.emplace_back(new Door(4));
        this->weapons.emplace_back(new FirstWeapon);
        this->weapons.at(0)->updatePos({500.f, 500.f}); //blad przy klikaniu game 
        sf::Vector2f c;
        c.x=1200.f;
        c.y=500.f;
        this->enemies.emplace_back(new Turret(c));
    }
    if(type_id==2){
        this->doors.emplace_back(new Door(1));
        this->doors.emplace_back(new Door(2));
        this->doors.emplace_back(new Door(3));
        this->doors.emplace_back(new Door(4));
        this->enemies.emplace_back(new Enemy());
        this->enemies.emplace_back(new Enemy());
        this->enemies[0]->setPosition(sf::Vector2f(140.f, 40.f));
        this->enemies[1]->setPosition(sf::Vector2f(140.f, 140.f));

        this->loot.emplace_back(new rbAmmo);
        this->loot.at(0)->setPosition({800.f, 300.f});
        this->loot.emplace_back(new fastAmmo);
        this->loot.at(1)->setPosition({800.f, 400.f});
    
        this->boosts.emplace_back(new SmallHealth);
        this->boosts.at(0)->setPosition({900.f, 400.f});
    }
    if(type_id==3){ //enemies
        this->doors.emplace_back(new Door(1));
        this->doors.emplace_back(new Door(2));
        this->doors.emplace_back(new Door(3));
        this->doors.emplace_back(new Door(4));
        sf::Vector2f c;
        c.x=1200.f;
        c.y=500.f;
        this->enemies.emplace_back(new whiteDumb(c));
        c.y=200.f;
        this->enemies.emplace_back(new greenDumb(c));
        c.x=800.f;
        this->enemies.emplace_back(new redDumb(c));
    }
    if(type_id==4){  //changing room
        this->doors.emplace_back(new Door(1));
        this->doors.emplace_back(new Door(2));
        this->doors.emplace_back(new Door(3));
        this->doors.emplace_back(new Door(4));
        this->loot.emplace_back(new rbAmmo);
        this->loot.at(0)->setPosition({800.f, 300.f});        //podniesienie przestalo dzialac
        this->loot.emplace_back(new fastAmmo);
        this->loot.at(1)->setPosition({800.f, 400.f});
        this->boosts.emplace_back(new SmallHealth);
        this->boosts.at(0)->setPosition({900.f, 400.f});
        sf::Vector2f c;
        c.x=1200.f;
        c.y=500.f;
        this->enemies.emplace_back(new Spike2(c));
        c.y=200.f;
        this->enemies.emplace_back(new Ram(c));
        c.x=300.f;
        c.y=500.f;
        this->enemies.emplace_back(new Spike(c));

    }
    if(type_id==5){  //changing room
        this->doors.emplace_back(new Door(1));
        this->doors.emplace_back(new Door(2));
        this->doors.emplace_back(new Door(3));
        this->doors.emplace_back(new Door(4));
        this->weapons.emplace_back(new MiniGunWeapon);
        this->weapons.at(0)->updatePos({780.f, 425.f}); 
        sf::Vector2f c;
        for(int j=0;j<100;j++){
        c.x=getRandomInt(200,1350);
        c.y=getRandomInt(200,650);
        this->enemies.emplace_back(new Spike2(c));
        }
    }
    if(type_id==6){  //changing room
        this->doors.emplace_back(new Door(1));
        this->doors.emplace_back(new Door(2));
        this->doors.emplace_back(new Door(3));
        this->doors.emplace_back(new Door(4));
        this->weapons.emplace_back(new ThreeBulletWeapon);
        this->weapons.at(0)->updatePos({780.f, 425.f}); 
        
        sf::Vector2f c;
        c.y=180;
        for(int j=200;j<1400;j+=40){
        c.x=j;
        this->enemies.emplace_back(new Spike(c));
        }

        c.y=660;
        for(int j=200;j<1400;j+=40){
        c.x=j;
        this->enemies.emplace_back(new Spike(c));
        }

        c.x=200;
        for(int j=220;j<=620;j+=40){
        c.y=j;
        this->enemies.emplace_back(new Spike(c));
        }
        c.x=1360;
        for(int j=220;j<=620;j+=40){
        c.y=j;
        this->enemies.emplace_back(new Spike(c));
        }

        c.y=320;
        for(int j=400;j<1200;j+=40){
        c.x=j;
        this->enemies.emplace_back(new Spike(c));
        }

        c.y=520;
        for(int j=400;j<1200;j+=40){
        c.x=j;
        this->enemies.emplace_back(new Spike(c));
        }

        c.x=400;
        for(int j=360;j<=480;j+=40){
        c.y=j;
        this->enemies.emplace_back(new Spike(c));
        }
        c.x=1160;
        for(int j=360;j<=480;j+=40){
        c.y=j;
        this->enemies.emplace_back(new Spike(c));
        }

    }




};

int Room::getRandomInt(int min,int max){
    static std::random_device rd;  // Seed
    static std::mt19937 gen(rd()); // Mersenne Twister generator
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
};


Room::~Room(){

};

void Room::update(){
    if(this->isActive){
    for(auto it = this->enemies.begin(); it != this->enemies.end();){
        if((*it)->getIsDead()){
            it = this->enemies.erase(it); //petla sprawdzajaca czy w pokoju umarli enemies
        }
        else{
            ++it;
        }
    }
    }
};

void Room::render(sf::RenderTarget* target){
    target->draw(this->floor);
    //target->draw(this->shape);
    for (const auto& enemy : enemies) {
        enemy->render(target);
    }
    for (const auto& door : doors) {
        door->render(target);
    }
    
    for (const auto& wall : walls) {
        wall->render(target);
    }
    
    for (const auto& weapon : weapons) {
        weapon->render(target);
    }
    
    for (const auto& ammo : loot) {
        ammo->render(target);
    }
    
    for (const auto& boost : boosts) {
        boost->render(target);
    }
};




#endif