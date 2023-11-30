//
// Created by Salieri on 2023/10/18.
//
#include "CoinMessageHandler.hpp"

#ifndef SOLVER_ENCAPSULATION_ZTEMESSAGEHANDLER_H
#define SOLVER_ENCAPSULATION_ZTEMESSAGEHANDLER_H


class ZteMessageHandler: public CoinMessageHandler{
public:
    /// Clone
    virtual ZteMessageHandler *clone();
};


#endif //SOLVER_ENCAPSULATION_ZTEMESSAGEHANDLER_H
