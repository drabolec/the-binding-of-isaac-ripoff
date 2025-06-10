#ifndef DOOR_H
#define DOOR_H


#include "Entity.h"

class Door:public Entity{
    public:
        Door();
        Door(int b);
        virtual ~Door();
        void render(sf::RenderTarget* target);
        int getDoorSide();
    private:
        int doorSide;
        sf::RectangleShape shape;
};

int Door::getDoorSide(){
    return doorSide;
}

inline Door::Door(){
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setSize(sf::Vector2f(200.f, 200.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));
};

inline Door::Door(int b){
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setSize(sf::Vector2f(64.f, 64.f));
    this->doorSide=b;
    if(this->doorSide==1){
        this->shape.setPosition(sf::Vector2f(0.f, 418.f));
    }
    else if(this->doorSide==2){
        this->shape.setPosition(sf::Vector2f(1536.f, 418.f));
    }
    else if(this->doorSide==3){
        this->shape.setPosition(sf::Vector2f(768.f, 0.f));
    }
    else if(this->doorSide==4){
        this->shape.setPosition(sf::Vector2f(768.f, 836.f));
    }
};

void Door::render(sf::RenderTarget* target){

    target->draw(this->shape);

}

inline Door::~Door(){

};



#endif