//
//  missile.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 1/28/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "missile.hpp"

Missile::Missile( sf::Texture * texture , sf::Vector2f velocity){
    this->velocity = velocity;
    body.setTexture(texture);
    body.setPosition(512, 512);
    body.setSize(sf::Vector2f(10,100));
}

Missile::~Missile(){}

void Missile::update(float deltaTime){
    sf::Vector2f movement;
    movement.x = velocity.x * deltaTime;
    movement.y = velocity.y * deltaTime;
    body.move(movement);
}

void Missile::draw(sf::RenderWindow& window){
    window.draw(body);
}

