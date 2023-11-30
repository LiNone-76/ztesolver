//
// Created by Salieri on 2023/10/17.
//
#include "CbcStrategy.hpp"

#ifndef SOLVER_ENCAPSULATION_ZTESTRATEGY_H
#define SOLVER_ENCAPSULATION_ZTESTRATEGY_H


class ZteStrategy: public CbcStrategy {
public:
    /// Clone
    virtual ZteStrategy *clone() const = 0;
};


#endif //SOLVER_ENCAPSULATION_ZTESTRATEGY_H
