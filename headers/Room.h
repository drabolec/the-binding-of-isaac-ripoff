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
#include "Boss.h"
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
#include "whiteRam.h"
#include "greenRam.h"
#include "Player.h"
class Room {
    public:
        Room();
        Room(int a,int b, int c,int d,Player* playerc);
        ~Room();
        void render(sf::RenderTarget* target);
        void update();
        bool getIsActive(){ return isActive; };
        int getId(){ return id; };
        int getX();
        int getY();
        bool getCleared();
        void setCleared(bool a);
        void getPlayer(Player* playerc);
        int getRandomInt(int min,int max);
        std::vector<Item*>& getWeapons();
        std::vector<std::unique_ptr<Boost>>& getBoosts();
        std::vector<Ammo*>& getLoot();
        std::vector<std::unique_ptr<Wall>>& getWalls();
        std::vector<std::unique_ptr<Door>>& getDoors();
        std::vector<Enemy*>& getEnemies();
        std::vector<Enemy*>& getSpikes();
        sf::RectangleShape floor;
        sf::Texture* texture;
    private:
        bool isActive=true;
        bool cleared=false;
        int type_id;
        Player* playerd=nullptr;
        sf::RectangleShape shape;
        std::vector<Enemy*> enemies;
        std::vector<Enemy*> spikes;
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
std::vector<Enemy*>& Room::getSpikes() { return spikes; };
std::vector<std::unique_ptr<Boost>>& Room::getBoosts() { return this->boosts; };
std::vector<std::unique_ptr<Wall>>& Room::getWalls() { return walls; };
std::vector<std::unique_ptr<Door>>& Room::getDoors() { return doors; };

Room::Room(){
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(200.f, 200.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));
};
Room::Room(int a,int b, int c,int d,Player* playerc){
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(1600.f, 900.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));
    this->type_id=a;
    this->x=b;
    this->y=c;
    this->id=d;
    playerd=playerc;
    /*
    if(this->x==0){
        this->walls.emplace_back(new Wall(9));
    }
    else{
        this->doors.emplace_back(new Door(1));
    }
    if(this->y==0){
        this->walls.emplace_back(new Wall(12));
    }
    else{
        this->doors.emplace_back(new Door(4));
    }
    if(this->x==4){
        this->walls.emplace_back(new Wall(10));
    }
    else{
      this->doors.emplace_back(new Door(2));
    }
    if(this->y==4){
        this->walls.emplace_back(new Wall(11));
    }
    else{
      this->doors.emplace_back(new Door(3));
    }
    */

    this->walls.emplace_back(new Wall(1));
    this->walls.emplace_back(new Wall(2));
    this->walls.emplace_back(new Wall(3));
    this->walls.emplace_back(new Wall(4));
    this->walls.emplace_back(new Wall(5));
    this->walls.emplace_back(new Wall(6));
    this->walls.emplace_back(new Wall(7));
    this->walls.emplace_back(new Wall(8));
    this->walls.emplace_back(new Wall(9));
    this->walls.emplace_back(new Wall(10));
    this->walls.emplace_back(new Wall(11));
    this->walls.emplace_back(new Wall(12));
    this->texture = new sf::Texture("./Textures/floor.png");
    this->texture->setRepeated(true);
    this->floor.setPosition({64.f, 64.f});
    this->floor.setSize({1472.f, 772.f});
    
    this->floor.setTexture(this->texture);
    this->floor.setTextureRect(*(new sf::IntRect({0, 0}, {368, 193})));
    //easy room to beat with deafutl ammo and weapon
    if(type_id==1){
        sf::Vector2f c;

        for(int j =0; j<20; j++){
            c.x=getRandomInt(2,22);
            c.y=getRandomInt(2,11);
            c = c*64.f;
            this->spikes.emplace_back(new Spike(c));
        }

        
        if(getRandomInt(0,10)==10){
            c.x=getRandomInt(2,22);
            c.y=getRandomInt(2,11);
            c = c*64.f;
            this->loot.emplace_back(new fastAmmo(c));
        }
        if(getRandomInt(0,10)==10){
            c.x=getRandomInt(2,22);
            c.y=getRandomInt(2,11);
            c = c*64.f;
            this->weapons.emplace_back(new MiniGunWeapon(c));
        }
        if(getRandomInt(0,10)==10){
            c.x=getRandomInt(2,22);
            c.y=getRandomInt(2,11);
            c = c*64.f;
            this->weapons.emplace_back(new ThreeBulletWeapon(c));
        }
        if(getRandomInt(0,5)==10){
            c.x=getRandomInt(2,22);
            c.y=getRandomInt(2,11);
            c = c*64.f;
            this->enemies.emplace_back(new whiteRam(c));
        }
        for(int j =0; j<getRandomInt(2, 7); j++){
            c.x=getRandomInt(2,22);
            c.y=getRandomInt(2,11);
            c = c*64.f;
            this->enemies.emplace_back(new whiteDumb(c));
        }

        c.x=12.f;
        c.y=8.f;
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));
    }
    //empty room
    if(type_id==2){

        //empty starting room
    }
    if(type_id==3){ //better loot room (better ammo)
        sf::Vector2f c;
        c.x=2;
        c.y=2;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=4;
        c.y=3;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=3;
        c.y=5;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=22;
        c.y=2;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=20;
        c.y=3;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=21;
        c.y=4;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=2;
        c.y=10;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=3;
        c.y=11;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=4;
        c.y=11;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=22;
        c.y=11;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=21;
        c.y=12;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=22;
        c.y=10;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=12;
        c.y=7;
        c = c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        c.x=13;
        c.y=9;
        c = c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        c.x=15;
        c.y=6;
        c = c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new Turret(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new whiteDumb(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new greenDumb(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new greenDumb(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new whiteDumb(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new whiteDumb(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=14.f;
        c.y=9.f;
        c = c*64.f;
        this->loot.emplace_back(new fastAmmo(c));
    }
    if(type_id==4){  //minigun room 

        
        sf::Vector2f c;
         c.x=2;
        c.y=2;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=3;
        c.y=2;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=4;
        c.y=3;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=3;
        c.y=5;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=22;
        c.y=2;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=22;
        c.y=3;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=20;
        c.y=3;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=21;
        c.y=4;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=2;
        c.y=10;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=2;
        c.y=12;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=3;
        c.y=11;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=4;
        c.y=11;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=22;
        c.y=11;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=21;
        c.y=12;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=21;
        c.y=9;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=22;
        c.y=10;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=12;
        c.y=6;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=14;
        c.y=7;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=11;
        c.y=5;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=13;
        c.y=6;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=12;
        c.y=8;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));

        c.x=12;
        c.y=3;
        c = c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        c.x=14;
        c.y=4;
        c = c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        c.x=11;
        c.y=3;
        c = c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        c.x=12;
        c.y=11;
        c = c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        c.x=13;
        c.y=10;
        c = c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        c.x=11;
        c.y=11;
        c = c*64.f;
        this->spikes.emplace_back(new Spike2(c));





        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new whiteRam(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new whiteDumb(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new whiteDumb(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new whiteDumb(c));

        c.x=21;
        c.y=4;
        c = c*64.f;
        this->enemies.emplace_back(new whiteDumb(c));

        c.x=13;
        c.y=7;
        c = c*64.f;
        this->weapons.emplace_back(new MiniGunWeapon(c));

        c.x=14;
        c.y=7;
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=12;
        c.y=6;
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=13;
        c.y=8;
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=14;
        c.y=8;
        c = c*64.f;
        this->enemies.emplace_back(new Turret(c));


        

    }
    if(type_id==5){  //changing room
        sf::Vector2f c;
        c.x=12;
        c.y=7;
        c=c*64.f;
        this->weapons.emplace_back(new MiniGunWeapon(c));
        for(int j=0;j<10;j++){
        c.x=getRandomInt(7,13)*64;
        c.y=getRandomInt(5,8)*64;
        this->spikes.emplace_back(new Spike2(c));
        }
        for(int j=0;j<10;j++){
        c.x=getRandomInt(1,6)*64;
        c.y=getRandomInt(1,12)*64;
        this->spikes.emplace_back(new Spike(c));
        }
        for(int j=0;j<10;j++){
        c.x=getRandomInt(13,23)*64;
        c.y=getRandomInt(1,12)*64;
        this->spikes.emplace_back(new Spike(c));
        }
        c.x=12;
        c.y=7;
        c = c*64.f;
        this->enemies.emplace_back(new greenRam(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new greenDumb(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new greenDumb(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));

        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));
        
    }
    if(type_id==6){  //changing room

        this->weapons.emplace_back(new ThreeBulletWeapon);
        this->weapons.at(0)->updatePos({780.f, 425.f}); 
        
        sf::Vector2f c;
        
        for(int j=3;j<22;j++){
        c.y=3;
        c.x=j;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));
        }

        
        for(int j=3;j<22;j++){
        c.y=10;
        c.x=j;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));
        }

        
        for(int j=4;j<=9;j++){
        c.x=3;
        c.y=j;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));
        }
        
        for(int j=4;j<=9;j++){
        c.x=21;
        c.y=j;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));
        }

        for(int j=6;j<19;j++){
        c.y=5;
        c.x=j;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));
        }

        
        for(int j=6;j<19;j++){
        c.y=8;
        c.x=j;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));
        }

        
        for(int j=5;j<=8;j++){
        c.x=5;
        c.y=j;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));
        }
        
        for(int j=5;j<=8;j++){
        c.x=19;
        c.y=j;
        c = c*64.f;
        this->spikes.emplace_back(new Spike(c));
        }
        for(int j=0;j<1;j++){
        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new Turret(c));
        }
        for(int j=0;j<1;j++){
        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new redDumb(c));
        }
        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->enemies.emplace_back(new greenRam(c));
        for(int j=0;j<6;j++){
        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->boosts.emplace_back(new SmallHealth(c));
        }
        c.x=getRandomInt(2,22);
        c.y=getRandomInt(2,11);
        c = c*64.f;
        this->loot.emplace_back(new fastAmmo(c));
       


    }

    if(type_id==7){  //boss room

        sf::Vector2f c;
        c.x=11.f;
        c.y=6.f;
        c= c*64.f;
        this->spikes.emplace_back(new Spike2(c));
        c.x=11.f;
        c.y=7.f;
        c= c*64.f;
        this->spikes.emplace_back(new Spike2(c));
        c.x=11.f;
        c.y=8.f;
        c= c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        c.x=12.f;
        c.y=8.f;
        c= c*64.f;
        this->spikes.emplace_back(new Spike2(c));
        c.x=13.f;
        c.y=8.f;
        c= c*64.f;
        this->spikes.emplace_back(new Spike2(c));
        c.x=13.f;
        c.y=7.f;
        c= c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        c.x=13.f;
        c.y=6.f;
        c= c*64.f;
        this->spikes.emplace_back(new Spike2(c));
        c.x=12.f;
        c.y=6.f;
        c= c*64.f;
        this->spikes.emplace_back(new Spike2(c));

        

        for(int j =0; j<10; j++){
            c.x=getRandomInt(11,13);
            c.y=getRandomInt(9,11);
            c = c*64.f;
            this->spikes.emplace_back(new Spike(c));
        }
        for(int j =0; j<10; j++){
            c.x=getRandomInt(11,13);
            c.y=getRandomInt(2,5);
            c = c*64.f;
            this->spikes.emplace_back(new Spike(c));
        }
        for(int j =0; j<20; j++){
            c.x=getRandomInt(14,21);
            c.y=getRandomInt(2,11);
            c = c*64.f;
            this->spikes.emplace_back(new Spike(c));
        }
        for(int j =0; j<20; j++){
            c.x=getRandomInt(3,10);
            c.y=getRandomInt(2,11);
            c = c*64.f;
            this->spikes.emplace_back(new Spike(c));
        }
        
        if(playerd!=nullptr){
            c.x=12.f;
        c.y=7.f;
        c= c*64.f;
        this->enemies.emplace_back(new Boss(sf::Vector2f(768.f,418.f),playerd));
        }
    }

};

int Room::getRandomInt(int min,int max){
    static std::random_device rd;  // Seed
    static std::mt19937 gen(rd()); // Mersenne Twister generator
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
};
void Room::setCleared(bool a){
    this->cleared=a;
}
bool Room::getCleared(){
    return this->cleared;
}

Room::~Room(){
    
    for(auto el:weapons){
        delete el;
    }
    for(auto el:loot){
        delete el;
    }
    for(auto el:enemies){
        delete el;
    }
    for(auto el:spikes){
        delete el;
    }
    
    
    delete texture;
    
    
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
    
    for (const auto& door : doors) {
        door->render(target);
    }
    
    for (const auto& wall : walls) {
        wall->render(target);
    }
    for (const auto& enemy : spikes) {
        enemy->render(target);
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
    
    for (const auto& enemy : enemies) {
        enemy->render(target);
    }

};




#endif