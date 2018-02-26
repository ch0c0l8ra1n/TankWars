//
//  explosion.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/26/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "explosion.hpp"
#include <sys/time.h>
#include <tank.hpp>
#include "player.hpp"


Explosion::Explosion(sf::Texture* texture, Player* player){
    height = texture->getSize().y/4.0f;
    width  = texture->getSize().x/4.0f;
    row = 3;
    column = 3;
    forward = true;
    lastKnownTime = getMs();
    shape.setSize(player->playerTank.getSize() * 2.0f);
    shape.setTexture(texture);
    shape.setTextureRect(sf::IntRect( column * width , row * height , width , height ));
    shape.setOrigin(shape.getSize()/2.0f);
    shape.setPosition(player->playerTank.getPosition());
    counter = 0;
}

void Explosion::update(){
    if (getMs() - lastKnownTime > 50){
        lastKnownTime = getMs();
        if(forward){
            if(row == 0 && column == 0){
                forward = false;
            }
            else if(column == 0){
                row--;
                column = 3;
                
            }
            else{
                column--;
            }
        }
        else{
            if(row == 3 && column == 3){
                expired = true;
            }
            else if(column == 3){
                row++;
                column = 0;
            }
            else{
                column++;
            }
        }
    }
    shape.setTextureRect(sf::IntRect( column * width , row * height , width , height ));
}

bool Explosion::isExpired(){
    return expired;
}

void Explosion::draw(sf::RenderWindow &window){
    window.draw(shape);
}





