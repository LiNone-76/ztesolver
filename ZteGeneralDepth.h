//
// Created by Salieri on 2023/10/18.
//
#include "CbcGeneralDepth.hpp"
#include "CbcBranchBase.hpp"
#include "ZteModel.h"

#ifndef SOLVER_ENCAPSULATION_ZTEGENERALDEPTH_H
#define SOLVER_ENCAPSULATION_ZTEGENERALDEPTH_H


class ZteGeneralDepth: public CbcGeneralDepth{
public:
    // Default Constructor
    ZteGeneralDepth();

    /** Useful constructor
          Just needs to point to model.
          Initial version does evaluation to depth N
          This is stored in CbcModel but may be
          better here
      */
    ZteGeneralDepth(ZteModel *model, int maximumDepth);
};


#endif //SOLVER_ENCAPSULATION_ZTEGENERALDEPTH_H
