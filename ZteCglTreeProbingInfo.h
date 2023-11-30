//
// Created by Salieri on 2023/10/17.
//
#include "CglTreeInfo.hpp"

#ifndef SOLVER_ENCAPSULATION_ZTECGLTREEPROBINGINFO_H
#define SOLVER_ENCAPSULATION_ZTECGLTREEPROBINGINFO_H

// Cgl: Cut Generation Library
class ZteCglTreeProbingInfo: public CglTreeProbingInfo {
public:
    /// Default constructor
    ZteCglTreeProbingInfo();
    /// Constructor from model
    ZteCglTreeProbingInfo(const OsiSolverInterface *model);
};


#endif //SOLVER_ENCAPSULATION_ZTECGLTREEPROBINGINFO_H
