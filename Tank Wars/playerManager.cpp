//
//  playerManager.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "playerManager.hpp"
#include <iostream>

PlayerManager::PlayerManager(MissileManager& misM){
    missileManager = &misM;
}
PlayerManager::~PlayerManager(){}

bool PlayerManager::addPlayer(Player player){
    for(int i=0;i<players.size();i++){
        if ( players[i].getHash() == player.getHash() ){
            return false;
        }
    }
    players.push_back(player);
    return true;
}

bool PlayerManager::removePlayersByIP(sf::IpAddress ip){
    for (int i=0;i<players.size();i++){
        if (players[i].getIP() == ip){
            players.erase(players.begin() + i);
            return true;
        }
    }
    return false;
}
void PlayerManager::updatePlayers(float deltaTime){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        missileManager->addMissile(players[0]);
    }
    for(int i=0;i<players.size();i++){
        players[i].playerTank.update(deltaTime);
    }
}

void PlayerManager::drawPlayers(sf::RenderWindow& window){
    for(int i=0;i<players.size();i++){
        players[i].playerTank.draw(window);
    }
}

Player& PlayerManager::getPlayer(int id){
    return players[id];
}

bool PlayerManager::removePlayer(uint64_t hash){
    for (int i=0;i<players.size();i++){
        if (players[i].getHash() == hash){
            players.erase(players.begin() + i);
            return true;
        }
    }
    return false;
}
