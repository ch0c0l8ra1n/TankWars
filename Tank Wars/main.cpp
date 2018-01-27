#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

#include "tank.hpp"
#include <iostream>


int main(int, char const**)
{
    //Initalize the window
    sf::RenderWindow window( sf::VideoMode( 1024 , 1024 ) , "Tank Wars" );
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    //Initialize the view
    sf::View view( sf::Vector2f(1024,1024) , sf::Vector2f(1024,1024) );
    
    //Load the texture
    sf::Texture tankTexture;
    tankTexture.loadFromFile( resourcePath() + "tank1.png" );
    
    
    Tank tank1(&tankTexture);
    
    sf::RectangleShape temp;
    temp.setFillColor(sf::Color(100,250,100));
    temp.setPosition(300.0f, 300.0f);
    temp.setSize(sf::Vector2f(100,100));
    
    float deltaTime = 0.0f;
    sf::Clock clock;
    
    while(window.isOpen()){
        
        deltaTime = clock.restart().asSeconds();
        
        
        sf::Event evnt;
        while(window.pollEvent(evnt)){
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                default:
                    break;
            }
        }
        
        tank1.updateBody(deltaTime);
        tank1.updateTurret(deltaTime,window);
        
        window.clear( sf::Color( 155 , 129 , 80 ) );
        
        view.setCenter( tank1.getPosition() );
        window.setView( view );
        
        tank1.draw( window );
        
        window.draw( temp );
        
        window.display();
    }

    return EXIT_SUCCESS;
}
