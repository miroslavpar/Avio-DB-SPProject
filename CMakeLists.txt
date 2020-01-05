cmake_minimum_required(VERSION 3.14)
project(SDPProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDPProject main.cpp command/ICommand.h command/CreateCommand.h dbmanager/TXTPlaneManager.cpp dbmanager/TXTPlaneManager.h Plane.cpp Plane.h command/ShowCommand.h command/DeleteCommand.h command/SearchCommand.h command/UpdateCommand.h command/OptimizeCommand.h command/ExitCommand.h Invoker.cpp Invoker.h dbmanager/IPlaneManager.h)