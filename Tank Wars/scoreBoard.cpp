//
//  scoreBoard.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/24/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "scoreBoard.hpp"
#include <algorithm>

bool compareByKills(const Score &a, const Score &b){
    return a.kills < b.kills;
}

void ScoreBoard::addPlayer(Player *player){
    for(int i=0;i<scores.size();i++){
        if(scores[i].player->getHash() == player->getHash()){
            return;
        }
    }
    Score temp;
    temp.player = player;
    temp.kills = 0;
    scores.push_back(temp);
    std::sort(scores.begin() , scores.end() , compareByKills);
}

void ScoreBoard::removePlayer(Player *player){
    for(int i=0;i<scores.size();i++){
        if(scores[i].player->getHash() == player->getHash()){
            scores.erase(scores.begin() + i);
            return;
        }
    }
    return;
    std::sort(scores.begin() , scores.end(), compareByKills);
}

void ScoreBoard::addKill(Player* player){
    for (int i=0;i<scores.size();i++){
        if(scores[i].player->getHash() == player->getHash()){
            scores[i].kills += 1;
        }
    }
}


void ScoreBoard::draw(sf::RenderWindow& window){
    
}
