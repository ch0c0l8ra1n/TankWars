//
//  missile.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 1/28/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//
#pragma once

#ifndef missile_hpp
#define missile_hpp

#define PI 3.14159265

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "ResourcePath.hpp"
#include <iostream>

class Missile{
public:
    Missile(Player* player, sf::Texture& texture );
    ~Missile();
    void update(float deltaTime);
    void draw(sf::RenderWindow & window);
    sf::CircleShape body;
    bool isExpired(long long dTime);
    sf::Vector2f getPosition();
    Player* getPlayer();
    
private:
    float velocityScalar;
    Player* originPlayer;
    float orientation;
    sf::Vector2f unitVector;
    sf::Vector2f velocity;
    long long creationTime;
    
};

#endif /* missile_hpp */
