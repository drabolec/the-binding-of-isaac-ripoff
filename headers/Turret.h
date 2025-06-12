#ifndef TURRET_H
#define TURRET_H

#include "Enemy.h"
#include "Bullet.h"
#include "RoundBullet.h"

class Turret:public Enemy{
    public:
        Turret();
        Turret(sf::Vector2f pos);
        virtual ~Turret();
        void move(sf::Vector2f pos);
        void update(sf::Vector2f pos);
        void shoot(sf::Vector2f direction);
        void setCurrentEnemyBullets(std::vector<Bullet*> vec);
        std::vector<Bullet*> getCurrentEnemyBullet();
        void animate();
        void initBlinkFrames();
        void render(sf::RenderTarget* traget);
    private:    
        float Random;
        int newx,newy;
        int counter=0;
        bool state=0;
        std::vector<Bullet*> enemyBullets;
        Bullet* bullet;
        sf::Clock clock;
        std::vector<sf::IntRect*> frames;
        sf::RectangleShape blink;
        sf::Texture* blinkTex;
        std::vector<sf::IntRect*> blinkFrames;
        sf::Clock blinkClock;
        int blinkFrame;
        int frame;
};

Turret::Turret(){};

Turret::Turret(sf::Vector2f pos){
    //blink frames
    this->blinkFrame = 0;
    this->blink.setSize({100.f, 100.f});
    this->blinkTex = new sf::Texture("./Textures/mageblink.png");
    this->blink.setTexture(this->blinkTex);
    this->initBlinkFrames();
    this->blink.setTextureRect(*(this->blinkFrames.at(this->blinkFrame)));
    //frames
    this->frame = 0;
    this->frames.emplace_back(new sf::IntRect({368, 230},{16, 16}));
    this->frames.emplace_back(new sf::IntRect({384, 230},{16, 16}));
    this->frames.emplace_back(new sf::IntRect({400, 230},{16, 16}));
    this->frames.emplace_back(new sf::IntRect({416, 230},{16, 16}));
    this->setHp(20.f);
    this->setDmg(20.f);
    this->setHitboxSize({64.f, 64.f});
    this->setShapeSize({64.f, 64.f});
    this->setPosition(pos);
    this->bullet = new RoundBullet();
    //texture
    this->texture = new sf::Texture("./Textures/all.png");
    this->shape.setTexture(this->texture);
    this->shape.setTextureRect(*(this->frames.at(this->frame)));
};

Turret::~Turret(){
    delete this->texture;
    delete this->blinkTex;
    for(auto el:this->blinkFrames){
        delete el;
    }
    for(auto el:this->frames){
        delete el;
    }
};


void Turret::update(sf::Vector2f pos){
    this->animate();
    this->blink.setPosition({this->shape.getPosition().x + this->shape.getSize().x/2-blink.getSize().x/2, this->shape.getPosition().y + this->shape.getSize().y/2-blink.getSize().y/2});
    counter++;
    if(counter>90){
        counter=0;
    }
    if(counter==0){
        if(state){
            state=false;
        }
        else{
            state=true;
        }
    }
};

void Turret::move(sf::Vector2f pos){

    Random = getRandomInt(200, 1400);
    newx=Random;
    Random = getRandomInt(200, 700);
    newy=Random;

    if(state){
        this->change_can_be_hit(true);
    }
    else{
        this->change_can_be_hit(false);
        //this->setColor(sf::Color::Red);
        if(counter==0){
        this->setPosition(sf::Vector2f(newx,newy));
        }

        if(counter==30){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }
        if(counter==45){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }      
        if(counter==60){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }
        if(counter==75){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }
        if(counter==90){
        this->shoot({1.f, 0.f});
        this->shoot({0.f, 1.f});
        this->shoot({-1.f, 0.f});
        this->shoot({0.f, -1.f});
        }
    }

};

void Turret::shoot(sf::Vector2f direction){
    
        Bullet* bullet;
        if(dynamic_cast<RoundBullet*>(this->bullet)!=NULL){
            bullet = new RoundBullet;
        }
        bullet->shape.setFillColor(sf::Color::Blue);
        bullet->direction = direction;
        //masterpiece
        bullet->initPos = {this->getPosition().x + this->shape.getSize().x/2-bullet->shape.getSize().x/2, this->getPosition().y+ this->shape.getSize().y/2-bullet->shape.getSize().y/2};
        bullet->setInitPos();
        this->enemyBullets.emplace_back(bullet);
    
}
void Turret::setCurrentEnemyBullets(std::vector<Bullet*> vec){
    this->enemyBullets = vec;
}
std::vector<Bullet*> Turret::getCurrentEnemyBullet(){
    return this->enemyBullets;
}
void Turret::animate(){
    if(this->clock.getElapsedTime().asSeconds() > 0.3f){
        this->clock.restart();
        this->shape.setTextureRect(*(this->frames.at(this->frame)));
        this->frame ++;
        if(this->frame >= 4){
            this->frame = 0;
        }
        //this->setColor(sf::Color::Green);
    }
    if(state){
        this->shape.setFillColor(sf::Color::White);
    }
    else{
        this->shape.setFillColor(sf::Color(92, 92, 255, 255));
    }
    if(counter<=50){
        this->blinkFrame = 0;
    }
    else if(counter > 50){
        if(this->blinkClock.getElapsedTime().asSeconds() > 0.04f){
            this->blinkClock.restart();
            this->blink.setTextureRect(*(this->blinkFrames.at(this->blinkFrame)));
            this->blinkFrame ++;
            if(this->blinkFrame >= this->blinkFrames.size()){
                this->blinkFrame = 0;
            }
        }
    }
}
void Turret::initBlinkFrames(){
    for(int i = 0; i < 1000; i = i + 100){
        for(int j = 0; j < 800; j = j + 100){
            this->blinkFrames.emplace_back(new sf::IntRect({i, j},{100, 100}));
        }
    }
}
void Turret::render(sf::RenderTarget* target){
    target->draw(this->shape);
    if(counter > 50){
        target->draw(this->blink);
    }
}

#endif