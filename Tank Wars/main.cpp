#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ResourcePath.hpp"

#include "tank.hpp"
#include "missile.hpp"
#include "message.hpp"
#include <iostream>
#include <string>
#include "player.hpp"

void clearBuffer(char * start,std::size_t size){
    for (uint i =0;i<size+1;i++){
        start[i] = '\0';
    }
}


int main(int, char const**){
    //Initialize client and server sockets
    sf::UdpSocket clientSocket,serverSocket;
    serverSocket.setBlocking(false);
    uint16_t serverPort=4325;
    
    sf::IpAddress tempIP;
    unsigned short tempPort;
    
    if (serverSocket.bind( serverPort ) != sf::Socket::Done){
        std::cout<<"Couldn't listen on port 4325.\n";
        return 1;
    }
    else{
        std::cout<<"Successfully listening on port 4325.\n";
    }
    
    sf::Texture tankTextures[6];
    for (int i=0;i<6;i++){
        tankTextures[i].loadFromFile(resourcePath() + "tank" + std::to_string(i) + ".png" );
    }
    
    
    //Initalize the window
    sf::RenderWindow window( sf::VideoMode( 2160 , 2160 ) , "Tank Wars" );
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    //Initialize the view
    sf::View view( sf::Vector2f(1440,1440) , sf::Vector2f(1440,1440) );
    view.setCenter(512, 512);
    view.setSize(2160, 2160);
    
    //Load the texture
    sf::Texture tankTexture;
    tankTexture.loadFromFile( resourcePath() + "tank3.png" );
    

    
    
    
    sf::RectangleShape temp;
    temp.setFillColor(sf::Color(100,250,100));
    temp.setPosition(450.0f, 450.0f);
    temp.setSize(sf::Vector2f(100,100));
    
    
    float deltaTime = 0.0f;
    sf::Clock clock;
    
    
    char receivingBuffer[1024];
    for(int i=0;i<1024;i++){
        receivingBuffer[i] = '\0';
    }
    
    std::size_t received;
    
    std::vector <Player> players;
    
    while(window.isOpen()){
        
        
        deltaTime = clock.restart().asSeconds();
        
        while(true){
            if (serverSocket.receive(receivingBuffer, 1024 ,received, tempIP, tempPort)){
                break;
                
            }
            else{
                std::cout<<receivingBuffer<<"\n";
                clearBuffer(receivingBuffer, received);
                players.push_back( Player(tempIP.toString(), tempPort, tankTexture , window ) );
            }
        }
        window.clear( sf::Color( 155 , 129 , 80 ) );
        
        for (int i=0;i<players.size();i++){
            players[i].playerTank.update(deltaTime);
            players[i].playerTank.draw(window);
            //std::cout<<players[i].playerTank.getPosition().x<<" "<<players[i].playerTank.getPosition().y<<"\n";
        }
        
        
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
        
        
        
        window.setView(view);
        
        window.draw(temp);
        
        window.display();
    }

    return EXIT_SUCCESS;
}
