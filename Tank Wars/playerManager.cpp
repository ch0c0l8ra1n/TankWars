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
    //player.playerTank.setPlayerRef(&player);
    players.push_back(player);
    Player* temp = getPlayerByHash(player.getHash());
    temp->playerTank.setPlayerRef(temp);
    
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

void PlayerManager::setPlayerButtons(uint64_t hash, bool *buttons){
    for (int i=0;i<players.size();i++){
        if (players[i].getHash() == hash){
            players[i].setPressedButtons(buttons);
            return;
        }
    }
    std::cout<<"Not found player\n";
}

Player* PlayerManager::getPlayerByHash(uint64_t hash){
    for (int i=0;i<players.size();i++){
        if (players[i].getHash() == hash ){
            return &players[i];
        }
    }
    return NULL;
}





