//
// Created by Salieri on 2023/10/18.
//

#include "ZteMessageHandler.h"

// Clone
ZteMessageHandler *
ZteMessageHandler::clone()
{
    return new ZteMessageHandler(*this);
}