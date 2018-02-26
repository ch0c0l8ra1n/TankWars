//
//  explosion.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/26/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef explosion_hpp
#define explosion_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Player;

class Explosion{
public:
    Explosion(sf::Texture * texture, Player* player);
    void update();
    bool isExpired();
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape shape;
    int row;
    int column;
    int height;
    int width;
    bool forward;
    bool expired;
    int counter;
    long long lastKnownTime;
};

#endif /* explosion_hpp */
