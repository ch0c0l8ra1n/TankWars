//
//  menu.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/26/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

enum state {NO_CHANGE , START , ABOUT, EXIT, ABOUT_SELECTED};

class Menu{
public:
    Menu();
    void update();
    void draw(sf::RenderWindow& window);
    state getState();
    void setState(state stat);
    
    
private:
    sf::Texture backGround;
    sf::Font font;
    sf::Text start;
    sf::Text about;
    sf::Text exit;
    state curState;
    bool selected;
    sf::Color selectedColor;
    sf::Color unSelectedColor;
    long long lastKeyPressedTime;
    sf::Text title;
    sf::Text rajat;
    sf::Text ronast;
    sf::Text esc2Back;
    sf::Texture bgTex;
    sf::RectangleShape menuBg;
};


#endif /* menu_hpp */
