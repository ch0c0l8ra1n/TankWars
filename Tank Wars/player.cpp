//
//  player.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "player.hpp"

Player::Player(uint64_t hash,sf::IpAddress IP , unsigned short port, sf::Texture& texture, char* name, sf::RenderWindow& win, MissileManager * mManager, sf::Texture* baseTexture):playerTank(&texture, mManager, baseTexture){
    playerTank.setName(std::string(name));
    playerIP = IP;
    playerPort = port;
    this->hash = hash;
    strcpy(this->name, name);
    window = &win;
    kills = 0;
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

char* Player::getName(){
    return name;
}

int Player::getKills(){
    return kills;
}

void Player::addKill(){
    kills++;
}


