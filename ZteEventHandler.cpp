//
// Created by Salieri on 2023/10/18.
//

#include "ZteEventHandler.h"

// Clone
ZteEventHandler *
ZteEventHandler::clone()
{
    return (new ZteEventHandler(*this));
}