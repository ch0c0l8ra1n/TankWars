//
//  message.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/4/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#ifndef message_hpp
#define message_hpp

#include <stdio.h>
#include <string>

class Message{
public:
    Message(std::string str);
    ~Message();
private:
    std::string type;
    std::string* content;
};

#endif /* message_hpp */
