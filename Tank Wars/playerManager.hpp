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
#include "ResourcePath.hpp"
#include "explosionManager.hpp"

class PlayerManager{
private:
    sf::RenderWindow* window;
    MissileManager* missileManager;
    b2World * world;
    sf::Font font;
    ExplosionManager* explosionManager;
    
public:
    PlayerManager(MissileManager& misM);
    std::vector<Player> players;
    void setWorld(b2World* worl);
    void updatePlayers(float deltaTime);
    bool addPlayer(Player player);
    bool removePlayersByIP(sf::IpAddress ip);
    bool removePlayer(uint64_t hash);
    void drawPlayers(sf::RenderWindow& window);
    void setPlayerButtons(uint64_t hash, bool * buttons);
    Player* getPlayerByHash(uint64_t hash);
    void updatePlayerRefs();
    Player& getPlayer(int id);
    void setExplosionManager(ExplosionManager* explosionM);
    ~PlayerManager();
};


#endif /* playerManager_hpp */
