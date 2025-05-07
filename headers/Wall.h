#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall:public Entity{
    public:
        Wall();
        virtual ~Wall();

    private:
        sf::RectangleShape shape;

};

Wall::Wall(){
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setSize(sf::Vector2f(200.f, 200.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));

};


Wall::~Wall(){
};


#endif