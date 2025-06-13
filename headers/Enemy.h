#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "DmgEntity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

class Enemy:public DmgEntity{
    public:
        Enemy();
        virtual ~Enemy();
        virtual void move(sf::Vector2f pos);
        virtual void update(sf::Vector2f pos);
        virtual void render(sf::RenderTarget* target);
        virtual bool getIsDead();
        virtual void setCollided(bool a);
        virtual bool getCollided();
        virtual void setColor(sf::Color color);
        virtual void setHitboxSize(sf::Vector2f size);
        virtual void setShapeSize(sf::Vector2f size);
        virtual void setPosition(sf::Vector2f pos);
        virtual void setPosition(float a,float b);
        virtual void change_can_be_hit(bool a);
        virtual bool get_can_be_hit();
        virtual sf::Vector2f getPosition();
        virtual int getState();
        virtual sf::Vector2f getHitbox();
        virtual void setCurrentEnemyBullets(std::vector<Bullet*> vec);
        virtual std::vector<Bullet*> getCurrentEnemyBullet();
        virtual sf::RectangleShape& getShape();
    private:    
        int hp;
        bool collided=false;
        bool isDead;
        bool can_be_hit=true;
        float movespeed;
        //sf::RectangleShape shape; //nie potrzben ejuz jest e entity
        
        
};
int Enemy::getState(){
    return 0;
};
sf::RectangleShape& Enemy::getShape(){
    return this->shape;
}
Enemy::Enemy(){
    //this->shape.setFillColor(sf::Color::Red);  //temporary
    //this->shape.setSize(sf::Vector2f(10.f, 10.f));
    //this->hitbox.setSize(sf::Vector2f(10.f, 10.f));
    this->movespeed = 1.f;
};
Enemy::~Enemy(){
};
void Enemy::setPosition(sf::Vector2f pos){
    this->shape.setPosition(pos);
    this->hitbox.setPosition(pos);//for now
}
void Enemy::setHitboxSize(sf::Vector2f size){
    this->hitbox.setSize(size);
}
void Enemy::setShapeSize(sf::Vector2f size){
    this->shape.setSize(size);
}
void Enemy::setColor(sf::Color color){
    this->shape.setFillColor(color);
}
void Enemy::setCollided(bool a){
    this->collided=a;
}
bool Enemy::getCollided(){
    return this->collided;
}
void Enemy::setPosition(float a,float b){
    sf::Vector2f c;
    c.x=a;
    c.y=b;
    this->shape.setPosition(c);
    this->hitbox.setPosition(c);//for now
}

void Enemy::change_can_be_hit(bool a){
    this->can_be_hit=a;
}

bool Enemy::get_can_be_hit(){
    return this->can_be_hit;
}
sf::Vector2f Enemy::getPosition(){
    return this->shape.getPosition();
}
sf::Vector2f Enemy::getHitbox(){
    return this->hitbox.getPosition();
}



void Enemy::move(sf::Vector2f pos){ //temporary
    
};

void Enemy::update(sf::Vector2f pos){
    //this->move(sf::Vector2f pos);
    //if(this->hp<=0){
    //    this->isDead=true;
    //}
};
void Enemy::render(sf::RenderTarget* target){
    target->draw(this->shape);
};

bool Enemy::getIsDead(){
    return this->isDead;
}
void Enemy::setCurrentEnemyBullets(std::vector<Bullet*> vec){}
std::vector<Bullet*> Enemy::getCurrentEnemyBullet(){
    std::vector<Bullet*> temp;
    return temp;
}

#endif