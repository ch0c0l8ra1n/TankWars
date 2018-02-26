//
//  missileManager.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#pragma once

#ifndef missileManager_hpp
#define missileManager_hpp

#include <stdio.h>
#include "missile.hpp"
#include "player.hpp"
#include "scoreBoard.hpp"

class PlayerManager;

class MissileManager{
private:
    sf::RenderWindow* window;
    sf::Texture texture;
    PlayerManager* playerManager;
    ScoreBoard* scoreBoard;
    sf::Music fire;
    
public:
    std::vector<Missile> missiles;
    MissileManager(sf::RenderWindow& win);
    ~MissileManager(){}
    void addMissile(Player* player);
    void updateMissiles(float deltaTime);
    void setPlayerManager(PlayerManager* manager);
    int checkCollisions();
    void setScoreBoard(ScoreBoard* scoreB);
};

#endif /* missileManager_hpp */
