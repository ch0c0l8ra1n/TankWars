//
//  playerManager.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "playerManager.hpp"
#include <iostream>

PlayerManager::PlayerManager(){}
PlayerManager::~PlayerManager(){}

bool PlayerManager::addPlayer(Player player){
    for(int i=0;i<players.size();i++){
        if ( players[i].getIP() == player.getIP() ){
            //return false;
        }
    }
    players.push_back(player);
    return true;
}

bool PlayerManager::removePlayerByIP(sf::IpAddress ip){
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

