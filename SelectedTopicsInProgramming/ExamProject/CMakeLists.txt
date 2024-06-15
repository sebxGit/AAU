cmake_minimum_required(VERSION 3.27.8)
project(ExamProject)

#add_executable(ExamProject main.cpp
#        definitions.cpp
#        genericSymbolTable.cpp genericSymbolTable.h
#        networkGraph.cpp networkGraph.h
#        peakHospitalizationObserver.cpp peakHospitalizationObserver.h
#        reaction.cpp reaction.h
#        reactor.cpp reactor.h
#        runner.cpp runner.h
#        simulation.cpp simulation.h
#        ThreadPool.cpp ThreadPool.h
#        Vessel.cpp Vessel.h
#        )

add_executable(ExamProject main.cpp)
add_executable(ExamProjectTest unitTests.cpp)
add_executable(ExamProjectBenchmark main_bm.cpp)

#include "reaction.cpp"
#include "reactor.cpp"
#include "genericSymbolTable.cpp"
#include "Vessel.cpp"
#include "simulation.cpp"
#include "peakHospitalizationObserver.h"
#include "ThreadPool.h"
#include "definitions.cpp"