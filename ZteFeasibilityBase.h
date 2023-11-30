//
// Created by Salieri on 2023/10/17.
//
#include "CbcFeasibilityBase.hpp"
#ifndef SOLVER_ENCAPSULATION_ZTEFEASIBILITYBASE_H
#define SOLVER_ENCAPSULATION_ZTEFEASIBILITYBASE_H


/**
 * @author: 高昊宇
 * @createDate: 2023/11/19
 * @updateUser: 高昊宇
 * @updateDate: 2023/11/19
 * @description: 判断可行性，已完成替换，但只有ZteModel的继承关系删除后，才能删除对CbcFeasibilityBase的继承并测试.
 */
class ZteModel;
class ZteFeasibilityBase: public CbcFeasibilityBase{
public:
    // Default Constructor
    ZteFeasibilityBase() {}
    // Copy constructor
    ZteFeasibilityBase(const ZteFeasibilityBase &) {}

    virtual ~ZteFeasibilityBase() {}

    // Assignment operator
    ZteFeasibilityBase &operator=(const ZteFeasibilityBase &)
    {
        return *this;
    }

    // Clone
    virtual ZteFeasibilityBase *clone() const
    {
        return new ZteFeasibilityBase(*this);
    }

    /**
     On input mode:
     0 - called after a solve but before any cuts
     -1 - called after strong branching
     Returns :
     0 - no opinion
     -1 pretend infeasible
     1 pretend integer solution
    */
    virtual int feasible(ZteModel *, int)
    {
        return 0;
    }
};


#endif //SOLVER_ENCAPSULATION_ZTEFEASIBILITYBASE_H
