#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ResourcePath.hpp"

#include "missile.hpp"
#include "message.hpp"
#include <iostream>
#include <string>
#include "missileManager.hpp"
#include "playerManager.hpp"

void clearBuffer(char * start,std::size_t size){
    for (uint i =0;i<std::min((int)size+1,1024);i++){
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
    sf::RenderWindow window( sf::VideoMode( 2160 , 1440 ) , "Tank Wars" );
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
    
    sf::Texture bTex;
    bTex.loadFromFile( resourcePath() + "fireball.png" );
    
    sf::CircleShape ball;
    ball.setTexture(&bTex);
    ball.setRadius(10.0f);
    ball.setPosition(450.0f, 450.0f);
    
    std::vector <Player> players;
    std::vector <Missile> missiles;
    MissileManager missileManager(window);
    PlayerManager playerManager(missileManager);
    tempIP = "127.0.0.1";
    playerManager.addPlayer( Player(0,tempIP.toString(), 43250, tankTextures[2], window ) );
    missileManager.addMissile(playerManager.getPlayer(0));
    missileManager.missiles[0].body.setTexture(&bTex);
    
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
                MessageTypes * msg;
                msg = (MessageTypes *) receivingBuffer;
                joinMessage* jm;
                leaveMessage* lm;
                buttonPress* bp;
                
                switch (*msg) {
                    case JOIN:
                        std::cout<<"JOIN\n";
                        jm = (joinMessage*) receivingBuffer;
                        playerManager.addPlayer( Player(jm->hash, tempIP, tempPort, tankTextures[jm->tankTextureId] , window) );
                        break;
                    case LEAVE:
                        std::cout<<"LEAVE\n";
                        lm = (leaveMessage*) receivingBuffer;
                        playerManager.removePlayer(lm->hash);
                        break;
                    case BUTTON_PRESS:
                        std::cout<<"BUTTON_PRESS\n";
                        break;
                    default:
                        break;
                }
                
                clearBuffer(receivingBuffer, received);
            }
        }
        
        playerManager.updatePlayers(deltaTime);
        playerManager.drawPlayers(window);
        missileManager.updateMissiles(deltaTime);
        
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
        //window.draw(temp);
        ball.move(1.0f, 0.1f);
        window.draw(ball);
        window.display();
        
        
        window.clear( sf::Color( 155 , 129 , 80 ) );
    }

    return EXIT_SUCCESS;
}
