//
//  playerManager.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#define PI 3.14159265

#include "playerManager.hpp"
#include <iostream>

PlayerManager::PlayerManager(MissileManager& misM){
    missileManager = &misM;
    font.loadFromFile(resourcePath() + "gameFont.ttf");
}
PlayerManager::~PlayerManager(){}

float dot (sf::Vector2f vec1, sf::Vector2f vec2){
    return vec1.x * vec2.x + vec1.y * vec2.y ;
}

bool PlayerManager::addPlayer(Player player){
    for(int i=0;i<players.size();i++){
        if ( players[i].getHash() == player.getHash() ){
            return false;
        }
    }
    players.push_back(player);
    Player* temp = getPlayerByHash(player.getHash());
    temp->playerTank.bodyDef.type = b2_dynamicBody;
    temp->playerTank.bodyDef.position.Set(temp->playerTank.getPosition().x, temp->playerTank.getPosition().y);
    temp->playerTank.cBody = world->CreateBody(&(temp->playerTank.bodyDef));
    temp->playerTank.shape.SetAsBox(temp->playerTank.getSize().x / 2, temp->playerTank.getSize().y/2);
    temp->playerTank.fixtureDef.shape = &temp->playerTank.shape;
    temp->playerTank.fixtureDef.friction = 0.0f;
    temp->playerTank.fixtureDef.density = 1.0f;
    temp->playerTank.fixtureDef.restitution = 0.0f;
    temp->playerTank.cBody->CreateFixture(&(temp->playerTank.fixtureDef));
    //temp->playerTank.cBody->SetLinearDamping(1.0f);
    //temp->playerTank.cBody->SetAngularDamping(1.0f);
    temp->playerTank.cBody->SetLinearVelocity(b2Vec2(random()%1000,random()%1000));
    temp->playerTank.cBody->SetAngularVelocity(1000.0f);
    temp->playerTank.setFont(&font);
    temp->playerTank.setExplosionManager(explosionManager);
    
    updatePlayerRefs();
    
    return true;
}

bool PlayerManager::removePlayersByIP(sf::IpAddress ip){
    for (int i=0;i<players.size();i++){
        if (players[i].getIP() == ip){
            players.erase(players.begin() + i);
            updatePlayerRefs();
            return true;
        }
    }
    updatePlayerRefs();
    return false;
}
void PlayerManager::updatePlayers(float deltaTime){
    for(int i=0;i<players.size();i++){
        players[i].playerTank.update(deltaTime);
    }
}

void PlayerManager::drawPlayers(sf::RenderWindow& window){
    for(int i=0;i<players.size();i++){
        if (players[i].isAlive()){
            players[i].playerTank.draw(window);
        }
    }
}

Player& PlayerManager::getPlayer(int id){
    return players[id];
}

bool PlayerManager::removePlayer(uint64_t hash){
    for (int i=0;i<players.size();i++){
        if (players[i].getHash() == hash){
            players.erase(players.begin() + i);
            updatePlayerRefs();
            return true;
        }
    }
    updatePlayerRefs();
    return false;
}

void PlayerManager::setPlayerButtons(uint64_t hash, bool *buttons){
    for (int i=0;i<players.size();i++){
        if (players[i].getHash() == hash){
            players[i].setPressedButtons(buttons);
            return;
        }
    }
    std::cout<<"Not found player\n";
}

Player* PlayerManager::getPlayerByHash(uint64_t hash){
    for (int i=0;i<players.size();i++){
        if (players[i].getHash() == hash ){
            return &(players[i]);
        }
    }
    std::cout<<"Player not found\n";
    return NULL;
}

void PlayerManager::setWorld(b2World * worl){
    world = worl;
}

void PlayerManager::updatePlayerRefs(){
    for(int i=0;i<players.size();i++){
        players[i].playerTank.setPlayerRef(&players[i]);
    }
}

void PlayerManager::setExplosionManager(ExplosionManager *explosionM){
    explosionManager = explosionM;
}


sf::FloatRect PlayerManager::getMaxBounds(){
    if(players.size() == 0){
        sf::FloatRect bounds;
        bounds.left = 250;
        bounds.top = 250;
        bounds.width = 500;
        bounds.height = 500/1.6f;
        return bounds;
    }
    sf::FloatRect bounds;
    bounds.left = 0;
    bounds.top = 0;
    bounds.width = 250*1.6f;
    bounds.height = 250;
    for (int i=0;i<players.size();i++){
        sf::Vector2f pos = players[i].playerTank.getPosition();
        bounds.left += pos.x;
        bounds.top += pos.y;
    }
    bounds.left /= players.size();
    bounds.top  /= players.size();
    sf::Vector2f maxDistance(0,0);
    for (int i=0;i <players.size(); i++){
        maxDistance.x = std::max(maxDistance.x , bounds.left - abs(players[i].playerTank.getPosition().x) );
        maxDistance.y = std::max(maxDistance.y , bounds.top - abs(players[i].playerTank.getPosition().y) );
    }
    maxDistance = maxDistance * 2.0f;
    maxDistance.x += 100.0f;
    maxDistance.y += 200.0f;
    bounds.width = std::max( 150.0f , std::min( 500.0f, maxDistance.x) );
    bounds.height = std::max( 150.0f , std::min(500.0f , maxDistance.y) );
    
    if (bounds.height * 1.6f > bounds.width ){
        std::cout<<bounds.width<<"\t";
        bounds.width = bounds.height * 1.6f;
        std::cout<<bounds.width<<"\n";
    }
    else{
        bounds.height = bounds.width / 1.6f;
    }
    bounds.left = std::min( 800 - bounds.width/2.0f , std::max(bounds.left , bounds.width/2.0f) );
    bounds.top = std::min( 500 - bounds.height/2.0f , std::max(bounds.top , bounds.height/2.0f) );
    return bounds;
}







