#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


class Wall:public Entity{
    public:
        Wall();
        virtual ~Wall();

    private:

}
Door::Door(){
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(200.f, 200.f));
    this->shape.setPosition(sf::Vector2f(0.f, 0.f));
}




#endif