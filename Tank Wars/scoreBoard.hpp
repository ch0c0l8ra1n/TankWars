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

struct Score{
    Player* player;
    int kills;
};

class ScoreBoard{
public:
    ScoreBoard(){};
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    void addKill(Player* player);
    void draw(sf::RenderWindow& window);

private:
    std::vector<Score> scores;
    sf::Text ScoreBoardTitle;
    sf::Text scoreTexts;
    
};


#endif /* scoreBoard_hpp */
