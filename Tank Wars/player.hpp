//
//  player.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#pragma once

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <SFML/Network.hpp>
#include "tank.hpp"
#include <SFML/Graphics.hpp>


class Player{
private:
    sf::IpAddress playerIP;
    unsigned short playerPort;
    sf::RenderWindow* window;
    uint64_t hash;
    char name[20];
    
public:
    Player(uint64_t hash, sf::IpAddress IP , unsigned short port , sf::Texture& texture , char * name , sf::RenderWindow& win,MissileManager * mManager, sf::Texture * baseTexture);
    ~Player();
    void destroyTank();
    void draw();
    sf::IpAddress getIP();
    uint64_t getHash();
    Tank playerTank;
    void setPressedButtons(bool * buttons);
    sf::Vector2f getPosition();
    bool isAlive();
};

#endif /* player_hpp */
