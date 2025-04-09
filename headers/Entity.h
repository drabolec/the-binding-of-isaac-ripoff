#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

class Entity{
public:
    //hitbox should be set in every entity whichc we want to be able to colide
    sf::RectangleShape hitbox;
    virtual void update();
    virtual void render(sf::RenderTarget* target);
};
void Entity::update(){

}
void Entity::render(sf::RenderTarget* target){
    
}


#endif