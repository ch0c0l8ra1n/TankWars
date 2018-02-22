//
//  playerManager.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#pragma once

#ifndef playerManager_hpp
#define playerManager_hpp

#include <stdio.h>
#include "player.hpp"
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
//#include "missileManager.hpp"

class PlayerManager{
private:
    std::vector<Player> players;
    sf::RenderWindow* window;
    MissileManager* missileManager;
    
public:
    PlayerManager(MissileManager& misM);
    void updatePlayers(float deltaTime);
    bool addPlayer(Player player);
    bool removePlayersByIP(sf::IpAddress ip);
    bool removePlayer(uint64_t hash);
    void drawPlayers(sf::RenderWindow& window);
    void setPlayerButtons(uint64_t hash, bool * buttons);
    Player* getPlayerByHash(uint64_t hash);
    Player& getPlayer(int id);
    int checkCollisions();
    
    ~PlayerManager();
};


#endif /* playerManager_hpp */
