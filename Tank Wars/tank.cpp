#include "tank.hpp"
#include <iostream>

#define PI 3.14159265

Tank::Tank(sf::Texture* texture ){
    
    linearAcc = 300.0f;
    angularAcc = 100.0f;
    
    turretVelocity = 100.0f;
    
    velocityVector.x = 0.0f;
    velocityVector.y = 0.0f;
    maxLinearVelocity = 200.0f;
    
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
    
    //body.setRotation(270);
    //turret.setRotation(270);
    
    
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        velocityScalar += linearAcc * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        velocityScalar -= linearAcc * deltaTime;
    }
    else{
        float delRetardation = linearAcc * deltaTime;
        velocityScalar -= (delRetardation>fabs(velocityScalar)) ? velocityScalar : sign(velocityScalar)*delRetardation;
    }
    velocityScalar = clamp(velocityScalar , maxLinearVelocity);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        angularVelocity -= angularAcc * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        angularVelocity += angularAcc * deltaTime;
    }
    else{
        float delRetardation = angularAcc * deltaTime;
        angularVelocity -= (delRetardation>fabs(angularVelocity)) ? angularVelocity : sign(angularVelocity)*delRetardation;
    }
    
    float delTurretTheta = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        delTurretTheta -= turretVelocity * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        delTurretTheta += turretVelocity * deltaTime;
    }
    turretOrientation += delTurretTheta;
    turretOrientation = fmod(turretOrientation,360);
    turretOrientation = (turretOrientation<0) ? 360-turretOrientation : turretOrientation;
    
    angularVelocity = clamp(angularVelocity,maxAngularVelocity);

    
    float deltaTheta = angularVelocity * deltaTime;
    bodyOrientation += deltaTheta;
    bodyOrientation = fmod(bodyOrientation,360);
    bodyOrientation = (bodyOrientation<0) ? 360-bodyOrientation : bodyOrientation;
    std::cout<<bodyOrientation<<"\n";
    
    
    
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











