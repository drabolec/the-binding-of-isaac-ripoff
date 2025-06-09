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
    int counterTargetability=0;
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
        idleright = 6,
        idleleft = 7,
        idleup = 8
    };
    sf::Vector2f nextMove;
    state st;
    bool animChange;
    //clock for animation 
    sf::Clock clock;
    sf::Vector2f originalPos;
    bool targetable = true;
public:
    Player();
    virtual ~Player();
    void setCollides(bool a);
void setCollidesUp(bool a);
void setCollidesDown(bool a);
void setCollidesRight(bool a);
void setCollidesLeft(bool a);
    void setHitWallNS(int a);
    void setHitWallWE(int a);
    void setPosition(sf::Vector2f pos);
    void setTargetable(bool a);
    bool getTargetable();
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    void setFont(sf::Font* font);
    void initHp();
    void animation();
    void changeState(state st);
    state getState();
    void preUpdate();
    void update();
    void move();
    void render(sf::RenderTarget* target);
    void resetCollisions();
    bool pressedE;
    bool collides;
    bool collidesUp = false;
    bool collidesDown = false;
    bool collidesLeft = false;
    bool collidesRight = false;
 
};
void Player::resetCollisions() {
    this->collidesUp = this->collidesDown = this->collidesLeft = this->collidesRight = false;
}
void Player::setCollides(bool a){
    this->collides=a;
}

void Player::setCollidesUp(bool a){
    this->collidesUp=a;
}

void Player::setCollidesDown(bool a){
    this->collidesDown=a;
}

void Player::setCollidesLeft(bool a){
    this->collidesLeft=a;
}

void Player::setCollidesRight(bool a){
    this->collidesRight=a;
}

void Player::setTargetable(bool a){
    this->targetable=a;
}
bool Player::getTargetable(){
    return this->targetable;
}

Player::state Player::getState(){
    return st;
}

Player::Player(){
    //seting defaul parameters
    this->movespeed = 7.f;
    this->pressedE = false;
    this->counter = 10;
    this->setHp(100);
    //setting hitbox size
    this->hitbox.setSize({40.f, 40.f});
    this->hitbox.setPosition({this->shape.getPosition().x+40.f, this->shape.getPosition().y+40.f});
    //setting up intrect and texture
    this->intrect = new sf::IntRect({0, 0}, {32, 32});
    //setting tecture
    this->texture = new sf::Texture("./Textures/Prototype_Character.png");
    //shape
    this->shape.setSize(sf::Vector2f(120.f, 120.f));
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
    this->hpText->setCharacterSize(20);
    this->hpText->setPosition({this->shape.getPosition().x+60.f, this->shape.getPosition().y- 30.f});
}
Player::~Player(){

}
void Player::setPosition(sf::Vector2f pos){
    this->shape.setPosition(pos);
    this->hitbox.setPosition({this->shape.getPosition().x+40.f, this->shape.getPosition().y+40.f});
}



sf::Vector2f Player::getPosition(){
    return this->shape.getPosition();
}
sf::Vector2f Player::getSize(){
    return this->shape.getSize();
}
void Player::move(){
    nextMove = sf::Vector2f(0.f, 0.f);
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !this->collidesUp) {
                nextMove.y -= this->movespeed;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !this->collidesDown) {
                nextMove.y += this->movespeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !this->collidesLeft) {
                nextMove.x -= this->movespeed;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !this->collidesRight) {
                nextMove.x += this->movespeed;
            }
        
        //changing state
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) )
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
            
            if(this->st == right){
                changeState(idleright);
            }else if(this->st == left){
                changeState(idleleft);
            }else if(this->st == up){
                changeState(idleup);
            }else if(this->st == down){
                changeState(idle);
            }else{
                this->animChange=0;
            }
            
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

void Player::preUpdate(){
    this->originalPos = this->shape.getPosition();
    this->shape.setPosition(originalPos + nextMove);
}


void Player::update(){
    //updates counter
    if(counter <60){
        this->counter ++;
    }
    if(counterTargetability<60&&targetable==false){
        this->counterTargetability ++;
    }
    else{
        this->targetable=true;
        this->counterTargetability=0;
    }
    //setting state as idle in case of no moving
    
    
    //mvoes and check for other actions
    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->collidesUp){
        this->shape.setPosition(originalPos);  // Don't allow the move
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->collidesDown){
        this->shape.setPosition(originalPos);  // Don't allow the move
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->collidesRight){
        this->shape.setPosition(originalPos);  // Don't allow the move
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->collidesLeft){
        this->shape.setPosition(originalPos);  // Don't allow the move
    }*/
    //animating
    this->animation();

    //setting hitbox position to match player position
    this->hitbox.setPosition({this->shape.getPosition().x+40.f, this->shape.getPosition().y+40.f});

    //updating hp text box
    this->hpText->setPosition({this->shape.getPosition().x+45.f, this->shape.getPosition().y- 15.f});
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
    if(this->st == idle || this->st == idleright || this->st == idleup){
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
    }else if(this->st == idleleft){
        if(animChange){
            shape.setTextureRect(*intrect);
        }
        else if(clock.getElapsedTime().asSeconds() > 0.5f){
            
            if(this->intrect->position.x == 64){
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
        }else if(st == idleright){
            this->intrect->size = {32, 32};
            this->intrect->position = {0, 32};
            this->st = idleright;
        }else if(st == idleleft){
            this->intrect->size = {-32, 32};
            this->intrect->position = {32, 32};
            this->st = idleleft;
        }else if(st == idleup){
            this->intrect->size = {32, 32};
            this->intrect->position = {0, 64};
            this->st = idleup;
        }
    }else{
        animChange = 0;
    }
}


#endif