//
//  explosionManager.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/26/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef explosionManager_hpp
#define explosionManager_hpp

#include <stdio.h>
#include "explosion.hpp"
#include <SFML/Audio.hpp>

class ExplosionManager{
public:
    ExplosionManager();
    void addExplosion(Player* player);
    void update();
    void drawExplosions(sf::RenderWindow& window);
private:
    std::vector<Explosion> explosions;
    sf::Texture explosionTexture;
    sf::Music explosionSound;
};

#endif /* explosionManager_hpp */
