#ifndef ITEM_H
#define ITEM_H


#include "Entity.h"
#include "Bullet.h"
#include "RoundBullet.h"
#include "FastBullet.h"

class Item: public Entity{
    public:
        Item();
        virtual ~Item();
        virtual void shoot(sf::Vector2f direction);
        virtual void setCurrentBullet(Bullet* bullet);
        virtual Bullet* getCuurentBullet();
        Bullet* bullet;
        sf::Vector2f playerPos;
        virtual void setPlayerPos(sf::Vector2f pos);
        virtual void setCurrentPlayerBullets(std::vector<Bullet*> playerBullets);
        virtual std::vector<Bullet*> getCurrentPlayerBullets();
        std::vector<Bullet*> playerBullets;
        void update();
        virtual void updatePos(sf::Vector2f pos);
        void render(sf::RenderTarget* target);
        sf::Clock clock;

        sf::SoundBuffer* shootBuffer;
        sf::Sound* shootSound;

};
Item::~Item(){
    delete this->shootBuffer;
    delete this->shootSound;
}
Item::Item(){
    this->shootBuffer = new sf::SoundBuffer("./Sound/shoot.mp3");
    this->shootSound = new sf::Sound(*(this->shootBuffer));
    this->shootSound->setVolume(2.f);
}
void Item::update(){

}
void Item::render(sf::RenderTarget* target){

}
void Item::updatePos(sf::Vector2f pos){

}
void Item::setCurrentBullet(Bullet* bullet){
    this->bullet = bullet;
}
void Item::setCurrentPlayerBullets(std::vector<Bullet*> playerBullets){
    this->playerBullets = playerBullets;
}
std::vector<Bullet*> Item::getCurrentPlayerBullets(){
    return this->playerBullets;
}
Bullet* Item::getCuurentBullet(){
    return this->bullet;
}
void Item::setPlayerPos(sf::Vector2f pos){
    this->playerPos = pos;
}
void Item::shoot(sf::Vector2f direction){
    
        Bullet* bullet;
        if(dynamic_cast<RoundBullet*>(this->bullet)!=NULL){
            bullet = new RoundBullet;
        }else if(dynamic_cast<FastBullet*>(this->bullet)!=NULL){
            bullet = new FastBullet;
        }
        this->shootSound->play();
        bullet->direction = direction;
        bullet->initPos = this->playerPos;
        bullet->setInitPos();
        this->playerBullets.emplace_back(bullet);
    
}
#endif