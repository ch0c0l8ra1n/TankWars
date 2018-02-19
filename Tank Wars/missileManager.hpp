//
//  missileManager.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef missileManager_hpp
#define missileManager_hpp

#include <stdio.h>
#include "missile.hpp"
#include "player.hpp"

class MissileManager{
private:
    sf::RenderWindow* window;
    sf::Texture texture;
public:
    std::vector<Missile> missiles;
    MissileManager(sf::RenderWindow& win);
    ~MissileManager(){}
    void addMissile(Player& player);
    void updateMissiles(float deltaTime);
};

#endif /* missileManager_hpp */
