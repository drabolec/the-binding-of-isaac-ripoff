#ifndef ITEM_H
#define ITEM_H


#include "Entity.h"
#include "Bullet.h"

class Item: public Entity{
    public:
        Item();
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
};
Item::Item(){

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

}
#endif