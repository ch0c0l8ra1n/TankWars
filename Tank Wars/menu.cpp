//
//  menu.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/26/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "menu.hpp"
#include "tank.hpp"

Menu::Menu(){
    font.loadFromFile(resourcePath() + "gameFont.ttf");
    
    selectedColor = sf::Color(255,25,75);
    unSelectedColor = sf::Color(255,255,255);
    
    selected = false;
    
    start.setFont(font);
    start.setString(sf::String("START"));
    start.setCharacterSize(100);
    start.setFillColor( selectedColor );
    start.setOutlineColor(sf::Color(0,0,0));
    start.setOutlineThickness(2.0f);
    start.setPosition(sf::Vector2f(1280.0f , 180.0f));
    curState = START;
    
    about.setFont(font);
    about.setString(sf::String("ABOUT"));
    about.setCharacterSize(100);
    about.setFillColor(unSelectedColor);
    about.setOutlineColor(sf::Color(0,0,0));
    about.setOutlineThickness(2.0f);
    about.setPosition(sf::Vector2f(1280.0f , 180.0f + 240.0f));
    
    exit.setFont(font);
    exit.setString(sf::String("EXIT"));
    exit.setCharacterSize(100);
    exit.setFillColor(unSelectedColor);
    exit.setOutlineColor(sf::Color(0,0,0));
    exit.setOutlineThickness(2.0f);
    exit.setPosition(sf::Vector2f(1280.0f , 180.0f + 480.0f));
    
    title.setFont(font);
    title.setString(sf::String("TANK WARS (TM)"));
    title.setCharacterSize(200);
    title.setFillColor(unSelectedColor);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2.0f);
    title.setPosition(sf::Vector2f(300.0f , 200.0f));
    
    rajat.setFont(font);
    rajat.setString(sf::String("Made By:\n\t\t1. Rajat Parajuli (073bct532)\n\t\t2. Ronast Subedi (073bct535)\n\nPress ESC key to go back"));
    rajat.setCharacterSize(100);
    rajat.setFillColor(unSelectedColor);
    rajat.setOutlineColor(sf::Color::Black);
    rajat.setOutlineThickness(2.0f);
    rajat.setPosition(sf::Vector2f(300.0f , 600.0f));
    
    bgTex.loadFromFile(resourcePath() + "menubg.jpg");
    menuBg.setTexture(&bgTex);
    menuBg.setSize(sf::Vector2f(2560,1440));
}

void Menu::update(){
    if(curState == ABOUT_SELECTED){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            curState = ABOUT;
            selected = false;
        }
        return;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        selected = true;
        return;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if(getMs() < lastKeyPressedTime+200){
            return;
        }
        lastKeyPressedTime = getMs();
        switch(curState){
            case ABOUT:
                curState = START;
                start.setFillColor(selectedColor);
                
                about.setFillColor(unSelectedColor);
                break;
            case EXIT:
                curState = ABOUT;
                about.setFillColor(selectedColor);
                
                exit.setFillColor(unSelectedColor);
                break;
        }
        
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if(getMs() < lastKeyPressedTime+200){
            return;
        }
        lastKeyPressedTime = getMs();
        switch (curState) {
            case ABOUT:
                curState = EXIT;
                exit.setFillColor(selectedColor);
                
                about.setFillColor(unSelectedColor);
                break;
            case START:
                curState = ABOUT;
                about.setFillColor(selectedColor);
                
                start.setFillColor(unSelectedColor);
                break;
                
        }
    }
    
}
void Menu::setState(state stat){
    curState = stat;
}

void Menu::draw(sf::RenderWindow &window){
    window.draw(menuBg);
    if (!(curState == ABOUT_SELECTED)){
        window.draw(start);
        window.draw(about);
        window.draw(exit);
        return;
    }
    window.draw(title);
    window.draw(rajat);
    
}

state Menu::getState(){
    return selected ? curState : NO_CHANGE;
}

