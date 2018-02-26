#include "tank.hpp"
#include <iostream>

#include "missileManager.hpp"
#include "player.hpp"
#include <sys/time.h>
#include <string.h>

#define PI 3.14159265

long long getMs(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

Tank::Tank(sf::Texture* texture, MissileManager* mManager, sf::Texture* baseTexture ){
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
    
    body.setPosition( random()%2400 , random()%1300 );
    turret.setPosition( body.getPosition() );
    
    body.setSize(sf::Vector2f(10,15));
    turret.setSize(sf::Vector2f(10,15));
    
    base.setTexture(baseTexture);
    base.setSize( sf::Vector2f( 1.5f * std::max(body.getSize().x, body.getSize().y),
                                1.5f * std::max(body.getSize().x, body.getSize().y)) );
    base.setOrigin(base.getSize()/2.0f);
    base.setFillColor(sf::Color(255,255,255,200));

    
    name.setCharacterSize(50.0f);
    name.setFillColor(sf::Color(100,255,200,255));
    
    
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
    
    healthBar.setSize(sf::Vector2f(150.0f,10.0f));
    healthBarLevel.setSize(healthBar.getSize());
    
    healthBarLevel.setFillColor(sf::Color(100,250,75));
    healthBar.setOutlineColor(sf::Color(250,75,25));
    healthBar.setOutlineThickness(2.0f);
    healthBar.setFillColor(sf::Color(0,0,0,0));
    
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
    window.draw(base);
    window.draw(body);
    window.draw(turret);
    window.draw(healthBar);
    window.draw(healthBarLevel);
    window.draw(name);
}


sf::Vector2f Tank::getPosition(){
    return body.getPosition();
}

void Tank::update(float deltaTime){
    if (!isAlive()){
        if(getMs() - deathTime < 1000){
            return;
        }
        else{
            dead = false;
            health = 1000;
            healthBarLevel.setSize(healthBar.getSize());
            cBody->SetTransform(b2Vec2(random()%500, random()%500) , 0.0f);
            cBody->SetLinearVelocity(b2Vec2(random()%1000,random()%1000));
            cBody->SetAngularVelocity(1000.0f);
        }
    }
    
    if (pressedButtons[W]){
        float angle = cBody->GetAngle();
        b2Vec2 unitVector;
        unitVector.x = -sin(angle*PI/180);
        unitVector.y = cos(angle*PI/180);
        float force = cBody->GetMass() * 500.0f;
        unitVector.x *= force;
        unitVector.y *= force;
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
        cBody->ApplyForceToCenter(unitVector, true);
    }
    else{
        b2Vec2 currVelocity =  cBody->GetLinearVelocity();
        float currVelocityScalar = sqrt(pow(currVelocity.x,2) + pow(currVelocity.y,2));
        std::cout<<currVelocityScalar<<"\n";
        if(currVelocityScalar<1.0f){
            cBody->SetLinearVelocity(b2Vec2(0.0f,0.0f));
        }
        else{
            b2Vec2 unitVector = b2Vec2(currVelocity.x/currVelocityScalar, currVelocity.y/currVelocityScalar );
            float force = cBody->GetMass() * 500.0f;
            unitVector.x *= -force/4.0f;
            unitVector.y *= -force/4.0f;
            cBody->ApplyForceToCenter(unitVector , true);
        }
    }
    
    if (pressedButtons[A]){
        float torque = cBody->GetMass() * -10000.0f * body.getSize().x / 2;
        cBody->ApplyTorque(torque, true);
    }
    else if (pressedButtons[D]){
        float torque = cBody->GetMass() * 10000.0f * body.getSize().x / 2;
        cBody->ApplyTorque(torque, true);
    }
    else{
        float angV = cBody->GetAngularVelocity();
        if(abs(angV) < 1.0f){
            cBody->SetAngularVelocity(0.0f);
        }
        else{
            int direction = (angV>=0) ? 1 : -1;
            float torque = cBody->GetMass() * 10000.0f * body.getSize().x / 2 * -direction;
            cBody->ApplyTorque(torque, true);
        }
        
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
            float angle = turretOrientation;
            b2Vec2 unitVector;
            unitVector.x = -sin(angle*PI/180);
            unitVector.y = cos(angle*PI/180);
            float force = cBody->GetMass() * 500.0f;
            unitVector.x *= -force*3.0f;
            unitVector.y *= -force*3.0f;
            cBody->ApplyForceToCenter(unitVector, true);
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
    
    base.setPosition( body.getPosition());
    base.setRotation(body.getRotation()- 180);
    name.setPosition(healthBar.getPosition());
    
    
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
    health -= 50;
    if (health == 0){
        die();
        return;
    }
}

void Tank::die(){
    deathTime = getMs();
    explosionManager->addExplosion(player);
    dead = true;
}

bool Tank::isAlive(){
    return !dead;
}

Player* Tank::getPlayerRef(){
    return player;
}

void Tank::setFont(sf::Font* font){
    this->font = font;
    name.setFont(*font);
}

void Tank::setName(std::string name){
    this->name.setString(name);
    this->name.setOrigin(75.0f, 0.0f);
}

void Tank::setExplosionManager(ExplosionManager *explosionM){
    explosionManager = explosionM;
}
