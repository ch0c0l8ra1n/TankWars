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
}

void ExplosionManager::addExplosion(Player *player){
    explosions.push_back(Explosion(&explosionTexture, player));
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
    /*
     int i = 0;
     int counter = 0;
     while (true){
     if (i >= missiles.size()){
     return counter;
     }
     sf::Vector2f center = missiles[i].getPosition();
     for (int j=0;j<playerManager->players.size();j++){
     if (playerManager->players[j].playerTank.getFloatRect().contains(center) &&
     playerManager->players[j].isAlive() &&
     playerManager->players[j].getHash() != missiles[i].getPlayer()->getHash()){
     playerManager->players[j].playerTank.damage();
     missiles.erase(missiles.begin() + i);
     break;
     }
     }
     i++;
     }*/
}

void ExplosionManager::drawExplosions(sf::RenderWindow &window){
    for(int i=0;i<explosions.size();i++){
        explosions[i].draw(window);
    }
}
