cmake_minimum_required(VERSION 3.24)
project(Chessboard_MinMax)

set(CMAKE_CXX_STANDARD 20)

add_executable(Chessboard_MinMax sources/main.cpp sources/FunctionsBoardEvaluation.cpp sources/FunctionsBoard.cpp sources/FunctionsBoardMinMax.cpp sources/FunctionsPGN.cpp sources/FunctionsPieces.cpp)
