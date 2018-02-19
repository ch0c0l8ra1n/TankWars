//
//  missile.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 1/28/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef missile_hpp
#define missile_hpp


#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "ResourcePath.hpp"
#include <iostream>

class Missile{
public:
    Missile(Player& player, sf::Texture& texture );
    ~Missile();
    void update(float deltaTime);
    void draw(sf::RenderWindow & window);
    sf::CircleShape body;
    
private:
    sf::Vector2f velocity;
    
    Player* originPlayer;
    
};

#endif /* missile_hpp */
