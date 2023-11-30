cmake_minimum_required(VERSION 3.23)
project(solver-for-implementation)

set(CMAKE_CXX_STANDARD 14)






set(INC_DIR  ./cbc/include)

file(GLOB CBCSOURCE cbc/src/*.cpp ZteModel.cpp ZteModel.h ZteThread.cpp ZteThread.h ZteStrategy.cpp ZteStrategy.h ZteGeneralDepth.cpp ZteGeneralDepth.h tools.cpp tools.h ZteFeasibilityBase.cpp ZteFeasibilityBase.h ZteBaseModel.cpp ZteBaseModel.h ZteMessageHandler.cpp ZteMessageHandler.h ZteEventHandler.cpp ZteEventHandler.h ZteCglTreeProbingInfo.cpp ZteCglTreeProbingInfo.h ZteCglDuplicateRow.cpp ZteCglDuplicateRow.h)

include_directories(cbc/include)




add_executable(solver-for-implementation main.cpp ${CBCSOURCE} ZteSolver.cpp ZteSolver.h zteUnitTestClp.cpp ZteSolve.cpp)
