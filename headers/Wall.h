#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall:public Entity{
    public:
        Wall();
        virtual ~Wall();
        Wall(int b);
        void render(sf::RenderTarget* target);
        sf::Texture* uptex;
    private:
    int wallSide; // NE - 1 wzgledem zegara
};

void Wall::render(sf::RenderTarget* target){

    target->draw(this->hitbox);

};

Wall::Wall(){
    this->hitbox.setFillColor(sf::Color::Black);
    this->hitbox.setSize(sf::Vector2f(200.f, 200.f));
    this->hitbox.setPosition(sf::Vector2f(0.f, 0.f));

};
inline Wall::Wall(int b){
    
    //this->hitbox.setFillColor(sf::Color::Blue);
    this->texture = new sf::Texture("./Textures/wall.png");
    this->uptex = new sf::Texture("./Textures/wallup.png");
    this->texture->setRepeated(true);
    this->uptex->setRepeated(true);
    this->wallSide=b;
    if(this->wallSide==1){
        this->hitbox.setPosition(sf::Vector2f(832.f, 0.f));
        this->hitbox.setSize(sf::Vector2f(704.f, 64.f));
        
        
        this->hitbox.setTexture(this->uptex);
        this->hitbox.setTextureRect(*(new sf::IntRect({0, 0},{176, 16})));
    }
    else if(this->wallSide==2){
        this->hitbox.setPosition(sf::Vector2f(1536.f, 0.f));
        this->hitbox.setSize(sf::Vector2f(64.f, 418.f));
        this->hitbox.setTexture(this->texture);
        this->hitbox.setTextureRect(*(new sf::IntRect({16, 0},{-16, 104})));
    }
    else if(this->wallSide==3){
        this->hitbox.setPosition(sf::Vector2f(1536.f, 482.f));
        this->hitbox.setSize(sf::Vector2f(64.f, 418.f));
        this->hitbox.setTexture(this->texture);
        this->hitbox.setTextureRect(*(new sf::IntRect({16, 0},{-16, 104})));
    }
    else if(this->wallSide==4){
        this->hitbox.setPosition(sf::Vector2f(832.f, 836.f));
        this->hitbox.setSize(sf::Vector2f(704.f, 64.f));
        this->hitbox.setTexture(this->uptex);
        this->hitbox.setTextureRect(*(new sf::IntRect({0, 16},{176, -16})));
    }
    else if(this->wallSide==5){
        this->hitbox.setPosition(sf::Vector2f(64.f, 832.f));
        this->hitbox.setSize(sf::Vector2f(704.f, 64.f));
        this->hitbox.setTexture(this->uptex);
        this->hitbox.setTextureRect(*(new sf::IntRect({0, 16},{176, -16})));
    }
    else if(this->wallSide==6){
        this->hitbox.setPosition(sf::Vector2f(0.f, 0.f));
        this->hitbox.setSize(sf::Vector2f(64.f, 418.f));
        this->hitbox.setTexture(this->texture);
        this->hitbox.setTextureRect(*(new sf::IntRect({0, 0},{16, 104})));
        
    }
    else if(this->wallSide==7){
        this->hitbox.setPosition(sf::Vector2f(0.f, 482.f));
        this->hitbox.setSize(sf::Vector2f(64.f, 418.f));
        this->hitbox.setTexture(this->texture);
        this->hitbox.setTextureRect(*(new sf::IntRect({0, 0},{16, 104})));
    }
    else if(this->wallSide==8){
        this->hitbox.setPosition(sf::Vector2f(64.f, 0.f));
        this->hitbox.setSize(sf::Vector2f(704.f, 64.f));
        this->hitbox.setTexture(this->uptex);
        this->hitbox.setTextureRect(*(new sf::IntRect({0, 0},{176, 16})));
    }

    else if(this->wallSide==9){
        this->hitbox.setPosition(sf::Vector2f(0.f, 418.f));
        this->hitbox.setSize(sf::Vector2f(64.f, 64.f));
        this->hitbox.setTexture(this->texture);
        this->hitbox.setTextureRect(*(new sf::IntRect({0, 0},{16, 16})));
    }

    else if(this->wallSide==10){
        this->hitbox.setPosition(sf::Vector2f(1536.f, 418.f));
        this->hitbox.setSize(sf::Vector2f(64.f, 64.f));
        this->hitbox.setTexture(this->texture);
        this->hitbox.setTextureRect(*(new sf::IntRect({16, 0},{-16, 16})));
    }
    else if(this->wallSide==11){
        this->hitbox.setPosition(sf::Vector2f(768.f, 0.f));
        this->hitbox.setSize(sf::Vector2f(64.f, 64.f));
        this->hitbox.setTexture(this->uptex);
        this->hitbox.setTextureRect(*(new sf::IntRect({0, 0},{16, 16})));
    }

    else if(this->wallSide==12){
        this->hitbox.setPosition(sf::Vector2f(768.f, 836.f));
        this->hitbox.setSize(sf::Vector2f(64.f, 64.f));
        this->hitbox.setTexture(this->uptex);
        this->hitbox.setTextureRect(*(new sf::IntRect({0, 16},{16, -16})));
    }





};

Wall::~Wall(){
    delete this->texture;
    delete this->uptex;
};


#endif