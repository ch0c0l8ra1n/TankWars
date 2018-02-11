//
//  player.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "player.hpp"

Player::Player(sf::IpAddress IP , unsigned short port, sf::Texture& texture, sf::RenderWindow& win):playerTank(&texture){
    playerIP = IP;
    playerPort = port;
    window = &win;
}

Player::~Player(){}

void Player::draw(){
    playerTank.draw(*window);
}
