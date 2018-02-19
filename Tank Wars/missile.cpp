//
//  missile.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 1/28/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "missile.hpp"

Missile::Missile(sf::Vector2f velocity, Player player):originPlayer(player){
    this->velocity = velocity;
    texture.loadFromFile(resourcePath() + "fireball.png");
    body.setTexture(&texture);
    body.setPosition(512, 512);
    body.setRadius(10.0f);
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

