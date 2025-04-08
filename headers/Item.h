#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>



class Item{
    public:
        Item();
        virtual void shoot()=0;
        virtual void update(sf::Vector2f pos)=0;
        virtual void render(sf::RenderTarget* target)=0;
};
Item::Item(){

}

#endif