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

class Missile{
public:
    Missile(sf::Vector2f velocity, Player player  );
    ~Missile();
    void update(float deltaTime);
    void draw(sf::RenderWindow & window);
    
private:
    sf::Vector2f velocity;
    sf::Texture texture;
    sf::CircleShape body;
    Player originPlayer;
    
};

#endif /* missile_hpp */
