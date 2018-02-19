//
//  missile.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 1/28/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "missile.hpp"

Missile::Missile( Player& player, sf::Texture& texture):originPlayer(&player){
    velocity = sf::Vector2f(100.0f,0.0f);
    body.setTexture(&texture);
    //body.setFillColor(sf::Color(0,0,0));
    body.setRadius(10.0f);
    body.setPosition(512.0f, 512.0f);
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

