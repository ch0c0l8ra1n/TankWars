//
//  explosionManager.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/26/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "explosionManager.hpp"
#include "ResourcePath.hpp"

ExplosionManager::ExplosionManager(){
    explosionTexture.loadFromFile(resourcePath() + "explosion.png");
    explosionSound.openFromFile(resourcePath() + "deathFlash.flac");
}

void ExplosionManager::addExplosion(Player *player){
    explosions.push_back(Explosion(&explosionTexture, player));
    explosionSound.play();
}

void ExplosionManager::update(){
    int i=0;
    while (true){
        if (i >= explosions.size()){
            break;
        }
        if(explosions[i].isExpired()){
            explosions.erase(explosions.begin() + i);
        }
        else{
            explosions[i].update();
            i++;
        }
    }
}

void ExplosionManager::drawExplosions(sf::RenderWindow &window){
    for(int i=0;i<explosions.size();i++){
        explosions[i].draw(window);
    }
}
