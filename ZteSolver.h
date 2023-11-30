//
// Created by Salieri on 2023/11/26.
//
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <deque>

#include "ZteModel.h"
#include "tools.h"

#include "CbcParameters.hpp"
#include "CbcCutGenerator.hpp"
#include "ClpFactorization.hpp"
#include "CbcHeuristic.hpp"

#ifndef SOLVER_ENCAPSULATION_NEW_ZTESOLVER_H
#define SOLVER_ENCAPSULATION_NEW_ZTESOLVER_H


// Empty callback to pass as default (why needed?)
static int dummyCallback(ZteModel * /*model*/, int /*whereFrom*/) { return 0; }

void ZteMain0(ZteModel &model, CbcParameters &parameters);

int ZteMain1(std::deque<std::string> inputQueue, ZteModel &model,
             CbcParameters &parameters, int callBack(ZteModel *currentSolver, int whereFrom) = dummyCallback);


//#############################################################################
//#############################################################################
#endif //SOLVER_ENCAPSULATION_NEW_ZTESOLVER_H