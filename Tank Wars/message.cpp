//
//  message.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/4/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#include "message.hpp"

Message::Message(std::string str){
    if (str.substr(0,4) == "JOIN"){
        type = "JOIN";
        content = new std::string[1];
        content[0] = str.substr(4);
    }
    else if (str.substr(0,4) == "ACCL"){
        type = "ACCL";
    }
    else if (str.substr(0,5) == "SPAWN"){
        type = "SPAWN";
    }
    else if (str.substr(0,5) == "FIRE"){
        type = "FIRE";
    }
}
