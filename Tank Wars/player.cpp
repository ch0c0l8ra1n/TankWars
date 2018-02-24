//
//  player.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "player.hpp"

Player::Player(uint64_t hash,sf::IpAddress IP , unsigned short port, sf::Texture& texture, sf::RenderWindow& win, MissileManager * mManager):playerTank(&texture, mManager){
    playerIP = IP;
    playerPort = port;
    this->hash = hash;
    window = &win;
}

Player::~Player(){}

void Player::draw(){
    playerTank.draw(*window);
}

sf::IpAddress Player::getIP(){
    return playerIP;
}

uint64_t Player::getHash(){
    return hash;
}

void Player::setPressedButtons(bool *buttons){
    playerTank.setPressedButtons(buttons);
}

bool Player::isAlive(){
    return playerTank.isAlive();
}


