#ifndef DOOR_H
#define DOOR_H


#include "Entity.h"

class Door:public Entity{
    public:
        Door();
        Door(int b);
        virtual ~Door();

    private:
        int doorSide;
        sf::RectangleShape shape;
};

inline Door::Door(){
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(200.f, 200.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));
};

inline Door::Door(int b){
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setSize(sf::Vector2f(20.f, 20.f));
    this->doorSide=b;
    if(this->doorSide==1){
        this->shape.setPosition(sf::Vector2f(0.f, 90.f));
    }
    else if(this->doorSide==2){
        this->shape.setPosition(sf::Vector2f(180.f, 90.f));
    }
    else if(this->doorSide==3){
        this->shape.setPosition(sf::Vector2f(90.f, 0.f));
    }
    else if(this->doorSide==4){
        this->shape.setPosition(sf::Vector2f(90.f, 180.f));
    }
};



inline Door::~Door(){

};



#endif