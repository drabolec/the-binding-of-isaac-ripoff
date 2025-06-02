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
        void move(sf::Vector2f pos);
        virtual void update(sf::RenderTarget* target);
        virtual void render(sf::RenderTarget* target);
        virtual bool getIsDead();
        virtual void setColor(sf::Color color);
        virtual void setHitboxSize(sf::Vector2f size);
        virtual void setShapeSize(sf::Vector2f size);
        virtual void setPosition(sf::Vector2f pos);
        virtual void setPosition(float a,float b);
        virtual sf::Vector2f getPosition();
        virtual sf::Vector2f getHitbox();
    private:    
        int hp;
        bool isDead;
        float movespeed;
        sf::RectangleShape shape;
        
};

Enemy::Enemy(){
    this->shape.setFillColor(sf::Color::Red);  //temporary
    this->shape.setSize(sf::Vector2f(10.f, 10.f));
    this->hitbox.setSize(sf::Vector2f(10.f, 10.f));
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

void Enemy::setPosition(float a,float b){
    sf::Vector2f c;
    c.x=a;
    c.y=b;
    this->shape.setPosition(c);
    this->hitbox.setPosition(c);//for now
}


sf::Vector2f Enemy::getPosition(){
    return this->shape.getPosition();
}
sf::Vector2f Enemy::getHitbox(){
    return this->hitbox.getPosition();
}

void Enemy::move(sf::Vector2f pos){ //temporary
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
    {
        this->shape.move({0.f, -this->movespeed});
        this->hitbox.move({0.f, -this->movespeed});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
    {
        this->shape.move({0.f, this->movespeed});
        this->hitbox.move({0.f, this->movespeed});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    {
        this->shape.move({-this->movespeed, 0.f});
        this->hitbox.move({-this->movespeed, 0.f});
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
    {
        this->shape.move({this->movespeed, 0.f});
        this->hitbox.move({this->movespeed, 0.f});
    }
};

void Enemy::update(sf::RenderTarget* target){
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

#endif