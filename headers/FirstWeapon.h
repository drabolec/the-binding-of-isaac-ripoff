#ifndef FIRSTWEAPON_H
#define FIRSTWEAPON_H
#include "Item.h"
#include "cmath"

class FirstWeapon: public Item{
    public:
        void shoot();
        void update(sf::Vector2f pos);
        void render(sf::RenderTarget* target);
        FirstWeapon();
    private:
        sf::RectangleShape shape;
    
};
FirstWeapon::FirstWeapon(){
    shape.setFillColor(sf::Color::Red);
    shape.setSize({10.f, 5.f});
}
void FirstWeapon::update(sf::Vector2f pos){
    this->shape.setPosition({pos.x-5.f, pos.y});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        //shooting
        
        
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        
    }
}
void FirstWeapon::render(sf::RenderTarget* target){
    target->draw(this->shape);
}
void FirstWeapon::shoot(){

}

#endif