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
    dead = false;
    lastMissileTime = getMs() - 1000;
    health  = 1000;
    linearAcc = 300.0f;
    angularAcc = 200.0f;
    
    turretVelocity = 150.0f;
    
    velocityScalar = 200.0f;
    
    velocityVector.x = 0.0f;
    velocityVector.y = 0.0f;
    maxLinearVelocity = 300.0f;
    
    externalVelocityScalar= 0.0f;
    externalVelocityDirection = 0.0f;
    
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
    
    healthBar.setSize(sf::Vector2f(100.0f,20.0f));
    healthBarLevel.setSize(healthBar.getSize());
    
    healthBarLevel.setFillColor(sf::Color(100,250,75));
    healthBar.setOutlineColor(sf::Color(250,75,25));
    healthBar.setOutlineThickness(4.0f);
    
    healthBar.setOrigin(healthBar.getSize()/2.0f);
    healthBarLevel.setOrigin(healthBarLevel.getSize()/2.0f);
    
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
    window.draw(healthBar);
    window.draw(healthBarLevel);
}


sf::Vector2f Tank::getPosition(){
    return body.getPosition();
}

void Tank::update(float deltaTime){
    if (!isAlive()){
        if (getMs() - deathTime >= 1000){
            dead = false;
            health = 1000;
            healthBarLevel.setSize(healthBar.getSize());
            cBody->SetTransform(b2Vec2(512,512) , 0.0f);
        }
        return;
    }
    
    if (pressedButtons[W]){
        float angle = cBody->GetAngle();
        b2Vec2 unitVector;
        unitVector.x = -sin(angle*PI/180);
        unitVector.y = cos(angle*PI/180);
        float force = cBody->GetMass() * 500.0f;
        unitVector.x *= force;
        unitVector.y *= force;
        cBody->SetLinearDamping(0.3f);
        cBody->ApplyForceToCenter(unitVector, true);
    }
    else if (pressedButtons[S]){
        float angle = cBody->GetAngle();
        b2Vec2 unitVector;
        unitVector.x = -sin(angle*PI/180);
        unitVector.y = cos(angle*PI/180);
        float force = cBody->GetMass() * -500.0f;
        unitVector.x *= force;
        unitVector.y *= force;
        cBody->SetLinearDamping(0.3f);
        cBody->ApplyForceToCenter(unitVector, true);
    }
    else{
        cBody->SetLinearDamping(0.5f);
    }
    
    if (pressedButtons[A]){
        float torque = cBody->GetMass() * -10000.0f * body.getSize().x / 2;
        cBody->ApplyTorque(torque, true);
    }
    else if (pressedButtons[D]){
        float torque = cBody->GetMass() * 10000.0f * body.getSize().x / 2;
        cBody->ApplyTorque(torque, true);
    }
    
    float delTurretTheta = 0;
    if (pressedButtons[LEFT]){
        delTurretTheta -= turretVelocity * deltaTime;
    }
    else if (pressedButtons[RIGHT]){
        delTurretTheta += turretVelocity * deltaTime;
    }
    
    if(pressedButtons[SPACE]){
        if (getMs() - lastMissileTime> 200){
            missileManager->addMissile(player);
            lastMissileTime = getMs();
        }
    }
    turret.rotate(delTurretTheta);
    turretOrientation = turret.getRotation();
    
    sf::Vector2f pos(cBody->GetPosition().x, cBody->GetPosition().y);
    float angle = cBody->GetAngle();
    body.setPosition(pos);
    turret.setPosition(pos);
    body.setRotation(angle);
    
    sf::Vector2f size ( ((float)health/1000) * healthBar.getSize().x , healthBar.getSize().y );
    healthBarLevel.setSize(size);
    
    healthBar.setPosition(pos.x , pos.y+100.0f);
    healthBarLevel.setPosition(healthBar.getPosition());
    
    
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

sf::FloatRect Tank::getFloatRect(){
    return body.getGlobalBounds();
}

float Tank::getVelocityScalar(){
    return velocityScalar;
}

float Tank::getOrientation(){
    return bodyOrientation;
}

void Tank::setExternalVelocity(float scalar, float direction){
    externalVelocityScalar = scalar;
    externalVelocityDirection = direction;
}

void Tank::move(sf::Vector2f movement){
    body.move(movement);
    turret.move(movement);
}

void Tank::revertMovement(){
    move((lastMovement*-1.0f) ) ;
}

float Tank::getLastDTime(){
    return lastDTime;
}

sf::Vector2f Tank::getVelocityVector(){
    return velocityVector;
}

sf::Vector2f Tank::getSize(){
    return body.getSize();
}

void Tank::damage(){
    health -= 100;
    if (health == 0){
        die();
        return;
    }
}

void Tank::die(){
    deathTime = getMs();
    dead = true;
}

bool Tank::isAlive(){
    return !dead;
}
