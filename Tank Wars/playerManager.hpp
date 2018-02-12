//
//  playerManager.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef playerManager_hpp
#define playerManager_hpp

#include <stdio.h>
#include "player.hpp"
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class PlayerManager{
private:
    std::vector<Player> players;
    sf::RenderWindow* window;
    
public:
    PlayerManager();
    void updatePlayers(float deltaTime);
    bool addPlayer(Player player);
    bool removePlayerByIP(sf::IpAddress ip);
    void drawPlayers(sf::RenderWindow& window);
    
    ~PlayerManager();
};


#endif /* playerManager_hpp */
