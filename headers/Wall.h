#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall:public Entity{
    public:
        Wall();
        virtual ~Wall();
        Wall(int b);
        void render(sf::RenderTarget* target);
    private:
    int wallSide; // NE - 1 wzgledem zegara
        sf::RectangleShape shape;

};

void Wall::render(sf::RenderTarget* target){

    target->draw(this->shape);

};

Wall::Wall(){
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setSize(sf::Vector2f(200.f, 200.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));

};
inline Wall::Wall(int b){
    this->shape.setFillColor(sf::Color::Blue);
    this->wallSide=b;
    if(this->wallSide==1){
        this->shape.setPosition(sf::Vector2f(850.f, 0.f));
        this->shape.setSize(sf::Vector2f(750.f, 100.f));
    }
    else if(this->wallSide==2){
        this->shape.setPosition(sf::Vector2f(1500.f, 100.f));
        this->shape.setSize(sf::Vector2f(100.f, 300.f));
    }
    else if(this->wallSide==3){
        this->shape.setPosition(sf::Vector2f(1500.f, 500.f));
        this->shape.setSize(sf::Vector2f(100.f, 300.f));
    }
    else if(this->wallSide==4){
        this->shape.setPosition(sf::Vector2f(850.f, 800.f));
        this->shape.setSize(sf::Vector2f(750.f, 100.f));
    }
    else if(this->wallSide==5){
        this->shape.setPosition(sf::Vector2f(0.f, 800.f));
        this->shape.setSize(sf::Vector2f(750.f, 100.f));
    }
    else if(this->wallSide==6){
        this->shape.setPosition(sf::Vector2f(0.f, 100.f));
        this->shape.setSize(sf::Vector2f(100.f, 300.f));
    }
    else if(this->wallSide==7){
        this->shape.setPosition(sf::Vector2f(0.f, 500.f));
        this->shape.setSize(sf::Vector2f(100.f, 300.f));
    }
    else if(this->wallSide==8){
        this->shape.setPosition(sf::Vector2f(0.f, 0.f));
        this->shape.setSize(sf::Vector2f(750.f, 100.f));
    }

};

Wall::~Wall(){
};


#endif