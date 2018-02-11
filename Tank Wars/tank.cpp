#include "tank.hpp"
#include <iostream>

#define PI 3.14159265

Tank::Tank(sf::Texture* texture ){
    
    linearAcc = 300.0f;
    angularAcc = 100.0f;
    
    turretVelocity = 2.0f;
    
    linearVelocity.x = 0.0f;
    linearVelocity.y = 0.0f;
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
    
    body.setRotation(270);
    turret.setRotation(270);
    
    
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        angularVelocity -= angularAcc * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        angularVelocity += angularAcc * deltaTime;
    }
    else{
        angularVelocity = reduce(angularVelocity);
    }
    
    angularVelocity = posOrNeg(angularVelocity) * std::min( fabs(angularVelocity) , maxAngularVelocity );
    float deltaTheta = angularVelocity * deltaTime;
    bodyOrientation += deltaTheta;
    
    sf::Vector2f unitVector;
    unitVector.x = cos(bodyOrientation * PI/180);
    unitVector.y = sin(bodyOrientation * PI/180);
    
    
    float absAcc = linearAcc * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        linearVelocity.y += unitVector.y * absAcc;
        linearVelocity.x += unitVector.x * absAcc;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        linearVelocity.y -= unitVector.y * absAcc;
        linearVelocity.x -= unitVector.x * absAcc;
    }
    else{
        linearVelocity.y = reduce(linearVelocity.y);
        linearVelocity.x = reduce(linearVelocity.x);
    }
    
    linearVelocity.x = posOrNeg(linearVelocity.x) * std::min( fabs(linearVelocity.x) , maxLinearVelocity );
    linearVelocity.y = posOrNeg(linearVelocity.y) * std::min( fabs(linearVelocity.y) , maxLinearVelocity );
    
    sf::Vector2f movement;
    movement.x = linearVelocity.x * deltaTime;
    movement.y = linearVelocity.y * deltaTime;
    
    float delTurretTheta = 0.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        turretOrientation -= turretVelocity;
        delTurretTheta = -turretVelocity;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        turretOrientation += turretVelocity;
        delTurretTheta = turretVelocity;
    }
    
    body.rotate(deltaTheta);
    body.move(movement);
    turret.move(movement);
    turret.rotate(delTurretTheta);
}


float Tank::reduce(float angularVelocity){
    if (abs(angularVelocity) > 10.0f)
        return posOrNeg(angularVelocity) * (abs(angularVelocity) - 10.0f);
    else
        return 0.0f;
}













