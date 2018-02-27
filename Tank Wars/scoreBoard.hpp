//
//  scoreBoard.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/24/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef scoreBoard_hpp
#define scoreBoard_hpp

#include <stdio.h>
#include "player.hpp"
#include "ResourcePath.hpp"



class PlayerManager;

class ScoreBoard{
public:
    ScoreBoard();
    void draw(sf::RenderWindow& window);
    void setPlayerManager(PlayerManager* playerM);

private:
    sf::Font font;
    sf::Text scoreBoardTitle;
    sf::Text scoreText;
    PlayerManager* playerManager;
    
    
};


#endif /* scoreBoard_hpp */
