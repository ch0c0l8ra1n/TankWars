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
#include <Box2D/Box2D.h>
//#include "missileManager.hpp"

class PlayerManager{
private:
    std::vector<Player> players;
    sf::RenderWindow* window;
    MissileManager* missileManager;
    b2World * world;
    
public:
    PlayerManager(MissileManager& misM);
    void setWorld(b2World* worl);
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
