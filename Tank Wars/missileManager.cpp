//
//  missileManager.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "missileManager.hpp"

MissileManager::MissileManager(sf::RenderWindow& win){
    window = &win;
    texture.loadFromFile(resourcePath() + "fireball.png");
}

void MissileManager::addMissile(Player& player){
    Missile temp(player,texture);
    missiles.push_back( temp );
}

void MissileManager::updateMissiles(float deltaTime){
    for (int i=0;i<missiles.size();i++){
        missiles[i].update(deltaTime);
        missiles[i].draw(*window);
    }
}
