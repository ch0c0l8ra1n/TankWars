//
//  tank.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 1/25/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef tank_hpp
#define tank_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>


class Tank{
public:
    Tank( sf::Texture* texture );
    ~Tank();
    void setOrigin(sf::Vector2f origin);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    void updateBody(float deltaTime);
    void updateTurret(float deltaTime, sf::RenderWindow& window);
    int posOrNeg(float x);
    float reduce(float angularVelocity);
    
    

private:
    sf::Texture texture;
    sf::RectangleShape body, turret;
    sf::IntRect bodyRect, turretRect;
    float textureWidth, textureHeight;
    
    float linearAcc;
    float angularAcc;
    
    sf::Vector2f linearVelocity;
    float maxLinearVelocity;
    
    float angularVelocity;
    float maxAngularVelocity;
    
    float orientation;
    
    
    
    
    
};
#endif /* tank_hpp */
