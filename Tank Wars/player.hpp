//
//  player.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <SFML/Network.hpp>
#include "tank.hpp"
#include <SFML/Graphics.hpp>


class Player{
private:
    sf::IpAddress playerIP;
    unsigned short playerPort;
    sf::RenderWindow* window;
    
public:
    Player(sf::IpAddress IP , unsigned short port , sf::Texture& texture , sf::RenderWindow& win);
    ~Player();
    void destroyTank();
    void draw();
    sf::IpAddress getIP();
    Tank playerTank;
};

#endif /* player_hpp */
