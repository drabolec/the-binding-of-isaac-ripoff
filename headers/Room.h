#ifndef ROOM_H
#define ROOM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Enemy.h"
#include "Door.h"
#include "Wall.h"

class Room{
    public:
        Room();
        Room(int a);
        virtual ~Room();
        void render(sf::RenderTarget* target);

    private:
        int isActive;
        int type_id;
        sf::RectangleShape shape;
        vector<Enemy> enemies;
        vector<Door> doors;
        vector<Wall> walls;

}

Room::Room(){
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(200.f, 200.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));
}
Room::Room(int a){
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(200.f, 200.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));
    this->type_id=a;
    if(type_id==1){
        Door rightDoor(2);
    }
    if(type_id==2){
        Door leftDoor(1);
        Door rightDoor(2);
        Door upDoor(3);
        Door downDoor(4);
        Enemy Zombie1;
        Enemy Zombie2;
        Zombie1.setPosition(sf::Vector2f(140.f, 40.f))
        Zombie2.setPosition(sf::Vector2f(140.f, 140.f))
    }
}



Room::~Room(){

}

void Room::update(sf::RenderTarget* target){
    for(Enemy : enemies){
        if()
    }

}

void Room::render(sf::RenderTarget* target){
    target->draw(this->shape);
}



#endif