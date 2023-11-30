//
// Created by Salieri on 2023/10/18.
//
#include "CbcEventHandler.hpp"

#ifndef SOLVER_ENCAPSULATION_ZTEEVENTHANDLER_H
#define SOLVER_ENCAPSULATION_ZTEEVENTHANDLER_H


class ZteEventHandler: public CbcEventHandler{
public:
    /*! \brief Clone (virtual) constructor. */
    virtual ZteEventHandler *clone();
};


#endif //SOLVER_ENCAPSULATION_ZTEEVENTHANDLER_H
