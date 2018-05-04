cmake_minimum_required(VERSION 3.10)
project(trab1_bolsa)

set(CMAKE_CXX_STANDARD 11)

add_executable(trab1_bolsa src/main.cpp src/WorkDay.cpp src/include/WorkDay.h src/WorkPaper.cpp src/include/WorkPaper.h src/Market.cpp src/include/Market.h src/include/Investor.h src/include/Company.h src/BasicInvestor.cpp src/include/BasicInvestor.h src/include/Utils.h src/Utils.cpp)