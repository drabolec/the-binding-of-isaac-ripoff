#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <random>

class Entity{
public:
    //hitbox should be set in every entity whichc we want to be able to colide
    sf::RectangleShape hitbox;
    sf::RectangleShape shape;
    sf::Texture* texture;
    sf::IntRect *intrect;
    virtual void update();
    virtual void render(sf::RenderTarget* target);
    virtual int getRandomInt(int min, int max);
    virtual ~Entity();
    
};
Entity::~Entity(){
    
    
}
void Entity::update(){

}
void Entity::render(sf::RenderTarget* target){
    
}
int Entity::getRandomInt(int min,int max){
    static std::random_device rd;  // Seed
    static std::mt19937 gen(rd()); // Mersenne Twister generator
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
};

#endif