#include "tank.hpp"
#include <iostream>

#include "missileManager.hpp"
#include "player.hpp"
#include <sys/time.h>

#define PI 3.14159265

long long getMs(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

Tank::Tank(sf::Texture* texture, MissileManager* mManager ){
    lastMissileTime = getMs() - 1000;
    
    linearAcc = 300.0f;
    angularAcc = 200.0f;
    
    turretVelocity = 150.0f;
    
    velocityScalar = 200.0f;
    
    velocityVector.x = 0.0f;
    velocityVector.y = 0.0f;
    maxLinearVelocity = 300.0f;
    
    angularVelocity = 0.0f;
    maxAngularVelocity = 100.0f;
    
    bodyOrientation = 0.0f;
    turretOrientation = 0.0f;
    
    body.setPosition( 512 , 512 );
    turret.setPosition( 512 , 512 );
    
    body.setSize(sf::Vector2f(100,150));
    turret.setSize(sf::Vector2f(100,150));
    
    body.setOrigin(body.getSize()/2.0f);
    turret.setOrigin(turret.getSize()/2.0f);
    
    body.setTexture(texture);
    turret.setTexture(texture);
    
    textureWidth = texture->getSize().x/2.0f;
    textureHeight = texture->getSize().y;
    bodyRect.width = textureWidth;
    bodyRect.left = 0.0f;
    bodyRect.height = textureHeight;
    bodyRect.top = 0.0f;
    
    turretRect.width = textureWidth;
    turretRect.left = textureWidth;
    turretRect.height = textureHeight;
    turretRect.top = 0.0f;
    
    body.setTextureRect(bodyRect);
    turret.setTextureRect(turretRect);
    
    for(int i=0;i<9;i++){
        pressedButtons[i]= false;
    }
    
    missileManager = mManager;
    
    int temp = random()%360;
    
    body.setRotation(temp);
    turret.setRotation(temp);
    bodyOrientation = temp;
    turretOrientation = temp;
    
    
}

Tank::~Tank(){}

int Tank::posOrNeg(float x){
    return (x>=0) ? 1:-1;
}

void Tank::setOrigin(sf::Vector2f origin){
    body.setOrigin(origin);
}

void Tank::draw(sf::RenderWindow &window){
    window.draw(body);
    window.draw(turret);
}


sf::Vector2f Tank::getPosition(){
    return body.getPosition();
}

void Tank::update(float deltaTime){
    if (pressedButtons[W]){
        velocityScalar += linearAcc * deltaTime;
    }
    else if (pressedButtons[S]){
        velocityScalar -= linearAcc * deltaTime;
    }
    else{
        float delRetardation = linearAcc * deltaTime;
        velocityScalar -= (delRetardation>fabs(velocityScalar)) ? velocityScalar : sign(velocityScalar)*delRetardation;
    }
    velocityScalar = clamp(velocityScalar , maxLinearVelocity);
    
    if (pressedButtons[A]){
        angularVelocity -= angularAcc * deltaTime;
    }
    else if (pressedButtons[D]){
        angularVelocity += angularAcc * deltaTime;
    }
    else{
        float delRetardation = angularAcc * deltaTime;
        angularVelocity -= (delRetardation>fabs(angularVelocity)) ? angularVelocity : sign(angularVelocity)*delRetardation;
    }
    
    float delTurretTheta = 0;
    if (pressedButtons[LEFT]){
        delTurretTheta -= turretVelocity * deltaTime;
    }
    else if (pressedButtons[RIGHT]){
        delTurretTheta += turretVelocity * deltaTime;
    }
    
    if(pressedButtons[SPACE]){
        std::cout<<getMs()<<"\t"<<lastMissileTime<<"\n";
        if (getMs() - lastMissileTime> 300){
            missileManager->addMissile(player);
            lastMissileTime = getMs();
        }
    }

    turretOrientation += delTurretTheta;
    turretOrientation = fmod(turretOrientation,360);
    turretOrientation = (turretOrientation<0) ? 360-turretOrientation : turretOrientation;
    
    
    angularVelocity = clamp(angularVelocity,maxAngularVelocity);

    
    float deltaTheta = angularVelocity * deltaTime;
    bodyOrientation += deltaTheta;
    bodyOrientation = fmod(bodyOrientation,360);
    bodyOrientation = (bodyOrientation<0) ? 360-bodyOrientation : bodyOrientation;
    
    
    
    sf::Vector2f unitVector;
    unitVector.x = -sin(bodyOrientation*PI/180);
    unitVector.y = cos(bodyOrientation*PI/180);
    
    velocityVector.x = velocityScalar * unitVector.x;
    velocityVector.y = velocityScalar * unitVector.y;
    
    sf::Vector2f movement;
    movement.x = velocityVector.x * deltaTime;
    movement.y = velocityVector.y * deltaTime;
    
    body.move(movement);
    turret.move(movement);
    body.rotate(deltaTheta);
    turret.rotate(delTurretTheta);
    
    
}


float Tank::sign(float temp){
    return (temp<0) ? std::max(-1.0f,temp) : std::min(temp,1.0f);
}

float Tank::clamp(float var, float limit){
    return std::min( std::max(var, -limit) , limit);
}

void Tank::setPressedButtons(bool * buttons){
    for (int i=0;i<9;i++){
        pressedButtons[i] = buttons[i];
    }
}

void Tank::setPlayerRef(Player *p){
    player = p;
}


float Tank::getTurretOrientation(){
    return turretOrientation;
}







