//
// Created by Salieri on 2023/10/17.
//
#include "CglDuplicateRow.hpp"

#ifndef SOLVER_ENCAPSULATION_ZTECGLDUPLICATEROW_H
#define SOLVER_ENCAPSULATION_ZTECGLDUPLICATEROW_H


class ZteCglDuplicateRow: public CglDuplicateRow {
public:
    /// Default constructor
    ZteCglDuplicateRow ();

    /// Useful constructor
    ZteCglDuplicateRow (OsiSolverInterface * solver);
};


#endif //SOLVER_ENCAPSULATION_ZTECGLDUPLICATEROW_H
