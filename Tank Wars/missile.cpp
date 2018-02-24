//
//  missile.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 1/28/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "missile.hpp"

Missile::Missile( Player* player, sf::Texture& texture):originPlayer(player){
    velocityScalar = 500.0f;
    body.setTexture(&texture);
    body.setRadius(10.0f);
    body.setOrigin(5.0f, 5.0f);
    body.setPosition(player->playerTank.getPosition());
    orientation = player->playerTank.getTurretOrientation();
    unitVector.x = -sin(orientation*PI/180);
    unitVector.y = cos(orientation*PI/180);
    velocity.x = velocityScalar * unitVector.x;
    velocity.y = velocityScalar * unitVector.y;
    body.move(velocity/7.0f);
    creationTime = getMs();
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

bool Missile::isExpired(long long dTime){
    return dTime>creationTime + 2000;
}

sf::Vector2f Missile::getPosition(){
    return body.getPosition();
}

Player* Missile::getPlayer(){
    return originPlayer;
}


