//
//  message.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/4/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef message_hpp
#define message_hpp

#include <iostream>

enum Button {UP, DOWN, LEFT, RIGHT, W, A, S, D, SPACE};
enum MessageTypes {JOIN, LEAVE, BUTTON_PRESS, CONNECTION_ALIVE};

struct joinMessage{
    MessageTypes messageType;
    uint64_t hash;
    char name[20];
    short tankTextureId;
};

struct leaveMessage{
    MessageTypes messageType;
    long long hash;
};

struct buttonsPressed{
    MessageTypes messageType;
    uint64_t hash;
    Button buttons[9];
};

struct connectionAlive{
    MessageTypes messageType;
    uint64_t hash;
};

#endif /* message_hpp */
