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
#include "missileManager.hpp"
#include "playerManager.hpp"

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
    std::vector <Missile> missiles;
    
    //MissileManager missileManager;
    PlayerManager playerManager;
    
    while(window.isOpen()){
        
        deltaTime = clock.restart().asSeconds();
        
        //accpets at maximum 64 udp messages.
        for(int i=0;i<64;i++){
            
            //if no more messages then stop waiting for messages.
            if (serverSocket.receive(receivingBuffer, 1024 ,received, tempIP, tempPort) != sf::Socket::Done){
                break;
            }
            
            //Handle JOIN, LEAVE, AND BUTTON_PRESS conditions
            else{
                MessageTypes message;
                memcpy(&message, receivingBuffer, sizeof(message));
                
                if (message == JOIN){
                    char name[10];
                    short texId;
                    memcpy(name, receivingBuffer + sizeof(message), 10);
                    memcpy(&texId, receivingBuffer + sizeof(message) + sizeof(name) , sizeof(texId));
                    texId %= 6;
                    std::cout<<"Player rjpj"<<name<<" with tank texture "<< texId <<" has entered the game\nIP: "<<tempIP.toString()<<"\n";
                    playerManager.addPlayer( Player(tempIP.toString(), tempPort, tankTextures[texId], window ) );
                }
                else if(message == LEAVE){
                    std::cout<<"Left\n";
                    playerManager.removePlayerByIP(tempIP);
                }
                else if(message == BUTTON_PRESS){
                    
                }
                
                //self-explanatory
                clearBuffer(receivingBuffer, received);
            }
        }
        
        playerManager.updatePlayers(deltaTime);
        playerManager.drawPlayers(window);
        
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
        
        window.clear( sf::Color( 155 , 129 , 80 ) );
    }

    return EXIT_SUCCESS;
}
