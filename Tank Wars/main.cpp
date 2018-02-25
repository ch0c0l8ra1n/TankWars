#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <Box2D/Box2D.h>

#include "ResourcePath.hpp"

#include "missile.hpp"
#include "message.hpp"
#include <string>
#include "missileManager.hpp"
#include "playerManager.hpp"

void clearBuffer(char * start,std::size_t size){
    for (uint i =0;i<std::min((int)size+1,1024);i++){
        start[i] = '\0';
    }
}


int main(int, char const**){
    sf::Sprite bg;
    sf::Texture bgTex;
    bgTex.loadFromFile(resourcePath() + "bg.png");
    bgTex.setRepeated(true);
    bg.setTexture(bgTex);
    bg.setPosition(0.0f, 0.0f);
    bg.setScale(2.0f, 2.0f);
    
    
    b2Vec2 gravity(0.0f,0.0f);
    b2World world(gravity);
    
    b2BodyDef walls[4];
    for(int i=0;i<4;i++){
        walls[i].type = b2_staticBody;
    }
    walls[0].position.Set( 0.0f, 720.0f );
    walls[2].position.Set( 2560.0f, 720.0f);
    walls[1].position.Set( 1280.0f, 0.0f);
    walls[3].position.Set( 1280.0f, 1440.0f);
    
    b2Body* wallBodies[4];
    for(int i=0;i<4;i++){
        wallBodies[i] = world.CreateBody(&(walls[i]));
    }
    
    b2PolygonShape wallShapes[4];
    wallShapes[0].SetAsBox(5.0f, 1440.0f);
    wallShapes[2].SetAsBox(5.0f, 1440.0f);
    
    wallShapes[1].SetAsBox(1440.0f, 5.0f);
    wallShapes[3].SetAsBox(1440.0f, 5.0f);
    
    b2FixtureDef wallFixtureDefs[4];
    for(int i=0;i<4;i++){
        wallFixtureDefs[i].shape = &(wallShapes[i]);
        wallFixtureDefs[i].density = 1.0f;
        wallFixtureDefs[i].friction = 1.0f;
        wallFixtureDefs[i].restitution = 0.0f;
    }
    for(int i = 0;i<4;i++){
        wallBodies[i]->CreateFixture(&(wallFixtureDefs[i]));
    }
    

    
    //Initialize client and server sockets
    sf::UdpSocket clientSowcket,serverSocket;
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
    sf::RenderWindow window( sf::VideoMode( 2560 , 1440 ) , "Tank Wars" );
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);
    
    //Initialize the view
    sf::View view( sf::Vector2f(216,216) , sf::Vector2f(216 , 216) );
    view.setCenter(512, 512);
    view.setSize(1440, 1440);
    
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
    playerManager.setWorld(&world);
    missileManager.setPlayerManager(&playerManager);
    tempIP = "127.0.0.1";
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    //playerManager.addPlayer( Player(0,tempIP.toString(), 43250, tankTextures[2], window ) );
    //missileManager.addMissile(playerManager.getPlayer(0));
    //missileManager.missiles[0].body.setTexture(&bTex);
    
    long long fpsCounter= 0;
    std::cout<<"hello\n";
    
    while(window.isOpen()){
        window.draw(bg);
        deltaTime = clock.restart().asSeconds();
        if (fpsCounter++%60 == 0){
            //window.setTitle("FPS: "+std::to_string(int(1/deltaTime)));
        }
        world.Step(deltaTime, velocityIterations, positionIterations);
        
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
                switch (*msg) {
                    case JOIN:
                        //std::cout<<"JOIN\n";
                        joinMessage* jm;
                        jm = (joinMessage*) receivingBuffer;
                        playerManager.addPlayer( Player(jm->hash, tempIP, tempPort, tankTextures[jm->tankTextureId] , jm->name, window, &missileManager) );
                        break;
                    case LEAVE:
                        //std::cout<<"LEAVE\n";
                        leaveMessage* lm;
                        lm = (leaveMessage*) receivingBuffer;
                        playerManager.removePlayer(lm->hash);
                        break;
                    case BUTTON_PRESS:
                        //std::cout<<"BUTTON_PRESS\n";
                        buttonsPressed* bp;
                        bp = (buttonsPressed*) receivingBuffer;
                        playerManager.setPlayerButtons(bp->hash, bp->buttons);
                        break;
                    case CONNECTION_ALIVE:
                        //std::cout<<"CONNECTION_ALIVE\n";
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
        
        
        
        //window.setView(view);
        //window.draw(temp);
        ball.move(1.0f, 0.1f);
        window.draw(ball);
        window.display();
        window.clear( sf::Color( 155 , 129 , 80 ) );
    }

    return EXIT_SUCCESS;
}
