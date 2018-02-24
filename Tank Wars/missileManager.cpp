//
//  missileManager.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "missileManager.hpp"
#include "playerManager.hpp"

MissileManager::MissileManager(sf::RenderWindow& win){
    window = &win;
    texture.loadFromFile(resourcePath() + "fireball.png");
}

void MissileManager::addMissile(Player* player){
    Missile temp(player,texture);
    missiles.push_back( temp );
}

void MissileManager::updateMissiles(float deltaTime){
    long long time= getMs();
    while (true){
        bool changed = false;
        for (int i=0;i<missiles.size();i++){
            if (missiles[i].isExpired(time)){
                missiles.erase(missiles.begin() + i);
                changed = true;
                break;
            }
        }
        if (!changed){
            break;}
    }
    checkCollisions();
    for (int i=0;i<missiles.size();i++){
        missiles[i].update(deltaTime);
        missiles[i].draw(*window);
    }
}

void MissileManager::setPlayerManager(PlayerManager *manager){
    playerManager = manager;
}

int MissileManager::checkCollisions(){
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
                std::cout<<"collision\n";
                playerManager->players[j].playerTank.damage();
                missiles.erase(missiles.begin() + i);
                break;
            }
        }
        i++;
    }
}
