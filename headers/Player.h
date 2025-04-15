#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>


#include "Item.h"
#include "FirstWeapon.h"
#include "DmgEntity.h"

class Player: public DmgEntity{
    private:
    //clicking speed for E button
    const int clickSpeed = 10;
    //frame counter for E button might later be used for animations
    int counter;

    //player texture
    sf::RectangleShape shape;
    //movespeed
    float movespeed;
    //font
    sf::Font* font;
    //hp bar
    sf::Text* hpText;
    //state anum
    enum state{
        idle = 1,
        right = 2,
        left = 3,
        up = 4,
        down = 5,
    };
    state st;
    //texture
    const sf::Texture *texture = new sf::Texture("./Textures/Prototype_Character.png");
    //rectagnle that itarates over different frames of animations
    sf::IntRect * intrect;
    bool animChange;
    //clock for animation 
    sf::Clock clock;
public:
    Player();
    virtual ~Player();
    
    
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    void setFont(sf::Font* font);
    void initHp();
    void animation();
    void changeState(state st);

    
    void update();
    void move();
    void render(sf::RenderTarget* target);

    bool pressedE;
    
    

};

Player::Player(){
    //seting defaul parameters
    this->shape.setSize(sf::Vector2f(120.f, 120.f));
    this->movespeed = 10.f;
    this->pressedE = false;
    this->counter = 10;
    this->setHp(100);
    //setting hitbox size
    this->hitbox.setSize({40.f, 40.f});
    this->hitbox.setPosition({this->shape.getPosition().x+40.f, this->shape.getPosition().y+40.f});
    //setting up intrect and texture
    intrect = new sf::IntRect({0, 0}, {32, 32});
    this->shape.setTexture(texture);
    this->shape.setTextureRect(*intrect);
    //settomg defualt state
    this->st = idle;
}
//text class does not have and empty construcotr and it has to be creater after the font is set so 
//this spageti code fixes that 
void Player::initHp(){
    this->hpText = new sf::Text(*font);
    this->hpText->setString(std::to_string(this->getHp())+ " hp");
    this->hpText->setFillColor(sf::Color::White); //change later
    this->hpText->setCharacterSize(10);
    this->hpText->setPosition({this->shape.getPosition().x+60.f, this->shape.getPosition().y- 30.f});
}
Player::~Player(){

}
void Player::setPosition(sf::Vector2f pos){
    this->shape.setPosition(pos);
}
sf::Vector2f Player::getPosition(){
    return this->shape.getPosition();
}
void Player::move(){
    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            this->shape.move({0.f, -this->movespeed});
            
        }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            this->shape.move({0.f, this->movespeed});
            
        }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            this->shape.move({-this->movespeed, 0.f});
            
        }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            this->shape.move({this->movespeed, 0.f});
            
            
        }
        //changing state
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            
            changeState(left);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            changeState(right);
        } 
    
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            changeState(up);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            changeState(down);
        } 
        
        else{
            changeState(idle);
        }
    
    
    //update change weapon bool if E is pressed 
    //if change weapon bool is true then it allows player to swap weapons
    //press E to swap ewapons
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)&&counter >= this->clickSpeed)
    {
        this->pressedE = true;
        counter = 0;
    }else{
        this->pressedE = false;
    }
    
}

void Player::update(){
    //updates counter
    if(counter <60){
        this->counter ++;
    }
    
    //setting state as idle in case of no moving
    
    
    //mvoes and check for other actions
    this->move();

    //animating
    this->animation();

    //setting hitbox position to match player position
    this->hitbox.setPosition({this->shape.getPosition().x+40.f, this->shape.getPosition().y+40.f});

    //updating hp text box
    this->hpText->setPosition({this->shape.getPosition().x+50.f, this->shape.getPosition().y- 30.f});
    this->hpText->setString(std::to_string(this->getHp())+ " hp");
}
void Player::render(sf::RenderTarget* target){
    target->draw(this->shape);
    target->draw(*hpText);
    
}
void Player::setFont(sf::Font* font){
    this->font = font;
}
void Player::animation(){
    if(this->st == idle){
        if(animChange){
            shape.setTextureRect(*intrect);
        }
        else if(clock.getElapsedTime().asSeconds() > 0.5f){
            
            if(this->intrect->position.x == 32){
                this->intrect->position.x = 0;
            }else{
                this->intrect->position.x += 32;
            }
            shape.setTextureRect(*intrect);
            clock.restart();
        }
    }
    else if(this->st == right || this->st == up || this->st == down){
        if(animChange){
            shape.setTextureRect(*intrect);
        }
        else if(clock.getElapsedTime().asSeconds() > 0.15f){
            
            if(this->intrect->position.x == 96){
                this->intrect->position.x = 0;
            }else{
                this->intrect->position.x += 32;
            }
            shape.setTextureRect(*intrect);
            clock.restart();
        }
    }
    else if(this->st == left){
        if(animChange){
            shape.setTextureRect(*intrect);
        }
        else if(clock.getElapsedTime().asSeconds() > 0.15f){
            
            if(this->intrect->position.x == 128){
                this->intrect->position.x = 32;
            }else{
                this->intrect->position.x += 32;
            }
            shape.setTextureRect(*intrect);
            clock.restart();
        }
    }
}
void Player::changeState(state st){
    if(st != this->st){
        animChange = true;
        if(st == idle){
            this->intrect->size = {32, 32};
            this->intrect->position = {0, 0};
            
            this->st = idle;
        }else if(st == right){
            this->intrect->size = {32, 32};
            this->intrect->position = {0, 128};
            
            this->st = right;
        }else if(st == left){
            this->intrect->size = {-32, 32};
            this->intrect->position = {32, 128};
            
            this->st = left;
        }else if(st == up){
            this->intrect->size = {32, 32};
            this->intrect->position = {0, 160};
            
            this->st = up;
        }else if(st == down){
            this->intrect->size = {32, 32};
            this->intrect->position = {0, 96};
            
            this->st = down;
        }
    }else{
        animChange = 0;
    }
}


#endif