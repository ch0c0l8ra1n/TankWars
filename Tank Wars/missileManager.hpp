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

class MissileManager{
private:
    std::vector<Missile> missiles;
public:
    MissileManager();
    ~MissileManager();
    void addMissile();
    void updateMissiles();
};

#endif /* missileManager_hpp */
