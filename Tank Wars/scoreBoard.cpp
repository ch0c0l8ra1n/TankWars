//
//  scoreBoard.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/24/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "scoreBoard.hpp"
#include <algorithm>
#include <iostream>

#include "playerManager.hpp"

ScoreBoard::ScoreBoard(){
    font.loadFromFile(resourcePath() + "gameFont.ttf");
    scoreText.setFont(font);
    scoreText.setPosition(1500, 1450);
    scoreText.setCharacterSize(15.0f);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(1.0f);
    
    scoreBoardTitle.setFont(font);
    scoreBoardTitle.setPosition(1500, 1400); //(1500, 1600)
    scoreBoardTitle.setCharacterSize(15.0f);
    scoreBoardTitle.setString(sf::String("ScoreBoard:"));
    scoreBoardTitle.setFillColor(sf::Color::White);
    scoreBoardTitle.setOutlineColor(sf::Color::Black);
    scoreBoardTitle.setOutlineThickness(1.0f);
}

void ScoreBoard::setPlayerManager(PlayerManager *playerM){
    playerManager = playerM;
}


void ScoreBoard::draw(sf::RenderWindow& window){
    window.draw(scoreBoardTitle);
    for(int i=0;i<playerManager->players.size();i++){
        std::string temp = std::string(playerManager->players[i].getName()) + std::string("\t") + std::to_string(playerManager->players[i].getKills());
        scoreText.setString( temp);
        std::cout<<playerManager->players[i].getName()<<"\t"<<playerManager->players[i].getKills()<<"\n";
        window.draw(scoreText);
        scoreText.setPosition(1500, 1450 + (20*(i+1) ) );
    }
}
